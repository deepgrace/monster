//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef RING_HPP 
#define RING_HPP

#include <array>
#include <atomic>
#include <optional>

namespace monster
{    
    template <typename T, size_t N>
    class ring
    {
        public:
            bool push(T&& t)
            {
                return do_push(std::move(t));
            }
    
            bool push(const T& t)
            {
                return do_push(t);
            }
    
            auto pop() -> std::optional<T>
            {
                auto val = std::optional<T>();

                if (size() > 0)
                {
                    val = std::move(buffer[reader]);

                    reader = (reader + 1) % N;
                    size_.fetch_sub(1);
                }
    
                return val;
            }
    
            auto size() const noexcept
            {
                return size_.load();
            }
    
            bool empty() const noexcept
            {
                return size() == 0;
            }

        private:
            bool do_push(auto&& t)
            {
                if (size() == N)
                    return false;
    
                buffer[writer] = std::forward<decltype(t)>(t);

                writer = (writer + 1) % N;
                size_.fetch_add(1);
    
                return true;
            }
    
            size_t reader = 0;
            size_t writer = 0;

            std::array<T, N> buffer{};
            std::atomic<size_t> size_{0};
    };
}
    
#endif
