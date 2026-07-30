#include <dominus/parser/parser.hpp>

namespace dominus
{

Parser::Parser(TokenSource &tokens, DiagnosticBag &diagnostics) : _tokens(tokens), _diagnostics(diagnostics)
{
}

SyntaxTree Parser::Parse()
{
    return SyntaxTree{
        Expression{
            IntegerLiteralExpression{
                _tokens.NextToken()
            }
        }
    };
}

} // namespace dominus
