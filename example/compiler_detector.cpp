//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -o /tmp/compiler_detector example/compiler_detector.cpp

#include <iostream>
#include <compiler_detector.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    std::cout << compiler_name() << std::endl;

    return 0;
}
