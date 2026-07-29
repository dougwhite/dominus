#pragma once

#include <dominus/source/source_id.hpp>

#include <cstddef>

namespace dominus
{

class SourceSpan
{
    public:
        SourceSpan(SourceId source_id, std::size_t begin, std::size_t end);

        SourceId Source() const;
        std::size_t Begin() const;
        std::size_t End() const;

    private:
        SourceId _source_id;
        std::size_t _begin;
        std::size_t _end;
};

} // namespace dominus
