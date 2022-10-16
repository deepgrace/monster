//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -o /tmp/arity example/arity.cpp

#include <arity.hpp>

using namespace monster;

struct foobar
{
    int a;
    double b;
    char c;
};

int main(int argc, char* argv[])
{
    static_assert(arity<foobar>() == 3);
    static_assert(arity<decltype([](){})>() == 0);

    static_assert(has_arity<2, std::tuple<int, char>>);
    static_assert(has_arity<3, decltype([](int, char,float){})>);

    return 0;
}
