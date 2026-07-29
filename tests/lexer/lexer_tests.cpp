#include <doctest/doctest.h>

#include <dominus/lexer/lexer.hpp>
#include <dominus/lexer/token.hpp>
#include <dominus/source/source_manager.hpp>

TEST_CASE("an empty source produces an end-of-file token")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("empty.dom", "");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token token = lexer.NextToken();

    CHECK(token.Kind() == dominus::TokenKind::EndOfFile);
    CHECK(token.Span().Begin() == 0);
    CHECK(token.Span().End() == 0);
    CHECK(sources.Text(token.Span()).empty());
}

TEST_CASE("a single digit produces an integer-literal token and an eof")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1");
    dominus::Lexer lexer{sources, source_id};

    // Get the "1" token
    const dominus::Token token = lexer.NextToken();

    CHECK(token.Kind() == dominus::TokenKind::IntegerLiteral);
    CHECK(token.Span().Begin() == 0);
    CHECK(token.Span().End() == 1);
    CHECK(sources.Text(token.Span()) == "1");

    // Get the eof token
    const dominus::Token eof = lexer.NextToken();

    CHECK(eof.Kind() == dominus::TokenKind::EndOfFile);
    CHECK(eof.Span().Begin() == 1);
    CHECK(eof.Span().End() == 1);
}

TEST_CASE("an integer literal consumes all consecutive digits")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "123");
    dominus::Lexer lexer{sources, source_id};

    // Get the "123" token
    const dominus::Token token = lexer.NextToken();

    CHECK(token.Kind() == dominus::TokenKind::IntegerLiteral);
    CHECK(token.Span().Begin() == 0);
    CHECK(token.Span().End() == 3);
    CHECK(sources.Text(token.Span()) == "123");

    // Get the EOF token
    const dominus::Token eof = lexer.NextToken();

    CHECK(eof.Kind() == dominus::TokenKind::EndOfFile);
    CHECK(eof.Span().Begin() == 3);
    CHECK(eof.Span().End() == 3);
}

TEST_CASE("a plus sign produces a plus token and an EOF")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "+");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token plus = lexer.NextToken();

    CHECK(plus.Kind() == dominus::TokenKind::Plus);
    CHECK(plus.Span().Begin() == 0);
    CHECK(plus.Span().End() == 1);
    CHECK(sources.Text(plus.Span()) == "+");

    const dominus::Token eof = lexer.NextToken();

    CHECK(eof.Kind() == dominus::TokenKind::EndOfFile);
    CHECK(eof.Span().Begin() == 1);
    CHECK(eof.Span().End() == 1);
}
