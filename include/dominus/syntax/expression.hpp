#pragma once

#include <dominus/syntax/integer_literal_expression.hpp>

#include <variant>

namespace dominus
{

class Expression
{
    public:
        explicit Expression(IntegerLiteralExpression expression);

        template<typename T>
        bool Is() const
        {
            return std::holds_alternative<T>(_node);
        }

        template<typename T>
        const T &As() const
        {
            return std::get<T>(_node);
        }

    private:
        std::variant<IntegerLiteralExpression> _node;
};

} // namespace dominus
