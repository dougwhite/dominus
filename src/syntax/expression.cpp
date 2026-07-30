#include <dominus/syntax/expression.hpp>

#include <utility>

namespace dominus
{

Expression::Expression(IntegerLiteralExpression expression) : _node(std::move(expression))
{
}

} // namespace dominus
