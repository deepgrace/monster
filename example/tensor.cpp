//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++20 -s -Wall -Os -o /tmp/tensor example/tensor.cpp

#include <iostream>
#include <tensor.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    tensor<int, 3> t;

    t[1][0][2] = 4;
    t[2][1][0] = 9;

    std::cout << t[2][1][0] << std::endl;

    return 0;
}
