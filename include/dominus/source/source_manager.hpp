#pragma once

#include <dominus/source/source_id.hpp>
#include <dominus/source/source_location.hpp>
#include <dominus/source/source_span.hpp>

#include <cstddef>
#include <deque>
#include <string>
#include <string_view>
#include <vector>

namespace dominus
{

class SourceManager
{
    public:
        SourceId AddSource(std::string name, std::string text);

        std::string_view Name(SourceId source_id) const;
        std::string_view Text(SourceId source_id) const;
        std::string_view Text(SourceSpan source_span) const;

        SourceLocation Locate(SourceId source_id, std::size_t byte_offset) const;

    private:
        struct Source
        {
            std::string name;
            std::string text;
            std::vector<std::size_t> line_starts;
        };

        std::deque<Source> _sources;
};

} // namespace dominus
