#pragma once

#include <dominus/source/source_span.hpp>

namespace dominus
{

enum class TokenKind
{
    EndOfFile,
    IntegerLiteral,
    Plus
};

class Token
{
  public:
    TokenKind Kind() const;
    SourceSpan Span() const;

  private:
    friend class Lexer;

    Token(TokenKind kind, SourceSpan span);

    TokenKind _kind;
    SourceSpan _span;
};

} // namespace dominus
