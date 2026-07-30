#pragma once

#include <dominus/lexer/token.hpp>
#include <dominus/source/source_span.hpp>

namespace dominus
{

class IntegerLiteralExpression
{
    public:
        explicit IntegerLiteralExpression(dominus::Token token);

        const dominus::Token &Token() const;
        SourceSpan Span() const;

    private:
        dominus::Token _token;
};

} // namespace dominus
