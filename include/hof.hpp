//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef HOF_HPP
#define HOF_HPP

#include <algorithm>
#include <numeric>

namespace monster
{
    template <typename F, typename R>
    R mapf(F&& f, R&& r)
    {
        std::transform(std::begin(r), std::end(r), std::begin(r), std::forward<F>(f));

        return r;
    }

    template <typename F, typename R, typename T>
    constexpr T foldl(F&& f, R&& r, T t)
    {
        return std::accumulate(std::begin(r), std::end(r), std::move(t), std::forward<F>(f));
    }

    template <typename F, typename R, typename T>
    constexpr T foldr(F&& f, R&& r, T t)
    {
        return std::accumulate(std::rbegin(r), std::rend(r), std::move(t), std::forward<F>(f));
    }
}

#endif
