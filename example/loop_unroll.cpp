//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -o /tmp/loop_unroll example/loop_unroll.cpp

#include <vector>
#include <iostream>
#include <loop_unroll.hpp>

using namespace loop_unroll;

template <typename T>
void print(T&& t)
{
    for (auto&& v : t)
         std::cout << v << " ";

    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    std::vector<int> t { -1, 2, 0, 7, 4, 8, -3, 5 };

    print(t);

    bubble<8>::sort(t);

    print(t);
}
