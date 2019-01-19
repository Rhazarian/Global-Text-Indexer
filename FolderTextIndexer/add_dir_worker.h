#pragma once

#include <filesystem>

#include "action_object.h"

#include "main_window.h"

class add_dir_worker : public action_object
{
	Q_OBJECT

public:
	explicit add_dir_worker(std::filesystem::path dir, QListWidgetItem* item, main_window* window);
	~add_dir_worker();

	std::filesystem::path const& get_dir_path();

private:
	std::filesystem::path dir;
	QListWidgetItem* item;
	main_window* window;

public slots:
	void process() override;

signals:
	void remove_dir_from_index(std::filesystem::path path);
	void add_indexed_file(std::filesystem::path dir, std::filesystem::path path, QSet<uint32_t> trigram_set);
	void add_matched_file(std::filesystem::path path, std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t> data);
};