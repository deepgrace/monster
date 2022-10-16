//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef TUPLE_ALGORITHM_HPP
#define TUPLE_ALGORITHM_HPP

#include <tuple>
#include <optional>
#include <functional>

namespace tuple_algorithm
{
    template <typename T>
    inline constexpr auto tuple_size_v = std::tuple_size_v<std::decay_t<T>>;

    template <typename F, typename T>
    constexpr decltype(auto) all_of(F&& f, T&& t)
    {
        return std::apply([&]<typename... Args>(Args&&... args)
        {
            return (... && std::invoke(std::forward<F>(f), std::forward<Args>(args)));
        }, std::forward<T>(t));
    }

    template <typename F, typename T>
    constexpr decltype(auto) none_of(F&& f, T&& t)
    {
        return all_of(std::not_fn(std::forward<F>(f)), std::forward<T>(t));
    }

    template <typename F, typename T>
    constexpr decltype(auto) any_of(F&& f, T&& t)
    {
        return !none_of(std::forward<F>(f), std::forward<T>(t));
    }

    template <typename F, typename T>
    constexpr decltype(auto) for_each(F&& f, T&& t)
    {
        return std::apply([&]<typename... Args>(Args&&... args)
        {
            (..., std::invoke(std::forward<F>(f), std::forward<Args>(args)));
        }, std::forward<T>(t));
    }

    template <std::size_t N, typename F, typename T>
    constexpr decltype(auto) for_each_n(F&& f, T&& t)
    {
        return [&]<size_t... n>(const std::index_sequence<n...>&)
        {
            (..., std::invoke(std::forward<F>(f), std::get<n>(std::forward<T>(t))));

            return f;
        }
        (std::make_index_sequence<N>());
    }

    template <typename F, typename T>
    constexpr decltype(auto) count_if(F&& f, T&& t)
    {
        std::size_t n = 0;

        for_each([&]<typename Args>(Args&& args)
        {
            n += std::invoke(std::forward<F>(f), std::forward<Args>(args));
        }, std::forward<T>(t));

        return n;
    }

    template <typename T, typename U>
    constexpr decltype(auto) count(T&& t, const U& value)
    {
        return count_if([&]<typename Args>(Args&& args)
        {
            return args == value;
        }, std::forward<T>(t));
    }

    template <std::size_t N, typename F, typename T, typename U>
    constexpr std::optional<std::size_t> mismatch(F&& f, T&& t, U&& u)
    {
        constexpr auto i = tuple_size_v<T> - N;

        if constexpr (N == 0)
            return std::nullopt;
        else if (!std::invoke(std::forward<F>(f), std::get<i>(std::forward<T>(t)), std::get<i>(std::forward<T>(u))))
            return std::make_optional(i);
        else
            return mismatch<N - 1>(std::forward<F>(f), std::forward<T>(t), std::forward<U>(u));
    }

    template <typename T, typename U>
    constexpr decltype(auto) mismatch(T&& t, U&& u)
    {
        return mismatch<tuple_size_v<T>>([](auto&& l, auto&& r)
        {
            return l == r;
        }, std::forward<T>(t), std::forward<U>(u));
    }

    template <typename F, typename T, typename U>
    constexpr decltype(auto) mismatch(F&& f, T&& t, U&& u)
    {
        return mismatch<tuple_size_v<T>>(std::forward<F>(f), std::forward<T>(t), std::forward<U>(u));
    }

    template <std::size_t N, typename T, typename U>
    constexpr std::optional<std::size_t> find(T&& t, const U& value)
    {
        constexpr auto i = tuple_size_v<T> - N;

        if constexpr (N == 0)
            return std::nullopt;
        else if (std::get<i>(std::forward<T>(t)) == value)
            return std::make_optional(i);
        else
            return find<N - 1>(std::forward<T>(t), value);
    }

    template <typename T, typename U>
    constexpr decltype(auto) find(T&& t, const U& value)
    {
        return find<tuple_size_v<T>>(std::forward<T>(t), value);
    }

    template <std::size_t N, typename F, typename T>
    constexpr std::optional<std::size_t> find_if(F&& f, T&& t)
    {
        constexpr auto i = tuple_size_v<T> - N;

        if constexpr (N == 0)
            return std::nullopt;
        else if (std::invoke(std::forward<F>(f), std::get<i>(std::forward<T>(t))))
            return std::make_optional(i);
        else
            return find_if<N - 1>(std::forward<F>(f), std::forward<T>(t));
    }

    template <typename F, typename T>
    constexpr decltype(auto) find_if(F&& f, T&& t)
    {
        return find_if<tuple_size_v<T>>(std::forward<F>(f), std::forward<T>(t));
    }

    template <std::size_t N, typename F, typename T>
    constexpr decltype(auto) find_if_not(F&& f, T&& t)
    {
        return find_if(std::not_fn(std::forward<F>(f)), std::forward<T>(t));
    }

    template <typename F, typename T>
    constexpr decltype(auto) find_if_not(F&& f, T&& t)
    {
        return find_if_not<tuple_size_v<T>>(std::forward<F>(f), std::forward<T>(t));
    }
}

#endif
