//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++20 -s -Wall -Os -o /tmp/tuple_algorithm example/tuple_algorithm.cpp

#include <iostream>
#include <tuple_algorithm.hpp>

using namespace tuple_algorithm;

int main(int argc, char* argv[])
{
    auto is_float = [](auto v){ return std::is_floating_point_v<decltype(v)>; };

    static_assert(all_of(is_float, std::make_tuple(1.0f, 2.0f, 3.0f)));
    static_assert(none_of(is_float, std::make_tuple('1', nullptr, '3')));
    static_assert(any_of(is_float, std::make_tuple(1.0f, '2', nullptr)));

    auto print = [](auto v){ std::cout << v << std::endl; };
    for_each(print, std::make_tuple(2, 4, 8));
    for_each_n<2>(print, std::make_tuple(2, 4, 8));

    static_assert(count(std::make_tuple(1, 3, 2, 4, 3, 3), 3) == 3);
    static_assert(count_if(is_float, std::make_tuple('1', 2.0, 'c', nullptr)) == 1);

    static_assert(mismatch(std::make_tuple(4, 3, 2, 1), std::make_tuple(4, 3, 1, 2)).value() == 2);
    static_assert(mismatch([](auto x, auto y){ return x != y}, std::make_tuple(1, 3), std::make_tuple(1, 4)).value() == 1);

    static_assert(find(std::make_tuple(4, 6, 7, 8), 6).value() == 1);
    static_assert(find_if([](auto x) { return x == 6; }, std::make_tuple(7, 8, 6, 9)).value() == 2);
    static_assert(find_if_not([](auto x) { return x == 6; }, std::make_tuple(6, 5, 7)).value() == 1);

    return 0;
}
