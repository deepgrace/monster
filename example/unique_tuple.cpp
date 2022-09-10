//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -o /tmp/unique_tuple example/unique_tuple.cpp

#include <iostream>
#include <unique_tuple.hpp>

using namespace monster;

constexpr bool operator==(auto lhs, auto rhs)
{
    return lhs.value == rhs.value;
}

template <typename T>
struct X
{
    T value;
};

int main(int argc, char* argv[])
{
    constexpr std::tuple t(X(7), X(7), X(4), X(3), X(3), X(4), X(6));

    constexpr auto v = unique_tuple(t);
    constexpr auto p = std::get<v.index()>(v);

    std::apply([]<typename... Args>(Args&&... args)
    {
        ((std::cout << args.value << " "), ...);
        std::cout << std::endl;
    }, p);

    return 0;
}
