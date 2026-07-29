#pragma once

#include <dominus/source/source_span.hpp>

namespace dominus
{

enum class DiagnosticCode
{
    UnexpectedCharacter
};

class Diagnostic
{
    public:
        DiagnosticCode Code() const;
        SourceSpan Span() const;

    private:
        friend class DiagnosticBag;

        Diagnostic(
            DiagnosticCode code,
            SourceSpan span
        );

        DiagnosticCode _code;
        SourceSpan _span;
};

} // namespace dominus
