//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>
#include <cstddef>

namespace monster
{
    template <typename T, size_t N>
    class tensor
    {
        public:
            explicit tensor(size_t size = 3);

            tensor<T, N-1>& operator[](size_t k);
            const tensor<T, N-1>& operator[](size_t k) const;

            template <typename... Args>
            requires (sizeof...(Args) < N) && (sizeof...(Args) >= 1)
            constexpr decltype(auto) operator[](size_t i, Args&&... args)
            {
                return operator[](i).operator[](args...);
            }

            void resize(size_t size);

            size_t size() const 
            { 
                return elements.size();
            }

        private:
            std::vector<tensor<T, N-1>> elements;
    };

    template <typename T>
    class tensor<T, 1>
    {
        public:
            explicit tensor(size_t size = 3);

            T& operator[](size_t k);
            const T& operator[](size_t k) const;

            void resize(size_t size);

            size_t size() const 
            { 
                return elements.size();
            }

        private:
            std::vector<T> elements;
    };

    template <typename T, size_t N>
    tensor<T, N>::tensor(size_t size)
    {
        resize(size);
    }

    template <typename T, size_t N>
    void tensor<T, N>::resize(size_t size)
    {
        elements.resize(size);

        for (auto& element : elements)
             element.resize(size);
    }

    template <typename T, size_t N>
    tensor<T, N-1>& tensor<T, N>::operator[](size_t k)
    {
        return elements[k];
    }

    template <typename T, size_t N>
    const tensor<T, N-1>& tensor<T, N>::operator[](size_t k) const
    {
        return elements[k];
    }

    template <typename T>
    tensor<T, 1>::tensor(size_t size)
    {
        resize(size);
    }

    template <typename T>
    void tensor<T, 1>::resize(size_t size)
    {
        elements.resize(size);
    }

    template <typename T>
    T& tensor<T, 1>::operator[](size_t k)
    {
        return elements[k];
    }

    template <typename T>
    const T& tensor<T, 1>::operator[](size_t k) const
    {
        return elements[k];
    }
}

#endif
