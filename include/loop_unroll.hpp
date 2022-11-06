//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef LOOP_UNROLL_HPP
#define LOOP_UNROLL_HPP

#include <utility>

namespace loop_unroll
{
    template <auto n>
    struct bubble
    {
        template <typename T>
        static constexpr void sort(T&& t)
        {
            if constexpr(n != 0)
            {
                f.template operator()<n - 1, 0>(f, std::forward<T>(t));
                bubble<n - 1>::sort(std::forward<T>(t));
            }
        }

        static constexpr auto f = []<auto i, auto j, typename F, typename T>(F&& f, T&& t)
        {
            if constexpr(i != 0 || j != 0)
            {
                constexpr auto k = j + 1;
                constexpr auto b = j < i - 1;

                if (t[j] > t[k])
                    std::swap(t[j], t[k]);

                if constexpr(b)
                    f.template operator()<i, k>(std::forward<F>(f), std::forward<T>(t));
            }
        };
    };
}

#endif
