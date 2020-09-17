# Monster Guidelines

## Installation
Monster is a header-only library that is self contained in one single header file without external dependencies.  
To use it, just download the library and add the directory containing it to your compiler's header search path, then include the library:
```cpp
#include <monster.hpp>
using namespace monster;
```
Unless specified otherwise, the documentation assumes the above lines to be present before examples and code snippets.

## Table of contents
Monster provides the following metaprograms to manipulate heterogeneous sequences.

- [access elements](#access-elements)
- [accumulate elements](#accumulate-elements)
- [algorithms](#algorithms)
- [combinations](#combinations)
- [currying](#currying)
- [delete elements](#delete-elements)
- [expand sequences](#expand-sequences)
- [generate sequences](#generate-sequences)
- [insert elements](#insert-elements)
- [loops](#loops)
- [metafunctions](#metafunctions)
- [object pool](#object-pool)
- [overload](#overload)
- [permutations](#permutations)
- [predicate elements](#predicate-elements)
- [range of sequences](#range-of-sequences)
- [replace elements](#replace-elements)
- [reverse sequences](#reverse-sequences)
- [rotate sequences](#rotate-sequences)
- [swap elements](#swap-elements)
- [search elements](#search-elements)
- [shift elements](#shift-elements)
- [sort elements](#sort-elements)
- [tensor](#tensor)
- [thread pool](#thread-pool)
- [transform elements](#transform-elements)
- [tuple operations](#tuple-operations)

## Reference

### Access elements
```cpp
// get the first element
using f1 = front_t<std::tuple<char, double, int>>;
using f2 = front_t<std::integer_sequence<int, 1, -2, 7, 4>>;
auto  f3 = front_v<std::integer_sequence<int, 1, -2, 7, 4>>;
using f4 = first_type<int, double, char*, float>;
// f1 == char
// f2 == c_1
// f3 == 1
// f4 == int

// get the first two elements
using f5 = take_front_t<2, std::tuple<int, double, int, char>>;
// f5 == std::tuple<int, double>

// get the last element
using b1 = back_t<std::tuple<char, double, int>>;
using b2 = back_t<std::integer_sequence<int, 1, -2, 7, 4>>;
auto  b3 = back_v<std::integer_sequence<int, 1, -2, 7, 4>>;
using b4 = last_type<int, double, char*, float>;
// b1 == int
// b2 == c_4
// b3 == 4
// b4 == float

// get the last two elements
using b5 = take_back_t<2, std::integer_sequence<int, 1, 2, -2, 4, 5>>;
// b5 == std::integer_sequence<int, 4, 5>

// get odd indexed elements
using odd1 = odd_t<std::tuple<int, char, double, int, char>>;
using odd2 = odd_t<std::integer_sequence<int, 1, 9, 0, 4, 2>>;
// odd1 == std::tuple<char, int>
// odd2 == std::integer_sequence<int, 9, 4>

// get even indexed elements
using even1 = even_t<std::tuple<int, char, double, int, char>>;
using even2 = even_t<std::integer_sequence<int, 1, 9, 0, 4, 2>>;
// even1 == std::tuple<int, double, char>
// even2 == std::integer_sequence<int, 1, 0, 2>

// get an element at specific index
using e1 = element_t<1, std::tuple<char, double, int>>;
using e2 = element_t<2, std::integer_sequence<int, 1, -2, 7, 4>>;
using e3 = get_t<1, std::integer_sequence<int, 1, 2, 4>>;
auto  e4 = get_v<1, std::integer_sequence<int, 1, 2, 4>>;
auto  e5 = element_v<3, std::integer_sequence<int, 1, -2, 7, 4>>;
using e6 = nth_type_t<2, int, double, char*, float>;
// e1 == double
// e2 == c_7
// e3 == c_2
// e4 == 2
// e5 == 4
// e6 == char*

// previous element of a specific index
using p1 = prev_t<2, std::tuple<int, double, char, float, char>>;
using p2 = prev_t<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>;
auo   p3 = prev_v<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>;
// p1 == double
// p2 == c_7
// p3 == 7

// next element of a specific index
using n1 = next_t<2, std::tuple<int, double, char, float, char>>;
using n2 = next_t<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>;
auto  n3 = next_v<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>;
// n1 == float
// n2 == c_<-1>
// n3 == -1

// middle element of a sequence
using m1 = midpoint_t<std::tuple<char, double, short, float, char>>;
using m2 = midpoint_t<std::integer_sequence<int, 7, 3, -1, 2, 4, 0>>;
auto  m3 = midpoint_v<std::integer_sequence<int, 7, 3, -1, 2, 4, 0>>;
// m1 == short
// m2 == c_<-1>
// m3 == -1

// size of a type
auto s1 = sizeof_t_v<c_8>;
auto s2 = sizeof_t_v<int>;
auto s3 = sizeof_t_v<std::tuple<int, char, double>>;
auto s4 = sizeof_t_v<std::index_sequence<1, 2, 0, 4>>;
// s1 == 8
// s2 == sizeof(int)
// s3 == 3
// s4 == 4

// size of a tuple element
auto t = tuple_element_size_v<2, std::tuple<short, int, double>>;
// t = sizeof(double)
```

### Accumulate elements
```cpp
// sum of a type
using s1 = sum_t<std::integer_sequence<int, 1, 2, 4>>;
auto  s2 = sum_v<std::integer_sequence<int, 6, 7, 8>>;
// s1 == c_7
// s2 == 21

// count the number of occurrences of an element
auto c1 = count_v<c_1, std::integer_sequence<int, 1, 2, 3, 1>>;
auto c2 = count_v<char, std::tuple<char, char, int, float, char, int>>;
// c1 == 2
// c2 == 3

// count the subtype of a sequence
auto n1 = number_of_v<std::tuple<nullptr_t>, std::tuple<short, int, double, int, int, double>>;
auto n2 = number_of_v<std::tuple<int, double>, std::tuple<short, int, double, int, int, double>>;
auto n3 = number_of_v<std::index_sequence<3, 6>, std::index_sequence<1, 5, 2, 7, 4, 2, 7, 2, 7>>;
auto n4 = number_of_v<std::index_sequence<2, 7>, std::index_sequence<1, 5, 2, 7, 4, 2, 7, 2, 7>>;
// n1 == 0
// n2 == 2
// n3 == 0
// n4 == 3

// count the number of elements satisfying specific criteria
auto c3 = count_if_v<is_even, std::integer_sequence<int, 1, 2, 3, 6, 4>>;
auto c4 = count_if_v<is_tuple, std::tuple<double, std::tuple<>, float, std::tuple<int>>>;
// c3 == 3
// c4 == 2

// get the number of members in a struct
struct foo
{
};

struct bar
{
    int x;
    double y;
};

auto N1 = aggregate_arity<foo>();
auto N2 = aggregate_arity_v<bar>;
// N1 == 0
// N2 == 2
```

### Algorithms
```cpp
/*
 *              _                         _                         _
 *             | |                       | |                       | |
 *            _| |_                      | |                       | |
 *           |_____|                     | |                       | |
 *          |_______|                    | |                       | |
 *         |_________|                   | |                       | |
 *        |___________|                  | |                       | |
 *       |_____________|                 | |                       | |
 *      |_______________|         _______| |_______         _______| |_______
 *     |                 |       |                 |       |                 |
 * -------------------------------------------------------------------------------
 *              #0                        #1                        #2
 */

// Tower of Hanoi
using one_disk = hanoi_t<1>;
using two_disks = hanoi_t<2>;
using three_disks = hanoi_t<3>;
/*
 * move                                      from   to
 * one_disk    == std::integer_sequence<int, 0,     1>
 *
 * two_disks   == std::integer_sequence<int, 0,     2,
 *                                           0,     1,
 *                                           2,     1>
 *
 * three_disks == std::integer_sequence<int, 0,     1,
 *                                           0,     2,
 *                                           1,     2,
 *                                           0,     1,
 *                                           2,     0,
 *                                           2,     1,
 *                                           0,     1>
 */

// arrange the same elements adjacent in a sequence, keep the relative order
using a1 = adjacent_t<std::tuple<int, char, int, double, char, int, char>>;
using a2 = adjacent_t<std::index_sequence<7, 2, 0, 7, 3, 7, 0, 2, 8, 5, 3>>;
// a1 == std::tuple<int, int, int, char, char, char, double>
// a2 == std::index_sequence<7, 7, 7, 2, 2, 0, 0, 3, 3, 8, 5>

// Boyer-Moore-Horspool (BMH) string searching algorithm for types
using b1 = bmh_t<std::tuple<char>, std::tuple<int, float, double, int, int>>;
using b2 = bmh_t<std::tuple<double>, std::tuple<double, int, int, double>>;
using b3 = bmh_t<std::tuple<int, double, int, double>,
           std::tuple<int, int, double, int, double, double, char, int, double, int, double, int>>;
// b1 == std::index_sequence<>
// b2 == std::index_sequence<0, 3>
// b3 == std::index_sequence<1, 7>

// Knuth–Morris–Pratt (KMP) string searching algorithm for types
using k1 = kmp_t<std::tuple<char>, std::tuple<int, float, double, int, int>>;
using k2 = kmp_t<std::tuple<double>, std::tuple<double, int, int, double>>;
using k3 = kmp_t<std::tuple<int, double, int, double>,
           std::tuple<int, int, double, int, double, double, char, int, double, int, double, int>>;
// k1 == std::index_sequence<>
// k2 == std::index_sequence<0, 3>
// k3 == std::index_sequence<1, 7>

// Knuth–Morris–Pratt (KMP) string searching algorithm for values
using k4 = kmp_t<std::integer_sequence<int, 1, 3, 1, 3, 1>,
           std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>;
using k5 = kmp_t<std::integer_sequence<int, 2, 1, 3, 1, 3, 1>,
           std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>;
// k4 == std::index_sequence<3, 10>
// k5 == std::index_sequence<>

// stable partition in the range [begin, end)
using p1 = typeof_t<stable_partition_t<0, 2, std::tuple<int, std::tuple<int>>, is_tuple>>;
using p2 = typeof_t<stable_partition_t<1, 6, std::tuple<int, char, std::tuple<char>, double,
           std::tuple<uint64_t>, int, std::tuple<float>>, is_tuple>>;
// p1 == std::tuple<std::tuple<int>, int>
// p2 == std::tuple<int, std::tuple<char>, std::tuple<uint64_t>,
         char, double, int, std::tuple<float>>

using p3 = typeof_t<stable_partition_t<1, 7, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, is_odd>>;
using p4 = typeof_t<stable_partition_t<1, 6, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, is_even>>;
// p3 == std::integer_sequence<int, 1, 3, 7, 1, 2, 8, 0, -2, 4, 5>
// p4 == std::integer_sequence<int, 1, 2, 8, 0, 3, 7, 1, -2, 4, 5>

// partition point in the range [begin, end)
using p5 = partition_point_t<p2, is_tuple, 1, 6>;
auto  p6 = partition_point_v<p4, is_even,  1, 6>;
// p5 == c_3
// p6 == 4

// partial sort in the range [begin, end)
using p7 = partial_sort_t<0, 4, std::integer_sequence<int, 6, -2, 8, 0, -7, 1, 7, -5, 4, 7, 3>>;
using p8 = partial_sort_t<4, 6, std::tuple<int, uint64_t, short, char, short, double, int, short>>;
// p7 == std::integer_sequence<int, -7, -5, -2, 0, 6, 1, 7, 3, 4, 7, 8>
// p8 == std::tuple<short, char, short, short, int, int, double, uint64_t>

// sort in the subrange [begin, end)
using su = sort_subrange_t<3, 6, std::index_sequence<3, 1, 4, 0, 2, 5, 9, 7, 4, 8>>;
// su == std::index_sequence<0, 1, 2, 3, 4, 4, 9, 7, 8, 5>

// partition in the subrange [begin, end)
using ps = partition_subrange_t<2, 7, std::index_sequence<4, 1, 8, 7, 0, 5, 3, 6, 2>>;
// ps == std::index_sequence<0, 1, 3, 2, 4, 5, 6, 7, 8>

// get the range and sum of maximum subarray of a sequence
using array = std::integer_sequence<int, -2, -3, 4, -1, -2, 1, 5, -3>;

using m1 = max_subarray_t<array>;          // iterative
using m2 = find_maximum_subarray_t<array>; // recursive
using m3 = kadane_t<array>;                // maximum type
auto  m4 = kadane_v<array>;                // maximum value
// m1 == std::integer_sequence<int, 2, 6, 7>
// m2 == m1
// m3 == c_7
// m4 == 7
// the elements in the range [2, 6] is the maximum subarray of array with sum 7

// equal range
using ins = std::integer_sequence<int, 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6>;

using equal_range1 = equal_range_t<c_3, ins>;
using rng1 = range_t<equal_range1::first, equal_range1::second, ins>;
// rng1 == std::integer_sequence<int, 3, 3, 3, 3>

using equal_range2 = equal_range_t<c_4, ins>;
using rng2 = range_t<equal_range2::first, equal_range2::second, ins>;
// rng2 == std::integer_sequence<int, 4, 4, 4>

// edit distance
auto ed1 = edit_distance_v<std::tuple<char, short, float, int, double, uint64_t>,
           std::tuple<char, double, nullptr_t, short, uint32_t, int, double, uint64_t>>;
auto ed2 = edit_distance_v<std::integer_sequence<int, 1, 2, 3, 4, 5, 6>,
           std::integer_sequence<int, 1, 5, 8, 2, 0, 4, 5, 6>>;
// ed1 == 3
// ed2 == 3

// set operations
using s1 = set_difference_t<less_t, std::integer_sequence<int, 1, 2, 5, 5, 5, 9>,
           std::integer_sequence<int, 2, 5, 7>>;
using s2 = set_symmetric_difference_t<less_t, std::integer_sequence<int, 1, 2, 5, 5, 5, 9>,
           std::integer_sequence<int, 2, 5, 7>>;
using s3 = set_intersection_t<less_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 6, 7, 8>,
           std::integer_sequence<int, 5, 7, 9, 10>>;
using s4 = set_union_t<less_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 5, 5>,
           std::integer_sequence<int, 3, 4, 5, 6, 7>>;
// s1 == std::integer_sequence<int, 1, 5, 5, 9>
// s2 == std::integer_sequence<int, 1, 5, 5, 7, 9>
// s3 == std::integer_sequence<int, 5, 7>
// s4 == std::integer_sequence<int, 1, 2, 3, 4, 5, 5, 5, 6, 7>

// find
auto f0 = find_v<char, std::tuple<float, char, double, int, char>>;
auto f1 = find_v<c_6, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>;
// f0 == 1
// f1 == 2

// find backward
auto f2 = find_backward_v<char, std::tuple<float, char, double, int, char>>;
auto f3 = find_backward_v<c_3, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>;
// f2 == 4
// f3 == 3

// find not
auto f4 = find_not_v<float, std::tuple<char, int, double, int, char>>;
auto f5 = find_not_v<c_4, std::integer_sequence<int, 4, 3, -2, 6, 3, 6>>;
// f4 == 0
// f5 == 1

// find not backward
auto f6 = find_not_backward_v<float, std::tuple<char, int, double, int, float>>;
auto f7 = find_not_backward_v<c_4, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>;
// f6 == 3
// f7 == 5

// find if
auto f8 = find_if_v<is_tuple, std::tuple<int, char, std::tuple<double>, float>>;
auto f9 = find_if_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>;
// f8 == 2
// f9 == 3

// find if backward
auto f10 = find_if_backward_v<equal<2>::template apply, std::integer_sequence<int, 1, 2, 3, 2, 4, 1, 2>>;
auto f11 = find_if_backward_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>;
// f10 == 6
// f11 == 6

// find if not
auto f12 = find_if_not_v<is_tuple, std::tuple<std::tuple<int>, char, std::tuple<double>, float>>;
auto f13 = find_if_not_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>;
// f12 == 1
// f13 == 0

// find if not backward
auto f14 = find_if_not_backward_v<equal<2>::template apply, std::integer_sequence<int, 1, 2, 3, 2, 4, 1, 2>>;
auto f15 = find_if_not_backward_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>;
// f14 == 5
// f15 == 7

// find first of
auto f16 = find_first_of_v<std::tuple<int, char, short, double>, std::tuple<float, nullptr_t, char>>;
auto f17 = find_first_of_v<std::index_sequence<4, 0, 3, 7, 5>, std::index_sequence<9, 8, 3, 6>>;
// f16 == 1
// f17 == 2

// any_of: apply an unary predicate to the sequence in the range [begin, end)
auto a1 = any_of_v<is_odd, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, 0, 10>;
auto a2 = any_of_v<is_tuple, std::tuple<int, char, std::tuple<char>, double,
          std::tuple<uint64_t>, int, std::tuple<float>>, 0, 7>;
// a1 == true
// a2 == true

// adjacent find: for a predicate f, where f(a[i], a[i+1]) returns true
auto a3 = adjacent_find_v<greater_t, std::integer_sequence<int, 0, 1, 2, 2, 4, 4, 3>>;
auto a4 = adjacent_find_v<std::is_same, std::integer_sequence<int, 0, 1, 2, 2, 4, 4, 3>>;
// a3 == 5
// a4 == 2

// adjacent difference: a[i] - a[i-1], a[i+1] - a[i], a[i+2] - a[i+1], ...
using a5 = adjacent_difference_t<minus_t, std::integer_sequence<int, 2, 4, 6, 8>>;
// a5 == std::integer_sequence<int, 2, 2, 2, 2>

// mismatch
using m = mismatch_t<equal_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 5, 5>,
          std::integer_sequence<int, 1, 2, 3, 5, 6, 7>>;
// m == pair_v<3, 3>

// includes
auto i = includes_v<equal_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 7>,
         std::integer_sequence<int, 2, 4, 7>>;
// i == true

// search
auto s5 = search_v<equal_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 7>,
          std::integer_sequence<int, 3, 4, 5>>
// s5 == 2

// find_end
auto f = find_end_v<equal_t, std::integer_sequence<int, 0, 1, 2, 0, 1, 2, 0, 1, 2>,
         std::integer_sequence<int, 0, 1, 2>>;
// f == 6

// search_n
auto s6 = search_n_v<std::is_same, 2, c_2, std::integer_sequence<int, 1, 2, 0, 2, 2, 7, 2>>;
auto s7 = search_n_v<std::is_same, 2, int, std::tuple<int, char, int, int, double, int, int, char>>;
// s6 == 3
// s7 == 2

// least common ancestor (lca) of two sequences, if not found, returns the first one
using lca1 = lca_t<std::tuple<int, char, short>, std::tuple<double, nullptr_t, int, char, short>>;
using lca2 = lca_t<std::tuple<short, double, int, char, short>, std::tuple<float, int, char, short>>;
using lca3 = lca_t<std::index_sequence<9, 4, 5>, std::index_sequence<1, 3, 7, 9, 4, 5>>;
auto  lca4 = lca_v<std::index_sequence<2, 3, 9, 4, 5>, std::index_sequence<0, 9, 4, 5>>;
// lca1 == int
// lca2 == int
// lca3 == index_t<9> (std::integral_constant<size_t, 9>)
// lca4 == 9

// inclusive_scan
using seq = std::integer_sequence<int, 1, 2, 3, 4>;

using in1 = inclusive_scan_t<plus_t, seq>;
using in2 = inclusive_scan_t<multiplies_t, seq>;
// in1 == std::integer_sequence<int, 1, 3, 6, 10>
// in2 == std::integer_sequence<int, 1, 2, 6, 24>

// exclusive_scan
using ex1 = exclusive_scan_t<plus_t, seq, c_2>;
using ex2 = exclusive_scan_t<multiplies_t, seq, c_2>;
// ex1 == std::integer_sequence<int, 2, 3, 5, 8>
// ex2 == std::integer_sequence<int, 2, 2, 4, 12>

// transform_inclusive_scan
using ti1 = transform_inclusive_scan_t<plus_t, seq, pred>;
using ti2 = transform_inclusive_scan_t<multiplies_t, seq, succ>;
// ti1 == std::integer_sequence<int, 0, 1, 3, 6>
// ti2 == std::integer_sequence<int, 2, 6, 24, 120>

// transform_exclusive_scan
using te1 = transform_exclusive_scan_t<plus_t, seq, pred, c_2>;
using te2 = transform_exclusive_scan_t<multiplies_t, seq, succ, c_2>;
// te1 == std::integer_sequence<int, 2, 2, 3, 5>
// te2 == std::integer_sequence<int, 2, 4, 12, 48>

// sum two sequences
using t = transmute_t<plus_t, std::integer_sequence<int, 1, 3, 0, 2>,
          std::integer_sequence<int, 1, 5, 4, 2>>;
// t == std::integer_sequence<int, 2, 8, 4, 4>

// inner product
auto in1 = inner_product_v<plus_t, equal_t, std::integer_sequence<int, 1, 3, 0, 2>,
           std::integer_sequence<int, 1, 5, 4, 2>, c_0>;
auto in2 = inner_product_v<plus_t, multiplies_t, std::integer_sequence<int, 1, 3, 0, 2>,
           std::integer_sequence<int, 1, 5, 4, 2>, c_0>;
// in1 == 2
// in2 == 20

// accumulate
auto acc = accumulate_v<multiplies_t, c_1, std::integer_sequence<int, 1, 3, -3, 2>>;
// acc == -18

// iota
using io = iota_t<succ, c_<-2>, std::integer_sequence<int, 0, 0, 0, 0, 0>>;
// io == std::integer_sequence<int, -2, -1, 0, 1, 2>

// tokenize a number into a sequence of specific length (default in base ten with length one)
constexpr auto N = 123456;
using t1 = tokenize_t<N, 10>;
using t2 = tokenize_t<N, 100>;
using t3 = tokenize_t<N, 1000>;
// t1 == std::integer_sequence<int, 1, 2, 3, 4, 5, 6>
// t2 == std::integer_sequence<int, 12, 34, 56>
// t3 == std::integer_sequence<int, 123, 456>
// tokenize_t<N> == tokenize_t<N, 10>

// multiply two large numbers that represented as two sequences
using l = large_number_multiplier_t<tokenize_t<984>, tokenize_t<987>>;
// l == std::integer_sequence<int, 9, 7, 1, 2, 0, 8>
// 984 * 987 == 971208

// starts with
auto sw = starts_with_v<std::tuple<int, char, short>, std::tuple<int, char>>;
// sw == true

// ends with
auto ew = ends_with_v<std::index_sequence<7, 4, 2>, std::index_sequence<4, 2>>;
// ew == true

// make a nested typelist flat
using nested = std::tuple<std::tuple<char, short>, double,
               std::tuple<char, std::tuple<char, int, double>>, short>;
using ft = flat_t<nested>;
// ft == std::tuple<char, short, double, char, char, int, double, short>

// reorder elements with index sequence order
// apply_permutation<type, indices> == apply_permutation<type, indices, false>
// apply_permutation<type, indices, true> == apply_permutation<reverse_t<type>, reverse_t<indices>>
using types1 = std::tuple<char, int, float, double, short>;
using types2 = std::integer_sequence<int, 8, 3, 5, -2, 7>;
using index1 = std::index_sequence<0, 2, 4, 1, 3>;
using index2 = std::index_sequence<4, 0, 2, 1, 3>;

using ap1 = apply_permutation_t<types1, index1>;
using ap2 = apply_permutation_t<types2, index2>;
// ap1 == std::tuple<char, float, short, int, double>
// ap2 == std::integer_sequence<int, 7, 8, 5, 3, -2>

using ap3 = apply_permutation_t<types1, index1, true>;
using ap4 = apply_permutation_t<types2, index2, true>;
// ap3 == std::tuple<int, double, char, float, short>
// ap4 == std::integer_sequence<int, 3, -2, 5, 7, 8>

// divides a sequence into several parts according to given criteria
using sp1 = split_t<is_tuple, std::tuple<int, char, std::tuple<double>, float, std::tuple<>>>;
using sp2 = split_t<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 8, 5>>;
// sp1 == std::tuple<std::tuple<int, char>, std::tuple<float>>
// sp2 == std::tuple<std::index_sequence<7, 3, 5>, std::index_sequence<9>, std::index_sequence<5>>
```

### Combinations
```cpp
// next combination of types C(4, 2)
using type0 = std::tuple<char, short, int, double>; // range_t<0, 2, type0> == std::tuple<char, short>
using type1 = next_combination_t<2, type0>;         // range_t<0, 2, type1> == std::tuple<char, int>
using type2 = next_combination_t<2, type1>;         // range_t<0, 2, type2> == std::tuple<char, double>
using type3 = next_combination_t<2, type2>;         // range_t<0, 2, type3> == std::tuple<short, int>
using type4 = next_combination_t<2, type3>;         // range_t<0, 2, type4> == std::tuple<short, double>
using type5 = next_combination_t<2, type4>;         // range_t<0, 2, type5> == std::tuple<int, double>

using next = next_combination_list<2, type0>;
/*
 * next == std::tuple<std::tuple<char, short>,
 *                    std::tuple<char, int>,
 *                    std::tuple<char, double>,
 *                    std::tuple<short, int>,
 *                    std::tuple<short, double>,
 *                    std::tuple<int, double>>
 */

// prev combination of types C(4, 2)
using prev = prev_combination_list<2, std::tuple<double, int, short, char>>;
/*
 * prev == std::tuple<std::tuple<double, int>,
 *                    std::tuple<double, short>,
 *                    std::tuple<double, char>,
 *                    std::tuple<int, short>,
 *                    std::tuple<int, char>,
 *                    std::tuple<short, char>>
 */

// next combination of values C(4, 2)
using val1 = next_combination_list<2, std::integer_sequence<int, 1, 2, 3, 4>>;
/*
 * val1 == std::tuple<std::integer_sequence<int, 1, 2>,
 *                    std::integer_sequence<int, 1, 3>,
 *                    std::integer_sequence<int, 1, 4>,
 *                    std::integer_sequence<int, 2, 3>,
 *                    std::integer_sequence<int, 2, 4>,
 *                    std::integer_sequence<int, 3, 4>>>
 */

// next combination of values C(5, 3)
using val2 = next_combination_list<3, std::integer_sequence<int, 1, 2, 3, 4, 5>>;
/*
 * val2 == std::tuple<std::integer_sequence<int, 1, 2, 3>,
 *                    std::integer_sequence<int, 1, 2, 4>,
 *                    std::integer_sequence<int, 1, 2, 5>,
 *                    std::integer_sequence<int, 1, 3, 4>,
 *                    std::integer_sequence<int, 1, 3, 5>,
 *                    std::integer_sequence<int, 1, 4, 5>,
 *                    std::integer_sequence<int, 2, 3, 4>,
 *                    std::integer_sequence<int, 2, 3, 5>,
 *                    std::integer_sequence<int, 2, 4, 5>,
 *                    std::integer_sequence<int, 3, 4, 5>>
 */

// next combination counts x + y + z = 2
using next_counts = next_combination_counts_list<0, 3, std::integer_sequence<int, 0, 0, 2>>;
/*
 *  next_counts = std::tuple<std::integer_sequence<int, 0, 0, 2>,
 *                           std::integer_sequence<int, 0, 1, 1>,
 *                           std::integer_sequence<int, 0, 2, 0>,
 *                           std::integer_sequence<int, 1, 0, 1>,
 *                           std::integer_sequence<int, 1, 1, 0>,
 *                           std::integer_sequence<int, 2, 0, 0>>
 */

// prev combination counts x + y + z = 2
using prev_counts = prev_combination_counts_list<0, 3, std::integer_sequence<int, 2, 0, 0>>;
// prev_counts == reverse_t<next_counts>

// hypercube indices
/*
 *  for i1 in [m..n]
 *      for i2 in [m..n]
 *          for i3 in [m..n]
 *               .
 *                 .
 *                   .
 *                    for ik in [m..n]
 *                        [i1..ik]
 */

// next hypercube indices for k = 3, m = 1, n = 2
using next_hyper = next_hypercube_indices_list<1, 3, std::integer_sequence<int, 1, 1, 1,>>;
/*
 * next_hyper == std::tuple<std::integer_sequence<int, 1, 1, 1>,
 *                          std::integer_sequence<int, 1, 1, 2>,
 *                          std::integer_sequence<int, 1, 2, 1>,
 *                          std::integer_sequence<int, 1, 2, 2>,
 *                          std::integer_sequence<int, 2, 1, 1>,
 *                          std::integer_sequence<int, 2, 1, 2>,
 *                          std::integer_sequence<int, 2, 2, 1>,
 *                          std::integer_sequence<int, 2, 2, 2>>
 */

// prev hypercube indices for k = 3, m = 1, n = 2
using prev_hyper = prev_hypercube_indices_list<1, 3, std::integer_sequence<int, 2, 2, 2>>;
// prev_hyper == reverse_t<next_hyper>
```

### Currying
In mathematics and computer science, currying is the technique of translating the evaluation of a function
that takes multiple arguments (or a tuple of arguments) into evaluating a sequence of functions, each with a single argument.

Partial application refers to the process of fixing a number of arguments to a function, producing another function of smaller arity.
It is a generalized form of currying: instead of binding one argument and getting (arity - 1) unary functions back,
it can bind n arguments at once and get another partially-applicable function with (arity - n) arity.

Currying is a special form of partial application where you can only bind a single argument at a time.
The result is another function with exactly 1 fewer parameter.

```cpp
#include <cassert>
#include <curry.hpp>
using namespace monster;

int main(int argc, char* argv[])
{
    auto sum = [](auto a, auto b, auto c, auto d, auto e, auto f)
    {
        return a + b + c + d + e + f;
    };

    auto expected = sum(0, 1, 2, 3, 4, 5);

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

    assert(s0 == expected);
    assert(s1 == expected);
    assert(s2 == expected);
    assert(s3 == expected);
    assert(s4 == expected);
    assert(s5 == expected);

    assert(t0 == expected);
    assert(t1 == expected);
    assert(t2 == expected);
    assert(t3 == expected);
    assert(t4 == expected);
    assert(t5 == expected);
    assert(t6 == expected);

    return expected;
}
```

### Delete elements
```cpp
// delete the first element
using p1 = pop_front_t<std::tuple<float, double, int>>;
using p2 = pop_front_t<std::integer_sequence<int, 1, 2, 3>>;
// p1 == std::tuple<double, int>
// p2 == std::integer_sequence<int, 2, 3>

// delete the last element
using p3 = pop_back_t<std::tuple<float, double, int>>;
using p4 = pop_back_t<std::integer_sequence<int, 1, 2, 3>>;
// p3 == std::tuple<float, double>
// p4 == std::integer_sequence<int, 1, 2>

// delete an element at specific index
using d1 = drop_t<2, std::tuple<int, double, int, char>>;
using d2 = drop_t<1, std::integer_sequence<int, 1, 2, -2, 4, 5>>;
// d1 == std::tuple<int, double, char>
// d2 == std::integer_sequence<int, 1, -2, 4, 5>

// delete an element of specific type or value
using d3 = eliminate_t<char, std::tuple<int, char, double, float, char>>;
using d4 = eliminate_t<c_3, std::integer_sequence<int, 0, 3, 2, 4, 7, 3>>;
using d5 = eliminate_c<4, std::integer_sequence<int, 4, 3, 2, 4, 7, 3>>;
// d3 == std::tuple<int, double, float>
// d4 == std::integer_sequence<int, 0, 2, 4, 7>
// d5 == std::integer_sequence<int, 3, 2, 7, 3>

// delete elements in the range [begin, end)
using d6 = erase_t<2, 5, std::tuple<int, char, float, double, int, char>>;
using d7 = erase_t<0, 6, std::tuple<int, char, float, double, int, char>>;
using d8 = erase_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>;
using d9 = erase_t<0, 6, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>;
// d6 == std::tuple<int, char, char>
// d7 == std::tuple<>
// d8 == std::integer_sequence<int, 1, 3, 5>
// d9 == std::integer_sequence<int>

// delete subtype of a sequence
using tpl = std::tuple<int, double, char, int, double, double, char, int>;
using tp2 = std::index_sequence<2, 0, 3, 5, 4, 4, 7, 3, 5, 4, 4, 3, 5, 4>;
using es1 = erase_subtype_t<std::tuple<int, double>, tpl>;
using es2 = erase_subtype_t<std::index_sequence<3, 5, 4>, tp2>;
using es3 = eliminate_subtype_t<std::tuple<double, char>, tpl>;
using es4 = eliminate_subtype_t<std::index_sequence<5, 4, 4>, tp2>;
// es1 == std::tuple<char, double, char, int>
// es2 == std::index_sequence<2, 0, 4, 7, 4>
// es3 == std::tuple<int, int, double, int>
// es4 == std::index_sequence<2, 0, 3, 7, 3, 3, 5, 4>

// delete the first two elements
using x = drop_front_t<2, std::tuple<int, double, int, char>>;
// x == std::tuple<int, char>

// delete the last two elements
using y = drop_back_t<2, std::integer_sequence<int, 1, 2, -2, 4, 5>>;
// y == std::integer_sequence<int, 1, 2, -2>

// delete all duplicate elements, keep the first appearance
using u1 = unique_t<std::tuple<int, char, int, double, float, double>>;
using u2 = unique_t<std::integer_sequence<int, 2, 1, 2, 3, 4, 3>>;
// u1 == std::tuple<int, char, double, float>
// u2 == std::integer_sequence<int, 2, 1, 3, 4>

// keep unique elements
using ue1 = unique_elements_t<std::tuple<short, int, char, int, double, char>>;
using ue2 = unique_elements_t<std::index_sequence<5, 7, 0, 5, 3, 2, 7>>;
// ue1 == std::tuple<short, double>
// ue2 == std::index_sequence<0, 3, 2>

// keep duplicate elements
using de1 = duplicate_elements_t<std::tuple<short, int, char, int, double, char>>;
using de2 = duplicate_elements_t<std::index_sequence<5, 7, 0, 5, 3, 2, 7>>;
// de1 == std::tuple<int, char>
// de2 == std::index_sequence<5, 7>

// remove unique elements, keep the relative order
using ru1 = remove_unique_t<std::tuple<short, int, double, int, double, int, char, int>>;
using ru2 = remove_unique_t<std::index_sequence<8, 4, 2, 0, 7, 0, 7, 0, 2, 8, 9, 6>>;
// ru1 == std::tuple<int, int, int, int, double, double>
// ru2 == std::index_sequence<8, 8, 2, 2, 0, 0, 0, 7, 7>

// delete all indices with duplicate elements, keep the last appearance
using u3 = unique_index_t<std::tuple<int, char, int, double, float, double>>;
using u4 = unique_index_t<std::integer_sequence<int, 2, 1, 2, 3, 4, 3>>;
// u3 == std::index_sequence<1, 2, 4, 5>
// u4 == u3

// delete all duplicate elements satisfying specific criteria
// for a type T, is_pointer_of_v<T*, T> == true
using u5 = unique_if_t<is_pointer_of, std::tuple<int*, int*, int, double, char, double*, double>>;
// u5 == std::tuple<int*, int*, double, char, double*>

// delete all elements satisfying specific criteria
using value = std::integer_sequence<int, 4, 0, 5, 6, 4, 1, 9, 21>;
using type = std::tuple<int, char, std::tuple<char>, double, std::tuple<double>, float, char>;

using r1 = remove_t<is_tuple, type>;
using r2 = remove_t<negaf<is_tuple>::template apply, type>;
using r3 = remove_t<is_odd, value>;
using r4 = remove_t<is_even, value>;
// r1 == std::tuple<int, char, double, float, char>
// r2 == std::tuple<std::tuple<char>, std::tuple<double>>
// r3 == std::integer_sequence<int, 4, 0, 6, 4>
// r4 == std::integer_sequence<int, 5, 1, 9, 21>

// delete all elements satisfying specific criteria in the range [begin, end)
using r5 = remove_if_t<is_odd, value, 1, 6>;
using r6 = remove_if_t<is_even, value, 1, 6>;
using r7 = remove_if_t<is_tuple, type, 1, 5>;
using r8 == remove_if_t<negaf<is_tuple>::template apply, type, 1, 5>;
// r7 == std::tuple<int, char, double, float, char>
// r8 == std::tuple<int, std::tuple<char>, std::tuple<double>, float, char>
// r5 == std::integer_sequence<int, 4, 0, 6, 4, 9, 21>
// r6 == std::integer_sequence<int, 4, 5, 1, 9, 21>

// copy the elements in the range [begin, end) for which the predicate F returns true
// copy_if<F, T> == copy_if<F, T, 0, sizeof_t_v<T>>
using type1 = std::integer_sequence<int, 4, 0, 5, 6, 4, 1, 9, 21>;
using type2 = std::tuple<int, std::tuple<char>, double, std::tuple<double>, float, char>;
using ci1 = copy_if_t<is_even, type1>;
using ci2 = copy_if_t<is_tuple, type2>;
// ci1 == std::integer_sequence<int, 4, 0, 6, 4>
// ci2 == std::tuple<std::tuple<char>, std::tuple<double>>

// delete elements at specific sorted index sequence
using indices = std::index_sequence<0, 1, 3, 4>;
using e1 = exclude_t<std::tuple<int, double, int, char, char, int>, indices>;
using e2 = exclude_t<std::integer_sequence<int, 1, 2, -2, 4, 5, 3>, indices>;
// e1 == std::tuple<int, int>
// e2 == std::integer_sequence<int, -2, 3>
```

### Expand sequences
**expand** provides indexed access to the elements of a list with specific index sequence,  
it takes a accessor `F`, a list `L`, an index sequence `I`, and an index offset `O` which is
optional (default value is 0).

**expand** is called like this `expand<F, L, I>` or `expand<F, L, I, O>`.

```cpp
using list1 = std::tuple<int, float, char, double>;
using list2 = std::integer_sequence<int, -1, 3, 7, 0, 5>;

// get the elements of the list at indices 0, 2
using e1 = expand_t<std::tuple_element, list1, std::index_sequence<0, 2>>;
using e2 = expand_t<get, list2, std::index_sequence<0, 2>>;
// e1 == std::tuple<int, char>
// e2 == std::integer_sequence<int, -1, 7>

// get the elements of the list at indices 0, 2 with offset 1,
// it's same as get the elements of the list at indices 1, 3 without offset
using e3 = expand_t<std::tuple_element, list1, std::index_sequence<0, 2>, 1>;
using e4 = expand_t<get, list2, std::index_sequence<0, 2>, 1>;
// e3 == std::tuple<float, double>
// e4 == std::integer_sequence<int, 3, 0>

// element combines std::tuple_element and get as a single accessor
using e5 = expand_t<element, list1, std::index_sequence<3, 0, 2, 1>>;
using e6 = expand_t<element, list2, std::index_sequence<4, 3, 2, 1, 0>>;
// e5 == std::tuple<double, int, char, float>
// e6 == std::integer_sequence<int, 5, 0, 7, 3, -1>
// e6 == reverse_t<list2>

// element is the default accessor of expand_of
using list3 = std::tuple<short, int, double, uint64_t, char>;
using list4 = std::integer_sequence<int, 3, 2, 0, 7, 5, 9>

using e7 = expand_of_t<list3, std::index_sequence<0, 2, 4>>;
using e8 = expand_of_t<list4, std::index_sequence<1, 3, 5>>;
// e7 == std::tuple<short, double, char>
// e8 == std::integer_sequence<int, 2, 7, 9>
// e7 == even_t<list3>
// e8 == odd_t<list4>>
```

### Generate sequences
```cpp
// generate a list
using f1 = fill_t<3, int>;
using f2 = fill_t<4, c_1>;
using f3 = fill_c<5, 2>;
using f4 = range_generator_t<int, 1, 7>;
using f5 = index_range<2, 7>;
using f6 = zero_sequence_t<int, 4>;
// f1 == std::tuple<int, int, int>
// f2 == std::integer_sequence<int, 1, 1, 1, 1>
// f3 == std::integer_sequence<int, 2, 2, 2, 2, 2>
// f4 == index_list<int, 1, 2, 3, 4, 5, 6>
// f5 == index_list<size_t, 2, 3, 4, 5, 6>
// f6 == std::integer_sequence<int, 0, 0, 0, 0>

// integer sequence {a, a + d, a + 2d, a + 3d, ...}
using i1 = integer_sequence_t<int, 4, 2, 0>;
using i2 = integer_sequence_t<int, 5, 3, 1>;
using i3 = integer_sequence_t<int, 6, 5, -1>;
// i1 == std::integer_sequence<int, 2, 2, 2, 2>
// i2 == std::integer_sequence<int, 3, 4, 5, 6, 7>
// i3 == std::integer_sequence<int, 5, 4, 3, 2, 1, 0>

// concat elements
using c1 = concat_t<std::tuple<int, char>, std::tuple<double>>;
using c2 = concat_t<std::integer_sequence<int, 1, 2, 3>, std::integer_sequence<int, 4, 5, 6>>;
// c1 == std::tuple<int, char, double>
// c2 == std::integer_sequence<int, 1, 2, 3, 4, 5, 6>

// cartesian product
using c3 = cartesian_product_t<std::tuple<int, double>, std::tuple<char, float>>;
using c4 = cartesian_product_t<std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>;
// c3 == std::tuple<int, char, int, float, double ,char, double, float>
// c4 == std::integer_sequence<int, 1, 3, 1, 4, 1, 5, 2, 3, 2, 4, 2, 5>

// matrix operatings
using matrix = std::tuple<std::tuple<char,   int,    double>,
                          std::tuple<char,   double, int>,
                          std::tuple<int,    char,   double>,
                          std::tuple<int,    double, char>,
                          std::tuple<double, char,   int>,
                          std::tuple<double, int,    char>>;

using m = get_matrix_element_t<3, 1, matrix>;
using n = set_matrix_element_t<3, 1, nullptr_t, matrix>;
// m == double
// get_matrix_element_t<3, 1, n> == nullptr_t

using t = matrix_transpose_t<matrix>;
// t == std::tuple<std::tuple<char,   char,   int,    int,    double, double>,
                   std::tuple<int,    double, char,   double, char,   int>,
                   std::tuple<double, int,    double, char,   int,    char>>

// matrix_transpose_t<matrix_transpose_t<matrix>> == matrix

using row1 = get_matrix_row_t<1, matrix>;
using col1 = get_matrix_col_t<1, matrix>;
// row1 == std::tuple<char, double, int>
// col1 == std::tuple<int, double, char, double, char, int>

using numbers = std::tuple<std::integer_sequence<int, 1, 2, 3>,
                           std::integer_sequence<int, 1, 3, 2>,
                           std::integer_sequence<int, 2, 1, 3>,
                           std::integer_sequence<int, 2, 3, 1>,
                           std::integer_sequence<int, 3, 1, 2>,
                           std::integer_sequence<int, 3, 2, 1>>;

using row2 = set_matrix_row_t<3, std::integer_sequence<int, 7, 8, 9>, numbers>;
using col2 = set_matrix_col_t<1, std::integer_sequence<int, 4, 5, 6, 7, 8, 9>, numbers>;
// row2 == std::tuple<std::integer_sequence<int, 1, 2, 3>,
                      std::integer_sequence<int, 1, 3, 2>,
                      std::integer_sequence<int, 2, 1, 3>,
                      std::integer_sequence<int, 7, 8, 9>,
                      std::integer_sequence<int, 3, 1, 2>,
                      std::integer_sequence<int, 3, 2, 1>>

// col2 == std::tuple<std::integer_sequence<int, 1, 4, 3>,
                      std::integer_sequence<int, 1, 5, 2>,
                      std::integer_sequence<int, 2, 6, 3>,
                      std::integer_sequence<int, 2, 7, 1>,
                      std::integer_sequence<int, 3, 8, 2>,
                      std::integer_sequence<int, 3, 9, 1>>

// zip elements
using z1 = zip_t<std::tuple<int, double>, std::tuple<char, float, nullptr_t>>;
using z2 = zip_t<std::integer_sequence<int, 1>, std::integer_sequence<int, 3>>;
using z3 = zip_t<std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>;
// z1 == std::tuple<int, char, double, float>
// z2 == std::integer_sequence<int, 1, 3>
// z3 == std::integer_sequence<int, 1, 3, 2, 4>

// zip with
using z4 = zip_with_t<multiplies_t, std::integer_sequence<int, 1, 2, -3>,
           std::integer_sequence<int, 3, 4, 5>>;
using z5 = zip_with_t<pair_t, std::tuple<int, char, short, double>, std::tuple<char, double, float>>;
// z4 == std::integer_sequence<int, 3, 8, -15>
// z5 == std::tuple<pair_t<int, char>, pair_t<char, double>, pair_t<short, float>>

// infinite call
using i = infinite_call_t<4, int, std::add_pointer>;
using p = multi_level_pointer_t<5, int>;
// i == int****
// p == int*****

// takes a single element in a sequence and replicates it to 
// create another sequence with some number of copies of that element
using s1 = splat_t<2, 4, std::integer_sequence<int, 1, 0, 3, 4>>;
using s2 = splat_t<3, 5, std::tuple<int, char, short, int, char>>;
// s1 == std::integer_sequence<int, 3, 3, 3, 3>
// s2 == std::tuple<int, int, int, int, int>

```

### Insert elements
```cpp
// insert elements at specific index
using i1 = insert_t<2, std::tuple<float, double, int>, float, char>;
using i2 = insert_t<1, std::integer_sequence<int, 1, 2, -2>, c_0, c_4>;
using i3 = insert_c<0, std::integer_sequence<int, 0, 4, 3>, 5, 6, 7>;
// i1 == std::tuple<float, double, float, char, int>
// i2 == std::integer_sequence<int, 1, 0, 4, 2, -2>
// i3 == std::integer_sequence<int, 5, 6, 7, 0, 4, 3>

// insert at specific index with elements in the range [begin, end)
using i4 = insert_range_t<2, std::tuple<float, double, int>, std::tuple<float, char, char>, 0, 2>;
using i5 = insert_range_t<1, std::integer_sequence<int, 1, 2, -2>,
           std::integer_sequence<int, 0, 9, -4, 3>, 1, 3>;
// i4 == std::tuple<float, double, float, char, int>
// i5 == std::integer_sequence<int, 1, 9, -4, 2, -2>

```
### Loops
```cpp
// compile time for
for_value<1, -2, 3>([]<auto N>()
{
    std::cout<< N << std::endl;
});

for_range<4, 7>([]<auto N>()
{
    std::cout<< N << std::endl;
});

for_type<double, int, char>([]<auto N, typename T>()
{
    std::cout << N << " " << typeid(T).name() << std::endl;
});

// call a function N times
loop<3>([](auto N, auto&& v)
{
    std::cout << N << " " << v << std::endl;
}, 4);

// call a function within a nested loop with the loop indices  
// as arguments (optional) in ascending or descending order

loop_for<BOOL>(indices...)(f);

// ascending order
loop_for<true>(2, 3, 4)
(
    [](auto i, auto j, auto k)
    {
        std::cout << '(' << i << ", " << j << ", " << k << ")" << std::endl;
    }
);

/*  This is equivalent to the following:
    for (int i = 0; i != 2; ++i)
         for (int j = 0; j != 3; ++j)
              for (int k = 0; k != 4; ++k)
                   f(i, j, k);
*/

// descending order
loop_for<false>(2, 3, 4)
(
    [](auto i, auto j, auto k)
    {
        std::cout << '(' << i << ", " << j << ", " << k << ")" << std::endl;
    }
);

/*  This is equivalent to the following:
    for (int i = 2 - 1; i >=0; --i)
         for (int j = 3 - 1; j >= 0; --j)
              for (int k = 4 - 1; k >= 0; --k)
                   f(i, j, k);
*/

// f can take fewer and even empty arguments than the loop depth
loop_for<true>(2, 3, 4)
(
    [](auto i, auto j)
    {
        std::cout << '(' << i << ", " << j << ")" << std::endl;
    }
);

loop_for<false>(2, 3, 4)
(
    []
    {
        std::cout << "don't use the loop index at all" << std::endl;
    }
);

iterate<4>([]
{
    std::cout << "x" << std::endl;
});

unroller<3> unroll;

unroll([](auto&&... args)
{
    (std::cout << ... << args) << std::endl;
}, 1, 2.3, "[]<typename ...>(){}();");

// fmap(f, Args...)
// invoke the callable object f with each argument of the parameter pack Args... independently
// fmap(f, Arg1, Arg2, Arg3, ..., ArgN) is equivalent to f(Arg1); f(Arg2); f(Args3); ...; f(ArgN);
fmap([](auto& v)
{
    std::cout << v << std::endl;
}, 1, 2.3, "string", 'x');
```

### Metafunctions
**bind_front**, bind arguments `Args...` to the front parameters of a function `F` in a a member template `apply`  
that can be later called with extra arguments `args...`.  
In other words, `bind_front<F, Args...>::template apply<args...>` is equivalent to `F<Args..., args...>`.  

**bind_front** is defined as:
```cpp
template <template <typename ...> typename F, typename... Args>
struct bind_front
{
    template <typename... args>
    using apply = F<Args..., args...>;
};
```

bind types at the front of a tuple
```cpp
using f = bind_front<std::tuple, int, double>;
using t = f::template apply<char, float, short>;
using g = call<f, char, float, short>;
// t == std::tuple<int, double, char, float, short>
// g == t
```

**bind_back**, bind arguments `Args...` to the back parameters of a function `F` in a a member template `apply`  
that can be later called with extra arguments `args...`.  
In other words, `bind_back<F, Args...>::template apply<args...>` is equivalent to `F<args..., Args...>`.  

**bind_back** is defined as:
```cpp
template <template <typename ...> typename F, typename... Args>
struct bind_back
{
    template <typename... args>
    using apply = F<args..., Args...>;
};
```

bind types at the back of a tuple
```cpp
using f = bind_back<std::tuple, int, double>;
using t = f::template apply<char, float, short>;
using g = call<f, char, float, short>;
// t == std::tuple<char, float, short, int, double>
// g == t
```

**call**, for a type `T`, which has a member template `apply` (class or alias) that take arguments `Args...`,  
it's usually called as `typename F::template apply<Args...>`, this is where **call** comes in handy:
```cpp
template <typename F, typename... Args>
using call = typename F::template apply<Args...>;

template <typename F, typename... Args>
using call_t = typename call<F, Args...>::type;
```
It can be used as `call<T, Args...>` or `call_t<T, Args...>`.

**curry**, currying is a technique that for a function taking multiple arguments (or, equivalently, a tuple of arguments),
it turns the function into a function which takes a single argument and returns a function to handle the remaining arguments.

**curry** is defined as:
```cpp
template <typename F, typename ...>
struct curry : F
{
};

template <typename F, typename T, typename... Args>
struct curry<F, T, Args...> : curry<call<F, T>, Args...>
{
};

template <typename F, typename... Args>
using curry_t = typename curry<F, Args...>::type;
```
where `F` is a function which can be invoked by `call`.  
Currying can be useful in several situations, especially when working with higher-order functions.

**fold**, folding a parameter pack (or, equivalently, a tuple of arguments), it takes a binary function `F`, 
when applied with two arguments `T` and `U`,  it products a type as a result of invoke `call_t<F, T, U>` 
which can be used together with the remaining arguments.

**fold** is defined as:
```cpp
template <typename F, typename T, typename ...>
struct fold : std::type_identity<T>
{
};

template <typename F, typename T, typename U, typename... Args>
struct fold<F, T, U, Args...> : fold<F, call_t<F, T, U>, Args...>
{
};

template <typename F, typename... Args>
using fold_t = typename fold<F, Args...>::type;
```
Folding is especially useful when iterating over a parameter pack with higher-order functions.

**negaf**, negate a function, it is defined as:
 ```cpp
template <bool B, template <typename ...> typename F, typename T>
using wrapin_if = std::conditional_t<B, F<T>, T>;

template <template <typename ...> typename F, bool neg = true>
struct negaf;
{
    template <typename... Args>
    using apply = wrapin_if<neg, std::negation, F<Args...>>;
};
```
For a bool `BOOL` and a function `F`, which take arguments `Args...`, `negaf` can be used as:  
`negaf<F, BOOL>::template apply<Args...>` or `call<negaf<F, BOOL>, Args...>`.
```cpp
using four = c_4;
using is_odd_ = negaf<is_even>;

auto ev1 = is_even_v<four>;
auto ev2 = is_odd_::template apply<four>::value;
auto ev3 = call<negaf<is_even, false>, four>::value;
// ev1 == true
// ev2 == false
// ev3 == true
```

**recurse**, it takes a function `F`, a type holder `T`, and a parameter pack `Args...`, when 
applied with `curry`, it products a type as result of invoke `T<F<Arg1>, F<Arg2>, F<Arg3>, ..., F<ArgN>>`.

**recurse** is defined as:
```cpp
template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
struct recurse : std::type_identity<T<Args...>>
{
    template <typename... args>
    using apply = recurse<F, T, Args..., typename F<args>::type...>;
};

template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
using recurse_t = typename recurse<F, T, Args...>::type;
```
**recurse** is commonly used with `curry` as a higher-order metafunction.  

As an example, add pointer to each argument of a parameter pack and store the result as a tuple is easy:
```cpp
using c = curry_t<recurse<std::add_pointer, std::tuple>, int*, double, short>;
// c == std::tuple<int**, double*, short*>
```

### Object pool
An object pool that can be used with any class that provides a default constructor.

```cpp
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
```

### Overload
```cpp
// call the first function compatible with arguments

overload_sequence element_count
{
    [](auto&&) { return 1; },
    [](auto&& v) -> decltype(v.size())
    {
         return std::forward<decltype(v)>(v).size();
    },
    [](auto&& v) -> type_t<std::size_t, decltype(std::begin(v)), decltype(std::end(v))>
    {
        return std::distance(std::begin(std::forward<decltype(v)>(v)),
               std::end(std::forward<decltype(v)>(v)));
    }
};

element_count(42);
element_count(std::vector({1 , 2, 3, 4}));
element_count(std::forward_list({1 , 2, 3}));

// call the best function for the provided arguments

overload_set
{
    [](auto x) { return x; },
    [](int x) { return x * 10; },
    [](double x) { return x / 10.; }
}(10.);
```

### Permutations
```cpp
/* for a type T and a value N, a permutation of P(element_size<T>, N)
 * satisfying the following conditions
 *
 * loop_permutation_t<T> == loop_permutation_t<T, element_size<T>>
 * loop_permutation_t<T, N> == reverse_t<loop_permutation_t<reverse_t<T>, N>>
 * reverse_t<loop_permutation_t<T, N>> == loop_permutation_t<reverse_t<T>, N>
 */

// next permutation of types P(3, 3)
using type0 = std::tuple<char, int, double>;
using type1 = next_permutation_t<type0>; // type1 == std::tuple<char, double, int>
using type2 = next_permutation_t<type1>; // type2 == std::tuple<int, char, double>
using type3 = next_permutation_t<type2>; // type3 == std::tuple<int, double, char>
using type4 = next_permutation_t<type3>; // type4 == std::tuple<double, char, int>
using type5 = next_permutation_t<type4>; // type5 == std::tuple<double, int, char>

using next = next_permutation_list<type0>;
/*
 * next == std::tuple<std::tuple<char, int, double>,
 *                    std::tuple<char, double, int>,
 *                    std::tuple<int, char, double>,
 *                    std::tuple<int, double, char>,
 *                    std::tuple<double, char, int>,
 *                    std::tuple<double, int, char>>
 *
 * next_partial_permutation_list<3, type0> == next
 *
 * loop_permutation_t<type0> == next
 * loop_permutation_t<type0, 3> == next
 */

using prev = prev_permutation_list<type5>;
/*
 * prev == reverse_t<next>
 * prev_partial_permutation_list<3, type5> == prev
 *
 * loop_permutation_t<type5> == prev
 * loop_permutation_t<type5, 3> == prev
 */

// next permutation of values P(3, 3)
using vals = next_permutation_list<std::integer_sequence<int, 1, 2, 3>>;
/*
 * vals == std::tuple<std::integer_sequence<int, 1, 2, 3>,
 *                    std::integer_sequence<int, 1, 3, 2>,
 *                    std::integer_sequence<int, 2, 1, 3>,
 *                    std::integer_sequence<int, 2, 3, 1>,
 *                    std::integer_sequence<int, 3, 1, 2>,
 *                    std::integer_sequence<int, 3, 2, 1>>
 *
 * prev_permutation_list<std::integer_sequence<int, 3, 2, 1>> == reverse_t<vals>
 *
 * loop_permutation_t<std::integer_sequence<int, 3, 2, 1>> == reverse_t<vals>
 * loop_permutation_t<std::integer_sequence<int, 3, 2, 1>, 3> == reverse_t<vals>
 */

// next partial permutation of types P(3, 2)
using next_partial = next_partial_permutation_list<2, std::tuple<char, int, double>>;
/*
 * next_partial == std::tuple<std::tuple<char, int>,
 *                            std::tuple<char, double>,
 *                            std::tuple<int, char>,
 *                            std::tuple<int, double>,
 *                            std::tuple<double, char>,
 *                            std::tuple<double, int>>
 *
 * loop_permutation_t<std::tuple<char, int, double>, 2> == next_partial
 */

// prev partial permutation of types P(3, 2)
using lp1 = reverse_t<loop_permutation_t<std::tuple<char, int, double>, 2>>;
using lp2 = loop_permutation_t<reverse_t<std::tuple<char, int, double>>, 2>;
using prev_partial = prev_partial_permutation_list<2, std::tuple<double, int, char>>;
/*
 * lp1 == lp2
 * prev_partial == reverse_t<next_partial>
 * loop_permutation_t<std::tuple<double, int, char>, 2> == prev_partial
 */

// recursive permutation
using pr1 = permutation_recursive_t<std::tuple<char, int, double>>;
/*
 * pr1 == std::tuple<std::tuple<char, int, double>,
 *                   std::tuple<char, double, int>,
 *                   std::tuple<int, char, double>,
 *                   std::tuple<int, double, char>,
 *                   std::tuple<double, int, char>,
 *                   std::tuple<double, char, int>>
 */

using pr2 = permutation_recursive_t<std::integer_sequence<int, 1, 2, 3>>;
/*
 * pr2 == std::tuple<std::integer_sequence<int, 1, 2, 3>,
 *                   std::integer_sequence<int, 1, 3, 2>,
 *                   std::integer_sequence<int, 2, 1, 3>,
 *                   std::integer_sequence<int, 2, 3, 1>,
 *                   std::integer_sequence<int, 3, 2, 1>,
 *                   std::integer_sequence<int, 3, 1, 2>>
 */
```

### Predicate elements
```cpp
// determine whether a type has all unique elements
auto v1 = is_unique_v<std::tuple<int, double, char, float>>;
auto v2 = is_unique_v<std::integer_sequence<int, 1, 2, 3, 1, 4>>;
// v1 == true
// v2 == false

// determine whether the first element can be found in the rest of a parameter pack
auto c1 = contains_v<int, double, char, float, int>;
auto c2 = comprise_v<1, -2, 3, 0, 4>;
// c1 == true
// c2 == false

// determine whether a parameter pack has all unique elements
auto b1 = is_unique_type_v<int, double, int, float>;
auto b2 = is_unique_value_v<1, 2, 7, 3, 4>;
// b1 == false
// b2 == true

// determine whether a parameter pack has duplicate elements
auto h1 = has_duplicates_type_v<int, double, char, int, float>;
auto h2 = has_duplicates_value_v<1, 2, 3, 1, 4>;
// h1 = true
// h2 = true

// determine whether a type has duplicate elements
auto h3 = has_duplicates_v<std::tuple<int, double, char, int, float>>;
auto h4 = has_duplicates_v<std::integer_sequence<int, 1, 2, 3, 1, 4>>;
// h3 == true
// h4 == true

// determine whether a type is palindrome
auto b3 = is_palindrome_v<std::tuple<int, double, int, int, double, int>>;
auto b4 = is_palindrome_v<std::integer_sequence<int, 3, 0, 2, 1, 2, 0, 3>>;
auto b5 = is_palindrome_v<std::tuple<int, double, char, int, int, double, int>>;
auto b6 = is_palindrome_v<std::integer_sequence<int, 4, 2, -1, 2, 0, 3, -2, 4>>;
// b3 == true
// b4 == true
// b5 == false
// b6 == false

// subset check
auto s1 = is_subset_v<std::integer_sequence<int, 4>, std::integer_sequence<int, 4>>;
auto s2 = is_subset_v<std::integer_sequence<int, 4, 5, 6>, std::integer_sequence<int, 4>>;
auto s3 = is_subset_v<std::integer_sequence<int, 4, 5, 6>, std::integer_sequence<int, 1, 3, 4, 5, 6, 7>>;
auto s4 = is_subset_v<std::tuple<float, char, double>, std::tuple<double, char, float, char, double, int>>;
// s1 == true
// s2 == false
// s3 == true
// s4 == true

// determine whether a type is iterable
auto i1 = is_iterable_v<int>;
auto i2 = is_iterable_v<std::vector<int>>;
// i1 == false
// i2 == true

// determine whether a type is a container
auto i3 = is_container_v<int>;
auto i4 = is_container_v<std::string>;
// i3 == false
// i4 == true

// determine whether a type is a pointer of another
auto i5 = is_pointer_of_v<std::add_pointer_t<int>, int>;
// i5 == true

// determine whether a type is a instance of a class template
auto i6 = is_instance_of_v<std::tuple, int>;
auto i7 = is_instance_of_v<std::tuple, std::tuple<int>>;
// i6 == false
// i7 == true

// determine whether a type is a integer sequence
auto i8 = is_sequence_of_v<std::integer_sequence, int>;
auto i9 = is_sequence_of_v<std::integer_sequence, std::index_sequence<1, 2, 3>>;
// i8 == false
// i9 == true

// determine whether a type is streamable
auto i10 = is_streamable_v<std::ostream, int>;
auto i11 = is_streamable_v<std::ostream, std::tuple<int>>;
// i10 == true
// i11 == false

// check whether a type is defined
auto i12 = is_type_complete_v<int>;
auto i13 = is_type_complete_v<struct none_exist_type>;
// i12 == true
// i13 == false

// check whether a type is lambda
template <typename T, typename... Args>
auto lambda_t = []<T v>(auto&&, Args&& ...) -> T { return T{}; };

auto i14 = is_lambda_v<nullptr_t>;
auto i15 = is_lambda_v<decltype([](){})>;
auto i16 = is_lambda_v<decltype(lambda_t<int, bool>)>;
auto i17 = is_lambda_v<decltype([]<typename ...>(auto ...){})>;
// i14 == false
// i15 == true
// i16 == true
// i17 == true
```

### Range of sequences
```cpp
// get the elements in the range [begin, end)
using r1 = range_t<1, 4, std::tuple<int, char, float, double, int>>;
using r2 = range_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>;
// r1 == std::tuple<char, float, double>
// r2 == std::integer_sequence<int, 2, -2, 4>

// get the elements in the range [begin, end), then reverse it
using e1 = extent_t<1, 4, std::tuple<int, char, float, double, int, char>>;
using e2 = extent_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>;
// e1 == std::tuple<double, float, char>
// e2 == std::integer_sequence<int, 4, -2, 2>

// reverse the elements, then get the elements in the range [begin, end)
using d1 = degree_t<1, 4, std::tuple<int, char, float, double, int, char>>;
using d2 = degree_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>;
// d1 == std::tuple<int, double, float>
// d2 == std::integer_sequence<int, 3, 4, -2>

// pivot sequences around N
// (A, ..., M, N, ..., Z) -> (N, ..., Z, A, ..., M)
using p1 = pivot_t<3, std::tuple<int, char, char, int, int>>;
using p2 = pivot_t<3, std::index_sequence<0, 1, 2, 3, 4, 5>>;
// p1 == std::tuple<int, int, int, char, char>
// p2 == std::index_sequence<3, 4, 5, 0, 1, 2>
```

### Replace elements
```cpp
// replace specific elements
using r1 = replace_with_t<int, float, std::tuple<int, char, int, double, int, float, char>>;
using r2 = replace_with_t<c_1, c_<-6>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
using r3 = replace_with_c<1, -6, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
// r1 == std::tuple<float, char, float, double, float, float, char>
// r2 == std::integer_sequence<int, -6, 3, -2, -6, 7, -6, 4, 6>
// r3 == std::integer_sequence<int, -6, 3, -2, -6, 7, -6, 4, 6>

// replace elements in the range [begin, end) with a parameter pack
using r4 = replace_t<1, 3, std::tuple<char, float, double, int>, float, char>;
using r5 = replace_c<1, 3, std::integer_sequence<int, 4, 1, 2, -2>, 4, 3>;
// r4 == std::tuple<char, float, char, int>;
// r5 == std::integer_sequence<int, 4, 4, 3, -2>

// replace elements of one type in range [begin1, end1) with the elemens in range [begin2, end2)
// of another type
using r6 = replace_range_t<1, 3, std::tuple<char, float, double, int>,
           std::tuple<float, char, int, double>, 1, 3>;
using r7 = replace_range_t<1, 3, std::integer_sequence<int, 4, 1, 2, -2>,
           std::integer_sequence<int, -2, 1, 0, 3>, 0, 3>;
// r6 == std::tuple<char, char, int, int>
// r7 == std::integer_sequence<int, 4, -2, 1, 0, -2>

// replace specific elements in the range [begin, end)
using g1 = gsub_t<1, 5, int, float, std::tuple<int, char, int, double, int, float, char>>;
using g2 = gsub_t<1, 5, c_<-2>, c_<-6>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
using g3 = gsub_c<1, 5, -2, -6, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
// g1 == std::tuple<int, char, float, double, float, float, char>
// g2 == std::integer_sequence<int, 1, 3, -6, 1, 7, 1, 4, 6>
// g3 == std::integer_sequence<int, 1, 3, -6, 1, 7, 1, 4, 6>

// replace elements in the range [begin, end) satisfying specific criteria
using g4 = gsub_if_t<1, 4, is_tuple, int, std::tuple<int, char, std::tuple<>, double, std::tuple<>>>;
using g5 = gsub_if_t<1, 5, is_even, c_<-6>, std::integer_sequence<int, 1, 3, -2, 4, 7, 0, 4, 6>>;
// g4 == std::tuple<int, char, int, double, std::tuple<>>
// g5 == std::integer_sequence<int, 1, 3, -6, -6, 7, 0, 4, 6>

// adjust specific elements in the range [begin, end)
using a1 = adjust_t<1, 5, int, std::tuple<int, char, int, double, int, float, char>, std::add_pointer>;
using a2 = adjust_t<1, 5, c_1, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>, succ>;
// a1 == std::tuple<int, char, int*, double, int*, float, char>
// a2 == std::integer_sequence<int, 1, 3, -2, 2, 7, 1, 4, 6>

// adjust elements in the range [begin, end) satisfying specific criteria
using a3 = adjust_if_t<1, 5, std::tuple<int, std::tuple<int>, double,
           std::tuple<float>, char>, std::add_pointer, is_tuple>;
using a4 = adjust_if_t<1, 5, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>, succ, is_odd>;
// a3 == std::tuple<int, std::tuple<int>*, double, std::tuple<float>*, char>
// a4 == std::integer_sequence<int, 1, 4, -2, 2, 8, 1, 4, 6>

// substitute elements in the range [begin, end) with specific element
using s1 = substitute_t<2, 5, int, std::tuple<int, char, int, double, int, float, char>>;
using s2 = substitute_t<2, 5, c_<-2>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
using s3 = substitute_c<3, 6, 9, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
// s1 == std::tuple<int, char, int, int, int, float, char>
// s2 == std::integer_sequence<int, 1, 3, -2, -2, -2, 1, 4, 6>
// s3 == std::integer_sequence<int, 1, 3, -2, 9, 9, 9, 4, 6>

// replace element at specific index
using e1 = exchange_t<2, int, std::tuple<int, int, char, double, int, float, char>>;
using e2 = exchange_t<1, c_<-2>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
using e3 = exchange_c<4, 9, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>;
// e1 == std::tuple<int, int, int, double, int, float, char>
// e2 == std::integer_sequence<int, 1, -2, -2, 1, 7, 1, 4, 6>
// e3 == std::integer_sequence<int, 1, 3, -2, 1, 9, 1, 4, 6>

// replace elements of src with elements of dst indexed by indices
// exchange_with<indices, dst, src>
// element_t<i, src> == element_t<i, dst> for i in indices
using ins1 = std::index_sequence<2, 4, 0, 1, 6>;
using src1 = std::tuple<char, int, double, int, char, double, float, nullptr_t>;
using dst1 = std::tuple<int, int, char, double, int, float, double>;
using ext1 = exchange_with_t<ins1, src1, dst1>;
// ext1 == std::tuple<int, int, char, int, int, double, double, nullptr_t>

using ins2 = std::index_sequence<1, 5, 3, 6, 2>;
using src2 = std::integer_sequence<int, 7, -1, 3, 5, 9, 2, 5>;
using dst2 = std::integer_sequence<int, 4, 0, 6, -5, 7, 4, 3, 2, 11>;
using ext2 = exchange_with_t<ins2, src2, dst2>;
// ext2 == std::integer_sequence<int, 4, -1, 3, 5, 7, 2, 5, 2, 11>

// replace subtype of a sequence with another sequence
// replace_subtype<subtype, dst, src>
using tp1 = std::tuple<short, int, char, double, int, int, char, double, int>;
using tp2 = std::index_sequence<7, 0, 2, 6, 4, 6, 4, 5, 2, 6, 4, 8, 2, 6, 3>;
using rs1 = replace_subtype_t<std::tuple<char, double>, std::tuple<float, nullptr_t>, tp1>;
using rs2 = replace_subtype_t<std::index_sequence<2, 6, 4>, std::index_sequence<9, 1>, tp2>;
// rs1 == std::tuple<short, int, float, nullptr_t, int, int, float, nullptr_t, int>
// rs2 == std::index_sequence<7,  0, 9, 1, 6, 4, 5, 9, 1, 8, 2, 6, 3>
```

### Reverse sequences
```cpp
// reverses the order of the elements
using r1 = reverse_t<std::tuple<float, double, int>>;
using r2 = reverse_t<std::integer_sequence<int, 1, 2, -2>>;
// r1 == std::tuple<int, double, float>
// r2 == std::integer_sequence<int, -2, 2, 1>

// reverses the order of the elements recursively
using r3 = reverse_recursive_t<std::tuple<int, std::tuple<int, std::tuple<double, short>>, char>>;
using r4 = reverse_recursive_t<std::tuple<char, std::integer_sequence<int, 7, 2, 0, -4, 8>, int>>;
// r3 == std::tuple<char, std::tuple<std::tuple<short, double>, int>, int>
// r4 == std::tuple<int, std::integer_sequence<int, 8, -4, 0, 2, 7>, char>

// reverse a parameter pack of types
using i1 = invert_type_t<>;
using i2 = invert_type_t<char>;
using i3 = invert_type_t<int, char, double, float>;
// i1 == invert_type<>
// i2 == char
// i3 == invert_type<float, double, char, int>

// reverse a parameter pack of values
using i4 = invert_value_t<>;
using i5 = invert_value_t<1>;
using i6 = invert_value_t<2, 1, 4, 3>;
// i4 == invert_value<>
// i5 == invert_value<1>
// i6 == invert_value<3, 4, 1, 2>

// reverse elements in the range [begin, end)
using r5 = reverse_range_t<1, 4, std::tuple<int, char, float, double, int, char>>;
using r6 = reverse_range_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>;
// r5 == std::tuple<int, double, float, char, int, char>
// r6 == std::integer_sequence<int, 1, 4, -2, 2, 3, 5>
```

### Rotate sequences
```cpp
/* rearrange the elements in the range [begin, middle, end), in such a way that
 * the elements in the range [middle, end) comes first,
 * the elements in the range [begin, middle) comes last.
 */
using r1 = rotate_t<0, 2, 5, std::tuple<int, char, double, float, int64_t>>;
using r2 = rotate_t<0, 2, 5, std::integer_sequence<int, 1, 2, 3, 4, 5>>;
using r3 = rotate_t<2, 4, 7, std::integer_sequence<int, 9, 8, 1, 2, 3, 4, 5, 7, 6>>;
// r1 == std::tuple<double, float, int64_t, int, char>
// r2 == std::integer_sequence<int, 3, 4, 5, 1, 2>
// r3 == std::integer_sequence<int, 9, 8, 3, 4, 5, 1, 2, 7, 6>
```

### Swap elements
```cpp
// swap elements at specific index
using s1 = swap_t<1, 3, std::tuple<int, double, char, float>>;
using s2 = swap_t<0, 2, std::integer_sequence<int, 1, -2, 7, 4>>;
// s1 == std::tuple<int, float, char, double>
// s2 == std::integer_sequence<int, 7, -2, 1, 4>

// swap elements in the range [begin, end) of each other
using ranges_t = swap_ranges<1, 4, std::integer_sequence<int, 0, 1, 2, 3, 4, 5>,
      std::integer_sequence<int, -1, -2, -3, -4, -5>>;

// first_t<ranges_t> == std::integer_sequence<int, 0, -2, -3, -4, 4, 5>
// second_t<ranges_t> == std::integer_sequence<int, -1, 1, 2, 3, -5>

// swap elements in the range [begin1, end1) of one type
// with elements in the range [begin2, end2) of another
using extents_t = swap_extent<1, 4, 2, 5, std::integer_sequence<int, 0, 1, 2, 3, 4, 5>,
      std::integer_sequence<int, -1, -2, -3, -4, -5>>;

// first_t<extents_t> == std::integer_sequence<int, 0, -3, -4, -5, 4, 5>
// second_t<extents_t> == std::integer_sequence<int, -1, -2, 1, 2, 3>
```

### Search elements
```cpp
// the kth minimum element
using s1 = select_t<2, std::tuple<short, int, double, int, char>>;
using s2 = select_t<3, std::integer_sequence<int, 0, 3, 2, 1, 2, 6>>;
auto  s3 = select_v<4, std::integer_sequence<int, -2, 1, 0, -7, 4, 3>>;
// s1 == short
// s2 == c_2
// s3 == 1

// the kth maximum element
using s4 = select_t<2, std::tuple<short, int, double, int, char>, greater_equal_t>;
using s5 = select_t<3, std::integer_sequence<int, 0, 3, 4, 1, -2, 6>, greater_equal_t>;
auto  s6 = select_v<4, std::integer_sequence<int, -2, 1, 0, -7, 4, 3>, greater_equal_t>;
// s4 == int
// s5 == c_3
// s6 == 0

// mode, the element that appears most often
using m1 = monster::mode_t<std::tuple<char, double, char, double, int, float, char>>;
using m2 = monster::mode_t<std::integer_sequence<int, 1, 2, 3, 1>>;
auto  m3 = mode_v<std::integer_sequence<int, 1, 2, 3, 1>>;
// m1 == char
// m2 == c_1
// m3 == 1

// returns the first index of the type that appears in the rest of a parameter pack
auto i1 = typeindex<char, float, int, char>();
auto i2 = typeindex<int, double, int, char>();
auto i3 = typeindex<int, double, double, float>();
// i1 == 3
// i2 == 2
// i3 == 4

// returns the first index at which the provided element appears in the type
auto i4 = type_index_v<int, std::tuple<char, float, double, int, char>>;
auto i5 = type_index_v<uint64_t, std::tuple<char, float, double, int, char>>;
auto i6 = value_index_v<6, std::integer_sequence<int, 1, -2, 0, 3, 6, 5>>;
auto i7 = value_index_v<7, std::integer_sequence<int, 1, -2, 0, 3, 6, 5>>;
// i4 == 3
// i5 == 5, not found
// i6 == 4
// i7 == 6, not found

// maximum element
using m4 = max_element_t<std::tuple<short, int, char>>;
using m5 = max_element_t<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>;
auto  m6 = max_element_v<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>;
using m7 = max_t<char, double>;
using m8 = maximum_t<short, int, char, short>;
// m4 == int
// m5 == c_4
// m6 == 4
// m7 == double
// m8 == int

// minimum element
using n4 = min_element_t<std::tuple<short, int, char>>;
using n5 = min_element_t<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>;
auto  n6 = min_element_v<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>;
using n7 = min_t<char, double>;
using n8 = minimum_t<short, int, char, int>;
// n4 == char
// n5 ==  c_<-2>
// n6 == -2
// n7 == char
// n8 = char

// search element
auto b1 = binary_search_v<double, std::tuple<short, int, double>>;
auto b2 = binary_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>;
auto b3 = exponential_search_v<double, std::tuple<short, int, double>>;
auto b4 = exponential_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>;
auto b5 = interpolation_search_v<double, std::tuple<short, int, double>>;
auto b6 = interpolation_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>>;
auto b7 = fibonacci_search_v<double, std::tuple<short, int, double>>;
auto b8 = fibonacci_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>>;
// b1..b8 == true

// majority element
auto  m0 = majority_search_v<std::integer_sequence<int, 1, 2, 2, 3, 2, 1, 2>>;
using m9 = majority_search_t<std::tuple<char, int, int, float, int, double, int>>;
// m0 == 2
// m9 == int
```

### Shift elements
```cpp
// shift left two elements
using s1 = shift_left_t<2, std::tuple<int, char, double, float, int64_t>>;
using s2 = shift_left_t<2, std::integer_sequence<int, 1, 2, 3, 4, 5>>;
// s1 == std::tuple<double, float, int64_t, int, char>
// s2 == std::integer_sequence<int, 3, 4, 5, 1, 2>

// shift right two elements
using s3 = shift_right_t<2, std::tuple<int, char, double, float, int64_t>>;
using s4 = shift_right_t<2, std::integer_sequence<int, 1, 2, 3, 4, 5>>;
// s3 == std::tuple<float, int64_t, int, char, double>
// s4 == std::integer_sequence<int, 4, 5, 1, 2, 3>
```

### Sort elements
```cpp
// sort values
using v = std::integer_sequence<int, 2, 1, 0, -3, 4, 1, -7, 5, -2>;

using a = stable_sort_t<v>;
using b = select_sort_t<v>;
using c = counting_sort_t<v>;
using d = radix_sort_t<v>;
using e = stooge_sort_t<v>;
using f = bubble_sort_t<v>;
using g = shaker_sort_t<v>;
using h = oddeven_sort_t<v>;
using i = gnome_sort_t<v>;
using j = selection_sort_t<v>;
using k = quick_sort_t<v>;
using l = quick_sort_iterative_t<v>;
using m = insert_sort_t<v>;
using n = insertion_sort_t<v>;
using o = merge_sort_t<v>;
using p = strand_sort_t<v>;
using q = heap_sort_t<v>;
using r = rank_sort_t<v>;

// a..r == std::integer_sequence<int, -7, -3, -2, 0, 1, 1, 2, 4, 5>

// sort types
using t = std::tuple<double, short, double, int, char, char, double>;

using A = stable_sort_t<t>;
using B = select_sort_t<t>;
using C = counting_sort_t<t>;
using D = radix_sort_t<t>;
using E = stooge_sort_t<t>;
using F = bubble_sort_t<t>;
using G = shaker_sort_t<t>;
using H = oddeven_sort_t<t>;
using I = gnome_sort_t<t>;
using J = selection_sort_t<t>;
using K = quick_sort_t<t>;
using L = quick_sort_iterative_t<t>;
using M = insert_sort_t<t>;
using N = insertion_sort_t<t>;
using O = merge_sort_t<t>;
using P = strand_sort_t<t>;
using Q = heap_sort_t<t>;
using R = map_sort_t<t>;

// A..R == std::tuple<char, char, short, int, double, double, double>

// sort values by index
using v_sorted_index = sort_index_t<v>;
// v_sorted_index == std::index_sequence<6, 3, 8, 2, 1, 5, 0, 4, 7>
// access v by v_sorted_index in a sorted order

// sort types by index
using t_sorted_index = sort_index_t<t>;
// t_sorted_index == std::index_sequence<4, 5, 1, 3, 6, 2, 0>
// access t by t_sorted_index in a sorted order
```

### Tensor
The tensor class template takes a type for its element and an integer specifying its “dimensionality.”
The key insight here is that the element type of the tensor is not the element type specified in the template parameter list,
but is in fact another tensor of dimensionality one less than the current one.
In other words, a three-dimensional tensor is a vector of two-dimensional tensors; the two dimensional tensors are each vectors of one-dimensional tensors.

```cpp
#include <iostream>
#include <tensor.hpp>
using namespace monster;

int main(int argc, char* argv[])
{
    tensor<int, 3> t;

    t[1][0][2] = 4;
    t[2][1][0] = 9;

    std::cout << t[2][1][0] << std::endl;

    return 0;
}
```

### Thread pool
```cpp
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
```

### Transform elements
```cpp
// add elements at the front
using p1 = prepend_t<std::tuple<float, double, int>, int, float>;
using p2 = prepend_t<std::integer_sequence<int, 1, 2, -2>, c_4, c_3>;
using p3 = prepend_c<std::integer_sequence<int, 1, 2, -2>, 4, 3>;
// p1 == std::tuple<int, float, float, double, int>
// p2 == std::integer_sequence<int, 4, 3, 1, 2, -2>
// p3 == p2

// add elements at the back
using a1 = append_t<std::tuple<float, double, int>, float, char>;
using a2 = append_t<std::integer_sequence<int, 1, 2, -2>, c_4, c_3>;
using a3 = append_c<std::integer_sequence<int, 1, 2, -2>, 4, 3>;
// a1 == std::tuple<float, double, int, float, char>
// a2 == std::integer_sequence<int, 1, 2, -2, 4, 3>
// a3 == a2

// add prefix to each element
using p4 = prefix_t<std::tuple<int, double>, float, char>;
using p5 = prefix_t<std::integer_sequence<int, 1, 2>, c_3, c_4>;
using p6 = prefix_c<std::integer_sequence<int, 5, 0>, 3, 4>;
// p4 == std::tuple<float, char, int, float, char, double>
// p5 == std::integer_sequence<int, 3, 4, 1, 3, 4, 2>
// p6 == std::integer_sequence<int, 3, 4, 5, 3, 4, 0>

// add suffix to each element
using s1 = suffix_t<std::tuple<int, double>, float, char>;
using s2 = suffix_t<std::integer_sequence<int, 1, 2>, c_3, c_4>;
using s3 = suffix_c<std::integer_sequence<int, 5, 0>, 2, 6>;
// s1 == std::tuple<int, float, char, double, float, char>
// s2 == std::integer_sequence<int, 1, 3, 4, 2, 3, 4>
// s3 == std::integer_sequence<int, 5, 2, 6, 0, 2, 6>

// add pointer to each element of a parameter pack
using c1 = currying_t<std::add_pointer, int*, double, char>;
using c2 = eval_t<currying_t, std::add_pointer, c1>;
// c1 == std::tuple<int**, double*, char*>
// c2 == std::tuple<int***, double**, char**>

// sequences in a repeated manner
using c3 = cycle_t<3, int, double>;
using c4 = cycle_t<3, c_2, c_4>;
using c5 = cycle_c<3, 2, 4>;
// c3 == std::tuple<int, double, int, double, int, double>
// c4 == std::integer_sequence<int, 2, 4, 2, 4, 2, 4>
// c5 == c4

// add pointer to each element
using t1 = transform_t<std::add_pointer, std::tuple<int, double, char*>>;
// t1 == std::tuple<int*, double*, char**>

// add one to each element
using t2 = transform_t<succ, std::integer_sequence<int, 7, 5, -2, 3, 1>>;
// t2 == std::integer_sequence<int, 8, 6, -1, 4, 2>

// apply a function to elements that satisfying specific criteria
using t3 = transform_if_t<succ, is_even, std::integer_sequence<int>,
            std::integer_sequence<int, 0, 3, 1, 2, 8, 4>>;
// t3 == std::integer_sequence<int, 1, 3, 9, 5>>

// apply a function to elements until the specific criteria isn't satisfied
using t4 = transform_while_t<succ, is_even, std::integer_sequence<int>,
           std::integer_sequence<int, 0, 2, 4, 2, 1, 8, 4>>;
// t4 == std::integer_sequence<int, 1, 3, 5, 3>

// turn a tuple to a integer sequence that consist of the size of the elements
using t5 = to_sequence_t<std::tuple<int, double>>;
// t5 == std::integer_sequence<int, sizeof(int), sizeof(double)>

// turn a integer sequence to a tuple that consist of the value of the elements
using t6 = to_tuple_t<std::integer_sequence<int, 4, 8>>;
// t6 == std::tuple<c_4, c_8>

// increase elements
using seq = std::integer_sequence<int, 2, 7, 4>;
using i1 = increase_t<seq, 3>;
using i2 = increase_t<seq, -3>;
// i1 == std::integer_sequence<int, 5, 10, 7>
// i2 == std::integer_sequence<int, -1, 4, 1>

// wrap elements
using w = wrapin_t<std::type_identity, int, double, short>;
// w == std::tuple<std::type_identity<int>, std::type_identity<double>, std::type_identity<short>>
```

### Tuple operations
```cpp
auto t = std::make_tuple(1, 2, 3.0, 2, 4);

// invoke the callable object f with a tuple of arguments
auto sum = tuple_apply([](auto... args){ return (args + ...); }, t);
// sum == 1 + 2 + 3.0 + 2 + 4

// reverse the tuple
auto r1 = tuple_reverse(t);
// r1 == std::make_tuple(4, 2, 3.0, 2, 1)

// add elements at the front
auto p1 = tuple_prepend(t, 0, 5);
// p1 == std::make_tuple(0, 5, 1, 2, 3.0, 2, 4);

// add elements at the back
auto p2 = tuple_append(t, 0, 5);
// p2 == std::make_tuple(1, 2, 3.0, 2, 4, 0, 5);

// remove the second element
auto r2 = tuple_remove<1>(t);
// r2 == std::make_tuple(1, 3.0, 2, 4);

// swap the first and third elements
auto s1 = tuple_swap<0, 2>(t);
// s1 == std::make_tuple(3.0, 2, 1, 2, 4);

// get elements in the range [begin, end)
auto i1 = tuple_range<1, 4>(t);
// i2 == std::make_tuple(2, 3.0, 2)

// remove elements in the range [begin, end)
auto e = tuple_erase<1, 4>(t);
// e == std::make_tuple(1, 4)

// reverse elements in the range [begin, end)
auto r3 = tuple_reverse_range<2, 5>(t);
// r3 == std::make_tuple(1, 2, 4, 2, 3.0)

// insert elements at specific index
auto i2 = tuple_insert<2>(t, 9, -7);
// i2 == std::make_tuple(1, 2, 9, -7, 3.0, 2, 4)

// replace element at specific index
auto r4 = tuple_replace<3>(t, 7);
// r4 == std::make_tuple(1, 2, 3.0, 7, 4)

// replace elements of specific value
auto r5 = tuple_replace(t, 2, 6);
// r5 == std::make_tuple(1, 6, 3.0, 6, 4)

/* rearrange the elements in the range [begin, middle, end), in such a way that
 * the elements in the range [middle, end) comes first,
 * the elements in the range [begin, middle) comes last.
 */
auto r6 = tuple_rotate<0, 2, 4>(t);
// r6 == std::make_tuple(3.0, 2, 1, 2, 4)

// shift left two elements
auto s2 = tuple_shift_left<2>(t);
// s2 == std::make_tuple(3.0, 2, 4, 1, 2)

// shift right two elements
auto s3 = tuple_shift_right<2>(t);
// s3 == std::make_tuple(2, 4, 1, 2, 3.0)

// get the first three elements
auto t1 = tuple_take_front<3>(t);
// t1 == std::make_tuple(1, 2, 3.0)

// get the last three elements
auto t2 = tuple_take_back<3>(t);
// t2 == std::make_tuple(3.0, 2, 4)

// remove the first three elements
auto t3 = tuple_drop_front<3>(t);
// t3 == std::make_tuple(2, 4)

// remove the last three elements
auto t4 = tuple_drop_back<3>(t);
// t4 == std::make_tuple(1, 2)

// cartesian product of two tuples
auto p = tuple_cartesian_product(std::make_tuple(2, 'T'), std::make_tuple(4.0, 6));
// p == std::make_tuple(std::make_pair(2, 4.0), std::make_pair(2, 6),
//                      std::make_pair('T', 4.0), std::make_pair('T', 6))

// tuple zip
auto z = tuple_zip(std::make_tuple(5, 4), std::make_tuple(2, 3));
// z == std::make_tuple(std::make_tuple(5, 2), std::make_tuple(4, 3))

// tuple transpose
auto t = tuple_transpose(std::make_tuple(std::make_tuple(5, 4), std::make_tuple(2, 3)));
// t == z

// fill elements since specific index
auto t5 = std::make_tuple(2, 3.0, 4, 5, 8);
tuple_fill<2>(t5, 2, 7);
// t5 == std::make_tuple(2, 3.0, 2, 7, 8)

// takes a single element in a tuple and replicates it to 
// create another tuple with some number of copies of that element
auto t6 = tuple_splat<3, 4>(t5);
// t6 == std::make_tuple(7, 7, 7, 7)

// delete all duplicate elements, keep the last appearance
auto t7 = tuple_unique(std::make_tuple(1, 's', 7.0, 1, 's'));
// t7 == std::make_tuple(7.0, 1, 's')
```
