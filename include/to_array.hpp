//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef TO_ARRAY_HPP
#define TO_ARRAY_HPP

#include <tuple>
#include <variant>

namespace monster
{
    template <typename... Args>
    constexpr decltype(auto) to_array(const std::tuple<Args...>& t)
    {
        using type = std::variant<Args...>;

        return [&]<auto... N>(std::index_sequence<N...>)
        {
            return std::array<type, sizeof...(Args)>{type(std::in_place_index<N>, std::get<N>(t))...};
        }
        (std::index_sequence_for<Args...>());
    }
}

#endif
