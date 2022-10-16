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
#include <functional>

namespace monster
{
    template <size_t N>
    using index_t = std::integral_constant<size_t, N>;

    template <const auto& t>
    using tuple_type = std::decay_t<decltype(t)>;

    template <const auto& t>
    constexpr decltype(auto) sorted_indices()
    {
        using type = tuple_type<t>;

        return [&]<auto... N>(std::index_sequence<N...>)
        {
            constexpr auto indices = [&]
            {
                using variant_t = std::variant<index_t<N>...>;
                std::array index {variant_t{std::in_place_index<N>}...};

                std::sort(index.begin(), index.end(), [&](auto&& l, auto&& r)
                {
                    return std::visit([&]<auto m, auto n>(index_t<m>, index_t<n>)
                    {
                        return std::less<>()(std::get<m>(t), std::get<n>(t));
                    }, l, r);
                });

                return index;
            }
            ();

            return std::index_sequence<indices[N].index()...>();
        }
        (std::make_index_sequence<std::tuple_size_v<type>>());
    }

    template <const auto& t>
    using sorted_indices_t = decltype(sorted_indices<t>());

    template <const auto& t>
    constexpr decltype(auto) sort_tuple()
    {
        using type = tuple_type<t>;

        return [&]<auto... N>(std::index_sequence<N...>)
        {
            return std::tuple<std::tuple_element_t<N, type>...>(std::get<N>(t)...);
        }
        (sorted_indices_t<t>());
    }
}

#endif
