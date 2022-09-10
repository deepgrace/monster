//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

// g++ -I include -m64 -std=c++23 -s -Wall -O3 -fconcepts -o /tmp/overview example/overview.cpp

#include <monster.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    // arrange the same elements adjacent in a sequence, keep the relative order
    using a1 = adjacent_t<std::tuple<char, double, char, int, double>>;
    using a2 = adjacent_t<std::index_sequence<4, 3, 0, 3, 2, 4, 5, 3>>;
    static_assert(std::is_same_v<a1, std::tuple<char, char, double, double, int>>);
    static_assert(std::is_same_v<a2, std::index_sequence<4, 4, 3, 3, 3, 0, 2, 5>>);

    // Boyer-Moore-Horspool (BMH) algorithm searches for occurrences of a sequence within another sequence
    using b1 = bmh_t<std::tuple<int, char, int>, std::tuple<int, int, char, int, char, int, char, int>>;
    using b2 = bmh_t<std::integer_sequence<int, 7, 5>, std::integer_sequence<int, 7, 5, 4, 0, 7, 5, 9>>;
    static_assert(std::is_same_v<b1, std::index_sequence<1, 3, 5>>);
    static_assert(std::is_same_v<b2, std::index_sequence<0, 4>>);

    // Knuth–Morris–Pratt (KMP) algorithm searches for occurrences of a sequence within another sequence
    using k1 = kmp_t<std::tuple<int, char, int>, std::tuple<int, int, char, int, char, int, char, int>>;
    using k2 = kmp_t<std::integer_sequence<int, 7, 5>, std::integer_sequence<int, 7, 5, 4, 0, 7, 5, 9>>;
    static_assert(std::is_same_v<k1, std::index_sequence<1, 3, 5>>);
    static_assert(std::is_same_v<k2, std::index_sequence<0, 4>>);

    // find K-th smallest element in a sequence (k == 2)
    using min1 = select_t<2, std::tuple<short, int, double, int, char>>;
    using min2 = select_t<2, std::integer_sequence<int, -2, 1, 0, -7, 4, 3>>;
    static_assert(std::is_same_v<min1, short>);
    static_assert(std::is_same_v<min2, c_<-2>>);

    // find K-th greatest element in a sequence (k == 2)
    using max1 = select_t<2, std::tuple<short, int, double, int, char>, greater_equal_t>;
    constexpr auto max2 = select_v<2, std::integer_sequence<int, -2, 1, 0, -7, 4, 3>, greater_equal_t>;
    static_assert(std::is_same_v<max1, int>);
    static_assert(max2 == 3);

    // returns element at specific index of a sequence
    using e1 = element_t<1, std::tuple<char, double, int>>;
    using e2 = element_t<3, std::integer_sequence<int, 1, -2, 7, 4>>;
    constexpr auto e3 = element_v<3, std::integer_sequence<int, 1, -2, 7, 4>>;
    static_assert(std::is_same_v<e1, double>);
    static_assert(std::is_same_v<e2, c_4>);
    static_assert(e3 == 4);

    // remove duplicate elements from a sequence, keep the first appearance
    using u1 = unique_t<std::tuple<int, char, int, double>>;
    using u2 = unique_t<std::integer_sequence<int, 2, 2, 3, 4, 3>>;
    static_assert(std::is_same_v<u1, std::tuple<int, char, double>>);
    static_assert(std::is_same_v<u2, std::integer_sequence<int, 2, 3, 4>>);

    // swap elements at specific index of a sequence
    using s1 = swap_t<1, 3, std::tuple<int, double, char, float>>;
    using s2 = swap_t<0, 2, std::integer_sequence<int, 1, -2, 7, 4>>;
    static_assert(std::is_same_v<s1, std::tuple<int, float, char, double>>);
    static_assert(std::is_same_v<s2, std::integer_sequence<int, 7, -2, 1, 4>>);

    // sort elements by value in a sequence
    using s3 = quick_sort_t<std::tuple<double, short, double, int, char, char, double>>;
    using s4 = quick_sort_t<std::integer_sequence<int, 2, 1, 0, -3, 4, 1, -7, 5, -2>>;
    static_assert(std::is_same_v<s3, std::tuple<char, char, short, int, double, double, double>>);
    static_assert(std::is_same_v<s4, std::integer_sequence<int, -7, -3, -2, 0, 1, 1, 2, 4, 5>>);

    // sort elements by index in a sequence
    using s5 = sort_index_t<std::tuple<double, short, double, int, char, char, double>>;
    using s6 = sort_index_t<std::integer_sequence<int, 2, 1, 0, -3, 4, 1, -7, 5, -2>>;
    static_assert(std::is_same_v<s5, std::index_sequence<4, 5, 1, 3, 6, 2, 0>>);
    static_assert(std::is_same_v<s6, std::index_sequence<6, 3, 8, 2, 1, 5, 0, 4, 7>>);

    // reverses the order of the elements of a sequence
    using r1 = reverse_t<std::tuple<float, double, int, short>>;
    using r2 = reverse_t<std::integer_sequence<int, 1, 0, 2, -2, 7, 6>>;
    static_assert(std::is_same_v<r1, std::tuple<short, int, double, float>>);
    static_assert(std::is_same_v<r2, std::integer_sequence<int, 6, 7, -2, 2, 0, 1>>);

    // reverses the order of the elements of a sequence recursively
    using r3 = reverse_recursive_t<std::tuple<int, std::tuple<int, std::tuple<char, short>>, char>>;
    using r4 = reverse_recursive_t<std::tuple<char, std::integer_sequence<int, 7, 2, 0, 4, 8>, int>>;
    static_assert(std::is_same_v<r3, std::tuple<char, std::tuple<std::tuple<short, char>, int>, int>>);
    static_assert(std::is_same_v<r4, std::tuple<int, std::integer_sequence<int, 8, 4, 0, 2, 7>, char>>);

    // rotates the elements in the range [begin, middle, end) of a sequence
    using r5 = rotate_t<0, 2, 5, std::tuple<int, char, double, float, int64_t>>;
    using r6 = rotate_t<2, 4, 7, std::integer_sequence<int, 9, 8, 1, 2, 3, 4, 5, 7, 6>>;
    static_assert(std::is_same_v<r5, std::tuple<double, float, int64_t, int, char>>);
    static_assert(std::is_same_v<r6, std::integer_sequence<int, 9, 8, 3, 4, 5, 1, 2, 7, 6>>);

    // returns the elements in the range [begin, end) of a sequence
    using r7 = range_t<1, 5, std::tuple<int, char, float, double, int, short>>;
    using r8 = range_t<2, 6, std::integer_sequence<int, 1, 2, -2, 4, 3, 5, 8, -5>>;
    static_assert(std::is_same_v<r7, std::tuple<char, float, double, int>>);
    static_assert(std::is_same_v<r8, std::integer_sequence<int, -2, 4, 3, 5>>);

    return 0;
}
