#include <dominus/source/source_manager.hpp>

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <utility>

namespace dominus
{

SourceId SourceManager::AddSource(std::string name, std::string text)
{
    // Scan the source once to calculate line starts
    std::vector<std::size_t> line_starts{0};

    for (std::size_t offset = 0; offset < text.size(); ++offset)
    {
        if (text[offset] == '\n')
        {
            line_starts.push_back(offset + 1);
        }
    }

    // Store the source internally and return a SourceId
    _sources.push_back(Source{
        .name = std::move(name),
        .text = std::move(text),
        .line_starts = std::move(line_starts)
    });

    return SourceId(_sources.size() - 1);
}

std::string_view SourceManager::Name(SourceId source_id) const
{
    return _sources.at(source_id._index).name;
}

std::string_view SourceManager::Text(SourceId source_id) const
{
    return _sources.at(source_id._index).text;
}

std::string_view SourceManager::Text(SourceSpan source_span) const
{
    const std::string_view source_text = Text(source_span.Source());

    // Check span is within the source text bounds
    if (source_span.End() > source_text.size())
    {
        throw std::out_of_range("SourceSpan end exceeds source text size");
    }

    return source_text.substr(source_span.Begin(), source_span.End() - source_span.Begin());
}

SourceLocation SourceManager::Locate(SourceId source_id, std::size_t byte_offset) const
{
    // Grab a reference to the source
    const Source &source = _sources.at(source_id._index);

    // Guard against out of bounds errors
    if (byte_offset > source.text.size())
    {
        throw std::out_of_range("Source location exceeds source text size");
    }

    // Find the first line start greater than the requested offset
    const auto next_line = std::upper_bound(
        source.line_starts.begin(),
        source.line_starts.end(),
        byte_offset
    );

    // The line we are interested in is the line directly before that
    const auto line_start = std::prev(next_line);

    // Calculate the line number from its position in the line-start table
    const std::size_t line_index = static_cast<std::size_t>(
        std::distance(source.line_starts.begin(), line_start)
    );

    return SourceLocation(
        source_id,
        byte_offset,
        line_index + 1,               // Lines are 1-indexed
        byte_offset - *line_start + 1 // Calculate column (1-indexed) from start of line
    );
}

} // namespace dominus
