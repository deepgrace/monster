//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef STREAM_HPP
#define STREAM_HPP

#include <istream>
#include <ostream>

namespace monster
{    
    template <template <typename... > typename S, typename T>
    using stream_type = S<typename T::char_type, typename T::traits_type>;

    template <typename T>
    using istream_type = stream_type<std::basic_istream, T>;

    template <typename T>
    using ostream_type = stream_type<std::basic_ostream, T>;

    template <typename T, typename S>
    requires std::is_base_of_v<istream_type<T>, T>
    constexpr decltype(auto) operator>>(T&& t, const S& s)
    {
        static_cast<istream_type<T>&>(t) >> s;

        return std::forward<T>(t);
    }

    template <typename T, typename S>
    requires std::is_base_of_v<ostream_type<T>, T>
    constexpr decltype(auto) operator<<(T&& t, const S& s)
    {
        static_cast<ostream_type<T>&>(t) << s;

        return std::forward<T>(t);
    }
}

#endif
