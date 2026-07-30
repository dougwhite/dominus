#include <dominus/syntax/integer_literal_expression.hpp>

#include <utility>

namespace dominus
{

IntegerLiteralExpression::IntegerLiteralExpression(dominus::Token token) : _token(std::move(token))
{
}

const Token &IntegerLiteralExpression::Token() const
{
    return _token;
}

SourceSpan IntegerLiteralExpression::Span() const
{
    return _token.Span();
}

} // namespace dominus
