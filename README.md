## ![monster logo](https://raw.githubusercontent.com/deepgrace/monster/master/logo/monster.png)
[![996.icu](https://img.shields.io/badge/link-996.icu-red.svg)](https://996.icu)
[![LICENSE](https://img.shields.io/badge/license-Anti%20996-blue.svg)](https://github.com/996icu/996.ICU/blob/master/LICENSE)
# Advanced C++ Template MetaProgramming Framework 

## Overview
```cpp
#include <vector>
#include <iostream>
#include <forward_list>
#include <monster.hpp>

using namespace monster;

int main(int argc, char* argv[])
{
    static_assert(std::is_same_v<kmp_t<std::tuple<double>,
                  std::tuple<int, float, double, int, int, double, int>>, std::index_sequence<2, 5>>);

    static_assert(std::is_same_v<kmp_t<std::tuple<int, double, int, double>,
                  std::tuple<int, float, int, double, int, double, double, char, int, double, int, double, int>>, std::index_sequence<2, 8>>);

    static_assert(std::is_same_v<kmp_t<std::tuple<char>,
                  std::tuple<int, float, double, int, int, double, int>>, std::index_sequence<>>);

    static_assert(std::is_same_v<kmp_t<std::integer_sequence<int, 1, 3, 1, 3, 1>,
                  std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>, std::index_sequence<3, 10>>);

    static_assert(std::is_same_v<kmp_t<std::integer_sequence<int, 2, 1, 3, 1, 3, 1>,
                  std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>, std::index_sequence<>>);

    static_assert(int_<1>::value == 1);
    static_assert(typev<int_<2>> == 2);

    static_assert(negav<has_value<int>>);
    static_assert(has_value_v<std::true_type>);

    static_assert(std::is_same_v<identity_t<int>, int>);
    static_assert(std::is_same_v<wrapper_t<3, int>, identity<identity<identity<int>>>>);

    static_assert(std::is_same_v<last_t<int, double, char>, char>);
    static_assert(std::is_same_v<alias_t<int>, int>);

    static_assert(contains_v<int, double, char, float, int>);
    static_assert(includes_v<1, -2, 3, 0, 1>);

    static_assert(is_unique_type_v<int, double, char, float>);
    static_assert(!is_unique_value_v<1, 2, 2, 3, 4>);

    static_assert(is_unique_v<std::tuple<int, double, char, float>>);
    static_assert(is_unique_v<std::integer_sequence<int, 1, 2, 3, 4>>);

    static_assert(!is_iterable_v<int>);
    static_assert(is_iterable_v<std::vector<int>>);

    static_assert(!is_container_v<int>);
    static_assert(is_container_v<std::string>);

    static_assert(!is_instance_of_v<std::tuple, int>);
    static_assert(is_instance_of_v<std::tuple, std::tuple<int>>);

    static_assert(!is_sequence_of_v<std::integer_sequence, int>);
    static_assert(is_sequence_of_v<std::integer_sequence, std::index_sequence<1, 2, 3>>);

    static_assert(sizeof_t_v<int_<8>> == 8);
    static_assert(sizeof_t_v<int> == sizeof(int));

    static_assert(sizeof_t_v<std::tuple<int, char, double>> == 3);
    static_assert(sizeof_t_v<std::index_sequence<1, 2, 0, 4>> == 4);

    static_assert(less_v<char, int>);

    static_assert(std::is_same_v<base_type_t<int>, int>);
    static_assert(std::is_same_v<base_type_t<std::tuple<int, char>>, std::tuple<>>);
    static_assert(std::is_same_v<base_type_t<std::integer_sequence<int, 1, 2, 4>>, std::integer_sequence<int>>);

    static_assert(homogeneous<0, 1, 2, 4>::size() == 4);
    static_assert(get_v<1, std::integer_sequence<int, 1, 2, 4>> == 2);
    static_assert(sum_v<std::integer_sequence<int, 1, 2, 4>> == 7);
    static_assert(pred_v<int_<3>> == 2);
    static_assert(succ_v<int_<3>> == 4);

    static_assert(std::is_same_v<prev_t<2, std::tuple<int, double, char, float, char>>, double>);
    static_assert(std::is_same_v<next_t<2, std::tuple<int, double, char, float, char>>, float>);
    static_assert(prev_v<1, std::integer_sequence<int, 7, 3, -1, 2, 4>> == 7);
    static_assert(next_v<1, std::integer_sequence<int, 7, 3, -1, 2, 4>> == -1);

    static_assert(std::is_same_v<unique_t<std::tuple<int, char, int, double>> , std::tuple<char, int, double>>);
    static_assert(std::is_same_v<unique_t<std::integer_sequence<int, 2, 1, 2, 3, 4, 3>>, std::integer_sequence<int, 1, 2, 4, 3>>);

    static_assert(std::is_same_v<call_t<metaf<std::add_pointer>, int*>, int**>);
    static_assert(std::is_same_v<folded_t<max, int, char, double>, double>);
    static_assert(std::is_same_v<folded_t<min, int, char, double>, char>);

    static_assert(std::is_same_v<curried_t<std::add_pointer, std::tuple, int*, double, char>, std::tuple<int**, double*, char*>>);
    static_assert(std::is_same_v<currying_t<std::add_pointer, int*, double, char>, std::tuple<int**, double*, char*>>);

    static_assert(negav<eval_t<folded_t, std::conjunction, std::tuple<std::false_type, std::true_type>, std::true_type>>);

    static_assert(std::is_same_v<invert_t<>, invert<>>);
    static_assert(std::is_same_v<invert_t<char>, char>);
    static_assert(std::is_same_v<invert_t<char, double>, invert<double, char>>);
    static_assert(std::is_same_v<invert_t<int, char, double, float>, invert<float, double, char, int>>);

    using nested = std::tuple<std::tuple<char, short>, std::tuple<char, int>>;
    using reversed = reverse_t<eval_t<currying_t, reverse_t, nested>>;
    static_assert(std::is_same_v<reversed, reverse_t<std::tuple<reverse_t<std::tuple<char, short>>, reverse_t<std::tuple<char, int>>>>>);

    using integer_t = std::integer_sequence<int, 2, 7, 4>;
    static_assert(std::is_same_v<increase_t<integer_t, 3>, std::integer_sequence<int, 5, 10, 7>>);
    static_assert(std::is_same_v<increase_t<integer_t, -3>, std::integer_sequence<int, -1, 4, 1>>);

    using add_one_t = eval_t<currying_t, succ, to_tuple_t<integer_t>>;
    static_assert(std::is_same_v<add_one_t, std::tuple<int_<3, int>, int_<8, int>, int_<5, int>>>);

    static_assert(std::is_same_v<next_slide_indices_t<2, 7, std::integer_sequence<int, 2, 3, 4>>, std::integer_sequence<int, 3, 4, 5>>);
    static_assert(std::is_same_v<prev_slide_indices_t<2, 7, std::integer_sequence<int, 3, 4, 5>>, std::integer_sequence<int, 2, 3, 4>>);

    using indices = std::tuple<std::integer_sequence<int, 2, 3, 4>,
                               std::integer_sequence<int, 3, 4, 5>,
                               std::integer_sequence<int, 4, 5, 6>>;

    static_assert(std::is_same_v<next_slide_indices_list<2, 7, std::integer_sequence<int, 2, 3, 4>>, indices>);

    static_assert(std::is_same_v<prev_slide_indices_list<2, 7, std::integer_sequence<int, 4, 5, 6>>, reverse_t<indices>>);

    static_assert(std::is_same_v<slide_list_t<3, std::integer_sequence<int, 1, 2, 3, 4>>, std::tuple<
                  std::integer_sequence<int, 1, 2, 3>,
                  std::integer_sequence<int, 2, 3, 4>>>);

    static_assert(std::is_same_v<slide_list_t<3, std::tuple<int, char, double, float>>, std::tuple<
                  std::tuple<int, char, double>,
                  std::tuple<char, double, float>>>);

    static_assert(std::is_same_v<on_t<std::add_pointer, std::tuple, int, double, char*>, std::tuple<int*, double*, char**>>);

    static_assert(first_of_v<is_tuple, std::tuple<int, char, std::tuple<double>, float>> == 2);
    static_assert(last_of_v<equal<2>::template apply, std::integer_sequence<int, 1, 2, 3, 2, 4, 1, 2>> == 6);

    static_assert(any_of_v<is_odd, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, 0, 10>);
    static_assert(any_of_v<is_tuple, std::tuple<int, char, std::tuple<char>, double, std::tuple<uint64_t>, int, std::tuple<float>>, 0, 7>);

    static_assert(std::is_same_v<nth_type_t<2, int, double, char*, float>, char*>);
    static_assert(std::is_same_v<range_generator_t<size_t, 1, 4>, index_list<size_t, 1, 2, 3>>);

    fmap([](auto& v){ std::cout << v << std::endl; }, 1, 2.3, "string", 'x');

    static_assert(std::is_same_v<concat_t<std::tuple<int, char>, std::tuple<double>>, std::tuple<int, char, double>>);

    using type = std::tuple<int, char, std::tuple<char>, double, std::tuple<double>, float, char>;
    static_assert(std::is_same_v<remove_if_t<is_tuple, type, 1, 5>, std::tuple<int, char, double, float, char>>);

    static_assert(std::is_same_v<remove_t<is_tuple, type>, std::tuple<int, char, double, float, char>>);
    static_assert(std::is_same_v<remove_t<negaf<is_tuple>::template apply, type>, std::tuple<std::tuple<char>, std::tuple<double>>>);

    static_assert(std::is_same_v<remove_t<is_odd, std::integer_sequence<int, 0, 3, 2, 4, 7, 3>>, std::integer_sequence<int, 0, 2, 4>>);
    static_assert(std::is_same_v<remove_t<is_even, std::integer_sequence<int, 0, 3, 2, 4, 7, 3>>, std::integer_sequence<int, 3, 7, 3>>);

    static_assert(std::is_same_v<maximum_t<std::tuple<short, int, char>>, int>);
    static_assert(std::is_same_v<minimum_t<std::tuple<short, int, char>>, char>);
    static_assert(maximum_v<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>> == 4);
    static_assert(minimum_v<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>> == -2);

    static_assert(std::is_same_v<min_t<char, double>, char>);
    static_assert(std::is_same_v<max_t<char, double>, double>);

    static_assert(std::is_same_v<min_type_t<short, int, char>, char>);
    static_assert(std::is_same_v<max_type_t<short, int, char>, int>);

    static_assert(std::is_same_v<expand_t<element, std::tuple<int, float, char, double>, std::index_sequence<0, 2>>, std::tuple<int, char>>);
    static_assert(std::is_same_v<expand_t<get, std::integer_sequence<int, -1, 3, 7, 0, 5>, std::index_sequence<1, 3, 0, 4>>,
                  std::integer_sequence<int, 3, 0, -1, 5>>);

    static_assert(std::is_same_v<to_sequence_t<std::tuple<int, double>>, std::integer_sequence<int, 4, 8>>);
    static_assert(std::is_same_v<to_sequence_t<std::index_sequence<4, 8>>, std::index_sequence<4, 8>>);
    static_assert(std::is_same_v<to_tuple_t<std::integer_sequence<int, 4, 8>>, std::tuple<int_<4>, int_<8>>>);
    static_assert(std::is_same_v<to_tuple_t<std::tuple<int, double>>, std::tuple<int, double>>);

    static_assert(std::is_same_v<swap_t<1, 3, std::tuple<int, double, char, float>>, std::tuple<int, float, char, double>>);
    static_assert(std::is_same_v<swap_t<0, 2, std::integer_sequence<int, 1, -2, 7, 4>>, std::integer_sequence<int, 7, -2, 1, 4>>);

    static_assert(std::is_same_v<swap_ranges_fst<1, 4, std::integer_sequence<int, 0, 1, 2, 3, 4, 5>,
                  std::integer_sequence<int, -1, -2, -3, -4, -5>>, std::integer_sequence<int, 0, -2, -3, -4, 4, 5>>);
    static_assert(std::is_same_v<swap_ranges_snd<0, 3, std::integer_sequence<int, 1, 2, 3, 4>,
                  std::integer_sequence<int, -1, -2, -3, -4, -5>>, std::integer_sequence<int, 1, 2, 3, -4, -5>>);

    static_assert(within_v<2, -2, 4>);
    static_assert(!within_v<5, -2, 4>);

    static_assert(std::is_same_v<element_t<1, std::tuple<char, double, int>>, double>);
    static_assert(std::is_same_v<element_t<1, std::integer_sequence<int, 1, -2, 7, 4>>, int_<-2>>);

    static_assert(std::is_same_v<gsub_t<1, 5, int, float, std::tuple<int, char, int, double, int, float, char>>,
                  std::tuple<int, char, float, double, float, float, char>>);
    static_assert(std::is_same_v<gsub_t<1, 5, int_<-2>, int_<-6>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
                  std::integer_sequence<int, 1, 3, -6, 1, 7, 1, 4, 6>>);

    static_assert(std::is_same_v<substitute_t<2, 5, int, std::tuple<int, char, int, double, int, float, char>>,
                  std::tuple<int, char, int, int, int, float, char>>);
    static_assert(std::is_same_v<substitute_t<2, 5, int_<-2>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
                  std::integer_sequence<int, 1, 3, -2, -2, -2, 1, 4, 6>>);

    static_assert(std::is_same_v<exchange_t<2, int, std::tuple<int, int, char, double, int, float, char>>,
                  std::tuple<int, int, int, double, int, float, char>>);
    static_assert(std::is_same_v<exchange_t<1, int_<-2>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
                  std::integer_sequence<int, 1, -2, -2, 1, 7, 1, 4, 6>>);

    static_assert(std::is_same_v<sub_t<3, 8, range_generator_t<int, -2, 3>>, index_list<int, -2, -1, 0, 8, 2>>);
    static_assert(std::is_same_v<sub_t<2, 3, index_list<size_t, 3, 4, 0, 5, 2>>, index_list<size_t, 3, 4, 3, 5, 2>>);
    static_assert(std::is_same_v<sub_t<4, -3, std::integer_sequence<int, -1, 8, 0, 2, 4, 7>>, std::integer_sequence<int, -1, 8, 0, 2, -3, 7>>);

    static_assert(std::is_same_v<range_t<1, 4, int>, int>);
    static_assert(std::is_same_v<range_t<1, 4, std::tuple<int, char, float, double, int>>, std::tuple<char, float, double>>);
    static_assert(std::is_same_v<range_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>, std::integer_sequence<int, 2, -2, 4>>);

    static_assert(std::is_same_v<reverse_t<double>, double>);
    static_assert(std::is_same_v<reverse_t<std::tuple<float, double, int>>, std::tuple<int, double, float>>);
    static_assert(std::is_same_v<reverse_t<std::integer_sequence<int, 1, 2, -2>>, std::integer_sequence<int, -2, 2, 1>>);

    static_assert(std::is_same_v<extent_t<1, 4, char>, char>);
    static_assert(std::is_same_v<extent_t<1, 4, std::tuple<int, char, float, double, int, char>>, std::tuple<double, float, char>>);
    static_assert(std::is_same_v<extent_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>, std::integer_sequence<int, 4, -2, 2>>);

    static_assert(std::is_same_v<erase_t<2, 5, std::tuple<int, char, float, double, int, char>>, std::tuple<int, char, char>>);
    static_assert(std::is_same_v<erase_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>, std::integer_sequence<int, 1, 3, 5>>);

    static_assert(std::is_same_v<drop_t<2, std::tuple<int, double, int, char>>, std::tuple<int, double, char>>);
    static_assert(std::is_same_v<drop_t<1, std::integer_sequence<int, 1, 2, -2, 4, 5>>, std::integer_sequence<int, 1, -2, 4, 5>>);

    static_assert(std::is_same_v<degree_t<1, 4, std::tuple<int, char, float, double, int, char>>, std::tuple<int, double, float>>);
    static_assert(std::is_same_v<degree_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>, std::integer_sequence<int, 3, 4, -2>>);

    static_assert(std::is_same_v<reverse_range_t<1, 4, float>, float>);
    static_assert(std::is_same_v<reverse_range_t<1, 4, std::tuple<int, char, float, double, int, char>>, std::tuple<int, double, float, char, int, char>>);
    static_assert(std::is_same_v<reverse_range_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>, std::integer_sequence<int, 1, 4, -2, 2, 3, 5>>);

    static_assert(tuple_index_v<int, std::tuple<char, float, double, int, char>> == 3);

    static_assert(binary_search_v<double, std::tuple<short, int, double>>);
    static_assert(binary_search_v<int_<7>, std::integer_sequence<int, -2, 0, 3, 7, 8>>);

    static_assert(std::is_same_v<inner_dot_t<std::integer_sequence<int, -3, 1, 2, 4, 5>, std::integer_sequence<int, 2, 4, -3, 4>>,
                  std::integer_sequence<int, -6, 4, -6, 16>>);

    overload_sequence element_count
    (
        [](auto&&) { return 1;},
        [](auto&& v) -> decltype(v.size())
        {
             return std::forward<decltype(v)>(v).size();
        },
        [](auto&& v) -> type_t<std::size_t, decltype(std::begin(v)), decltype(std::end(v))>
        {
            return std::distance(std::begin(std::forward<decltype(v)>(v)), std::end(std::forward<decltype(v)>(v)));
        }
    );

    element_count(42);
    element_count(std::vector({1 , 2, 3, 4}));
    element_count(std::forward_list({1 , 2, 3}));

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

    loop<3>([](auto N, auto&& v)
    {
        std::cout << N << " " << v << std::endl;
    }, 4);

    iterate<4>([]
    {
        std::cout << "x" << std::endl;
    });

    static_assert(std::is_same_v<infinite_call_t<4, int, std::add_pointer>, int****>);
    static_assert(std::is_same_v<multi_level_pointer_t<4, int>, int****>);

    static_assert(std::is_same_v<pop_front_t<std::tuple<float, double, int>>, std::tuple<double, int>>);
    static_assert(std::is_same_v<pop_front_t<std::integer_sequence<int, 1, 2, 3>>, std::integer_sequence<int, 2, 3>>);
    static_assert(std::is_same_v<pop_back_t<std::tuple<float, double, int>>, std::tuple<float, double>>);
    static_assert(std::is_same_v<pop_back_t<std::integer_sequence<int, 1, 2, 3>>, std::integer_sequence<int, 1, 2>>);

    static_assert(std::is_same_v<prepend_t<std::tuple<float, double, int>, int, float>, std::tuple<int, float, float, double, int>>);
    static_assert(std::is_same_v<prepend_t<std::integer_sequence<int, 1, 2, -2>, int_<4>, int_<3>>, std::integer_sequence<int, 4, 3, 1, 2, -2>>);

    static_assert(std::is_same_v<append_t<std::tuple<float, double, int>, float, char>, std::tuple<float, double, int, float, char>>);
    static_assert(std::is_same_v<append_t<std::integer_sequence<int, 1, 2, -2>, int_<4>, int_<3>>, std::integer_sequence<int, 1, 2, -2, 4, 3>>);

    static_assert(std::is_same_v<replace_t<1, 3, std::tuple<char, float, double, int>, float, char>, std::tuple<char, float, char, int>>);
    static_assert(std::is_same_v<replace_t<1, 3, std::integer_sequence<int, 4, 1, 2, -2>, int_<4>, int_<3>>, std::integer_sequence<int, 4, 4, 3, -2>>);

    static_assert(std::is_same_v<insert_t<2, std::tuple<float, double, int>, float, char>, std::tuple<float, double, float, char, int>>);
    static_assert(std::is_same_v<insert_t<1, std::integer_sequence<int, 1, 2, -2>, int_<0>, int_<4>>, std::integer_sequence<int, 1, 0, 4, 2, -2>>);

    static_assert(std::is_same_v<fill_t<3, int>, std::tuple<int, int, int>>);
    static_assert(std::is_same_v<fill_t<3, int_<1>>, std::integer_sequence<int, 1, 1, 1>>);

    static_assert(std::is_same_v<rotate_t<0, 2, 5, std::tuple<int, char, double, float, int64_t>>, std::tuple<double, float, int64_t, int, char>>);
    static_assert(std::is_same_v<rotate_t<0, 2, 5, std::integer_sequence<int, 1, 2, 3, 4, 5>>, std::integer_sequence<int, 3, 4, 5, 1, 2>>);
    static_assert(std::is_same_v<rotate_t<2, 4, 7, std::integer_sequence<int, 9, 8, 1, 2, 3, 4, 5, 7, 6>>,
                  std::integer_sequence<int, 9, 8, 3, 4, 5, 1, 2, 7, 6>>);

    static_assert(std::is_same_v<shift_t<2, std::tuple<int, char, double, float, int64_t>>, std::tuple<double, float, int64_t>>);
    static_assert(std::is_same_v<shift_t<2, std::integer_sequence<int, 1, 2, 3, 4, 5>>, std::integer_sequence<int, 3, 4, 5>>);

    static_assert(std::is_same_v<zero_sequence_t<int, 3>, std::integer_sequence<int, 0, 0, 0>>);

    static_assert(std::is_same_v<integer_sequence_n<int, 4, 2, 0>, std::integer_sequence<int, 2, 2, 2, 2>>);
    static_assert(std::is_same_v<integer_sequence_n<int, 4, 2, 1>, std::integer_sequence<int, 2, 3, 4, 5>>);

    static_assert(std::is_same_v<odd_t<std::tuple<int, char, double, int, char>>, std::tuple<char, int>>);
    static_assert(std::is_same_v<odd_t<std::integer_sequence<int, 1, 9, 0, 4, 2>>, std::integer_sequence<int, 9, 4>>);

    static_assert(std::is_same_v<even_t<std::tuple<int, char, double, int, char>>, std::tuple<int, double, char>>);
    static_assert(std::is_same_v<even_t<std::integer_sequence<int, 1, 9, 0, 4, 2>>, std::integer_sequence<int, 1, 0, 2>>);

    static_assert(count_v<int_<1>, std::integer_sequence<int, 1, 2, 3, 1>> == 2);
    static_assert(count_v<char, std::tuple<char, double, char, int, float, char, int, double>> == 3);

    static_assert(mode_v<std::integer_sequence<int, 1, 2, 3, 1>> == 1);
    static_assert(std::is_same_v<monster::mode_t<std::tuple<char, double, char, double, int, float, char>>, char>);
    static_assert(std::is_same_v<transform_t<pointer_type_of, std::tuple<int, double, char*>>, std::tuple<int*, double*, char**>>);

    static_assert(is_palindromic_v<std::tuple<int, double, int, int, double, int>>);
    static_assert(is_palindromic_v<std::integer_sequence<int, 3, 0, 2, 1, 2, 0, 3>>);
    static_assert(!is_palindromic_v<std::integer_sequence<int, 0, 2, 1, 2, 0, 3>>);
    static_assert(!is_palindromic_v<std::tuple<int, double, char, int, int, double, int>>);

    static_assert(subset_v<std::integer_sequence<int, 4>, std::integer_sequence<int, 4>>);
    static_assert(!subset_v<std::integer_sequence<int, 4, 5, 6>, std::integer_sequence<int, 4>>);
    static_assert(subset_v<std::integer_sequence<int, 4, 5, 6>, std::integer_sequence<int, 1, 2, 3, 4, 5, 6, 7>>);
    static_assert(subset_v<std::tuple<float, char, double>, std::tuple<int, double, char, float, char, double, int>>);

    static_assert(std::is_same_v<cartesian_product_t<std::tuple<int, double>, std::tuple<char, float>>,
                  std::tuple<int, char, int, float, double ,char, double, float>>);
    static_assert(std::is_same_v<cartesian_product_t<std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>,
                  std::integer_sequence<int, 1, 3, 1, 4, 1, 5, 2, 3, 2, 4, 2, 5>>);

    static_assert(std::is_same_v<zip_t<std::tuple<int, double>, std::tuple<char, float, nullptr_t>>, std::tuple<int, char, double, float>>);
    static_assert(std::is_same_v<zip_t<std::integer_sequence<int, 1>, std::integer_sequence<int, 3>>, std::integer_sequence<int, 1, 3>>);
    static_assert(std::is_same_v<zip_t<std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>, std::integer_sequence<int, 1, 3, 2, 4>>);

    static_assert(std::is_same_v<next_permutation_t<std::tuple<char, int, double>>, std::tuple<char, double, int>>);
    static_assert(std::is_same_v<next_permutation_t<std::tuple<char, double, int>>, std::tuple<int, char, double>>);
    static_assert(std::is_same_v<next_permutation_t<std::tuple<int, char, double>>, std::tuple<int, double, char>>);
    static_assert(std::is_same_v<next_permutation_t<std::tuple<int, double, char>>, std::tuple<double, char, int>>);
    static_assert(std::is_same_v<next_permutation_t<std::tuple<double, char, int>>, std::tuple<double, int, char>>);
    static_assert(std::is_same_v<next_permutation_t<std::tuple<double, int, char>>, std::tuple<double, int, char>>);

    using list_t = std::tuple<std::tuple<char, int, double>,
                              std::tuple<char, double, int>,
                              std::tuple<int, char, double>,
                              std::tuple<int, double, char>,
                              std::tuple<double, char, int>,
                              std::tuple<double, int, char>>;

    static_assert(std::is_same_v<next_permutation_list<std::tuple<char, int, double>>, list_t>);

    static_assert(std::is_same_v<next_permutation_list<std::integer_sequence<int, 1, 2, 3>>, std::tuple<
                  std::integer_sequence<int, 1, 2, 3>,
                  std::integer_sequence<int, 1, 3, 2>,
                  std::integer_sequence<int, 2, 1, 3>,
                  std::integer_sequence<int, 2, 3, 1>,
                  std::integer_sequence<int, 3, 1, 2>,
                  std::integer_sequence<int, 3, 2, 1>>>);

    static_assert(std::is_same_v<prev_permutation_list<std::tuple<double, int, char>>, reverse_t<list_t>>);
    static_assert(std::is_same_v<next_partial_permutation_list<3, std::tuple<char, int, double>>, list_t>);
    static_assert(std::is_same_v<prev_partial_permutation_list<3, std::tuple<double, int, char>>, reverse_t<list_t>>);

    using list_s = std::tuple<std::tuple<char, int>,
                              std::tuple<char, double>,
                              std::tuple<int, char>,
                              std::tuple<int, double>,
                              std::tuple<double, char>,
                              std::tuple<double, int>>;

    static_assert(std::is_same_v<next_partial_permutation_list<2, std::tuple<char, int, double>>, list_s>);
    static_assert(std::is_same_v<prev_partial_permutation_list<2, std::tuple<double, int, char>>, reverse_t<list_s>>);

    using comb0 = std::tuple<char, short, int, double>;
    static_assert(std::is_same_v<range_t<0, 2, comb0>, std::tuple<char, short>>);
    using comb1 = next_combination_t<2, comb0>;
    static_assert(std::is_same_v<range_t<0, 2, comb1>, std::tuple<char, int>>);
    using comb2 = next_combination_t<2, comb1>;
    static_assert(std::is_same_v<range_t<0, 2, comb2>, std::tuple<char, double>>);
    using comb3 = next_combination_t<2, comb2>;
    static_assert(std::is_same_v<range_t<0, 2, comb3>, std::tuple<short, int>>);

    using comb_list = std::tuple<std::tuple<char, short>,
                              std::tuple<char, int>,
                              std::tuple<char, double>,
                              std::tuple<short, int>,
                              std::tuple<short, double>,
                              std::tuple<int, double>>;

    static_assert(std::is_same_v<next_combination_list<2, std::tuple<char, short, int, double>>, comb_list>);

    static_assert(std::is_same_v<next_combination_list<2, std::integer_sequence<int, 1, 2, 3, 4>>, std::tuple<
                  std::integer_sequence<int, 1, 2>,
                  std::integer_sequence<int, 1, 3>,
                  std::integer_sequence<int, 1, 4>,
                  std::integer_sequence<int, 2, 3>,
                  std::integer_sequence<int, 2, 4>,
                  std::integer_sequence<int, 3, 4>>>);

    static_assert(std::is_same_v<prev_combination_list<2, std::tuple<double, int, short, char>>,
                   std::tuple<std::tuple<double, int>,
                              std::tuple<double, short>,
                              std::tuple<double, char>,
                              std::tuple<int, short>,
                              std::tuple<int, char>,
                              std::tuple<short, char>>>);

    using counts_list = std::tuple<std::integer_sequence<int, 0, 0, 2>,
                                   std::integer_sequence<int, 0, 1, 1>,
                                   std::integer_sequence<int, 0, 2, 0>,
                                   std::integer_sequence<int, 1, 0, 1>,
                                   std::integer_sequence<int, 1, 1, 0>,
                                   std::integer_sequence<int, 2, 0, 0>>;

    static_assert(std::is_same_v<next_combination_counts_list<0, 3, std::integer_sequence<int, 0, 0, 2>>, counts_list>);
    static_assert(std::is_same_v<prev_combination_counts_list<0, 3, std::integer_sequence<int, 2, 0, 0>>, reverse_t<counts_list>>);

    using integer = monster::integer_sequence_n<int, 3, 1, 0>;

    using indices_list = std::tuple<std::integer_sequence<int, 1, 1, 1>,
                                    std::integer_sequence<int, 1, 1, 2>,
                                    std::integer_sequence<int, 1, 2, 1>,
                                    std::integer_sequence<int, 1, 2, 2>,
                                    std::integer_sequence<int, 2, 1, 1>,
                                    std::integer_sequence<int, 2, 1, 2>,
                                    std::integer_sequence<int, 2, 2, 1>,
                                    std::integer_sequence<int, 2, 2, 2>>;

    static_assert(std::is_same_v<next_hypercube_indices_list<1, 3, integer>, indices_list>);
    static_assert(std::is_same_v<prev_hypercube_indices_list<1, 3, integer_sequence_n<int, 3, 2, 0>>, reverse_t<indices_list>>);

    static_assert(std::is_same_v<select_t<2, std::tuple<uint64_t, int, double, int, char>>, int>);
    static_assert(std::is_same_v<select_t<2, std::integer_sequence<int, 0, 3, 2, 1, 2, 6>>, int_<3, int>>);

    static_assert(std::is_same_v<stable_partition_t<0, 2, std::tuple<int, std::tuple<int>>, is_tuple>, std::tuple<std::tuple<int>, int>>);

    static_assert(std::is_same_v<stable_partition_t<1, 6,
                  std::tuple<int, char, std::tuple<char>, double, std::tuple<uint64_t>, int, std::tuple<float>>, is_tuple>,
                  std::tuple<int, std::tuple<char>, std::tuple<uint64_t>, char, double, int, std::tuple<float>>>);

    static_assert(std::is_same_v<stable_partition_t<1, 7, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, is_odd>,
                  std::integer_sequence<int, 1, 3, 7, 1, 2, 8, 0, -2, 4, 5>>);

    static_assert(std::is_same_v<stable_partition_t<1, 6, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, is_even>,
                  std::integer_sequence<int, 1, 2, 8, 0, 3, 7, 1, -2, 4, 5>>);

    static_assert(std::is_same_v<counting_sort_t<std::tuple<int, char, double, uint64_t, int>>, std::tuple<char, int, int, double, uint64_t>>);

    static_assert(std::is_same_v<stooge_sort_t<std::tuple<int, double, int, float, char, double>>,
                  std::tuple<char, int, int, float, double, double>>);

    static_assert(std::is_same_v<bubble_sort_t<std::tuple<int, double, char, int, char, float, double>>,
                  std::tuple<char, char, int, int, float, double, double>>);

    static_assert(std::is_same_v<selection_sort_t<std::tuple<int, int, double, char, int, char, double>>,
                  std::tuple<char, char, int, int, int, double, double>>);

    static_assert(std::is_same_v<quick_sort_t<std::tuple<double, uint64_t, float, char, char, double>>,
                  std::tuple<char, char, float, double, uint64_t, double>>);

    static_assert(std::is_same_v<stable_sort_t<std::tuple<double, uint64_t, double, float, int, char, float, char, double>>,
                  std::tuple<char, char, float, int, float, double, uint64_t, double, double>>);

    static_assert(std::is_same_v<insertion_sort_t<std::tuple<float, int, int, double, char, int, float, char, double>>,
                  std::tuple<char, char, float, int, int, int, float, double, double>>);

    static_assert(std::is_same_v<merge_sort_t<std::tuple<double, char, double, int, float>>, std::tuple<char, int, float, double, double>>);

    static_assert(std::is_same_v<heap_sort_t<std::tuple<uint64_t, double, float, char, char, double>>,
                  std::tuple<char, char, float, double, double, uint64_t>>);

    using input = std::integer_sequence<int, 2, 0, -3, 4, -7, 5>;
    using output = std::integer_sequence<int, -7, -3, 0, 2, 4, 5>;

    static_assert(std::is_same_v<counting_sort_t<input>, output>);
    static_assert(std::is_same_v<stooge_sort_t<input>, output>);
    static_assert(std::is_same_v<bubble_sort_t<input>, output>);
    static_assert(std::is_same_v<selection_sort_t<input>, output>);
    static_assert(std::is_same_v<quick_sort_t<input>, output>);
    static_assert(std::is_same_v<insertion_sort_t<input>, output>);
    static_assert(std::is_same_v<merge_sort_t<input>, output>);
    static_assert(std::is_same_v<heap_sort_t<input>, output>);

    static_assert(sort_v<input, output, stable_sort, counting_sort, stooge_sort, bubble_sort, selection_sort, quick_sort, insertion_sort, merge_sort, heap_sort>);

    return 0;
}
```
