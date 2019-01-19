#pragma once

#include <iosfwd>
#include <optional>
#include <vector>
#include <tuple>
#include <array>

#include <QSet>
#include <QVector>

using default_string_type = std::string;
using default_trigram_set_type = QSet<uint32_t>;
constexpr std::streamsize default_max_line_size = 2048;
constexpr default_trigram_set_type::size_type default_max_trigram_set_size = 32768;

template<typename SetT = default_trigram_set_type, std::streamsize MaxLineSize = default_max_line_size, typename SetT::size_type MaxTrigramSetSize = default_max_trigram_set_size>
std::optional<SetT> get_trigram_set(std::istream& in)
{
	std::array<char, MaxLineSize> buffer{};
	SetT trigram_set;
	do {
		in.getline(buffer.data(), buffer.size());
		const auto gcount = in.gcount() - !in.eof();
		if (gcount < 3)
		{
			continue;
		}
		if (gcount >= MaxLineSize)
		{
			return std::nullopt;
		}
		std::uint32_t trigram = (buffer[0] << 8u) | buffer[1];
		for (std::streamsize i = 2; i < gcount; ++i)
		{
			trigram &= 0b1111111111111111;
			trigram <<= 8u;
			trigram |= buffer[i];
			trigram_set.insert(trigram);
		}
		if (trigram_set.size() > MaxTrigramSetSize)
		{
			return std::nullopt;
		}
	} while (!in.eof() && !in.fail());
	return std::move(trigram_set);
}

template<typename SearcherT, typename StringT = default_string_type>
std::tuple<QVector<std::tuple<size_t, size_t, StringT>>, size_t> pattern_lookup(std::istream& in, SearcherT const& searcher)
{
	std::array<char, default_max_line_size> buffer{};
	QVector<std::tuple<size_t, size_t, StringT>> vector;
	in.getline(buffer.data(), buffer.size());
	size_t total_count = 0;
	for (size_t line = 0; !in.fail(); ++line, in.getline(buffer.data(), buffer.size()))
	{
		const auto gcount = in.gcount() - !in.eof();
		size_t count = 0;
		for (auto end = buffer.begin() + gcount, it = std::search(buffer.begin(), end, searcher); it != end; it = std::search(it + 1, end, searcher))
		{
			++count;
		}
		if (count != 0) {
			vector.push_back({ count, line, StringT{ buffer.begin(), buffer.begin() + gcount } });
			total_count += count;
		}
		if (in.eof())
		{
			break;
		}
	}
	return { vector, total_count };
}