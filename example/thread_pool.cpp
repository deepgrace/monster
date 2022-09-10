//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -l pthread -o /tmp/thread_pool example/thread_pool.cpp

#include <vector>
#include <iostream>
#include <thread_pool.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    thread_pool pools(4);
    std::vector<std::future<int>> results;

    for (int i = 0; i != 16; ++i)
    {
        results.emplace_back
        (
            pools.post([i]
            {
                return 2 * i + 1;
            })
        );
    }

    for (auto&& result : results)
        std::cout << result.get() << " ";
    std::cout << std::endl;

    return 0;
}
