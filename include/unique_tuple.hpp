//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef UNIQUE_TUPLE_HPP
#define UNIQUE_TUPLE_HPP

#include <tuple>
#include <variant>
#include <algorithm>

namespace monster
{
    template <size_t N>
    using index_t = std::integral_constant<size_t, N>;

    template <typename T, auto N>
    constexpr decltype(auto) carry(const std::array<T, N>& a, auto l)
    {
        return [&]<auto... n>(std::index_sequence<n...>)
        {
            return std::tuple(a[n]...);
        }
        (std::make_index_sequence<l + 1>());
    }

    template <typename T, auto M, auto... N>
    constexpr std::variant<decltype(carry(std::array<T, M>(), index_t<N>()))...>
    to_variant(const std::array<T, M>& a, auto l, std::index_sequence<N...>)
    {
        return carry(a, l);
    }

    template <typename T>
    constexpr decltype(auto) unique_tuple(const T& t)
    {
        constexpr auto N = std::tuple_size_v<T>;

        auto a = std::apply([]<typename... Args>(Args&&... args)
        {
            return std::array<std::common_type_t<Args...>, N>{std::forward<Args>(args)...};
        }, t);

        using indices = std::make_index_sequence<N>;

        constexpr auto index = []<auto... n>(std::index_sequence<n...>)
        {
            using variant_t = std::variant<index_t<n>...>;
            std::array index {variant_t{std::in_place_index<n>}...};

            return index;
        }
        (indices());

        auto k = std::unique(a.begin(), a.end()) - a.begin();

        return std::visit([&](auto l) { return to_variant(a, l, indices()); }, index[k - 1]);
    }
}

#endif
