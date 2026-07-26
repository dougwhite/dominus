#include <doctest/doctest.h>

#include <dominus/source/source_manager.hpp>
#include <dominus/source/source_span.hpp>

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
