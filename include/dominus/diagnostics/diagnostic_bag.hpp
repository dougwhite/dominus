#pragma once

#include <dominus/diagnostics/diagnostic.hpp>
#include <dominus/source/source_span.hpp>

#include <cstddef>
#include <vector>

namespace dominus
{

class DiagnosticBag
{
    public:
        void Report(
            DiagnosticCode code,
            SourceSpan span
        );

        bool Empty() const;
        std::size_t Size() const;
        const Diagnostic &At(std::size_t offset) const;

    private:
        std::vector<Diagnostic> _diagnostics;
};

} // namespace dominus
