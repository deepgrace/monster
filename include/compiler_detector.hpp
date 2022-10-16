//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef COMPILER_DETECTOR_HPP
#define COMPILER_DETECTOR_HPP

#include <type_traits>

namespace monster
{
    struct W {};
    struct X {};

    struct Y {};
    struct Z {};

    struct V
    {
        using T = W;
        using U = Y;

        operator W Y::*();
        operator X Y::*();

        operator W Z::*();
        operator X Z::*();
    };

    struct gcc_compiler {};
    struct icc_compiler {};

    struct msvc_compiler {};
    struct clang_compiler {};

    struct unknown_compiler {};

    template <typename T>
    struct compiler_detector : std::type_identity<unknown_compiler>
    {
    };

    template <>
    struct compiler_detector<W Y::*> : std::type_identity<gcc_compiler>
    {
    };

    template <>
    struct compiler_detector<X Y::*> : std::type_identity<icc_compiler>
    {
    };

    template <>
    struct compiler_detector<W Z::*> : std::type_identity<msvc_compiler>
    {
    };

    template <>
    struct compiler_detector<X Z::*> : std::type_identity<clang_compiler>
    {
    };

    template <typename T>
    using compiler_detector_t = typename compiler_detector<T>::type;

    struct compiler_type
    {
        using T = X;
        using U = Z;

        using type = compiler_detector_t<decltype(std::declval<V>().operator T U::*())>;
    };

    using compiler_type_t = typename compiler_type::type;

    constexpr decltype(auto) compiler_name()
    {
        using type = compiler_type_t;

        if constexpr(std::is_same_v<type, gcc_compiler>)
            return "gcc";
        else if constexpr(std::is_same_v<type, icc_compiler>)
            return "icc";
        else if constexpr(std::is_same_v<type, msvc_compiler>)
            return "msvc";
        else if constexpr(std::is_same_v<type, clang_compiler>)
            return "clang";
        else
            return "unknow";
    }
}

#endif
