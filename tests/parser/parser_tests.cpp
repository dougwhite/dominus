#include <doctest/doctest.h>

#include <dominus/diagnostics/diagnostic_bag.hpp>
#include <dominus/lexer/token.hpp>
#include <dominus/parser/parser.hpp>
#include <dominus/source/source_span.hpp>
#include <dominus/syntax/expression.hpp>
#include <dominus/syntax/integer_literal_expression.hpp>
#include <dominus/syntax/syntax_tree.hpp>

#include <support/test_token_source.hpp>

TEST_CASE("an integer literal parses as an integer literal expression")
{
    // Prepare diagnostics and token provider
    dominus::DiagnosticBag diagnostics;

    dominus::test::TestTokenSource tokens{
        "123",
        {
            { dominus::TokenKind::IntegerLiteral, 0, 3 }
        }
    };

    // Parse the token stream
    dominus::Parser parser{tokens, diagnostics};
    const dominus::SyntaxTree tree = parser.Parse();

    // Retrieve the root expression as an int literal
    const dominus::Expression &root = tree.Root();
    REQUIRE(root.Is<dominus::IntegerLiteralExpression>());

    const dominus::IntegerLiteralExpression &literal = root.As<dominus::IntegerLiteralExpression>();

    // Confirm the underlying token type
    CHECK(literal.Token().Kind() == dominus::TokenKind::IntegerLiteral);

    // Check the source span content is what we expect
    const dominus::SourceSpan expected_span{tokens.Source(), 0, 3};

    CHECK(literal.Span() == expected_span);
    CHECK(tokens.Sources().Text(literal.Span()) == "123");
    CHECK(literal.Token().Span() == expected_span);

    // Make sure no diagnostic errors were fired
    CHECK(diagnostics.Empty());
}
