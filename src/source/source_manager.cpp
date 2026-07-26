#include <dominus/source/source_manager.hpp>

#include <stdexcept>
#include <utility>

namespace dominus
{

SourceId SourceManager::AddSource(std::string name, std::string text)
{
    _sources.push_back(Source{
        .name = std::move(name),
        .text = std::move(text),
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

} // namespace dominus
