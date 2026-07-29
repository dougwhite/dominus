#include <doctest/doctest.h>

#include <dominus/source/source_location.hpp>
#include <dominus/source/source_manager.hpp>
#include <dominus/source/source_span.hpp>

#include <stdexcept>

TEST_CASE("a source manager owns an added source")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1 + 2 * 3");

    CHECK(sources.Name(source_id) == "expression.dom");
    CHECK(sources.Text(source_id) == "1 + 2 * 3");
}

TEST_CASE("a source manager retrieves the exact text selected by a source span")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1 + 2 * 3");

    const dominus::SourceSpan span{source_id, 4, 9};

    CHECK(sources.Text(span) == "2 * 3");
}

TEST_CASE("a source manager retrieves empty text for an empty span")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1 + 2 * 3");

    const dominus::SourceSpan span{source_id, 9, 9};

    CHECK(sources.Text(span).empty());
}

TEST_CASE("a source manager rejects a span whose end exceeds the source size")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1 + 2 * 3");

    const dominus::SourceSpan span{source_id, 4, 1000};

    CHECK_THROWS_AS(sources.Text(span), std::out_of_range);
}

TEST_CASE("source spans use UTF-8 byte offsets")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "aéz");

    const dominus::SourceSpan span{source_id, 1, 3};

    CHECK(sources.Text(span) == "é");
}

TEST_CASE("a source manager locates a byte offset by line and byte column")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("example.dom", "one\ntwo\nthree");

    const dominus::SourceLocation location = sources.Locate(source_id, 6);

    CHECK(sources.Name(location.Source()) == "example.dom");
    CHECK(location.ByteOffset() == 6);
    CHECK(location.Line() == 2);
    CHECK(location.ByteColumn() == 3);
}

TEST_CASE("a source manager rejects location requests exceeding the source size")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("example.dom", "one\ntwo\nthree");

    CHECK_THROWS_AS(sources.Locate(source_id, 1000), std::out_of_range);
}
