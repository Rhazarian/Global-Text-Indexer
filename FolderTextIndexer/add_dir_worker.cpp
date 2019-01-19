#include "add_dir_worker.h"

#include <filesystem>
#include <fstream>

#include <QMetaType>

#include "main_window.h"
#include "trigram_util.h"

namespace fs = std::filesystem;

Q_DECLARE_METATYPE(fs::path);

add_dir_worker::add_dir_worker(std::filesystem::path dir, QListWidgetItem* item, main_window* window) : dir(std::move(dir)), item(item), window(window)
{
	qRegisterMetaType<std::filesystem::path>("std::filesystem::path");
	qRegisterMetaType<QVector<std::filesystem::path>>("QVector<std::filesystem::path>");
	qRegisterMetaType<std::tuple<QVector<std::tuple<size_t, size_t, std::string> >, size_t>>("std::tuple<QVector<std::tuple<size_t,size_t,std::string> >,size_t>");
	qRegisterMetaType<QSet<uint32_t>>("QSet<uint32_t>");
}

add_dir_worker::~add_dir_worker() = default;

std::filesystem::path const& add_dir_worker::get_dir_path()
{
	return dir;
}

void add_dir_worker::process()
{
	QVector<fs::path> paths;
	std::lock_guard<std::mutex> lg(window->get_index_mutex());
	try {
		int progress = 0;
		for (auto const& file_path : fs::recursive_directory_iterator(dir)) {
			++progress;
		}
		emit set_progress_max(progress);
		progress = 0;
		for (auto const& file_path : fs::recursive_directory_iterator(dir)) {
			cancellation_point();
			std::ifstream fin(file_path.path());
			if (fin) {
				auto trigram_set = get_trigram_set(fin);
				if (trigram_set.has_value())
				{
					std::lock_guard<std::mutex> lg(window->get_pattern_mutex());
					emit add_indexed_file(dir, file_path, trigram_set.value());
					if (!window->get_pattern_trigram_set().empty() && trigram_set.value().contains(window->get_pattern_trigram_set()))
					{
						fin.clear();
						fin.seekg(0, std::ios::beg);
						if (auto data = pattern_lookup(fin, window->get_pattern_searcher()); !std::get<0>(data).empty())
						{
							emit add_matched_file(file_path, data);
						}
					}
					paths.push_back(file_path);
				}
			}
			++progress;
			emit set_progress(progress);
		}
		item->setFlags(item->flags() | Qt::ItemIsEnabled);
	} catch (...)
	{
		handle_catch();
		emit remove_dir_from_index(dir);
	}
	handle_finish();
}
