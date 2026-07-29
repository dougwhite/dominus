#include <dominus/source/source_location.hpp>

namespace dominus
{

SourceLocation::SourceLocation(SourceId source_id, std::size_t byte_offset, std::size_t line, std::size_t byte_column)
    : _source_id(source_id), _byte_offset(byte_offset), _line(line), _byte_column(byte_column)
{
}

SourceId SourceLocation::Source() const
{
    return _source_id;
}

std::size_t SourceLocation::ByteOffset() const
{
    return _byte_offset;
}

std::size_t SourceLocation::Line() const
{
    return _line;
}

std::size_t SourceLocation::ByteColumn() const
{
    return _byte_column;
}

} // namespace dominus
