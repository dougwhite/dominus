#include <dominus/lexer/token.hpp>

namespace dominus
{

Token::Token(TokenKind kind, SourceSpan span) : _kind(kind), _span(span)
{
}

TokenKind Token::Kind() const
{
    return _kind;
}

SourceSpan Token::Span() const
{
    return _span;
}

} // namespace dominus
