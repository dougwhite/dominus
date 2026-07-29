#pragma once

#include <dominus/lexer/token.hpp>
#include <dominus/source/source_id.hpp>
#include <dominus/source/source_manager.hpp>

#include <cstddef>
#include <string_view>

namespace dominus
{

class Lexer
{
    public:
        Lexer(const SourceManager &sources, SourceId source_id);

        Token NextToken();

    private:
        SourceId _source_id;
        std::string_view _source_text;
        std::size_t _offset = 0;

        bool AtEnd() const;
        char Current() const;
        Token ConsumeSingle(TokenKind token_kind);
};

} // namespace dominus
