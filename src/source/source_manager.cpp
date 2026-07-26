#include <dominus/source/source_manager.hpp>

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

} // namespace dominus