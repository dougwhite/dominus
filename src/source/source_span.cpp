#include <dominus/source/source_span.hpp>

#include <stdexcept>

namespace dominus
{

SourceSpan::SourceSpan(SourceId source_id, std::size_t begin, std::size_t end)
    : _source_id(source_id), _begin(begin), _end(end)
{
    if (end < begin)
    {
        throw std::invalid_argument("SourceSpan end must not be before begin");
    }
}

SourceId SourceSpan::Source() const
{
    return _source_id;
}

std::size_t SourceSpan::Begin() const
{
    return _begin;
}

std::size_t SourceSpan::End() const
{
    return _end;
}

} // namespace dominus
