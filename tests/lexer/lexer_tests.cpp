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
