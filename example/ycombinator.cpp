//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -o /tmp/ycombinator example/ycombinator.cpp

#include <iostream>
#include <ycombinator.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    auto f = []<typename F>(F&& gcd, int a, int b) -> int
    {
        return b == 0 ? a : gcd(b, a % b);
    };

    ycombinator y(f);

    std::cout << y(16, 24) << std::endl;

    return 0;
}
