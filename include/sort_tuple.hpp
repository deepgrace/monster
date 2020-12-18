//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef SORT_TUPLE_HPP
#define SORT_TUPLE_HPP

#include <tuple>
#include <variant>
#include <algorithm>

namespace monster
{
    template <size_t N>
    using index_t = std::integral_constant<size_t, N>;

    template <const auto& t>
    constexpr auto sort_tuple()
    {
        using type = std::decay_t<decltype(t)>;

        return [&]<auto... N>(std::index_sequence<N...>)
        {
            constexpr auto indices = [&]
            {
                using variant_t = std::variant<index_t<N>...>;
                std::array index {variant_t{std::in_place_index<N>}...};

                std::sort(index.begin(), index.end(), [&](auto&& lhs, auto&& rhs)
                {
                    return std::visit([&]<auto m, auto n>(index_t<m>, index_t<n>)
                    {
                        return std::less<>()(std::get<m>(t), std::get<n>(t));
                    }, lhs, rhs);
                });

                return index;
            }();

            return std::tuple<std::tuple_element_t<indices[N].index(), type>...>(std::get<indices[N].index()>(t)...);
        }(std::make_index_sequence<std::tuple_size_v<type>>());
    }
}

#endif
