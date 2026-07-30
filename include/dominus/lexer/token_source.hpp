#pragma once

#include <dominus/lexer/token.hpp>

namespace dominus
{

class TokenSource
{
    public:
        virtual ~TokenSource() = default;

        virtual Token NextToken() = 0;
};

} // namespace dominus
