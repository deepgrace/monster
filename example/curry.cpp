//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++20 -s -Wall -Os -o /tmp/curry example/curry.cpp

#include <cassert>
#include <curry.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    auto sum = [](auto a, auto b, auto c, auto d, auto e, auto f)
    {
        return a + b + c + d + e + f;
    };

    auto result = sum(0, 1, 2, 3, 4, 5);

    auto s0 = curry(sum)(0, 1, 2, 3, 4, 5);
    auto s1 = curry(sum)(0)(1, 2, 3, 4, 5);
    auto s2 = curry(sum)(0, 1)(2, 3, 4, 5);
    auto s3 = curry(sum)(0, 1, 2)(3, 4, 5);
    auto s4 = curry(sum)(0, 1, 2, 3)(4, 5);
    auto s5 = curry(sum)(0, 1, 2, 3, 4)(5);

    auto t0 = curry(sum, std::make_tuple())(0, 1, 2, 3, 4, 5);
    auto t1 = curry(sum, std::make_tuple(0))(1, 2, 3, 4, 5);
    auto t2 = curry(sum, std::make_tuple(0, 1))(2, 3, 4, 5);
    auto t3 = curry(sum, std::make_tuple(0, 1, 2))(3, 4, 5);
    auto t4 = curry(sum, std::make_tuple(0, 1, 2, 3))(4, 5);
    auto t5 = curry(sum, std::make_tuple(0, 1, 2, 3, 4))(5);
    auto t6 = curry(sum, std::make_tuple(0, 1, 2, 3, 4, 5))();

    assert(s0 == result);
    assert(s1 == result);
    assert(s2 == result);
    assert(s3 == result);
    assert(s4 == result);
    assert(s5 == result);

    assert(t0 == result);
    assert(t1 == result);
    assert(t2 == result);
    assert(t3 == result);
    assert(t4 == result);
    assert(t5 == result);
    assert(t6 == result);

    return 0;
}
