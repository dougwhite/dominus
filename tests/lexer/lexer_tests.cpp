#include <doctest/doctest.h>

#include <dominus/lexer/lexer.hpp>
#include <dominus/lexer/token.hpp>
#include <dominus/source/source_manager.hpp>

#include <cstddef>
#include <string>
#include <string_view>

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
}

TEST_CASE("a plus sign produces a Plus token")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "+");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token plus = lexer.NextToken();

    CHECK(plus.Kind() == dominus::TokenKind::Plus);
    CHECK(plus.Span().Begin() == 0);
    CHECK(plus.Span().End() == 1);
    CHECK(sources.Text(plus.Span()) == "+");
}

TEST_CASE("a minus sign produces a Minus token")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "-");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token minus = lexer.NextToken();

    CHECK(minus.Kind() == dominus::TokenKind::Minus);
    CHECK(minus.Span().Begin() == 0);
    CHECK(minus.Span().End() == 1);
    CHECK(sources.Text(minus.Span()) == "-");
}

TEST_CASE("an asterisk produces a Star token")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "*");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token star = lexer.NextToken();

    CHECK(star.Kind() == dominus::TokenKind::Star);
    CHECK(star.Span().Begin() == 0);
    CHECK(star.Span().End() == 1);
    CHECK(sources.Text(star.Span()) == "*");
}

TEST_CASE("a slash produces a Slash token")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "/");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token slash = lexer.NextToken();

    CHECK(slash.Kind() == dominus::TokenKind::Slash);
    CHECK(slash.Span().Begin() == 0);
    CHECK(slash.Span().End() == 1);
    CHECK(sources.Text(slash.Span()) == "/");
}

TEST_CASE("a left parenthesis produces a LeftParenthesis token")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "(");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token paren = lexer.NextToken();

    CHECK(paren.Kind() == dominus::TokenKind::LeftParenthesis);
    CHECK(paren.Span().Begin() == 0);
    CHECK(paren.Span().End() == 1);
    CHECK(sources.Text(paren.Span()) == "(");
}

TEST_CASE("a right parenthesis produces a RightParenthesis token")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", ")");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token paren = lexer.NextToken();

    CHECK(paren.Kind() == dominus::TokenKind::RightParenthesis);
    CHECK(paren.Span().Begin() == 0);
    CHECK(paren.Span().End() == 1);
    CHECK(sources.Text(paren.Span()) == ")");
}

TEST_CASE("spaces between tokens are ignored")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1 + 2");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token one = lexer.NextToken();

    CHECK(one.Kind() == dominus::TokenKind::IntegerLiteral);
    CHECK(one.Span().Begin() == 0);
    CHECK(one.Span().End() == 1);
    CHECK(sources.Text(one.Span()) == "1");

    const dominus::Token plus = lexer.NextToken();

    CHECK(plus.Kind() == dominus::TokenKind::Plus);
    CHECK(plus.Span().Begin() == 2);
    CHECK(plus.Span().End() == 3);

    const dominus::Token two = lexer.NextToken();

    CHECK(two.Kind() == dominus::TokenKind::IntegerLiteral);
    CHECK(two.Span().Begin() == 4);
    CHECK(two.Span().End() == 5);
    CHECK(sources.Text(two.Span()) == "2");
}

TEST_CASE("a source containing only spaces produces an EOF at the source end")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "   ");
    dominus::Lexer lexer{sources, source_id};

    const dominus::Token eof = lexer.NextToken();

    CHECK(eof.Kind() == dominus::TokenKind::EndOfFile);
    CHECK(eof.Span().Begin() == 3);
    CHECK(eof.Span().End() == 3);
}

TEST_CASE("ASCII whitespace between tokens is ignored")
{
    struct WhitespaceCase
    {
        std::string_view name;
        std::string_view text;
    };

    const WhitespaceCase cases[] = {
        {"space", " "},
        {"horizontal tab", "\t"},
        {"line feed", "\n"},
        {"carriage return", "\r"},
        {"CRLF", "\r\n"},
        {"vertical tab", "\v"},
        {"form feed", "\f"}
    };

    for (const WhitespaceCase &whitespace : cases)
    {
        CAPTURE(whitespace.name);

        dominus::SourceManager sources;

        std::string source_text = "1";
        source_text += whitespace.text;
        source_text += "+2";

        const dominus::SourceId source_id = sources.AddSource("expression.dom", source_text);
        dominus::Lexer lexer{sources, source_id};

        const dominus::Token one = lexer.NextToken();
        const dominus::Token plus = lexer.NextToken();
        const dominus::Token two = lexer.NextToken();

        const std::size_t plus_begin = 1 + whitespace.text.size();
        const std::size_t two_begin = plus_begin + 1;
        const std::size_t source_end = two_begin + 1;

        CHECK(one.Kind() == dominus::TokenKind::IntegerLiteral);
        CHECK(one.Span().Begin() == 0);
        CHECK(one.Span().End() == 1);

        CHECK(plus.Kind() == dominus::TokenKind::Plus);
        CHECK(plus.Span().Begin() == plus_begin);
        CHECK(plus.Span().End() == plus_begin + 1);

        CHECK(two.Kind() == dominus::TokenKind::IntegerLiteral);
        CHECK(two.Span().Begin() == two_begin);
        CHECK(two.Span().End() == source_end);
    }
}

TEST_CASE("an arithmetic expression produces the expected token sequence")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id =
        sources.AddSource("expression.dom", "1 + 2 * 3");

    dominus::Lexer lexer{sources, source_id};

    const dominus::Token one = lexer.NextToken();
    const dominus::Token plus = lexer.NextToken();
    const dominus::Token two = lexer.NextToken();
    const dominus::Token star = lexer.NextToken();
    const dominus::Token three = lexer.NextToken();
    const dominus::Token eof = lexer.NextToken();

    CHECK(one.Kind() == dominus::TokenKind::IntegerLiteral);
    CHECK(plus.Kind() == dominus::TokenKind::Plus);
    CHECK(two.Kind() == dominus::TokenKind::IntegerLiteral);
    CHECK(star.Kind() == dominus::TokenKind::Star);
    CHECK(three.Kind() == dominus::TokenKind::IntegerLiteral);
    CHECK(eof.Kind() == dominus::TokenKind::EndOfFile);

    CHECK(sources.Text(one.Span()) == "1");
    CHECK(sources.Text(two.Span()) == "2");
    CHECK(sources.Text(three.Span()) == "3");
}
