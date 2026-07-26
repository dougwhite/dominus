#include <doctest/doctest.h>

#include <dominus/source/source_manager.hpp>

TEST_CASE("a source manager owns an added source")
{
    dominus::SourceManager sources;

    const dominus::SourceId source_id = sources.AddSource("expression.dom", "1 + 2 * 3");

    CHECK(sources.Name(source_id) == "expression.dom");
    CHECK(sources.Text(source_id) == "1 + 2 * 3");
}
