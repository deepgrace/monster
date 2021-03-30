//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++20 -s -Wall -Os -o /tmp/stream example/stream.cpp

#include <sstream>
#include <iostream>
#include <stream.hpp>

using namespace monster;

int main(int argc, char* argv[])
{    
    std::string lambda = "[]<template auto ...>(){}()";
    auto is = (std::ostringstream() << "ostreaming " << lambda).str();
    std::cout << is << std::endl;

    double f;
    std::string s;
    std::istringstream("7.06 <T>") >> f >> s;
    std::cout << f << std::endl;
    std::cout << s << std::endl;

    return 0;
}
