#pragma once

#include <dominus/lexer/token.hpp>
#include <dominus/source/source_id.hpp>
#include <dominus/source/source_manager.hpp>

namespace dominus
{

class Lexer
{
  public:
    Lexer(const SourceManager &sources, SourceId source_id);

    Token NextToken();

  private:
    const SourceManager &_sources;
    SourceId _source_id;
};

} // namespace dominus
