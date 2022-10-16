//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef OBJECT_POOL_HPP
#define OBJECT_POOL_HPP

#include <queue>
#include <memory>

// An object pool that can be used with any class that provides a default constructor.

namespace monster
{
    template <typename T>
    class object_pool
    {
        public:
            using type = std::shared_ptr<T>;

            object_pool() = default;

            object_pool(const object_pool&) = delete;
            object_pool& operator=(const object_pool&) = delete;

            object_pool(object_pool&&) = delete;
            object_pool& operator=(object_pool&&) = delete;

            type allocate()
            {
                if (objects.empty())
                    objects.emplace(std::make_unique<T>());

                std::unique_ptr<T> obj(std::move(objects.front()));
                objects.pop();

                type dst(obj.release(), [this](T* t)
                {
                    objects.emplace(t);
                });

                return dst;
            }

            virtual ~object_pool() = default;

        private:
            std::queue<std::unique_ptr<T>> objects;
    };

    template <typename T>
    using object_pool_t = typename object_pool<T>::type;
}

#endif
