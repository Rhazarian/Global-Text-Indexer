#pragma once

#include <mutex>
#include <set>

#include "action_object.h"
#include "main_window.h"

struct pattern_lookup_worker : public action_object
{
	Q_OBJECT

public:
	pattern_lookup_worker(std::string_view pattern, QMap<std::filesystem::path, QSet<uint32_t>> indexed_files);
	pattern_lookup_worker(std::string_view pattern, QSet<uint32_t> trigram_set, QMap<std::filesystem::path, QSet<uint32_t>> indexed_files);
	~pattern_lookup_worker();

public slots:
	void process() override;

signals:
	void clear_matched_files();
	void add_matched_file(std::filesystem::path path, std::tuple<QVector<std::tuple<size_t, size_t, std::string>>, size_t> data);

private:
	std::string pattern;
	QSet<uint32_t> trigram_set;
	QMap<std::filesystem::path, QSet<uint32_t>> indexed_files;
};