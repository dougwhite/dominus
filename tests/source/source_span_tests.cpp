#include <doctest/doctest.h>

#include <dominus/source/source_manager.hpp>
#include <dominus/source/source_span.hpp>

#include <stdexcept>

TEST_CASE("a source span rejects an end before its begin")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1 + 2 * 3");

    CHECK_THROWS_AS(dominus::SourceSpan(source_id, 9, 4), std::invalid_argument);
}
