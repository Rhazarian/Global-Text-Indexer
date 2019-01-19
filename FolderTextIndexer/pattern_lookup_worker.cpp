#include "pattern_lookup_worker.h"

#include <sstream>
#include <fstream>
#include <functional>

#include "trigram_util.h"

namespace fs = std::filesystem;

pattern_lookup_worker::pattern_lookup_worker(std::string_view pattern,
	QMap<std::filesystem::path, QSet<uint32_t>> indexed_files, main_window* window) : pattern(pattern), indexed_files(std::move(indexed_files)), window(window)
{
	qRegisterMetaType<std::filesystem::path>("std::filesystem::path");
	qRegisterMetaType<std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t>>("std::tuple<QVector<std::tuple<size_t,size_t,std::string> >,size_t>");
	std::istringstream iss(this->pattern);
	auto trigram_set = get_trigram_set(iss);
	if (!trigram_set.has_value())
	{
		throw std::invalid_argument("cannot construct trigram set");
	}
	this->trigram_set = std::move(trigram_set.value());
}

pattern_lookup_worker::pattern_lookup_worker(std::string_view pattern, QSet<uint32_t> trigram_set,
	QMap<std::filesystem::path, QSet<uint32_t>> indexed_files, main_window* window) : pattern(pattern), trigram_set(std::move(trigram_set)), indexed_files(std::move(indexed_files)), window(window)
{
	qRegisterMetaType<fs::path>("std::filesystem::path");
}

pattern_lookup_worker::~pattern_lookup_worker() = default;

void pattern_lookup_worker::process()
{
	std::lock_guard<std::mutex> lg(window->get_lookup_mutex());
	try {
		std::boyer_moore_horspool_searcher searcher(pattern.begin(), pattern.end());
		emit clear_matched_files();
		if (!trigram_set.empty()) {
			emit set_progress_max(indexed_files.size());
			int progress = 0;
			for (auto it = indexed_files.begin(); it != indexed_files.end(); ++it)
			{
				cancellation_point();
				emit set_progress(progress);
				if (auto const& test_set = it.value(); test_set.contains(trigram_set))
				{
					std::ifstream fin(it.key());
					if (auto data = pattern_lookup(fin, searcher); !std::get<0>(data).empty())
					{
						emit add_matched_file(it.key(), data);
					}
				}
				++progress;
			}
		}
	}
	catch (...)
	{
		handle_catch();
		emit clear_matched_files();
	}
	handle_finish();
}