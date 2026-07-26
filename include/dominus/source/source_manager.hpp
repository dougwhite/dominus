#pragma once

#include <dominus/source/source_id.hpp>
#include <dominus/source/source_span.hpp>

#include <deque>
#include <string>
#include <string_view>

namespace dominus
{

class SourceManager
{
  public:
    SourceId AddSource(std::string name, std::string text);

    std::string_view Name(SourceId source_id) const;
    std::string_view Text(SourceId source_id) const;
    std::string_view Text(SourceSpan source_span) const;

  private:
    struct Source
    {
        std::string name;
        std::string text;
    };

    std::deque<Source> _sources;
};

} // namespace dominus
