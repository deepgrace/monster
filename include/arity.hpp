//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef ARITY_HPP
#define ARITY_HPP

#include <monster.hpp>
#include <is_lambda.hpp>

namespace monster
{
    template <typename T>
    constexpr decltype(auto) arity()
    {
        if constexpr(is_tuple_v<T>)
            return std::tuple_size_v<T>;
        else if constexpr(std::is_aggregate_v<T>)
            return aggregate_arity_v<T>;
        else if constexpr(invocable<T>)
            return function_traits_v<T>;
        else
            return 0;
    }

    template <auto N, typename T>
    concept has_arity = arity<T>() == N;
}

#endif
