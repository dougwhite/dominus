#include <dominus/diagnostics/diagnostic_bag.hpp>

namespace dominus
{

void DiagnosticBag::Report(DiagnosticCode code, SourceSpan span)
{
    _diagnostics.push_back(Diagnostic{code, span});
}

bool DiagnosticBag::Empty() const
{
    return _diagnostics.empty();
}

std::size_t DiagnosticBag::Size() const
{
    return _diagnostics.size();
}

const Diagnostic &DiagnosticBag::At(std::size_t offset) const
{
    return _diagnostics.at(offset);
}

} // namespace dominus
