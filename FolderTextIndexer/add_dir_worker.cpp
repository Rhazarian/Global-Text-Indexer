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
	qRegisterMetaType<fs::path>("std::filesystem::path");
	qRegisterMetaType<QVector<fs::path>>("QVector<std::filesystem::path>");
	qRegisterMetaType<QSet<uint32_t>>("QSet<uint32_t>");
	qRegisterMetaType<pattern_lookup_data<>>("pattern_lookup_data<>");
}

add_dir_worker::~add_dir_worker() = default;

void add_dir_worker::process()
{
	QVector<fs::path> paths;
	try {
		int progress = 0;
		for (auto const& file_path : fs::recursive_directory_iterator(dir)) {
			++progress;
		}
		emit set_progress_max(progress);
		progress = 0;
		for (auto const& file_path : fs::recursive_directory_iterator(dir)) {
			cancellation_point();
			std::ifstream fin(file_path);
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
						if (auto data = pattern_lookup(fin, window->get_pattern_searcher()); !data.empty())
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