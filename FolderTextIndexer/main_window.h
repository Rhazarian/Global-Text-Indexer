#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileSystemWatcher>
#include <QMenu>

#include "ui_main_window.h"

#include <filesystem>
#include <map>
#include <queue>
#include <string>
#include <utility>
#include <mutex>

#include "action_object.h"

#include "add_directory_dialog.h"
#include "trigram_util.h"

struct add_dir_worker;
struct pattern_lookup_worker;

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = Q_NULLPTR);

private:
	Ui::FolderTextIndexerClass ui;
	QFileSystemWatcher fs_watcher;
	QSet<uint32_t> pattern_trigram_set;
	std::string pattern;
	mutable std::mutex pattern_mtx;
	std::optional<std::boyer_moore_horspool_searcher<decltype(pattern)::iterator>> pattern_searcher;
	std::map<std::filesystem::path, QListWidgetItem*> wdirs_list_items;
	QMap<std::filesystem::path, QSet<uint32_t>> indexed_files;
	std::map<std::filesystem::path, std::tuple<QListWidgetItem*, pattern_lookup_data<>>> matched_files;
	std::map<std::filesystem::path, std::vector<std::filesystem::path>> dir_files;
	std::map<std::filesystem::path, size_t> dir_count;
	QMenu indexed_dirs_context_menu;
	QAction* open_dir_action;
	QAction* remove_dir_from_index_action;

	add_directory_dialog add_dir_dlg;

	add_dir_worker* cur_add_dir_worker = nullptr;
	std::deque<std::pair<add_dir_worker*, std::string>> queued_add_dir_workers;
	pattern_lookup_worker* cur_lookup_worker = nullptr;

	template<typename SetProgressMaxReceiverT, typename SetProgressMaxFuncPtrT, typename SetProgressReceiverT, typename SetProgressFuncPtrT, typename FinishReceiverT, typename FinishFuncPtrT, typename ExReceiverT, typename ExFuncPtrT>
	void launch_action_internal(action_object* obj,
		SetProgressMaxReceiverT progress_max_receiver, SetProgressMaxFuncPtrT set_progress_max_func_ptr,
		SetProgressReceiverT progress_receiver, SetProgressFuncPtrT set_progress_func_ptr,
		FinishReceiverT finish_receiver, FinishFuncPtrT finish_func_ptr,
		ExReceiverT ex_receiver, ExFuncPtrT ex_func_ptr
	);
	void launch_add_dir_worker(add_dir_worker* obj, std::string_view name);
	void launch_lookup_worker();
	void queue_add_dir_worker(add_dir_worker* obj, std::string_view name);

public:
	std::mutex& get_pattern_mutex() const;
	std::string const& get_pattern() const;
	QSet<uint32_t> const& get_pattern_trigram_set() const;
	std::boyer_moore_horspool_searcher<decltype(pattern)::iterator> const& get_pattern_searcher() const;

private slots:
	void cancel_dir_indexing();

	void add_dir_button_clicked();

	void dir_worker_finished();
	void dir_worker_threw_exception(std::exception_ptr ex_ptr);

	void search_pattern_changed(QString const& pattern);
	void search_pattern_changed_synced(QString const& pattern);

	void lookup_worker_finished(bool cancelled);
	void lookup_worker_threw_exception(std::exception_ptr ex_ptr);

	void provide_indexed_dirs_context_menu(QPoint const& point);

public slots:
	void add_indexed_file(std::filesystem::path dir, std::filesystem::path path, QSet<uint32_t> trigram_set);
	void add_matched_file(std::filesystem::path path, pattern_lookup_data<> data);
	void remove_dir_from_index(std::filesystem::path path);
	void clear_matched_files();
	void set_dir_worker_progress_max(int progress_max);
	void set_dir_worker_progress(int progress);

signals:
	void search_pattern_changed_internal(QString const& pattern);
};