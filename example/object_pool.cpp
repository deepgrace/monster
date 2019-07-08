//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++2a -s -Wall -Os -o /tmp/object_pool example/object_pool.cpp

#include <vector>
#include <object_pool.hpp>

using namespace monster;

class expensive_object
{
public:
    expensive_object()
    {
        /* Expensive construction ... */
    }

    virtual ~expensive_object() = default;

    // Methods to populate the object with specific information.
    // Methods to retrieve the object data.
    // (not shown)

private:
    // Data members (not shown)
};

object_pool_t<expensive_object> get_expensive_object(object_pool<expensive_object>& pool)
{
    // Obtain an expensive_object object from the pool.
    auto object = pool.allocate();

    // Populate the object. (not shown)
    return object;
}

void process_expensive_object(object_pool<expensive_object>::type& object)
{
    // Process the object. (not shown)
}

int main(int argc, char* argv[])
{
    object_pool<expensive_object> pools;

    {
        std::vector<object_pool_t<expensive_object>> objects;
        for (size_t i = 0; i != 8; ++i)
            objects.push_back(get_expensive_object(pools));
    }

    for (size_t i = 0; i < 100; ++i)
    {
        auto req = get_expensive_object(pools);
        process_expensive_object(req);
    }

    return 0;
}
