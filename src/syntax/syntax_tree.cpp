#include <dominus/syntax/syntax_tree.hpp>

#include <utility>

namespace dominus
{

SyntaxTree::SyntaxTree(Expression root) : _root(std::move(root))
{
}

const Expression &SyntaxTree::Root() const
{
    return _root;
}

}
