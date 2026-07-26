#pragma once

#include <cstddef>
#include <deque>
#include <string>
#include <string_view>

namespace dominus
{

class SourceId
{
  private:
    friend class SourceManager;

    explicit SourceId(std::size_t index) : _index(index) {}

    std::size_t _index;
};

class SourceManager
{
  public:
    SourceId AddSource(std::string name, std::string text);

    std::string_view Name(SourceId source_id) const;
    std::string_view Text(SourceId source_id) const;

  private:
    struct Source
    {
        std::string name;
        std::string text;
    };

    std::deque<Source> _sources;
};

} // namespace dominus
