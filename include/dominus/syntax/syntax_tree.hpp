#pragma once

#include <dominus/syntax/expression.hpp>

namespace dominus
{

class SyntaxTree
{
    public:
        explicit SyntaxTree(Expression root);

        const Expression &Root() const;

    private:
        Expression _root;
};

} // namespace dominus
