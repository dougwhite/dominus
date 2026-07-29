#pragma once

#include <dominus/source/source_id.hpp>

#include <cstddef>

namespace dominus
{

class SourceLocation
{
  public:
    SourceId Source() const;
    std::size_t ByteOffset() const;
    std::size_t Line() const;
    std::size_t ByteColumn() const;

  private:
    friend class SourceManager;

    SourceLocation(SourceId source_id, std::size_t byte_offset, std::size_t line, std::size_t byte_column);

    SourceId _source_id;
    std::size_t _byte_offset;
    std::size_t _line;
    std::size_t _byte_column;
};

} // namespace dominus
