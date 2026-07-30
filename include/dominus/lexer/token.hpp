#pragma once

#include <dominus/source/source_span.hpp>

namespace dominus
{

enum class TokenKind
{
    Invalid,
    EndOfFile,
    IntegerLiteral,
    Plus,
    Minus,
    Star,
    Slash,
    LeftParenthesis,
    RightParenthesis
};

class Token
{
    public:
        Token(TokenKind kind, SourceSpan span);

        TokenKind Kind() const;
        SourceSpan Span() const;

    private:
        TokenKind _kind;
        SourceSpan _span;
};

} // namespace dominus
