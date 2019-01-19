#include "main_window.h"

#include <QThread>
#include <QObject>
#include <QUrl>
#include <QDesktopServices>

#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>

#include "trigram_util.h"

#include "add_dir_worker.h"
#include "pattern_lookup_worker.h"

#include "exception_occured_dialog.h"
#include "details_dialog.h"
#include <QFileInfo>

namespace fs = std::filesystem;

main_window::main_window(QWidget *parent) : QMainWindow(parent)
{
	ui.setupUi(this);

	ui.indexed_dirs_list_widget->setContextMenuPolicy(Qt::CustomContextMenu);
	open_dir_action = indexed_dirs_context_menu.addAction("Open");
	remove_dir_from_index_action = indexed_dirs_context_menu.addAction("Remove from index");
	connect(ui.indexed_dirs_list_widget, &QListWidget::customContextMenuRequested, this, &main_window::provide_indexed_dirs_context_menu);

	ui.dir_indexing_progress_group_box->setEnabled(false);
	ui.dir_indexing_progress_bar->reset();

	connect(ui.add_dir_button, &QPushButton::clicked, this, &main_window::add_dir_button_clicked);

	ui.matched_files_tree_widget->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
	ui.matched_files_tree_widget->setUniformRowHeights(true);

	ui.matched_files_tree_widget->setContextMenuPolicy(Qt::CustomContextMenu);
	open_file_action = matched_files_context_menu.addAction("Open");
	show_details_action = matched_files_context_menu.addAction("Show details");
	connect(ui.matched_files_tree_widget, &QTreeWidget::customContextMenuRequested, this, &main_window::provide_matched_files_context_menu);
	connect(ui.matched_files_tree_widget, &QTreeWidget::itemDoubleClicked, this, &main_window::show_details);

	ui.lookup_progress_group_box->setEnabled(false);
	ui.lookup_progress_bar->reset();

	connect(ui.lookup_pattern_line_edit, &QLineEdit::textChanged, this, &main_window::search_pattern_changed);
	connect(this, &main_window::search_pattern_changed_internal, this, &main_window::search_pattern_changed_synced);

	connect(&fs_watcher, &QFileSystemWatcher::fileChanged, this, &main_window::file_changed);
	connect(&fs_watcher, &QFileSystemWatcher::directoryChanged, this, &main_window::dir_changed);
}

std::mutex& main_window::get_pattern_mutex() const
{
	return pattern_mtx;
}

std::string const& main_window::get_pattern() const
{
	return pattern;
}

QSet<uint32_t> const& main_window::get_pattern_trigram_set() const
{
	return pattern_trigram_set;
}

std::boyer_moore_horspool_searcher<decltype(main_window::pattern)::iterator> const& main_window::get_pattern_searcher() const
{
	return pattern_searcher.value();
}

void main_window::add_indexed_file(std::filesystem::path dir, std::filesystem::path path, QSet<uint32_t> trigram_set)
{
	file_to_dirs_tmp[path].emplace(dir);

	indexed_files.insert(path, trigram_set);
	fs_watcher.addPath(path.string().c_str());
	++dir_count[path];
	dir_files[dir].emplace_back(std::move(path));
}

void main_window::add_matched_file(std::filesystem::path path, std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t> data)
{
	if (matched_files.find(path) != matched_files.end())
	{
		return;
	}
	auto item = new QTreeWidgetItem();
	item->setText(0, QString::number(std::get<1>(data)));
	item->setText(1, path.lexically_normal().string().c_str());
	ui.matched_files_tree_widget->addTopLevelItem(item);
	matched_files.emplace(std::piecewise_construct, std::forward_as_tuple(std::move(path)), std::forward_as_tuple(item, std::move(data)));
}

void main_window::remove_dir_from_index(std::filesystem::path path)
{
	auto it = wdirs_list_items.find(path);
	if (it == wdirs_list_items.end())
	{
		return;
	}
	if (std::find(queued_dir_workers.begin(), queued_dir_workers.end(), path) == queued_dir_workers.end())
	{
		delete it->second;
		wdirs_list_items.erase(it);
	}
	if (auto const file_it = dir_files.find(path); file_it != dir_files.end())
	{
		for (auto const& file : file_it->second)
		{
			if (--dir_count[file] == 0)
			{
				indexed_files.erase(indexed_files.find(file));
				if (auto const matched_it = matched_files.find(file); matched_it != matched_files.end())
				{
					delete std::get<QTreeWidgetItem*>(matched_it->second);
					matched_files.erase(matched_it);
				}
				dir_count.erase(dir_count.find(file));
				fs_watcher.removePath(file.string().c_str());
			}

			file_to_dirs_tmp[file].erase(file_to_dirs_tmp[file].find(path));
		}
		dir_files.erase(file_it);
	}
	fs_watcher.removePath(path.string().c_str());
}

void main_window::file_changed(QString const& path)
{
	dir_changed(file_to_dirs_tmp[path.toStdString()].begin()->string().c_str());
}

void main_window::dir_changed(QString const& path)
{
	const auto& str = path.toStdString();
	QFileInfo dir(path);
	if (cur_dir_worker && cur_dir_worker->get_dir_path() == str)
	{
		cancel_dir_indexing();
		if (dir.exists() && dir.isDir()) {
			queue_dir_worker(path.toStdString(), true);
		}
	}
	else {
		if (const auto it = std::find(queued_dir_workers.begin(), queued_dir_workers.end(), str); it == queued_dir_workers.end()) {
			remove_dir_from_index(str);
			if (dir.exists() && dir.isDir()) {
				queue_dir_worker(path.toStdString());
			}
		}
		else if (!(dir.exists() && dir.isDir())) {
			queued_dir_workers.erase(it);
			remove_dir_from_index(str);
		}
	}
}

void main_window::clear_matched_files()
{
	for (auto it = matched_files.begin(); it != matched_files.end(); ++it)
	{
		delete std::get<QTreeWidgetItem*>(it->second);
	}
	matched_files.clear();
}

void main_window::show_details(QTreeWidgetItem* item)
{
	const auto str = item->text(1).toStdString();
	new details_dialog(str, std::get<1>(matched_files.find(str)->second));
}

template<typename SetProgressMaxReceiverT, typename SetProgressMaxFuncPtrT, typename SetProgressReceiverT, typename SetProgressFuncPtrT, typename FinishReceiverT, typename FinishFuncPtrT, typename ExReceiverT, typename ExFuncPtrT>
void main_window::launch_action_internal(action_object* obj,
	SetProgressMaxReceiverT progress_max_receiver, SetProgressMaxFuncPtrT set_progress_max_func_ptr,
	SetProgressReceiverT progress_receiver, SetProgressFuncPtrT set_progress_func_ptr,
	FinishReceiverT finish_receiver, FinishFuncPtrT finish_func_ptr,
	ExReceiverT ex_receiver, ExFuncPtrT ex_func_ptr
)
{
	auto working_thread = new QThread();
	obj->moveToThread(working_thread);
	connect(working_thread, &QThread::started, obj, &action_object::process);
	if constexpr (!std::is_same<SetProgressReceiverT, std::nullptr_t>::value || !std::is_same<SetProgressFuncPtrT, std::nullptr_t>::value) {
		connect(obj, &action_object::set_progress, progress_receiver, set_progress_func_ptr);
	}
	if constexpr (!std::is_same<SetProgressMaxReceiverT, std::nullptr_t>::value || !std::is_same<SetProgressMaxFuncPtrT, std::nullptr_t>::value) {
		connect(obj, &action_object::set_progress_max, progress_max_receiver, set_progress_max_func_ptr);
	}
	if constexpr (!std::is_same<FinishReceiverT, std::nullptr_t>::value || !std::is_same<FinishFuncPtrT, std::nullptr_t>::value) {
		connect(obj, &action_object::finished, finish_receiver, finish_func_ptr);
	}
	connect(obj, &action_object::finished, working_thread, &QThread::quit);
	connect(obj, &action_object::finished, obj, &action_object::deleteLater);
	if constexpr (!std::is_same<ExReceiverT, std::nullptr_t>::value || !std::is_same<ExFuncPtrT, std::nullptr_t>::value) {
		connect(obj, &action_object::exception_is_thrown, ex_receiver, ex_func_ptr);
	}
	connect(obj, &action_object::exception_is_thrown, working_thread, &QThread::quit);
	connect(obj, &action_object::exception_is_thrown, obj, &action_object::deleteLater);
	connect(working_thread, &QThread::finished, working_thread, &QThread::deleteLater);
	working_thread->start();
}

void main_window::launch_dir_worker(std::string const& name)
{
	cur_dir_worker = new add_dir_worker(name, wdirs_list_items[name], this);
	ui.dir_indexing_progress_group_box->setEnabled(true);
	ui.dir_indexing_progress_group_box->setTitle(std::string("Indexing directory \"").append(name).append("\"...").c_str());
	fs_watcher.addPath(name.c_str());
	connect(cur_dir_worker, &add_dir_worker::add_indexed_file, this, &main_window::add_indexed_file);
	connect(cur_dir_worker, &add_dir_worker::add_matched_file, this, &main_window::add_matched_file);
	connect(cur_dir_worker, &add_dir_worker::remove_dir_from_index, this, &main_window::remove_dir_from_index);
	launch_action_internal(cur_dir_worker, ui.dir_indexing_progress_bar, &QProgressBar::setMaximum, ui.dir_indexing_progress_bar, &QProgressBar::setValue, this, &main_window::dir_worker_finished, this, &main_window::dir_worker_threw_exception);
}

void main_window::launch_lookup_worker()
{
	ui.lookup_progress_group_box->setEnabled(true);
	ui.lookup_progress_group_box->setTitle(std::string("Looking up \"").append(pattern).append("\"...").c_str());
	cur_lookup_worker = new pattern_lookup_worker(pattern, pattern_trigram_set, indexed_files);
	connect(cur_lookup_worker, &pattern_lookup_worker::clear_matched_files, this, &main_window::clear_matched_files);
	connect(cur_lookup_worker, &pattern_lookup_worker::add_matched_file, this, &main_window::add_matched_file);
	launch_action_internal(cur_lookup_worker, ui.lookup_progress_bar, &QProgressBar::setMaximum, ui.lookup_progress_bar, &QProgressBar::setValue, this, &main_window::lookup_worker_finished, this, &main_window::lookup_worker_threw_exception);
}

void main_window::queue_dir_worker(std::string const& name, bool front)
{
	if (wdirs_list_items.find(name) == wdirs_list_items.end()) {
		auto item = new QListWidgetItem();
		item->setText(name.c_str());
		item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
		ui.indexed_dirs_list_widget->addItem(item);
		wdirs_list_items.insert({ name, item });
	}
	if (cur_dir_worker == nullptr)
	{
		launch_dir_worker(name);
		return;
	}
	if (!front) {
		queued_dir_workers.emplace_back(name);
	} else
	{
		queued_dir_workers.emplace_front(name);
	}
	ui.queued_dirs_counter_lcd_number->display(ui.queued_dirs_counter_lcd_number->intValue() + 1);
}

void main_window::cancel_dir_indexing()
{
	cur_dir_worker->request_cancellation();
}

void main_window::add_dir_button_clicked()
{
	if (auto res = add_dir_dlg.get_dir(); res.has_value())
	{
		fs::path path(res.value());
		if (wdirs_list_items.find(path) != wdirs_list_items.end())
		{
			return;
		}
		queue_dir_worker(path.lexically_normal().string());
	}
}

void main_window::search_pattern_changed_synced(QString const& pattern)
{
	this->pattern = pattern.toStdString();
	pattern_searcher.emplace(this->pattern.begin(), this->pattern.end());
	std::istringstream iss(this->pattern);
	pattern_trigram_set = get_trigram_set(iss).value();
	if (cur_lookup_worker == nullptr)
	{
		launch_lookup_worker();
	}
	else
	{
		cur_lookup_worker->request_cancellation();
	}
}

void main_window::search_pattern_changed(QString const& pattern)
{
	std::lock_guard<std::mutex> lg(pattern_mtx);
	emit search_pattern_changed_internal(pattern);
}

void main_window::lookup_worker_finished(bool cancelled)
{
	ui.lookup_progress_group_box->setEnabled(false);
	ui.lookup_progress_bar->setMaximum(1);
	ui.lookup_progress_bar->reset();
	ui.lookup_progress_group_box->setTitle("Idle...");
	if (cancelled)
	{
		launch_lookup_worker();
	} else
	{
		cur_lookup_worker = nullptr;
	}
}

void main_window::provide_indexed_dirs_context_menu(QPoint const& point)
{
	const auto index = ui.indexed_dirs_list_widget->indexAt(point);
	if (!index.isValid())
	{
		return;
	}
	const auto item_point = ui.indexed_dirs_list_widget->mapToGlobal(point);
	const auto item = ui.indexed_dirs_list_widget->item(index.row());
	const auto action = indexed_dirs_context_menu.exec(item_point);
	if (action == open_dir_action)
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(item->text()));
	} else if (action == remove_dir_from_index_action)
	{
		const auto dir = item->text().toStdString();
		if (const auto queue_it = std::find(queued_dir_workers.begin(), queued_dir_workers.end(), dir); queue_it != queued_dir_workers.end())
		{
			queued_dir_workers.erase(queue_it);
		}
		if (const auto li_it = wdirs_list_items.find(dir); (li_it->second->flags() & Qt::ItemIsEnabled) != 0)
		{
			remove_dir_from_index(dir);
		}
		if (cur_dir_worker != nullptr && cur_dir_worker->get_dir_path() == dir)
		{
			cancel_dir_indexing();
		}
	}
}

void main_window::provide_matched_files_context_menu(QPoint const& point)
{
	const auto index = ui.matched_files_tree_widget->indexAt(point);
	if (!index.isValid())
	{
		return;
	}
	const auto item_point = ui.matched_files_tree_widget->mapToGlobal(point);
	const auto item = ui.matched_files_tree_widget->topLevelItem(index.row());
	const auto action = matched_files_context_menu.exec(item_point);
	if (action == open_file_action)
	{
		QDesktopServices::openUrl(QUrl::fromLocalFile(item->text(1)));
	}
	else if (action == show_details_action)
	{
		show_details(item);
	}
}

void main_window::dir_worker_finished()
{
	cur_dir_worker = nullptr;
	if (queued_dir_workers.empty())
	{
		ui.dir_indexing_progress_group_box->setTitle("Idle...");
		ui.dir_indexing_progress_group_box->setEnabled(false);
		ui.dir_indexing_progress_bar->reset();
		return;
	}
	const auto& next_dir = queued_dir_workers.front();
	launch_dir_worker(next_dir);
	queued_dir_workers.pop_front();
	ui.queued_dirs_counter_lcd_number->display(ui.queued_dirs_counter_lcd_number->intValue() - 1);
}

void main_window::dir_worker_threw_exception(std::exception_ptr ex_ptr)
{
	dir_worker_finished();
	try
	{
		std::rethrow_exception(ex_ptr);
	}
	catch (std::exception const& ex)
	{
		new exception_occured_dialog("Something went wrong while indexing a directory :(", ex.what());
	}
	catch (...)
	{
		new exception_occured_dialog("Something went wrong while indexing a directory :(", "unknown error");
	}
	
}

void main_window::lookup_worker_threw_exception(std::exception_ptr ex_ptr)
{
	ui.lookup_pattern_line_edit->setText("");
	try
	{
		std::rethrow_exception(ex_ptr);
	}
	catch (std::exception const& ex)
	{
		new exception_occured_dialog("Something went wrong while looking up the pattern :(", ex.what());
	}
	catch (...)
	{
		new exception_occured_dialog("Something went wrong while looking up the pattern :(", "unknown error");
	}

}
