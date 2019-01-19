#pragma once

#include <QtWidgets/QMainWindow>
#include <QMenu>
#include <QFileSystemWatcher>

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
#include <set>

struct add_dir_worker;
struct pattern_lookup_worker;

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget *parent = Q_NULLPTR);

private:
	Ui::FolderTextIndexerClass ui;
	QSet<uint32_t> pattern_trigram_set;
	std::string pattern;
	mutable std::mutex pattern_mtx;
	std::optional<std::boyer_moore_horspool_searcher<decltype(pattern)::iterator>> pattern_searcher;
	std::map<std::filesystem::path, QListWidgetItem*> wdirs_list_items;
	QMap<std::filesystem::path, QSet<uint32_t>> indexed_files;
	std::map<std::filesystem::path, std::tuple<QTreeWidgetItem*, std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t>>> matched_files;
	std::map<std::filesystem::path, std::vector<std::filesystem::path>> dir_files;
	std::map<std::filesystem::path, size_t> dir_count;

	std::map<std::filesystem::path, std::set<std::filesystem::path>> file_to_dirs_tmp;

	QFileSystemWatcher fs_watcher;

	QMenu indexed_dirs_context_menu;
	QAction* open_dir_action;
	QAction* remove_dir_from_index_action;

	QMenu matched_files_context_menu;
	QAction* open_file_action;
	QAction* show_details_action;

	add_directory_dialog add_dir_dlg;

	add_dir_worker* cur_dir_worker = nullptr;
	std::deque<std::string> queued_dir_workers;
	pattern_lookup_worker* cur_lookup_worker = nullptr;

	template<typename SetProgressMaxReceiverT, typename SetProgressMaxFuncPtrT, typename SetProgressReceiverT, typename SetProgressFuncPtrT, typename FinishReceiverT, typename FinishFuncPtrT, typename ExReceiverT, typename ExFuncPtrT>
	void launch_action_internal(action_object* obj,
		SetProgressMaxReceiverT progress_max_receiver, SetProgressMaxFuncPtrT set_progress_max_func_ptr,
		SetProgressReceiverT progress_receiver, SetProgressFuncPtrT set_progress_func_ptr,
		FinishReceiverT finish_receiver, FinishFuncPtrT finish_func_ptr,
		ExReceiverT ex_receiver, ExFuncPtrT ex_func_ptr
	);
	
	void launch_lookup_worker();

	void launch_dir_worker(std::string const& name);
	void queue_dir_worker(std::string const& name, bool front = false);

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
	void provide_matched_files_context_menu(QPoint const& point);

	void add_indexed_file(std::filesystem::path dir, std::filesystem::path path, QSet<uint32_t> trigram_set);
	void add_matched_file(std::filesystem::path path, std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t> data);
	void remove_dir_from_index(std::filesystem::path path);

	void file_changed(QString const& path);
	void dir_changed(QString const& path);

	void clear_matched_files();

	void show_details(QTreeWidgetItem* item);

signals:
	void search_pattern_changed_internal(QString const& pattern);
};