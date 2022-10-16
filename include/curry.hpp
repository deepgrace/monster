//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef CURRIED_HPP
#define CURRIED_HPP

#include <tuple>
#include <utility>
    
namespace monster
{
    template <typename F, typename... Args>
    class curry
    {
        public:
            using type = std::tuple<std::decay_t<Args>...>;

            curry(F f, Args... args) : f(f), args(forward(std::move(args)...))
            {
            }

            curry(F f, std::tuple<Args...> args) : f(f), args(std::move(args))
            {
            }

            template <typename... T>
            constexpr decltype(auto) operator()(T&&... t) const
            {
                auto p = std::tuple_cat(args, forward(std::forward<T>(t)...));
        
                if constexpr(std::is_invocable_v<F, Args..., T...>)
                    return std::apply(f, p);
                else
                    return curry<F, Args..., T...>(f, p);
            }

        private:

            template <typename... T>
            static constexpr decltype(auto) forward(T&&... t)
            {
                return std::tuple<std::decay_t<T>...>(std::forward<T>(t)...);
            }

            F f;
            std::tuple<Args...> args;
    };
}
    
#endif
