//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++2a -s -Wall -Os -o /tmp/memoized_invoke example/memoized_invoke.cpp

#include <memoized_invoke.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    std::function<int(int)> fib = memoized_invoke([&](int n)
    {
        return n < 2 ? n : fib(n - 1) + fib(n - 2);
    });

    fib(8);

    return 0;
}
