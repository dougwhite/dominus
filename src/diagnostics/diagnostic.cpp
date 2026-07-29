#include <dominus/diagnostics/diagnostic.hpp>

namespace dominus
{

Diagnostic::Diagnostic(DiagnosticCode code, SourceSpan span)
    : _code(code), _span(span)
{
}

DiagnosticCode Diagnostic::Code() const {
    return _code;
}

SourceSpan Diagnostic::Span() const {
    return _span;
}

} // namespace dominus
