#pragma once

#include <cstddef>

namespace dominus
{

class SourceId
{
    public:
        bool operator==(const SourceId &other) const = default;

    private:
        friend class SourceManager;

        explicit SourceId(std::size_t index) : _index(index) {}

        std::size_t _index;
};

} // namespace dominus
