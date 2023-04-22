//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef IS_IDENTICAL_HPP
#define IS_IDENTICAL_HPP

#include <type_traits>

namespace monster
{
    template <bool b>
    consteval decltype(auto) is_identical()
    {
        static_assert(b);
    }

    template <auto p, auto q>
    consteval decltype(auto) is_identical()
    {
        is_identical<p == q>();
    }

    template <typename T, typename U>
    consteval decltype(auto) is_identical()
    {
        is_identical<std::is_same_v<T, U>>();
    }
}

#endif
