//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -o /tmp/sort_tuple example/sort_tuple.cpp

#include <sort_tuple.hpp>

using namespace monster;

constexpr bool operator<(auto lhs, auto rhs)
{
    return lhs.value < rhs.value;
}

template <typename T>
struct X
{
    T value;
};

constexpr auto t = std::make_tuple(X<short>{4}, X<int>{8}, X<float>{5.4f}, X<double>{5.0}, X<int>{2});
constexpr auto s = sort_tuple<t>();

using result = std::tuple<X<int>, X<short>, X<double>, X<float>, X<int>>;
static_assert(std::is_same_v<result, tuple_type<s>>);

int main(int argc, char* argv[])
{
    return 0;
}
