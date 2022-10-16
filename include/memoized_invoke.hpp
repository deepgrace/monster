//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef MEMOIZED_INVOKE_HPP
#define MEMOIZED_INVOKE_HPP

#include <map>
#include <monster.hpp>

namespace monster
{
    template <typename F>
    constexpr decltype(auto) memoized_invoke(F&& f)
    {
        std::map<function_traits_t<F>, function_traits_r<F>> table;

        return [=]<typename... Args>(Args&&... args) mutable
        {
            auto tuple = std::forward_as_tuple(std::forward<Args>(args)...);
            auto cache = table.find(tuple);

            if (cache == table.end())
            {
                auto result = std::apply(f, tuple);
                table[tuple] = result;

                return result;
            }

            return cache->second;
        };
    }
}

#endif
