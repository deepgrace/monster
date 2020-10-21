//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef YCOMBINATOR_HPP
#define YCOMBINATOR_HPP

#include <functional>

namespace monster
{
    template <typename F>
    struct ycombinator
    {
        template <typename... Args>
        decltype(auto) operator()(Args&&... args)
        {
            return std::invoke(f, *this, std::forward<Args>(args)...);
        }

        F f;
    };
}

#endif
