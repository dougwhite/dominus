#pragma once

#include <cstddef>

namespace dominus
{

class SourceId
{
  private:
    friend class SourceManager;

    explicit SourceId(std::size_t index) : _index(index) {}

    std::size_t _index;
};

} // namespace dominus
