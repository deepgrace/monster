//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++2a -s -Wall -Os -o /tmp/is_lambda example/is_lambda.cpp

#include <is_lambda.hpp>

using namespace monster;

template <typename T, typename... Args>
auto lambda_t = []<T v>(auto&&, Args&& ...) -> T { return T{}; };

int main(int argc, char* argv[])
{
    static_assert(!is_lambda_v<nullptr_t>);
    static_assert(is_lambda_v<decltype([](){})>);
    static_assert(is_lambda_v<decltype(lambda_t<int, bool>)>);
    static_assert(is_lambda_v<decltype([]<typename ...>(auto ...){})>);

    return 0;
}
