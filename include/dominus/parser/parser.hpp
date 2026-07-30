#pragma once

#include <dominus/diagnostics/diagnostic_bag.hpp>
#include <dominus/lexer/token_source.hpp>
#include <dominus/syntax/syntax_tree.hpp>

namespace dominus
{

class Parser
{
    public:
        Parser(TokenSource &tokens, DiagnosticBag &diagnostics);

        SyntaxTree Parse();

    private:
        TokenSource &_tokens;
        DiagnosticBag &_diagnostics;
};

} // namespace dominus
