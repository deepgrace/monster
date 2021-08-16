# Tutorial
```cpp
#include <vector>
#include <iostream>
#include <forward_list>
#include <monster.hpp>

using namespace monster;

template <typename ...> struct T0 {};
template <typename ...> struct T1 {};
template <typename ...> struct T2 {};
template <typename ...> struct T3 {};
template <typename ...> struct T4 {};

template <typename T, typename U>
struct comp
{
    static constexpr auto value = first_v<T> - first_v<U>;
};

template <typename T, typename U>
struct comb : std::type_identity<pair_v<first_v<T>, second_v<T> + second_v<U>>>
{
};

template <template <typename ...> typename f, typename T, typename... Args>
struct nest
{
    static constexpr auto value = sizeof...(Args) == 0;

    using curr = std::conditional_t<value, std::type_identity<T>, f<Args...>>;
    using type = std::conditional_t<value, std::tuple<T>, std::tuple<T, typename curr::type>>;
};

template <bool B>
void execute()
{
    static_assert(B);
}

template <auto p , auto q>
void execute()
{
    execute<p == q>();
}

template <typename T, typename U>
void execute()
{
    execute<std::is_same_v<T, U>>();
}

int main(int argc, char* argv[])
{
    execute<hanoi_t<1>, std::integer_sequence<int, 0, 1>>();
    execute<hanoi_t<2>, std::integer_sequence<int, 0, 2, 0, 1, 2, 1>>();
    execute<hanoi_t<3>, std::integer_sequence<int, 0, 1, 0, 2, 1, 2, 0, 1, 2, 0, 2, 1, 0, 1>>();

    execute<bmh_t<std::tuple<char>, std::tuple<int, float, double, int, int>>, std::index_sequence<>>();
    execute<bmh_t<std::tuple<double>, std::tuple<double, int, int, double>>, std::index_sequence<0, 3>>();

    execute<kmp_t<std::tuple<char>, std::tuple<int, float, double, int, int>>, std::index_sequence<>>();
    execute<kmp_t<std::tuple<double>, std::tuple<double, int, int, double>>, std::index_sequence<0, 3>>();

    execute<!contains_subtype_v<std::tuple<char, int>, std::tuple<int, float, double, int, int>>>();
    execute<contains_subtype_v<std::tuple<int, double>, std::tuple<double, int, int, double>>>();

    execute<first_subtype_index_t<std::tuple<char, int>, std::tuple<int, float, int>>, std::index_sequence<>>();
    execute<first_subtype_index_t<std::tuple<int, double>, std::tuple<int, double, int, int, double>>,
            std::index_sequence<0>>();

    execute<subtype_indices_t<std::tuple<char>, std::tuple<int, float, double, int, int>>, std::index_sequence<>>();
    execute<subtype_indices_t<std::tuple<double>, std::tuple<double, int, int, double>>, std::index_sequence<0, 3>>();

    execute<erase_subtype_t<std::tuple<char>, std::tuple<int, float, double, int, int>>,
            std::tuple<int, float, double, int, int>>();
    execute<erase_subtype_t<std::tuple<double>, std::tuple<double, int, int, double>>, std::tuple<int, int>>();

    execute<eliminate_subtype_t<std::tuple<char>, std::tuple<int, float, double, int, int>>,
            std::tuple<int, float, double, int, int>>();
    execute<eliminate_subtype_t<std::tuple<double>, std::tuple<double, int, int, double>>, std::tuple<int, int>>();

    execute<replace_subtype_t<std::tuple<char>, std::tuple<short, int>, std::tuple<int, float, double, int, int>>,
            std::tuple<int, float, double, int, int>>();
    execute<replace_subtype_t<std::tuple<double>, std::tuple<char, short>, std::tuple<double, int, int, double>>,
            std::tuple<char ,short, int, int, char, short>>();

    execute<bmh_t<std::tuple<int, double, char, float>,
            std::tuple<int, int, double, char, float, double, char, int, double, char, float, int>>,
            std::index_sequence<1, 7>>();

    execute<bmh_t<std::tuple<int, double, int, double>,
            std::tuple<int, int, double, int, double, double, char, int, double, int, double, int>>,
            std::index_sequence<1, 7>>();

    execute<bmh_t<std::integer_sequence<int, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::index_sequence<3, 10>>();

    execute<bmh_t<std::integer_sequence<int, 2, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::index_sequence<>>();

    execute<kmp_t<std::tuple<int, double, char, float>,
            std::tuple<int, int, double, char, float, double, char, int, double, char, float, int>>,
            std::index_sequence<1, 7>>();

    execute<kmp_t<std::tuple<int, double, int, double>,
            std::tuple<int, int, double, int, double, double, char, int, double, int, double, int>>,
            std::index_sequence<1, 7>>();

    execute<kmp_t<std::integer_sequence<int, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::index_sequence<3, 10>>();

    execute<kmp_t<std::integer_sequence<int, 2, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::index_sequence<>>();

    execute<erase_subtype_t<std::tuple<int, double, char, float>,
            std::tuple<int, int, double, char, float, double, char, int, double, char, float, int>>,
            std::tuple<int, double, char, int>>();

    execute<erase_subtype_t<std::tuple<int, double, int, double>,
            std::tuple<int, int, double, int, double, double, char, int, double, int, double, int>>,
            std::tuple<int, double, char, int>>();

    execute<erase_subtype_t<std::integer_sequence<int, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::integer_sequence<int, -8, 2, -1, 0, -4, -5>>();

    execute<erase_subtype_t<std::integer_sequence<int, 2, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>();

    execute<eliminate_subtype_t<std::tuple<int, double, char, float>,
            std::tuple<int, int, double, char, float, double, char, int, double, char, float, int>>,
            std::tuple<int, double, char, int>>();

    execute<eliminate_subtype_t<std::tuple<int, double, int, double>,
            std::tuple<int, int, double, int, double, double, char, int, double, int, double, int>>,
            std::tuple<int, double, char, int>>();

    execute<eliminate_subtype_t<std::integer_sequence<int, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::integer_sequence<int, -8, 2, -1, 0, -4, -5>>();

    execute<eliminate_subtype_t<std::integer_sequence<int, 2, 1, 3, 1, 3, 1>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>();

    execute<replace_subtype_t<std::tuple<int, double, char, float>, std::tuple<float, short>,
            std::tuple<int, int, double, char, float, double, char, int, double, char, float, int>>,
            std::tuple<int, float, short, double, char, float, short, int>>();

    execute<replace_subtype_t<std::tuple<int, double, int, double>, std::tuple<char, int, char>,
            std::tuple<int, int, double, int, double, double, char, int, double, int, double, int>>,
            std::tuple<int, char, int, char, double, char, char, int, char, int>>();

    execute<replace_subtype_t<std::integer_sequence<int, 1, 3, 1, 3, 1>, std::integer_sequence<int, 7, 9>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::integer_sequence<int, -8, 2, -1, 7, 9, 0, -4, 7, 9, -5>>();

    execute<replace_subtype_t<std::integer_sequence<int, 2, 1, 3, 1, 3, 1>, std::integer_sequence<int, 3>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>,
            std::integer_sequence<int, -8, 2, -1, 1, 3, 1, 3, 1, 0, -4, 1, 3, 1, 3, 1, -5>>();

    execute<number_of_v<std::tuple<int, double>, std::tuple<short, int, double, int, int, double>>, 2>();
    execute<number_of_v<std::index_sequence<2, 7>, std::index_sequence<1, 5, 2, 7, 4, 2, 7, 2, 7>>, 3>();

    using not_adjacent_type = std::tuple<char, double, char, double, int, float, char>;
    using adjacent_type = std::tuple<char, char, char, double, double, int, float>;
    execute<adjacent_t<not_adjacent_type>, adjacent_type>();
    execute<remove_unique_t<not_adjacent_type>, std::tuple<char, char, char, double, double>>();
    execute<remove_duplicate_t<not_adjacent_type>, std::tuple<int, float>>();
    execute<group_t<not_adjacent_type>, std::tuple<std::tuple<char, char, char>,
            std::tuple<double, double>, std::tuple<int>, std::tuple<float>>>();

    using not_adjacent_value = std::index_sequence<2, 1, 3, 5, 3, 5, 8, 7, 2, 5, 9, 8>;
    using adjacent_value = std::index_sequence<2, 2, 1, 3, 3, 5, 5, 5, 8, 8, 7, 9>;
    execute<adjacent_t<not_adjacent_value>, adjacent_value>();
    execute<remove_unique_t<not_adjacent_value>, std::index_sequence<2, 2, 3, 3, 5, 5, 5, 8, 8>>();
    execute<remove_duplicate_t<not_adjacent_value>, std::index_sequence<1, 7, 9>>();
    execute<group_t<not_adjacent_value>, std::tuple<std::index_sequence<2, 2>, std::index_sequence<1>,
            std::index_sequence<3, 3>, std::index_sequence<5, 5, 5>, std::index_sequence<8, 8>,
            std::index_sequence<7>, std::index_sequence<9>>>();

    std::cout << e<double> << std::endl; // 2.71828
    std::cout << pi<double> << std::endl; // 3.14159

    execute<c_1::value, 1>();
    execute<typev<c_2>, 2>();

    execute<value_t<std::true_type>, bool>();

    execute<!has_value_type_v<int>>();
    execute<negav<has_value_type<double>>>();
    execute<has_value_type_v<std::true_type>>();

    execute<first_t<pair_t<int, char>>, int>();
    execute<second_t<pair_t<float, double>>, double>();

    execute<first_v<pair_v<2, 4>>, 2>();
    execute<second_v<pair_v<3, 5>>, 5>();

    execute<identity_t<0, int>, int>();
    execute<wrapper_t<3, int>, std::type_identity<std::type_identity<std::type_identity<int>>>>();

    execute<alias_t<int>, int>();

    execute<wrapin_t<std::type_identity, int, double>,
            std::tuple<std::type_identity<int>, std::type_identity<double>>>();

    execute<contains_v<int, double, char, float, int>>();
    execute<comprise_v<1, -2, 3, 0, 1>>();

    execute<is_unique_type_v<int, double, char, float>>();
    execute<has_duplicates_type_v<int, double, char, int, float>>();

    execute<!is_unique_value_v<1, 2, 2, 3, 4>>();
    execute<has_duplicates_value_v<1, 2, 3, 1, 4>>();

    execute<is_base_template_of_v<std::tuple, std::tuple<int, char>>>();

    execute<is_unique_v<std::tuple<int, double, char, float>>>();
    execute<is_unique_v<std::integer_sequence<int, 1, 2, 3, 4>>>();

    execute<has_duplicates_v<std::tuple<int, double, char, int, float>>>();
    execute<has_duplicates_v<std::integer_sequence<int, 1, 2, 3, 1, 4>>>();

    execute<disable_if_t<false, int>, int>();

    execute<is_streamable_v<std::ostream, int>>();
    execute<!is_streamable_v<std::ostream, std::tuple<int>>>();

    execute<is_type_complete_v<nullptr_t>>();
    execute<!is_type_complete_v<struct none_exist_type>>();

    execute<!is_iterable_v<int>>();
    execute<is_iterable_v<std::vector<int>>>();

    execute<!is_container_v<int>>();
    execute<is_container_v<std::string>>();

    execute<is_pointer_of_v<std::add_pointer_t<int>, int>>();

    execute<!is_instance_of_v<std::tuple, int>>();
    execute<is_instance_of_v<std::tuple, std::tuple<int>>>();

    execute<!is_sequence_of_v<std::integer_sequence, int>>();
    execute<is_sequence_of_v<std::integer_sequence, std::index_sequence<1, 2, 3>>>();

    execute<sizeof_t_v<c_8>, 8>();
    execute<sizeof_t_v<int>, sizeof(int)>();

    execute<sizeof_t_v<std::tuple<int, char, double>>, 3>();
    execute<sizeof_t_v<std::index_sequence<1, 2, 0, 4>>, 4>();
    execute<sizeof_t_v<std::index_sequence<1>>, 1>();
    execute<sizeof_t_v<std::tuple<std::index_sequence<1>>>, 1>();
    execute<sizeof_t_v<std::tuple<std::index_sequence<1, 2>>>, 1>();
    execute<sizeof_t_v<std::tuple<std::integral_constant<int, 3>>>, 1>();

    execute<function_traits_v<decltype([](int, char){})>, 2>();
    execute<function_traits_v<decltype(+[](int, int){})>, 2>();
    execute<function_traits_v<void(*)(int, char, short)>, 3>();

    execute<less_v<char, int>>();
    execute<less_equal_v<c_3, c_4>>();

    execute<equal_v<float, float>>();

    execute<greater_equal_v<double, float>>();
    execute<greater_v<double, int>>();

    execute<clear_t<int>, int>();
    execute<clear_t<std::tuple<int, char>>, std::tuple<>>();
    execute<clear_t<std::integer_sequence<int, 1, 2, 4>>, std::integer_sequence<int>>();

    execute<homogeneous<0, 1, 2, 4>::size(), 4>();
    execute<sizeof_t_v<homogeneous<0, 1, 2, 4>>, 4>();

    execute<get_t<1, std::integer_sequence<int, 1, 2, 4>>, c_2>();
    execute<get_v<1, std::integer_sequence<int, 1, 2, 4>>, 2>();

    execute<sum_t<std::integer_sequence<int, 1, 2, 4>>, c_7>();
    execute<sum_v<std::integer_sequence<int, 1, 2, 4>>, 7>();

    execute<means_v<std::integer_sequence<int, 1, 2, 4>>, 2>();

    execute<mul_t<std::integer_sequence<int, 1, 2, 4>>, c_8>();
    execute<mul_v<std::integer_sequence<int, 1, 2, 4>>, 8>();

    execute<element_t<1, std::tuple<char, double, int>>, double>();
    execute<element_t<2, std::integer_sequence<int, 1, -2, 7, 4>>, c_7>();
    execute<element_v<3, std::integer_sequence<int, 1, -2, 7, 4>>, 4>();

    execute<cat_element_t<3, std::tuple<int, char, bool>, std::tuple<short, double>>, short>();
    execute<cat_element_v<3, std::index_sequence<0, 1, 2>, std::index_sequence<4, 5, 6>>, 4>();

    execute<tuple_offset_v<1, std::tuple<int, int, int>>, 4>();
    execute<tuple_offset_v<2, std::tuple<int, double, int>>, 12>();

    execute<midpoint_t<std::tuple<char, double, int>>, double>();
    execute<midpoint_t<std::integer_sequence<int, 1, -2, 7, 4>>, c_<-2>>();
    execute<midpoint_v<std::integer_sequence<int, 1, -2, 7, 4>>, -2>();

    execute<front_t<std::tuple<char, double, int>>, char>();
    execute<front_t<std::integer_sequence<int, 1, -2, 7, 4>>, c_1>();
    execute<front_v<std::integer_sequence<int, 1, -2, 7, 4>>, 1>();

    execute<back_t<std::tuple<char, double, int>>, int>();
    execute<back_t<std::integer_sequence<int, 1, -2, 7, 4>>, c_4>();
    execute<back_v<std::integer_sequence<int, 1, -2, 7, 4>>, 4>();

    execute<plus_t<c_3, c_4>, c_7>();
    execute<plus_v<c_3, c_4>, 7>();

    execute<minus_t<c_5, c_7>, c_<-2>>();
    execute<minus_v<c_5, c_7>, -2>();

    execute<multiplies_t<c_2, c_6>, c_<12>>();
    execute<multiplies_v<c_2, c_6>, 12>();

    execute<divides_t<c_<11>, c_5>, c_2>();
    execute<divides_v<c_<11>, c_5>, 2>();

    execute<modulus_t<c_<12>, c_7>, c_5>();
    execute<modulus_v<c_<12>, c_7>, 5>();

    execute<negate_t<c_<-12>>, c_<12>>();
    execute<negate_v<c_<12>>, -12>();

    execute<pred_t<c_3>, c_2>();
    execute<pred_v<c_3>, 2>();

    execute<succ_t<c_3>, c_4>();
    execute<succ_v<c_3>, 4>();

    execute<prev_t<2, std::tuple<int, double, char, float, char>>, double>();
    execute<prev_t<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>, c_7>();
    execute<prev_v<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>, 7>();

    execute<next_t<2, std::tuple<int, double, char, float, char>>, float>();
    execute<next_t<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>, c_<-1>>();
    execute<next_v<1, std::integer_sequence<int, 7, 3, -1, 2, 4>>, -1>();

    execute<gcd_v<4, 4>, 4>();
    execute<gcd_v<4, 18>, 2>();
    execute<gcd_v<7, 13>, 1>();

    execute<lcm_v<4, 4>, 4>();
    execute<lcm_v<4, 18>, 36>();
    execute<lcm_v<7, 13>, 91>();

    execute<unpack_t<maximum_t, std::tuple<int, double, char>>, maximum_t<int, double, char>>();

    using bf = bind_front<maximum_t, int, double>;
    execute<bf::template apply<char, float>, maximum_t<int, double, char, float>>();
    execute<call_t<bf, char, float>, maximum_t<int, double, char, float>>();
    execute<call_t<partial<bf, char>, float>, maximum_t<int, double, char, float>>();

    using bb = bind_back<std::tuple, int, double>;
    execute<bb::template apply<char, float>, std::tuple<char, float, int, double>>();
    execute<call_t<bb, char, float>, std::tuple<char, float, int, double>>();
    execute<call_t<partial<bb, char>, float>, std::tuple<char, float, int, double>>();

    execute<call_t<bind_front<std::add_pointer>, int*>, int**>();

    execute<folded_t<max, int, char, double>, double>();
    execute<folded_t<min, int, char, double>, char>();

    execute<curried_t<std::add_pointer, std::tuple, int*, double>, std::tuple<int**, double*>>();
    execute<currying_t<std::add_pointer, int*, double, char>, std::tuple<int**, double*, char*>>();
    execute<curry_t<recurse<std::add_pointer, std::tuple>, int*, double, short>,
            std::tuple<int**, double*, short*>>();

    execute<ycombinator_t<nest, int, char, double>, std::tuple<int, std::tuple<char, std::tuple<double>>>>();

    execute<negav<transform_apply_t<folded_t, std::conjunction, std::tuple<std::false_type, std::true_type>,
            std::true_type>>>();

    execute<on_t<std::add_pointer, std::tuple, int, double, char*>, std::tuple<int*, double*, char**>>();

    execute<equal<3>::template apply<c_3>::value>();

    execute<compose_left_t<std::tuple<int, char, short, double>, tail, reverse, head>,
            std::tuple<double, short>>();
    execute<compose_right_t<std::tuple<int, char, short, double>, tail, reverse, head>,
            std::tuple<char, int>>();

    execute<is_variadic_type_v<std::tuple<>>>();
    execute<is_variadic_value_v<std::index_sequence<>>>();
    execute<!is_variadic_type_v<nullptr_t>>();
    execute<!is_variadic_value_v<nullptr_t>>();

    execute<is_variadic_v<std::tuple<>>>();
    execute<is_variadic_v<std::index_sequence<>>>();
    execute<!is_variadic_v<nullptr_t>>();

    execute<find_if_v<is_tuple, std::tuple<int, char, std::tuple<double>, float>>, 2>();
    execute<find_if_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>, 3>();

    execute<find_if_not_v<is_tuple, std::tuple<std::tuple<int>, char, std::tuple<double>, float>>, 1>();
    execute<find_if_not_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>, 0>();

    execute<find_if_backward_v<equal<2>::template apply, std::integer_sequence<int, 1, 2, 3, 2, 4, 1, 2>>, 6>();
    execute<find_if_backward_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>, 6>();

    execute<find_if_not_backward_v<equal<2>::template apply, std::integer_sequence<int, 1, 2, 3, 2, 4, 1, 2>>, 5>();
    execute<find_if_not_backward_v<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 5>>, 7>();

    execute<split_t<is_tuple, std::tuple<int, char, std::tuple<double>, float, std::tuple<>>>,
            std::tuple<std::tuple<int, char>, std::tuple<float>>>();
    execute<split_t<is_even, std::index_sequence<7, 3, 5, 4, 9, 0, 2, 8, 5>>,
            std::tuple<std::index_sequence<7, 3, 5>, std::index_sequence<9>, std::index_sequence<5>>>();

    using lists = std::integer_sequence<int, 1, 1, 2, 3, 3, 3, 3, 4, 4, 4, 5, 5, 6>;
    using equal_range = equal_range_t<c_4, lists>;
    execute<range_t<equal_range::first, equal_range::second, lists>, std::integer_sequence<int, 4, 4, 4>>();

    execute<all_of_v<is_odd, std::integer_sequence<int, 1, 3, 7, 5, 11, 9, 5>>>();
    execute<!all_of_v<is_odd, std::integer_sequence<int, 1, 2, 7, 5, 11, 9, 5>>>();

    execute<none_of_v<is_even, std::integer_sequence<int, 1, 3, 7, 5, 11, 9, 5>>>();
    execute<one_of_v<is_even, std::integer_sequence<int, 1, 2, 7, 5, 11, 9, 5>>>();

    execute<any_of_v<is_odd, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, 0, 10>>();
    execute<any_of_v<is_tuple, std::tuple<int, char, std::tuple<char>, double,
            std::tuple<uint64_t>, int, std::tuple<float>>, 0, 7>>();

    execute<is_sorted_v<std::index_sequence<2, 3, 4, 4, 4, 5, 6, 8, 9, 9>>>();
    execute<is_partitioned_v<is_even, std::integer_sequence<int, 2, 8, 6, 4, 0, 5, 7, 3, 1>>>();

    execute<is_partitioned_until_v<is_even, std::integer_sequence<int, 2, 8, 6, 4, 5, 7, 3, 8, 6>>, 7>();
    execute<is_partitioned_until_v<is_even, std::integer_sequence<int, 1, 0, 8, 4, 5, 7, 3, 8, 6>>, 1>();

    execute<is_permutation_v<std::index_sequence<1, 2, 3, 4, 5>, std::index_sequence<3, 5, 4, 1, 2>>>();
    execute<!is_permutation_v<std::index_sequence<1, 2, 3, 4, 5>, std::index_sequence<3, 5, 4, 1, 1>>>();

    execute<is_permutation_of<std::tuple<int, char, short, double>, std::tuple<char, double, int, short>>()>();
    execute<!is_permutation_of<std::tuple<bool, char, short, double>, std::tuple<char, double, int, short>>()>();

    execute<adjacent_difference_t<minus_t, std::integer_sequence<int, 2, 4, 6, 8>>,
            std::integer_sequence<int, 2, 2, 2, 2>>();

    execute<adjacent_find_v<greater_t, std::integer_sequence<int, 0, 1, 2, 2, 4, 4, 3>>, 5>();
    execute<adjacent_find_v<std::is_same, std::integer_sequence<int, 0, 1, 2, 2, 4, 4, 3>>, 2>();

    execute<invert_type_t<>, invert_type<>>();
    execute<invert_type_t<char>, char>();
    execute<invert_type_t<char, double>, invert_type<double, char>>();
    execute<invert_type_t<int, char, double, float>, invert_type<float, double, char, int>>();

    execute<invert_value_t<>, invert_value<>>();
    execute<invert_value_t<1>, invert_value<1>>();
    execute<invert_value_t<1, 2>, invert_value<2, 1>>();
    execute<invert_value_t<2, 1, 4, 3>, invert_value<3, 4, 1, 2>>();

    execute<flip_t<std::tuple, int, char, double>, std::tuple<double, char, int>>();

    execute<set_difference_t<less_t, std::integer_sequence<int, 1, 2, 5, 5, 5, 9>,
            std::integer_sequence<int, 2, 5, 7>>, std::integer_sequence<int, 1, 5, 5, 9>>();

    execute<set_symmetric_difference_t<less_t, std::integer_sequence<int, 1, 2, 5, 5, 5, 9>,
            std::integer_sequence<int, 2, 5, 7>>, std::integer_sequence<int, 1, 5, 5, 7, 9>>();

    execute<set_intersection_t<less_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 6, 7, 8>,
            std::integer_sequence<int, 5, 7, 9, 10>>, std::integer_sequence<int, 5, 7>>();

    execute<set_union_t<less_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 5, 5>,
            std::integer_sequence<int, 3, 4, 5, 6, 7>>,
            std::integer_sequence<int, 1, 2, 3, 4, 5, 5, 5, 6, 7>>();

    execute<intersect_t<std::tuple<int, char>, std::tuple<char, double>, std::tuple<short, char>>,
            std::tuple<char>>();

    execute<mismatch_t<equal_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 5, 5>,
            std::integer_sequence<int, 1, 2, 3, 5, 6, 7>>, pair_v<3, 3>>();

    execute<includes_v<equal_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 7>,
            std::integer_sequence<int, 2, 4, 7>>>();

    execute<search_v<equal_t, std::integer_sequence<int, 1, 2, 3, 4, 5, 7>,
            std::integer_sequence<int, 3, 4, 5>>, 2>();
    execute<find_end_v<equal_t, std::integer_sequence<int, 0, 1, 2, 0, 1, 2, 0, 1, 2>,
            std::integer_sequence<int, 0, 1, 2>>, 6>();

    execute<search_n_v<std::is_same, 2, c_2, std::integer_sequence<int, 1, 2, 0, 2, 2, 7, 2>>, 3>();
    execute<search_n_v<std::is_same, 2, int, std::tuple<int, char, int, int, double, int, int, char>>, 2>();

    execute<inclusive_scan_t<plus_t, std::integer_sequence<int, 1, 2, 3, 4>>,
            std::integer_sequence<int, 1, 3, 6, 10>>();
    execute<inclusive_scan_t<multiplies_t, std::integer_sequence<int, 1, 2, 3, 4>>,
            std::integer_sequence<int, 1, 2, 6, 24>>();

    execute<exclusive_scan_t<plus_t, std::integer_sequence<int, 1, 2, 3, 4>, c_2>,
            std::integer_sequence<int, 2, 3, 5, 8>>();
    execute<exclusive_scan_t<multiplies_t, std::integer_sequence<int, 1, 2, 3, 4>, c_2>,
            std::integer_sequence<int, 2, 2, 4, 12>>();

    execute<transform_inclusive_scan_t<plus_t, std::integer_sequence<int, 1, 2, 3, 4>, pred>,
            std::integer_sequence<int, 0, 1, 3, 6>>();
    execute<transform_inclusive_scan_t<multiplies_t, std::integer_sequence<int, 1, 2, 3, 4>, succ>,
            std::integer_sequence<int, 2, 6, 24, 120>>();

    execute<transform_exclusive_scan_t<plus_t, std::integer_sequence<int, 1, 2, 3, 4>, pred, c_2>,
            std::integer_sequence<int, 2, 2, 3, 5>>();
    execute<transform_exclusive_scan_t<multiplies_t, std::integer_sequence<int, 1, 2, 3, 4>, succ, c_2>,
            std::integer_sequence<int, 2, 4, 12, 48>>();

    execute<lca_t<std::tuple<int, char, short>, std::tuple<double, nullptr_t, int, char, short>>, int>();
    execute<lca_t<std::tuple<short, double, int, char, short>, std::tuple<float, int, char, short>>, int>();

    execute<lca_t<std::index_sequence<9, 4, 5>, std::index_sequence<1, 3, 7, 9, 4, 5>>, index_t<9>>();
    execute<lca_v<std::index_sequence<2, 3, 9, 4, 5>, std::index_sequence<0, 9, 4, 5>>, 9>();

    execute<lca_t<std::tuple<short, double, int, char, short>, std::tuple<int, char, short, float>>,
                  std::tuple<short, double, int, char, short>>();
    execute<lca_t<std::tuple<>, std::tuple<int, char, short, float>>,
                  std::tuple<>>();

    execute<lca_t<std::index_sequence<1, 2, 8, 5, 7>, std::index_sequence<4, 2, 7, 3>>,
                  std::index_sequence<1, 2, 8, 5, 7>>();
    execute<lca_t<std::index_sequence<>, std::index_sequence<1, 2, 8, 5, 7>>,
                  std::index_sequence<>>();

    execute<transmute_t<plus_t, std::integer_sequence<int, 1, 3, 0, 2>,
            std::integer_sequence<int, 1, 5, 4, 2>>, std::integer_sequence<int, 2, 8, 4, 4>>();

    execute<inner_product_v<plus_t, equal_t, std::integer_sequence<int, 1, 3, 0, 2>,
            std::integer_sequence<int, 1, 5, 4, 2>, c_0>, 2>();
    execute<inner_product_v<plus_t, multiplies_t, std::integer_sequence<int, 1, 3, 0, 2>,
            std::integer_sequence<int, 1, 5, 4, 2>, c_0>, 20>();

    execute<accumulate_v<multiplies_t, c_1, std::integer_sequence<int, 1, 3, -3, 2>>, -18>();

    execute<iota_t<succ, c_<-2>, std::integer_sequence<int, 0, 0, 0, 0, 0>>,
            std::integer_sequence<int, -2, -1, 0, 1, 2>>();

    using nested = std::tuple<std::tuple<char, short>, double,
                   std::tuple<char, std::tuple<char, int, double>>, short>;

    execute<flat_t<int>, int>();
    execute<flat_t<std::tuple<>>, std::tuple<>>();
    execute<flat_t<nested>, std::tuple<char, short, double, char, char, int, double, short>>();

    execute<combine_t<nullptr_t, int, char, std::tuple<>, double, short, std::tuple<char>>,
            std::tuple<nullptr_t, int, char, double, short, char>>();

    using reversed = reverse_recursive_t<nested>;
    execute<reversed, reverse_t<std::tuple<reverse_t<std::tuple<char, short>>, double,
            reverse_t<std::tuple<char, reverse_t<std::tuple<char, int, double>>>>, short>>>();

    using integer_t = std::integer_sequence<int, 2, 7, 4>;
    execute<increase_t<integer_t, 3>, std::integer_sequence<int, 5, 10, 7>>();
    execute<increase_t<integer_t, -3>, std::integer_sequence<int, -1, 4, 1>>();

    execute<offset_sequence_t<2, std::index_sequence<0, 1, 2>>, std::index_sequence<2, 3, 4>>();
    execute<offset_sequence_t<-2, std::index_sequence<3, 4, 5>>, std::index_sequence<1, 2, 3>>();

    using typelist_ = std::tuple<std::tuple<bool, float>, std::tuple<int, double, short>, std::tuple<char>>;
    using pairindex = pair_t<std::index_sequence<0, 0, 1, 1, 1, 2>, std::index_sequence<0, 1, 0, 1, 2, 0>>;
    execute<matrix_index_sequences_t<typelist_>, pairindex>();

    using add_one_t = transform_apply_t<currying_t, succ, to_tuple_t<integer_t>>;
    execute<add_one_t, std::tuple<c_<3, int>, c_<8, int>, c_<5, int>>>();

    execute<next_slide_indices_t<2, 7, std::integer_sequence<int, 2, 3, 4>>,
            std::integer_sequence<int, 3, 4, 5>>();
    execute<prev_slide_indices_t<2, 7, std::integer_sequence<int, 3, 4, 5>>,
            std::integer_sequence<int, 2, 3, 4>>();

    using indices = std::tuple<std::integer_sequence<int, 2, 3, 4>,
                               std::integer_sequence<int, 3, 4, 5>,
                               std::integer_sequence<int, 4, 5, 6>>;

    execute<next_slide_indices_list<2, 7, std::integer_sequence<int, 2, 3, 4>>, indices>();
    execute<prev_slide_indices_list<2, 7, std::integer_sequence<int, 4, 5, 6>>, reverse_t<indices>>();

    execute<slide_list_t<3, std::integer_sequence<int, 1, 2, 3, 4>>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>, std::integer_sequence<int, 2, 3, 4>>>();

    execute<slide_list_t<3, std::tuple<int, char, double, float>>,
            std::tuple<std::tuple<int, char, double>, std::tuple<char, double, float>>>();

    execute<fibonacci_v<4>, 3>();

    constexpr std::tuple<int, short, char> first(1, 2, 3);
    constexpr std::tuple<short, float> second(4, 5);
    constexpr std::tuple<int, double, short> third(6, 7, 8);
    constexpr auto t_ = tuple_cat_unique(first, second, third);

    static_assert(std::get<0>(t_) == 1);
    static_assert(std::get<1>(t_) == 2);
    static_assert(std::get<2>(t_) == 3);
    static_assert(std::get<3>(t_) == 5);
    static_assert(std::get<4>(t_) == 7);

    auto a_ = std::make_tuple(1, 2, 3);
    auto b_ = std::make_tuple("one", "two", "three");
    auto f_ = [](auto i, auto s) { std::cout << ++i << " " << s << std::endl; };
    zipped_tuple_map(f_, a_, b_);

    execute<triangular_number_v<4>, 10>();
    execute<triangular_number_sequence_t<4>, std::integer_sequence<int, 1, 3, 6, 10>>();

    execute<nth_type_t<2, int, double, char*, float>, char*>();
    execute<first_type<int, double, char*, float>, int>();
    execute<last_type<int, double, char*, float>, float>();

    execute<arg_t<arg<1>, int, float, double>, float>();

    execute<make_index_tuple<4>, index_tuple<0, 1, 2, 3>>();
    execute<index_tuple_for<int, char, double>, index_tuple<0, 1, 2>>();

    execute<make_index_sequence<4>, index_sequence<0, 1, 2, 3>>();
    execute<index_sequence_for<int, char, double>, index_sequence<0, 1, 2>>();

    execute<integral_range_t<size_t, 1, 4>, index_list<size_t, 1, 2, 3>>();
    execute<integral_range_t<size_t, 4, 1>, index_list<size_t, 4, 3, 2>>();

    execute<index_range<2, 5>, std::index_sequence<2, 3, 4>>();
    execute<index_range<5, 2>, std::index_sequence<5, 4, 3>>();

    execute<integer_range<-2, 3>, std::integer_sequence<int, -2, -1, 0, 1, 2>>();
    execute<integer_range<3, -2>, std::integer_sequence<int, 3, 2, 1, 0, -1>>();

    execute<reverse_index_sequence<0>, std::index_sequence<>>();
    execute<reverse_index_sequence<5>, std::index_sequence<4, 3, 2, 1, 0>>();

    execute<rotated_index_sequence_t<3, 7>, std::index_sequence<3, 4, 5, 6, 0, 1, 2>>();

    execute<repeat_range_t<3>, std::index_sequence<1, 2, 2, 3, 3, 3>>();

    auto pf = [](auto&&... v){ (std::cout << ... << v) << std::endl; };
    {
        int i = 3;
        auto tuple_ = make_lambda_tuple(1, 2.8, i);
        lambda_tuple_get<2>(tuple_) = i + 1;
        auto tuples0 = make_lambda_tuple(nullptr, std::string("CPP-TMP"), 9.8f);
        auto tuples1 = lambda_tuple_cat(tuple_, tuples0);
        auto tuples2 = lambda_tuple_reverse_cat(tuple_, tuples0, make_lambda_tuple(7, 4));
        auto select = lambda_tuple_select<std::index_sequence<2, 0, 4, 5>>(tuples1);
        auto extrac = lambda_tuple_extract<1, 3, 2, 4, 0>(tuples1);
        auto revers = lambda_tuple_reverse(extrac);
        auto range = lambda_tuple_range<2, 5>(tuples1);
        auto rotat = lambda_tuple_rotate<1, 3, 5>(tuples1);
        auto gathe = lambda_tuple_gather<std::string, nullptr_t, double>(tuples1);

        std::cout << "lambda_tuple_get " << lambda_tuple_get<2>(tuple_) << std::endl;
        std::cout << "lambda_tuple_get " << lambda_tuple_get<double>(tuple_) << std::endl;
        std::cout << "lambda_tuple_get " << lambda_tuple_get<1>(revers) << std::endl;
        std::cout << "lambda_tuple_get " << lambda_tuple_get<2>(range) << std::endl;
        std::cout << "lambda_tuple_get " << lambda_tuple_get<6>(tuples2) << std::endl;
        std::cout << "lambda_tuple_get " << lambda_tuple_get<2>(rotat) << std::endl;
        std::cout << "lambda_tuple_get " << lambda_tuple_get<0>(gathe) << std::endl;
        std::cout << "lambda_tuple_size " << lambda_tuple_size(select) << std::endl;
        std::cout << "lambda_tuple_size " << lambda_tuple_size(extrac) << std::endl;
        std::cout << "lambda_tuple_size " << lambda_tuple_size(tuples1) << std::endl;
        std::cout << "lambda_tuple_gather_invoke" << std::endl;
        lambda_tuple_gather_invoke<4, 1, 5>(tuples1, pf);
        lambda_tuple_gather_invoke<std::string, double, float>(tuples1, pf);
    }

    reverse_invoke([](auto&&... args){ (std::cout << ... << args) << std::endl; }, 1, 2, 3, 4);

    fmap([](auto& v)
    {
        std::cout << v << std::endl;
    }, 1, 2.3, "string", 'x');

    reverse_fmap([](auto& v)
    {
        std::cout << v << std::endl;
    }, 1, 2.3, "string", 'x');

    execute<concat_t<std::tuple<int, char>, std::tuple<double>>, std::tuple<int, char, double>>();
    execute<concat_t<std::integer_sequence<int, 1, 2, 3>, std::integer_sequence<int, 4, 5, 6>>,
            std::integer_sequence<int, 1, 2, 3, 4, 5, 6>>();

    execute<unique_t<std::tuple<int, char, int, double>>, std::tuple<int, char, double>>();
    execute<unique_t<std::integer_sequence<int, 2, 2, 3, 4, 3>>, std::integer_sequence<int, 2, 3, 4>>();

    execute<unique_elements_t<std::tuple<short, int, char, int, double, char>>, std::tuple<short, double>>();
    execute<unique_elements_t<std::index_sequence<5, 7, 0, 5, 3, 2, 7>>, std::index_sequence<0, 3, 2>>();

    execute<duplicate_elements_t<std::tuple<short, int, char, int, double, char>>, std::tuple<int, char>>();
    execute<duplicate_elements_t<std::index_sequence<5, 7, 0, 5, 3, 2, 7>>, std::index_sequence<5, 7>>();

    execute<unique_index_t<std::tuple<int, int, char, int, double>>, std::index_sequence<2, 3, 4>>();
    execute<unique_index_t<std::integer_sequence<int, 3, 1, 2, 5, 3>>, std::index_sequence<1, 2, 3, 4>>();

    execute<unique_if_t<is_pointer_of, std::tuple<int*, int*, int, double, char, double*, double, float>>,
            std::tuple<int*, int*, double, char, double*, float>>();
    execute<unique_if_not_t<is_pointer_of, std::tuple<int*, int*, int, double, char, double*, double, float>>,
            std::tuple<int*, int>>();

    using value = std::integer_sequence<int, 4, 0, 5, 6, 4, 1, 9, 21>;
    using type = std::tuple<int, char, std::tuple<char>, double, std::tuple<double>, float, char>;

    execute<is_even_v<c_4>>();
    execute<!call<negaf<is_even>, c_4>::value>();
    execute<!negaf<is_even>::template apply<c_4>::value>();

    execute<remove_if_t<is_odd, value, 1, 6>, std::integer_sequence<int, 4, 0, 6, 4, 9, 21>>();
    execute<remove_if_t<is_even, value, 1, 6>, std::integer_sequence<int, 4, 5, 1, 9, 21>>();
    execute<remove_if_t<is_tuple, type, 1, 5>, std::tuple<int, char, double, float, char>>();
    execute<remove_if_not_t<is_tuple, type, 1, 5>, std::tuple<int, std::tuple<char>,
            std::tuple<double>, float, char>>();

    execute<copy_if_t<is_even, value>, std::integer_sequence<int, 4, 0, 6, 4>>();
    execute<copy_if_t<is_tuple, type>, std::tuple<std::tuple<char>, std::tuple<double>>>();

    execute<copy_if_not_t<is_even, value>, std::integer_sequence<int, 5, 1, 9, 21>>();
    execute<copy_if_not_t<is_tuple, type>, std::tuple<int, char, double, float, char>>();

    execute<exclude_t<std::index_sequence<1, 2, 3, 4, 5, 7>, std::index_sequence<1, 3, 4>>,
            std::index_sequence<1, 3, 7>>();
    execute<exclude_t<std::tuple<char, int, double, int, short>, std::index_sequence<0, 2, 3>>,
            std::tuple<int, short>>();

    execute<erase_if_t<is_tuple, type>, std::tuple<int, char, double, float, char>>();
    execute<remove_copy_if_t<is_tuple, type>, std::tuple<std::tuple<char>, std::tuple<double>>>();

    execute<erase_if_t<is_odd, std::integer_sequence<int, 0, 3, 2, 4, 7, 3>>,
            std::integer_sequence<int, 0, 2, 4>>();
    execute<erase_if_not_t<is_odd, std::integer_sequence<int, 0, 3, 2, 4, 7, 3>>,
            std::integer_sequence<int, 3, 7, 3>>();

    execute<remove_copy_t<char, std::tuple<int, char, double, float, char>>,
            std::tuple<int, double, float>>();
    execute<remove_copy_t<c_3, std::integer_sequence<int, 0, 3, 2, 4, 7, 3>>,
            std::integer_sequence<int, 0, 2, 4, 7>>();
    execute<remove_copy_c<4, std::integer_sequence<int, 4, 3, 2, 4, 7, 3>>,
            std::integer_sequence<int, 3, 2, 7, 3>>();

    execute<remove_elements_t<std::tuple<int, char>, std::tuple<char, double, int, short, bool, char, int>>,
            std::tuple<double, short, bool>>();
    execute<remove_elements_t<std::index_sequence<1, 0, 3, 5>, std::index_sequence<2, 1, 5, 7, 4, 0, 6, 9>>,
            std::index_sequence<2, 7, 4, 6, 9>>();

    execute<remove_subtypes_t<std::tuple<std::tuple<int, short>, std::tuple<char, int>>,
            std::tuple<char, double, int, short, bool, char, int>>, std::tuple<char, double, bool>>();
    execute<remove_subtypes_t<std::tuple<std::index_sequence<5, 7, 4>, std::index_sequence<6, 9>>,
            std::index_sequence<2, 1, 5, 7, 4, 0, 6, 9>>, std::index_sequence<2, 1, 0>>();

    execute<unique_copy_t<std::tuple<int, int, short, char, char, double, double, bool>>,
            std::tuple<int, short, char, double, bool>>();
    execute<unique_copy_t<std::index_sequence<1, 2, 3, 8, 7, 5, 4, 6, 0>, 0, 9, less_t>,
            std::index_sequence<1, 7, 5, 4, 0>>();

    execute<max_element_t<std::tuple<short, int, char>>, int>();
    execute<min_element_t<std::tuple<short, int, char>>, char>();
    execute<max_element_t<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>, c_4>();
    execute<min_element_t<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>, c_<-2>>();
    execute<max_element_v<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>, 4>();
    execute<min_element_v<std::integer_sequence<int, 1, -2, 3, 0, 2, 4>>, -2>();

    execute<first_t<minmax_element<std::tuple<short, int, char>>>, char>();
    execute<second_t<minmax_element<std::tuple<short, int, char>>>, int>();

    execute<min_t<char, double>, char>();
    execute<max_t<char, double>, double>();

    execute<minimum_t<short, int, char>, char>();
    execute<maximum_t<short, int, char>, int>();

    execute<expand_t<std::tuple_element, std::tuple<int, float, char, double>,
            std::index_sequence<0, 2>>, std::tuple<int, char>>();
    execute<expand_t<get, std::integer_sequence<int, -1, 3, 7, 0, 5>,
            std::index_sequence<1, 3, 0, 4>>, std::integer_sequence<int, 3, 0, -1, 5>>();

    execute<expand_t<element, std::tuple<int, float, char, double>,
            std::index_sequence<0, 2>>, std::tuple<int, char>>();
    execute<expand_t<element, std::integer_sequence<int, -1, 3, 7, 0, 5>,
            std::index_sequence<1, 3, 0, 4>>, std::integer_sequence<int, 3, 0, -1, 5>>();

    execute<expand_of_t<std::tuple<int, float, char, double>,
            std::index_sequence<0, 2>>, std::tuple<int, char>>();
    execute<expand_of_t<std::integer_sequence<int, -1, 3, 7, 0, 5>,
            std::index_sequence<1, 3, 0, 4>>, std::integer_sequence<int, 3, 0, -1, 5>>();

    execute<slice_t<std::index_sequence<3, 2, 1, 0>, std::tuple<int, float, char, double>>,
            std::tuple<double, char, float, int>>();
    execute<slice_t<std::index_sequence<3, 1, 4>, std::integer_sequence<int, -1, 3, 7, 0, 5>>,
            std::integer_sequence<int, 0, 3, 5>>();

    execute<choose_t<bool_pack<0, 1, 1, 0>, std::tuple<int, float, char, double>>,
            std::tuple<float, char>>();
    execute<choose_t<bool_pack<1, 0, 1, 1, 0>, std::integer_sequence<int, -1, 3, 7, 0, 5>>,
            std::integer_sequence<int, -1, 7, 0>>();

    execute<apply_permutation_t<std::tuple<char, int, float, double, short>,
            std::index_sequence<0, 2, 4, 1, 3>>, std::tuple<char, float, short, int, double>>();
    execute<apply_permutation_t<std::integer_sequence<int, 8, 3, 5, -2, 7>,
            std::index_sequence<4, 0, 2, 1, 3>>, std::integer_sequence<int, 7, 8, 5, 3, -2>>();

    execute<apply_permutation_t<std::tuple<char, int, float, double, short>,
            std::index_sequence<0, 2, 4, 1, 3>, true>, std::tuple<int, double, char, float, short>>();
    execute<apply_permutation_t<std::integer_sequence<int, 8, 3, 5, -2, 7>,
            std::index_sequence<4, 0, 2, 1, 3>, true>, std::integer_sequence<int, 3, -2, 5, 7, 8>>();

    execute<to_sequence_t<std::tuple<int, double>>, std::integer_sequence<int, 4, 8>>();
    execute<to_sequence_t<std::index_sequence<4, 8>>, std::index_sequence<4, 8>>();

    execute<to_tuple_t<std::integer_sequence<int, 4, 8>>, std::tuple<c_4, c_8>>();
    execute<to_tuple_t<std::tuple<int, double>>, std::tuple<int, double>>();

    execute<swap_t<1, 3, std::tuple<int, double, char, float>>, std::tuple<int, float, char, double>>();
    execute<swap_t<0, 2, std::integer_sequence<int, 1, -2, 7, 4>>,
            std::integer_sequence<int, 7, -2, 1, 4>>();

    using ranges_t = swap_ranges<1, 4, std::integer_sequence<int, 0, 1, 2, 3, 4, 5>,
          std::integer_sequence<int, -1, -2, -3, -4, -5>>;

    execute<first_t<ranges_t>, std::integer_sequence<int, 0, -2, -3, -4, 4, 5>>();
    execute<second_t<ranges_t>, std::integer_sequence<int, -1, 1, 2, 3, -5>>();

    execute<swap_ranges_first<1, 4, std::integer_sequence<int, 0, 1, 2, 3, 4, 5>,
            std::integer_sequence<int, -1, -2, -3, -4, -5>>,
            std::integer_sequence<int, 0, -2, -3, -4, 4, 5>>();

    execute<swap_ranges_second<0, 3, std::integer_sequence<int, 1, 2, 3, 4>,
            std::integer_sequence<int, -1, -2, -3, -4, -5>>,
            std::integer_sequence<int, 1, 2, 3, -4, -5>>();

    using extents_t = swap_extent<1, 4, 2, 5, std::integer_sequence<int, 0, 1, 2, 3, 4, 5>,
          std::integer_sequence<int, -1, -2, -3, -4, -5>>;

    execute<first_t<extents_t>, std::integer_sequence<int, 0, -3, -4, -5, 4, 5>>();
    execute<second_t<extents_t>, std::integer_sequence<int, -1, -2, 1, 2, 3>>();

    execute<swap_extent_first<1, 4, 2, 5, std::integer_sequence<int, 0, 1, 2, 3, 4, 5>,
            std::integer_sequence<int, -1, -2, -3, -4, -5>>,
            std::integer_sequence<int, 0, -3, -4, -5, 4, 5>>();

    execute<swap_extent_second<0, 3, 1, 4, std::integer_sequence<int, 1, 2, 3, 4>,
            std::integer_sequence<int, -1, -2, -3, -4, -5>>,
            std::integer_sequence<int, -1, 1, 2, 3, -5>>();

    execute<within_v<2, -2, 4>>();
    execute<!within_v<5, -2, 4>>();

    execute<gsub_t<1, 5, int, float, std::tuple<int, char, int, double, int, float, char>>,
            std::tuple<int, char, float, double, float, float, char>>();
    execute<gsub_t<1, 5, c_<-2>, c_<-6>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, 1, 3, -6, 1, 7, 1, 4, 6>>();
    execute<gsub_c<1, 5, -2, -6, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, 1, 3, -6, 1, 7, 1, 4, 6>>();

    execute<replace_with_t<int, float, std::tuple<int, char, int, double, int, float, char>>,
            std::tuple<float, char, float, double, float, float, char>>();
    execute<replace_with_t<c_1, c_<-6>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, -6, 3, -2, -6, 7, -6, 4, 6>>();
    execute<replace_with_c<1, -6, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, -6, 3, -2, -6, 7, -6, 4, 6>>();

    execute<replace_if_t<1, 5, is_tuple, int, std::tuple<int, char, std::tuple<>, double,
            std::tuple<>, float, char>>, std::tuple<int, char, int, double, int, float, char>>();
    execute<replace_if_c<1, 5, is_even, -6, std::integer_sequence<int, 1, 3, -2, 4, 7, 0, 4, 6>>,
            std::integer_sequence<int, 1, 3, -6, -6, 7, 0, 4, 6>>();
    execute<replace_if_not_c<1, 5, is_odd, -6, std::integer_sequence<int, 1, 3, -2, 4, 7, 0, 4, 6>>,
            std::integer_sequence<int, 1, 3, -6, -6, 7, 0, 4, 6>>();

    execute<adjust_t<1, 5, int, std::tuple<int, char, int, double, int, float, char>, std::add_pointer>,
            std::tuple<int, char, int*, double, int*, float, char>>();
    execute<adjust_t<1, 5, c_1, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>, succ>,
            std::integer_sequence<int, 1, 3, -2, 2, 7, 1, 4, 6>>();

    execute<adjust_if_t<1, 5, std::tuple<int, std::tuple<int>, double,
            std::tuple<float>, char>, std::add_pointer, is_tuple>,
            std::tuple<int, std::tuple<int>*, double, std::tuple<float>*, char>>();
    execute<adjust_if_t<1, 5, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>, succ, is_odd>,
            std::integer_sequence<int, 1, 4, -2, 2, 8, 1, 4, 6>>();
    execute<adjust_if_not_t<1, 5, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>, succ, is_even>,
            std::integer_sequence<int, 1, 4, -2, 2, 8, 1, 4, 6>>();

    execute<substitute_t<2, 5, int, std::tuple<int, char, int, double, int, float, char>>,
            std::tuple<int, char, int, int, int, float, char>>();
    execute<substitute_t<2, 5, c_<-2>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, 1, 3, -2, -2, -2, 1, 4, 6>>();
    execute<substitute_c<3, 6, 9, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, 1, 3, -2, 9, 9, 9, 4, 6>>();

    execute<change_t<2, int, std::tuple<int, int, char, double, int, float, char>>,
            std::tuple<int, int, int, double, int, float, char>>();
    execute<change_t<1, c_<-2>, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, 1, -2, -2, 1, 7, 1, 4, 6>>();
    execute<change_c<4, 9, std::integer_sequence<int, 1, 3, -2, 1, 7, 1, 4, 6>>,
            std::integer_sequence<int, 1, 3, -2, 1, 9, 1, 4, 6>>();

    execute<exchange_with_t<std::index_sequence<2, 4, 0, 1, 6>,
            std::tuple<int, int, char, double, int, float, double>,
            std::tuple<char, int, double, int, char, double, float, nullptr_t>>,
            std::tuple<int, int, char, int, int, double, double, nullptr_t>>();

    execute<exchange_with_t<std::index_sequence<1, 5, 3, 6, 2>,
            std::integer_sequence<int, 7, -1, 3, 5, 9, 2, 5>,
            std::integer_sequence<int, 4, 0, 6, -5, 7, 4, 3, 2, 11>>,
            std::integer_sequence<int, 4, -1, 3, 5, 7, 2, 5, 2, 11>>();

    execute<sub_t<3, 8, integral_range_t<int, -2, 3>>, index_list<int, -2, -1, 0, 8, 2>>();
    execute<sub_t<2, 3, index_list<size_t, 3, 4, 0, 5, 2>>, index_list<size_t, 3, 4, 3, 5, 2>>();
    execute<sub_t<4, -3, std::integer_sequence<int, -1, 8, 0, 2, 4, 7>>,
            std::integer_sequence<int, -1, 8, 0, 2, -3, 7>>();

    execute<range_t<1, 4, int>, int>();
    execute<range_t<1, 4, std::tuple<int, char, float, double, int>>, std::tuple<char, float, double>>();
    execute<range_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>,
            std::integer_sequence<int, 2, -2, 4>>();

    execute<subset_t<1, 3, std::tuple<int, char, float, double, int>>, std::tuple<char, float, double>>();
    execute<subset_t<1, 3, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>,
            std::integer_sequence<int, 2, -2, 4>>();

    execute<copy_n_t<1, 3, std::tuple<short, int, char>, std::tuple<int, char, float, double>>,
            std::tuple<short, int, char, char, float, double>>();
    execute<copy_n_t<1, 3, std::integer_sequence<int, 6, 0, 1, 4>, std::integer_sequence<int, 8, 3, 4, 0>>,
            std::integer_sequence<int, 6, 0, 1, 4, 3, 4, 0>>();

    execute<pivot_t<3, std::tuple<int, char, char, int, int>>, std::tuple<int, int, int, char, char>>();
    execute<pivot_t<3, std::index_sequence<0, 1, 2, 3, 4, 5>>, std::index_sequence<3, 4, 5, 0, 1, 2>>();

    execute<axial_symmetry_t<std::tuple<int>>, std::tuple<int>>();
    execute<axial_symmetry_t<std::index_sequence<>>, std::index_sequence<>>();

    execute<axial_symmetry_t<std::tuple<int, char, char, int, int>>, std::tuple<int, int, char, int, char>>();
    execute<axial_symmetry_t<std::index_sequence<0, 1, 2, 3, 4, 5>>, std::index_sequence<3, 4, 5, 0, 1, 2>>();

    execute<starts_with_v<std::tuple<int, char, short>, std::tuple<int, char>>>();
    execute<ends_with_v<std::index_sequence<7, 4, 2>, std::index_sequence<4, 2>>>();

    execute<reverse_t<double>, double>();
    execute<reverse_t<std::tuple<float, double, int>>, std::tuple<int, double, float>>();
    execute<reverse_t<std::integer_sequence<int, 1, 2, -2>>, std::integer_sequence<int, -2, 2, 1>>();

    execute<extent_t<1, 4, char>, char>();
    execute<extent_t<1, 4, std::tuple<int, char, float, double, int, char>>,
            std::tuple<double, float, char>>();
    execute<extent_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>,
            std::integer_sequence<int, 4, -2, 2>>();

    execute<erase_t<2, 5, std::tuple<int, char, float, double, int, char>>,
            std::tuple<int, char, char>>();
    execute<erase_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>,
            std::integer_sequence<int, 1, 3, 5>>();

    execute<erase_at_t<2, std::tuple<int, double, int, char>>, std::tuple<int, double, char>>();
    execute<erase_at_t<1, std::integer_sequence<int, 1, 2, -2, 4, 5>>,
            std::integer_sequence<int, 1, -2, 4, 5>>();

    execute<drop_t<2, std::tuple<int, double, int, char>>, std::tuple<int, char>>();
    execute<drop_last_t<2, std::integer_sequence<int, 1, 2, -2, 4, 5>>,
            std::integer_sequence<int, 1, 2, -2>>();

    execute<take_t<2, std::tuple<int, double, int, char>>, std::tuple<int, double>>();
    execute<take_last_t<2, std::integer_sequence<int, 1, 2, -2, 4, 5>>,
            std::integer_sequence<int, 4, 5>>();

    execute<drop_while_t<std::is_pointer, std::tuple<int*, double*, int, char>>, std::tuple<int, char>>();
    execute<take_while_t<std::is_pointer, std::tuple<int*, double*, int, char>>, std::tuple<int*, double*>>();

    execute<drop_last_while_t<std::is_pointer, std::tuple<int, double, int*, char*>>, std::tuple<int, double>>();
    execute<take_last_while_t<std::is_pointer, std::tuple<int, double, int*, char*>>, std::tuple<int*, char*>>();

    execute<trim_if_t<std::is_pointer, std::tuple<int*, double*, int, char, int*>>, std::tuple<int, char>>();
    execute<trim_if_not_t<std::is_pointer, std::tuple<int, short, int*, char*, int>>, std::tuple<int*, char*>>();

    execute<degree_t<1, 4, std::tuple<int, char, float, double, int, char>>,
            std::tuple<int, double, float>>();
    execute<degree_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>,
            std::integer_sequence<int, 3, 4, -2>>();

    execute<reverse_range_t<1, 4, float>, float>();
    execute<reverse_range_t<1, 4, std::tuple<int, char, float, double, int, char>>,
            std::tuple<int, double, float, char, int, char>>();
    execute<reverse_range_t<1, 4, std::integer_sequence<int, 1, 2, -2, 4, 3, 5>>,
            std::integer_sequence<int, 1, 4, -2, 2, 3, 5>>();

    execute<reverse_subrange_t<int, std::tuple<short, char, int, double, char, int, char>>,
            std::tuple<char, int, double, char, int, short, char>>();
    execute<reverse_subrange_t<c_2, std::index_sequence<0, 3, 1, 2, 4, 5, 2, 7, 8, 2>>,
            std::index_sequence<2, 7, 8, 2, 4, 5, 2, 0, 3, 1>>();

    execute<typeindex<char, float, double, int, char>(), 4>();
    execute<typeindex<short, float, double, int, char>(), 5>();

    execute<valueindex<3, 7, 5, 4, 3, 8, 3>(), 4>();
    execute<valueindex<4, 8, 6, 7, 5, 3, 4>(), 6>();

    execute<type_index_v<int, std::tuple<char, float, double, int, char>>, 3>();
    execute<type_index_v<uint64_t, std::tuple<char, float, double, int, char>>, 5>();
    execute<value_index_v<6, std::integer_sequence<int, 1, -2, 0, 3, 6, 5>>, 4>();
    execute<value_index_v<7, std::integer_sequence<int, 1, -2, 0, 3, 6, 5>>, 6>();

    execute<find_v<char, std::tuple<float, char, double, int, char>>, 1>();
    execute<find_v<c_6, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 2>();

    execute<tuple_find_v<char, std::tuple<float, char, double, int, char>>, 1>();
    execute<tuple_find<c_6, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>() == 2>();

    execute<delimit_t<double, std::tuple<float, char, double, int, char>>, std::tuple<float, char>>();
    execute<delimit_t<c_8, std::index_sequence<3, 9, 6, 7, 8, 5>>, std::index_sequence<3, 9, 6, 7>>();

    execute<find_nth_v<2, char, std::tuple<float, char, double, int, char>>, 4>();
    execute<find_nth_v<4, c_6, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 6>();

    execute<find_all_t<char, std::tuple<float, char, double, int, char>>, std::index_sequence<1, 4>>();
    execute<find_all_not_c<6, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, std::index_sequence<0, 1, 3, 5>>();

    execute<match_t<std::tuple<int, char, short>, std::tuple<char, int, double, char, float, short>>,
            std::index_sequence<1, 3, 5>>();
    execute<match_t<std::integer_sequence<int, 2, 4, 1>, std::integer_sequence<int, 2, 1, 4, 0, 3, 1, 4>>,
            std::index_sequence<0, 2, 5>>();

    execute<unordered_match_t<std::tuple<short, char, double, char, short>, std::tuple<char, int, short, double, char, float, short>>,
            std::index_sequence<2, 0, 3, 4, 6>>();
    execute<unordered_match_t<std::integer_sequence<int, 4, 3, 1, 4>, std::integer_sequence<int, 2, 1, 4, 0, 3, 1, 4>>,
            std::index_sequence<2, 4, 1, 6>>();

    using func = std::function<void(int, char)>;
    execute<function_traits_v<func>, 2>();
    execute<function_traits_r<func>, void>();
    execute<function_traits_t<func>, std::tuple<int, char>>();

    execute<fmatch_t<void(int, char, float), std::tuple<short, int, double, char, float>>,
            std::index_sequence<1, 3, 4>>();
    execute<fmatch_t<decltype([](int, double, short){}), std::tuple<int, double, char, short>>,
            std::index_sequence<0, 1, 3>>();

    execute<unordered_fmatch_t<void(float, int, char, int), std::tuple<int, short, int, double, char, float>>,
            std::index_sequence<5, 0, 4, 2>>();
    execute<unordered_fmatch_t<decltype([](char, int, float, int){}), std::tuple<int, double, char, float, int>>,
            std::index_sequence<2, 0, 3, 4>>();

    auto f1 = [](double a, int b, int c, std::string& s, std::pair<int, double>& p, float f)
              {
                  std::cout << a << std::endl;
                  std::cout << b << std::endl;
                  std::cout << c << std::endl;
                  std::cout << s << std::endl;
                  std::cout << p.second << std::endl;
                  std::cout << p.first << std::endl;

                  return f;
              };

    auto argx = std::make_tuple(1, 2.5f, std::string("monster"), 7, -3, std::make_pair(20, 80.9), 4.7, 5);

    // expected output: 4.7, 1, 7, monster, 80.9, 20, 2.5
    std::cout << advanced_apply(argx, f1) << std::endl;
    // or std::cout << advanced_apply(f1, argx) << std::endl;

    auto f2 = [](int& a, float b)
              {
                  std::cout << a << std::endl;

                  return b;
              };

    auto argy = std::make_pair(3.6f, 2020);

    // expected output: 2020, 3.6
    std::cout << advanced_apply(f2, argy) << std::endl;
    // or std::cout << advanced_apply(argy, f2) << std::endl;

    std::cout << "reverse_multi_apply" << std::endl;
    auto f3 = [](const std::pair<int, double>& p, double f, int a, float b, const std::string& s, int c)
              {
                  std::cout << p.second << std::endl;
                  std::cout << p.first << std::endl;
                  std::cout << f << std::endl;
                  std::cout << a << std::endl;
                  std::cout << b << std::endl;
                  std::cout << s << std::endl;

                  return c;
              };

    std::cout << reverse_multi_apply(f3, std::make_tuple(1, 2.5f, std::string("monster"), -3),
                 std::make_tuple(std::make_pair(20, 80.9), 4.7)) << std::endl;

    auto ints = select_values_of_type<int>(5.f, 3, std::string("Template"), 1,  4.5, 9);
    std::cout << ints[2] << std::endl;

    auto tups = exclude_values_of_type<int>(5.f, 3, std::string("Template"), 1,  4.5, 9);
    std::cout << std::get<2>(tups) << std::endl;

    execute<map_find_v<int, std::tuple<std::tuple<char, float>, std::tuple<int, char>>>, 1>();
    execute<map_find_v<int, std::tuple<offset<int, 2>, offset<char, 1>, offset<short, 3>>>, 0>();

    execute<map_update_t<char, short, std::tuple<std::tuple<char, float>, std::tuple<int, char>>>,
            std::tuple<std::tuple<char, short>, std::tuple<int, char>>>();

    using fg1 = find_group_t<char, std::tuple<std::tuple<float, char>, std::tuple<double, int, char>>>;
    execute<first_v<fg1>, 0>();
    execute<second_v<fg1>, 1>();
    execute<typeof_t<fg1>, std::tuple<float, char>>();

    using fg2 = find_group_t<c_6, std::tuple<std::integer_sequence<int, 3, -2>,
            std::integer_sequence<int, 6, 3>, std::integer_sequence<int, 6, 5>>>;
    execute<first_v<fg2>, 1>();
    execute<second_v<fg2>, 0>();
    execute<typeof_t<fg2>, std::integer_sequence<int, 6, 3>>();

    using fg3 = find_group_if_t<is_tuple, std::tuple<>, std::tuple<std::tuple<float, char>,
                std::tuple<std::tuple<double>, int, char>>>;
    execute<first_v<fg3>, 1>();
    execute<second_v<fg3>, 0>();
    execute<typeof_t<fg3>, std::tuple<std::tuple<double>, int, char>>();

    execute<find_backward_v<char, std::tuple<float, char, double, int, char>>, 4>();
    execute<find_backward_v<c_3, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 3>();

    execute<find_not_v<char, std::tuple<float, char, double, int, char>>, 0>();
    execute<find_not_v<c_3, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 1>();

    execute<find_not_backward_v<char, std::tuple<float, char, double, int, char>>, 3>();
    execute<find_not_backward_v<c_3, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 5>();

    execute<find_v<float, std::tuple<char, int, double, int, char>>, 5>();
    execute<find_v<c_4, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 6>();

    execute<find_backward_v<float, std::tuple<char, int, double, int, char>>, 5>();
    execute<find_backward_v<c_4, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 6>();

    execute<find_not_v<float, std::tuple<char, int, double, int, char>>, 0>();
    execute<find_not_v<c_4, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 0>();

    execute<find_not_backward_v<float, std::tuple<char, int, double, int, char>>, 4>();
    execute<find_not_backward_v<c_4, std::integer_sequence<int, 3, -2, 6, 3, 6, 5>>, 5>();

    execute<tuple_element_size_v<2, std::tuple<short, int, double>>, sizeof(double)>();

    using nest1 = T0<T1<T2<T3<T4<>>>>>;
    using nest2 = T0<T1<T2<T3<T4<int>>>>>;

    using flat1 = std::tuple<T0<>, T1<>, T2<>, T3<>, T4<>>;
    using flat2 = std::tuple<T0<>, T1<>, T2<>, T3<>, T4<>, int>;

    execute<!is_nest_v<int>>();
    execute<is_nest_v<T1<T2<>>>>();
    execute<is_nest_v<T1<T2<int>>>>();
    execute<is_nest_v<std::tuple<>>>();
    execute<!is_nest_v<T1<int, T2<>>>>();
    execute<!is_nest_v<T1<T2<int, char>>>>();

    execute<nest_depth_v<nest1>, 5>();
    execute<nest_depth_v<nest2>, 5>();

    execute<nest_size_v<nest1>, 5>();
    execute<nest_size_v<nest2>, 6>();

    execute<nest_element_t<3, nest1>, T3<T4<>>>();
    execute<nest_element_t<5, nest2>, int>();

    execute<nest_clear_t<nest1>, T0<T1<T2<T3<T4<>>>>>>();
    execute<nest_clear_t<nest2>, T0<T1<T2<T3<T4<>>>>>>();

    execute<nest_set_t<nest1, nullptr_t>, T0<T1<T2<T3<T4<nullptr_t>>>>>>();
    execute<nest_set_t<nest2, nullptr_t>, T0<T1<T2<T3<T4<nullptr_t>>>>>>();

    execute<nest_set_t<nest1, nest2>, T0<T1<T2<T3<T4<T0<T1<T2<T3<T4<int>>>>>>>>>>>();
    execute<nest_set_t<nest2, nest1>, T0<T1<T2<T3<T4<T0<T1<T2<T3<T4<>>>>>>>>>>>();

    execute<nest_concat_t<T0<int>, T1<T2<short>>, T3<>, T4<int>>, T0<T1<T2<T3<T4<int>>>>>>();
    execute<nest_concat_t<std::tuple<>, T1<T2<>>, T3<T4<>>>, std::tuple<T1<T2<T3<T4<>>>>>>();

    execute<to_flat_t<nest1>, flat1>();
    execute<to_nest_t<flat1>, nest1>();

    execute<to_flat_t<nest2>, flat2>();
    execute<to_nest_t<flat2>, nest2>();

    execute<nest_erase_t<1, 4, nest1>, T0<T4<>>>();
    execute<nest_erase_t<2, 5, nest2>, T0<T1<int>>>();

    execute<nest_range_t<1, 4, nest1>, T1<T2<T3<>>>>();
    execute<nest_range_t<2, 5, nest2>, T2<T3<T4<>>>>();

    execute<nest_extent_t<1, 4, nest1>, T3<T2<T1<>>>>();
    execute<nest_extent_t<2, 5, nest2>, T4<T3<T2<>>>>();

    execute<nest_degree_t<0, 3, nest1>, T4<T3<T2<>>>>();
    execute<nest_degree_t<1, 4, nest2>, T3<T2<T1<>>>>();

    execute<nest_swap_t<0, 3, nest1>, T3<T1<T2<T0<T4<>>>>>>();
    execute<nest_swap_t<1, 4, nest2>, T0<T4<T2<T3<T1<int>>>>>>();

    execute<nest_unique_t<T0<T1<T2<T1<T3<T4<T4<>>>>>>>>, T0<T1<T2<T3<T4<>>>>>>();
    execute<nest_unique_t<T0<T1<T2<T1<T3<T4<T0<int>>>>>>>>, T0<T1<T2<T3<T4<int>>>>>>();

    execute<nest_remove_unique_t<T0<T1<T2<T1<T3<T4<T4<>>>>>>>>, T1<T1<T4<T4<>>>>>();
    execute<nest_remove_unique_t<T0<T1<T2<T1<T3<T4<T0<int>>>>>>>>, T0<T0<T1<T1<>>>>>();

    execute<nest_remove_duplicate_t<T0<T1<T2<T1<T3<T4<T4<>>>>>>>>, T0<T2<T3<>>>>();
    execute<nest_remove_duplicate_t<T0<T1<T2<T1<T3<T4<T0<int>>>>>>>>, T2<T3<T4<int>>>>();

    execute<nest_unique_elements_t<T0<T1<T2<T1<T3<T4<T4<>>>>>>>>, T0<T2<T3<>>>>();
    execute<nest_unique_elements_t<T0<T1<T2<T1<T3<T4<T0<int>>>>>>>>, T2<T3<T4<int>>>>();

    execute<nest_duplicate_elements_t<T0<T1<T2<T1<T3<T4<T4<>>>>>>>>, T1<T4<>>>();
    execute<nest_duplicate_elements_t<T0<T1<T2<T1<T3<T4<T0<int>>>>>>>>, T0<T1<>>>();

    execute<nest_midpoint_t<nest1>, T2<T3<T4<>>>>();
    execute<nest_midpoint_t<nest2>, T2<T3<T4<int>>>>();

    execute<nest_head_t<nest1>, T0<T1<T2<T3<>>>>>();
    execute<nest_head_t<nest2>, T0<T1<T2<T3<T4<>>>>>>();

    execute<nest_tail_t<nest1>, T1<T2<T3<T4<>>>>>();
    execute<nest_tail_t<nest2>, T1<T2<T3<T4<int>>>>>();

    execute<nest_reverse_t<nest1>, T4<T3<T2<T1<T0<>>>>>>();
    execute<nest_reverse_t<nest2>, T4<T3<T2<T1<T0<int>>>>>>();

    execute<nest_reverse_range_t<1, 4, nest1>, T0<T3<T2<T1<T4<>>>>>>();
    execute<nest_reverse_range_t<2, 5, nest2>, T0<T1<T4<T3<T2<int>>>>>>();

    execute<nest_subset_t<1, 3, nest1>, T1<T2<T3<>>>>();
    execute<nest_subset_t<2, 4, nest2>, T2<T3<T4<int>>>>();

    execute<nest_rotate_t<0, 2, 4, nest1>, T2<T3<T0<T1<T4<>>>>>>();
    execute<nest_rotate_t<1, 3, 5, nest2>, T0<T3<T4<T1<T2<int>>>>>>();

    execute<nest_shift_left_t<3, nest1>, T3<T4<T0<T1<T2<>>>>>>();
    execute<nest_shift_right_t<3, nest2>, T2<T3<T4<T0<T1<int>>>>>>();

    execute<nest_drop_t<2, nest1>, T2<T3<T4<>>>>();
    execute<nest_drop_last_t<2, nest2>, T0<T1<T2<T3<>>>>>();

    execute<nest_take_t<3, nest1>, T0<T1<T2<>>>>();
    execute<nest_take_last_t<3, nest2>, T3<T4<int>>>();

    execute<nest_erase_at_t<3, nest1>, T0<T1<T2<T4<>>>>>();
    execute<nest_erase_at_t<3, nest2>, T0<T1<T2<T4<int>>>>>();

    execute<nest_pivot_t<3, nest1>, T3<T4<T0<T1<T2<>>>>>>();
    execute<nest_pivot_t<3, nest2>, T3<T4<T0<T1<T2<int>>>>>>();

    execute<nest_remove_copy_t<T2, nest1>, T0<T1<T3<T4<>>>>>();
    execute<nest_remove_copy_t<T3, nest2>, T0<T1<T2<T4<int>>>>>();

    execute<nest_prepend_t<T2, nest1>, T2<T0<T1<T2<T3<T4<>>>>>>>();
    execute<nest_append_t<T3, nest2>, T0<T1<T2<T3<T4<T3<int>>>>>>>();

    execute<nest_change_t<1, T4, nest1>, T0<T4<T2<T3<T4<>>>>>>();
    execute<nest_change_t<2, T0, nest2>, T0<T1<T0<T3<T4<int>>>>>>();

    execute<nest_find_v<T2, nest1>, 2>();
    execute<nest_find_v<T4, nest2>, 4>();

    execute<nest_find_backward_v<T2, nest1>, 2>();
    execute<nest_find_backward_v<T4, nest2>, 4>();

    execute<nest_find_not_v<T2, nest1>, 0>();
    execute<nest_find_not_v<T4, nest2>, 0>();

    execute<nest_find_not_backward_v<T2, nest1>, 4>();
    execute<nest_find_not_backward_v<T4, nest2>, 3>();

    execute<nest_fill_t<3, T2>, T2<T2<T2<>>>>();

    execute<nest_assign_t<nest1, T0>, T0<T0<T0<T0<T0<>>>>>>();
    execute<nest_assign_t<nest2, T1>, T1<T1<T1<T1<T1<int>>>>>>();

    execute<nest_front_t<nest1>, T0<>>();
    execute<nest_back_t<nest2>, T4<>>();

    execute<nest_count_v<T2, T1<T2<T3<T2<>>>>>, 2>();
    execute<nest_count_v<T3, T1<T2<T3<T2<int>>>>>, 1>();

    execute<nest_find_nth_v<2, T2, T1<T2<T3<T2<>>>>>, 3>();
    execute<nest_find_nth_v<1, T3, T1<T2<T3<T2<int>>>>>, 2>();

    execute<nest_contains_v<T3, T0<T2<T3<T4<>>>>>>();
    execute<!nest_contains_v<T1, T0<T2<T3<T4<int>>>>>>();

    execute<nest_bmh_t<T3, T3<T1<T3<T3<T4<T0<>>>>>>>, std::index_sequence<0, 2, 3>>();
    execute<nest_kmp_t<T2, T4<T2<T0<T2<T2<T1<>>>>>>>, std::index_sequence<1, 3, 4>>();

    using perm1 = std::tuple<T0<T1<T2<int>>>, T0<T2<T1<int>>>, T1<T0<T2<int>>>,
                             T1<T2<T0<int>>>, T2<T0<T1<int>>>, T2<T1<T0<int>>>>;

    using perm2 = std::tuple<T0<T1<T2<int>>>, T0<T2<T1<int>>>, T1<T0<T2<int>>>,
                             T1<T2<T0<int>>>, T2<T1<T0<int>>>, T2<T0<T1<int>>>>;

    using perm3 = std::tuple<T0<T1<int>>, T0<T2<int>>, T1<T0<int>>, T1<T2<int>>, T2<T0<int>>, T2<T1<int>>>;

    execute<nest_loop_permutation_t<T0<T1<T2<int>>>>, perm1>();
    execute<nest_permutation_recursive_t<T0<T1<T2<int>>>>, perm2>();

    execute<nest_next_permutation_list<T0<T1<T2<int>>>>, perm1>();
    execute<nest_prev_permutation_list<T0<T1<T2<int>>>>, reverse_t<perm1>>();

    execute<nest_next_partial_permutation_list<2, T0<T1<T2<int>>>>, perm3>();
    execute<nest_prev_partial_permutation_list<2, T0<T1<T2<int>>>>, reverse_t<perm3>>();

    using cmb1 = std::tuple<T0<T1<int>>, T0<T2<int>>, T0<T3<int>>,
                            T1<T2<int>>, T1<T3<int>>, T2<T3<int>>>;

    using cmb2 = std::tuple<T3<T2<int>>, T3<T1<int>>, T3<T0<int>>,
                            T2<T1<int>>, T2<T0<int>>, T1<T0<int>>>;

    execute<nest_next_combination_list<2, T0<T1<T2<T3<int>>>>>, cmb1>();
    execute<nest_prev_combination_list<2, T0<T1<T2<T3<int>>>>>, cmb2>();

    execute<nest_slice_t<std::index_sequence<2, 1, 0, 3>, nest1>, T2<T1<T0<T3<>>>>>();
    execute<nest_slice_t<std::index_sequence<3, 0, 2, 1, 4, 5>, nest2>, T3<T0<T2<T1<T4<int>>>>>>();

    execute<nest_is_palindrome_v<T0<T1<T2<T1<T0<int>>>>>>>();
    execute<!nest_is_palindrome_v<T0<T1<T2<T1<T0<T2<>>>>>>>>();

    execute<nest_erase_subtype_t<T2<T3<>>, nest1>, T0<T1<T4<>>>>();
    execute<nest_erase_subtype_t<T3<T4<int>>, nest2>, T0<T1<T2<>>>>();

    execute<nest_eliminate_subtype_t<T2<T3<>>, nest1>, T0<T1<T4<>>>>();
    execute<nest_eliminate_subtype_t<T3<T4<int>>, nest2>, T0<T1<T2<>>>>();

    execute<nest_replace_subtype_t<T2<T3<>>, T3<T2<T0<>>>, nest1>, T0<T1<T3<T2<T0<T4<>>>>>>>();
    execute<nest_replace_subtype_t<T3<T4<int>>, T1<T0<T2<char>>>, nest2>, T0<T1<T2<T1<T0<T2<char>>>>>>>();

    execute<nest_contains_subtype_v<T2<T3<>>, nest1>>();
    execute<!nest_contains_subtype_v<T3<T2<>>, nest2>>();

    execute<nest_adjacent_t<T1<T2<T1<T3<T2<>>>>>>, T1<T1<T2<T2<T3<>>>>>>();
    execute<nest_adjacent_t<T0<T3<T2<T3<T2<int>>>>>>, T0<T3<T3<T2<T2<int>>>>>>();

    execute<binary_search_v<double, std::tuple<short, int, double>>>();
    execute<binary_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>>();

    execute<ternary_search_v<double, std::tuple<short, int, double>>>();
    execute<ternary_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>>();

    execute<exponential_search_v<double, std::tuple<short, int, double>>>();
    execute<exponential_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>>();

    execute<interpolation_search_v<double, std::tuple<short, int, double>>>();
    execute<interpolation_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>>();

    execute<fibonacci_search_v<double, std::tuple<short, int, double>>>();
    execute<fibonacci_search_v<c_7, std::integer_sequence<int, -2, 0, 3, 7, 8>>>();

    execute<majority_search_v<std::integer_sequence<int, 1, 2, 2, 3, 2, 1, 2>>, 2>();
    execute<majority_search_t<std::tuple<char, int, int, float, int, double, int>>, int>();

    execute<max_subarray_t<std::integer_sequence<int, -2, -3, 4, -1, -2, 1, 5, -3>>,
            std::integer_sequence<int, 2, 6, 7>>();

    execute<find_maximum_subarray_t<std::integer_sequence<int, -2, -3, 4, -1, -2, 1, 5, -3>>,
            std::integer_sequence<int, 2, 6, 7>>();

    execute<kadane_t<std::integer_sequence<int, -2, -3, 4, -1, -2, 1, 5, -3>>, c_7>();
    execute<kadane_v<std::integer_sequence<int, -2, -3, 4, -1, -2, 1, 5, -3>>, 7>();

    execute<inner_dot_t<std::integer_sequence<int, -3, 1, 2, 4, 5>,
            std::integer_sequence<int, 2, 4, -3, 4>>, std::integer_sequence<int, -6, 4, -6, 16>>();

    execute<inner_sum_t<std::integer_sequence<int, -3, 1, 2, 4, 5>,
            std::integer_sequence<int, 2, 4, -3, 4>>, std::integer_sequence<int, -1, 5, -1, 8>>();

    execute<inner_mul_t<4, std::integer_sequence<int, -3, 1, 2, 4, 5>>,
            std::integer_sequence<int, -12, 4, 8, 16, 20>>();

    execute<alter_t<std::integer_sequence<int, 1, 0, 3, 4>, size_t>,
            std::integer_sequence<size_t, 1, 0, 3, 4>>();

    execute<splat_t<2, 4, std::integer_sequence<int, 1, 0, 3, 4>>,
            std::integer_sequence<int, 3, 3, 3, 3>>();

    execute<splat_t<3, 4, std::tuple<int, char, short, int, double, char>>,
            std::tuple<int, int, int, int>>();

    struct foo
    {
    };

    struct bar
    {
        int x;
        double y;
    };

    execute<aggregate_arity<foo>(), 0>();
    execute<aggregate_arity_v<bar>, 2>();

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

    execute<best_match_t<char*, std::string, void>, std::string>();
    execute<best_match_t<int, std::string, double, char*>, double>();

    overload_set
    {
        [](auto x) { return x; },
        [](int x) { return x * 10; },
        [](double x) { return x / 10.; }
    }
    (10.0);

    for_value<1, -2, 3>([]<auto N>()
    {
        std::cout<< N << std::endl;
    });

    for_pack<std::index_sequence<5, 4, 7>, std::integer_sequence<int, 1, -2, 3>>([]<auto N>()
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

    for_pack<std::tuple<double, int, char>, std::tuple<short, float>>([]<auto N, typename T>()
    {
        std::cout << N << " " << typeid(T).name() << std::endl;
    });

    loop<3>([](auto N, auto&& v)
    {
        std::cout << N << " " << v << std::endl;
    }, 4);

    loop_for<1>(2, 3, 4)
    (
        [](auto i, auto j, auto k)
        {
            std::cout << '(' << i << ", " << j << ", " << k << ")" << std::endl;
        }
    );

    std::cout << std::endl;

    loop_for<0>(2, 3, 4)
    (
        [](auto i, auto j, auto k)
        {
            std::cout << '(' << i << ", " << j << ", " << k << ")" << std::endl;
        }
    );

    iterate<4>([]
    {
        std::cout << "x" << std::endl;
    });

    unroller<3> unroll;

    auto fa = [](double x, double y) { return std::make_pair(x, y); };
    auto fb = [](std::pair<double, double> p) { return p.first + p.second; };
    auto fc = [](double x) { return 2 * x; };

    std::cout << compose(fc, fb, fa)(4.0, 8.0) << std::endl;

    unroll([](auto&&... args)
    {
        (std::cout << ... << args) << std::endl;
    }, 1, 2.3, "[]<typename ...>(){}();");

    auto tuple = std::make_tuple(1, 2, 3.0, 5, 4);
    indices_for(tuple)([&tuple](auto... N){ (std::cout << ... << std::get<N>(tuple)) << std::endl; });

    std::cout << "tuple_apply " << tuple_apply(tuple, [](auto... args){ return (args + ...); }) << std::endl;
    std::cout << "tuple_reverse " << std::get<0>(tuple_reverse(tuple)) << std::endl;
    std::cout << "tuple_prepend " << std::get<0>(tuple_prepend(tuple, 0)) << std::endl;
    std::cout << "tuple_append " << std::get<5>(tuple_append(tuple, 8)) << std::endl;
    std::cout << "tuple_remove " << std::get<1>(tuple_remove<1>(tuple)) << std::endl;
    std::cout << "tuple_swap " << std::get<1>(tuple_swap<1, 4>(tuple)) << std::endl;
    std::cout << "tuple_range " << std::get<1>(tuple_range<1, 4>(tuple)) << std::endl;
    std::cout << "tuple_erase " << std::get<1>(tuple_erase<1, 4>(tuple)) << std::endl;
    std::cout << "tuple_reverse_range " << std::get<2>(tuple_reverse_range<2, 5>(tuple)) << std::endl;
    std::cout << "tuple_insert " << std::get<2>(tuple_insert<2>(tuple, 9)) << std::endl;
    std::cout << "tuple_replace " << std::get<3>(tuple_replace<3>(tuple, 7)) << std::endl;
    std::cout << "tuple_replace all " << std::get<1>(tuple_replace(tuple, 2, 6)) << std::endl;
    std::cout << "tuple_replace all " << std::get<3>(tuple_replace(tuple, 2, 6)) << std::endl;
    std::cout << "tuple_rotate " << std::get<2>(tuple_rotate<0, 2, 4>(tuple)) << std::endl;
    std::cout << "tuple_shift_left " << std::get<1>(tuple_shift_left<2>(tuple)) << std::endl;
    std::cout << "tuple_shift_right " << std::get<1>(tuple_shift_right<2>(tuple)) << std::endl;
    std::cout << "tuple_take " << std::get<1>(tuple_take<3>(tuple)) << std::endl;
    std::cout << "tuple_take_last " << std::get<2>(tuple_take_last<3>(tuple)) << std::endl;
    std::cout << "tuple_drop " << std::get<0>(tuple_drop<3>(tuple)) << std::endl;
    std::cout << "tuple_drop_last " << std::get<1>(tuple_drop_last<3>(tuple)) << std::endl;
    std::cout << "tuple_head " << std::get<3>(tuple_head(tuple)) << std::endl;
    std::cout << "tuple_tail " << std::get<3>(tuple_tail(tuple)) << std::endl;
    std::cout << "tuple_axial_symmetry " << std::get<1>(tuple_axial_symmetry(tuple)) << std::endl;
    std::cout << "tuple_axial_symmetry " << std::get<1>(tuple_axial_symmetry(tuple_head(tuple))) << std::endl;
    std::cout << "tuple_extract " << std::get<1>(tuple_extract<0, 2, 3>(tuple)) << std::endl;
    std::cout << "tuple_exclude " << std::get<1>(tuple_exclude<0, 2, 3>(tuple)) << std::endl;
    auto trans = tuple_transpose(std::make_tuple(tuple, std::make_tuple(7, 5)));
    std::cout << "tuple_transpose " << std::get<0>(std::get<1>(trans)) << std::endl;
    tuple_fill<3>(tuple, 3, 5);
    std::cout << "tuple_fill " << std::get<4>(tuple) << std::endl;
    std::cout << "tuple_splat " << std::get<2>(tuple_splat<2, 5>(tuple)) << std::endl;
    auto dupt = std::make_tuple(1, 's', 7.0, 2.0f, std::string("TMP"));
    std::cout << "tuple_unique " << std::get<0>(tuple_unique(dupt)) << std::endl;
    std::cout << "tuple_gather " << std::get<0>(tuple_gather<double, int, char>(dupt)) << std::endl;
    using indices_ = std::index_sequence<0, 3, 4>;
    std::cout << "tuple_slice " << std::get<2>(tuple_slice<indices_>(tuple)) << std::endl;
    std::cout << "tuple_repeat " << std::get<2>(tuple_repeat<4>(9)) << std::endl;
    std::cout << "tuple_filter " << std::get<2>(tuple_filter<std::is_arithmetic>(dupt)) << std::endl;
    std::cout << "tuple_chunk " << std::get<1>(std::get<1>(tuple_chunk<2>(tuple))) << std::endl;
    std::cout << "tuple_slide " << std::get<1>(std::get<1>(tuple_slide<3>(tuple))) << std::endl;
    std::cout << "tuple_stride " << std::get<1>(tuple_stride<2>(tuple)) << std::endl;
    std::cout << "tuple_subranges " << std::get<1>(std::get<1>(tuple_subranges<3>(tuple))) << std::endl;
    std::cout << "tuple_gather_invoke" << std::endl;
    tuple_gather_invoke<2, 0, 1>(dupt, pf);
    tuple_gather_invoke<double, int, char>(dupt, pf);

    execute<nth_level_pointer_t<4, int>, int****>();
    execute<call_ntimes_t<4, int, std::add_pointer>, int****>();

    execute<head_t<std::tuple<float, double, int>>, std::tuple<float, double>>();
    execute<head_t<std::integer_sequence<int, 1, 2, 3>>, std::integer_sequence<int, 1, 2>>();
    execute<tail_t<std::tuple<float, double, int>>, std::tuple<double, int>>();
    execute<tail_t<std::integer_sequence<int, 1, 2, 3>>, std::integer_sequence<int, 2, 3>>();

    execute<prepend_t<std::tuple<float, double, int>, int, float>,
            std::tuple<int, float, float, double, int>>();
    execute<prepend_t<std::integer_sequence<int, 1, 2, -2>, c_4, c_3>,
            std::integer_sequence<int, 4, 3, 1, 2, -2>>();
    execute<prepend_c<std::integer_sequence<int, 1, 2, -2>, 4, 3>,
            std::integer_sequence<int, 4, 3, 1, 2, -2>>();

    execute<append_t<std::tuple<float, double, int>, float, char>,
            std::tuple<float, double, int, float, char>>();
    execute<append_t<std::integer_sequence<int, 1, 2, -2>, c_4, c_3>,
            std::integer_sequence<int, 1, 2, -2, 4, 3>>();

    execute<append_range_t<std::tuple<float, double, int>, std::tuple<float, char>>,
            std::tuple<float, double, int, float, char>>();
    execute<append_range_t<std::integer_sequence<int, 1, 2, -2>, std::integer_sequence<int, 4, 3>>,
            std::integer_sequence<int, 1, 2, -2, 4, 3>>();

    execute<append_c<std::integer_sequence<int, 1, 2, -2>, 4, 3>,
            std::integer_sequence<int, 1, 2, -2, 4, 3>>();

    execute<replace_t<1, 3, std::tuple<char, float, double, int>, float, char>,
            std::tuple<char, float, char, int>>();
    execute<replace_c<1, 3, std::integer_sequence<int, 4, 1, 2, -2>, 4, 3>,
            std::integer_sequence<int, 4, 4, 3, -2>>();

    execute<replace_range_t<1, 3, std::tuple<char, float, double, int>,
            std::tuple<float, char, int, double>, 1, 3>, std::tuple<char, char, int, int>>();
    execute<replace_range_t<1, 3, std::integer_sequence<int, 4, 1, 2, -2>,
            std::integer_sequence<int, -2, 1, 0, 3>, 0, 3>,
            std::integer_sequence<int, 4, -2, 1, 0, -2>>();

    execute<copy_backward_t<std::tuple<int, char, double>, std::tuple<short, char, int, char>>,
            std::tuple<short, int, char, double>>();

    execute<insert_t<2, std::tuple<float, double, int>, float, char>,
            std::tuple<float, double, float, char, int>>();
    execute<insert_t<1, std::integer_sequence<int, 1, 2, -2>, c_0, c_4>,
            std::integer_sequence<int, 1, 0, 4, 2, -2>>();
    execute<insert_c<1, std::integer_sequence<int, 1, 2, -2>, 0, 4>,
            std::integer_sequence<int, 1, 0, 4, 2, -2>>();

    execute<insert_range_t<2, std::tuple<float, double, int>, std::tuple<float, char, char>, 0, 2>,
            std::tuple<float, double, float, char, int>>();
    execute<insert_range_t<1, std::integer_sequence<int, 1, 2, -2>,
            std::integer_sequence<int, 0, 9, -4, 3>, 1, 3>, std::integer_sequence<int, 1, 9, -4, 2, -2>>();

    execute<fill_t<3, int>, std::tuple<int, int, int>>();
    execute<fill_t<5, c_2>, std::integer_sequence<int, 2, 2, 2, 2, 2>>();
    execute<fill_c<5, 2>, std::integer_sequence<int, 2, 2, 2, 2, 2>>();
    execute<fill_t<3, T1<>>, std::tuple<T1<>, T1<>, T1<>>>();

    execute<assign_t<std::tuple<char, short, double>, int>, std::tuple<int, int, int>>();
    execute<assign_t<std::index_sequence<1, 2, 3, 4>, c_0>, std::index_sequence<0, 0, 0, 0>>();

    execute<cycle_t<3, int, double>, std::tuple<int, double, int, double, int, double>>();
    execute<cycle_t<3, c_2, c_4>, std::integer_sequence<int, 2, 4, 2, 4, 2, 4>>();
    execute<cycle_c<3, 2, 4>, std::integer_sequence<int, 2, 4, 2, 4, 2, 4>>();

    execute<rotate_t<0, 2, 5, std::tuple<int, char, double, float, int64_t>>,
            std::tuple<double, float, int64_t, int, char>>();
    execute<rotate_t<0, 2, 5, std::integer_sequence<int, 1, 2, 3, 4, 5>>,
            std::integer_sequence<int, 3, 4, 5, 1, 2>>();
    execute<rotate_t<2, 4, 7, std::integer_sequence<int, 9, 8, 1, 2, 3, 4, 5, 7, 6>>,
            std::integer_sequence<int, 9, 8, 3, 4, 5, 1, 2, 7, 6>>();

    execute<rotate_copy_t<1, 2, 4, std::tuple<int, char, short, bool, double>,
            std::tuple<float>>, std::tuple<float, short, bool, char>>();
    execute<rotate_copy_t<2, 3, 7, std::index_sequence<1, 2, 3, 4, 5, 6, 9>,
            std::index_sequence<7, 8>>, std::index_sequence<7, 8, 4, 5, 6, 9, 3>>();

    execute<revolve_t<1, 3, 5, std::tuple<bool, int, char, double, float, int64_t>>,
            std::tuple<double, float, int, char>>();
    execute<revolve_t<0, 2, 4, std::integer_sequence<int, 1, 2, 3, 4, 5>>,
            std::integer_sequence<int, 3, 4, 1, 2>>();

    execute<shift_left_t<2, std::tuple<int, char, double, float, int64_t>>,
            std::tuple<double, float, int64_t, int, char>>();
    execute<shift_left_t<2, std::integer_sequence<int, 1, 2, 3, 4, 5>>,
            std::integer_sequence<int, 3, 4, 5, 1, 2>>();

    execute<shift_right_t<2, std::tuple<int, char, double, float, int64_t>>,
            std::tuple<float, int64_t, int, char, double>>();
    execute<shift_right_t<2, std::integer_sequence<int, 1, 2, 3, 4, 5>>,
            std::integer_sequence<int, 4, 5, 1, 2, 3>>();

    execute<zero_sequence_t<int, 3>, std::integer_sequence<int, 0, 0, 0>>();

    execute<integer_sequence_t<int, 3, 2, 0>, std::integer_sequence<int, 2, 2, 2>>();
    execute<integer_sequence_t<int, 4, 3, 1>, std::integer_sequence<int, 3, 4, 5, 6>>();
    execute<integer_sequence_t<int, 6, 5, -1>, std::integer_sequence<int, 5, 4, 3, 2, 1, 0>>();

    execute<odd_t<std::tuple<int, char, double, int, char>>, std::tuple<char, int>>();
    execute<odd_t<std::integer_sequence<int, 1, 9, 0, 4, 2>>, std::integer_sequence<int, 9, 4>>();

    execute<even_t<std::tuple<int, char, double, int, char>>, std::tuple<int, double, char>>();
    execute<even_t<std::integer_sequence<int, 1, 9, 0, 4, 2>>, std::integer_sequence<int, 1, 0, 2>>();

    execute<chunk_t<2, std::tuple<int, char, double, int, char, short>>,
            std::tuple<std::tuple<int, char>, std::tuple<double, int>, std::tuple<char, short>>>();
    execute<chunk_t<3, std::index_sequence<1, 9, 0, 4, 2, 5, 7, 4>>,
            std::tuple<std::index_sequence<1, 9, 0>, std::index_sequence<4, 2, 5>, std::index_sequence<7, 4>>>();

    execute<slide_t<3, std::tuple<int, char, double, int, char, short>>,
            std::tuple<std::tuple<int, char, double>, std::tuple<char, double, int>,
            std::tuple<double, int, char>, std::tuple<int, char, short>>>();

    execute<slide_t<4, std::index_sequence<1, 9, 0, 4, 2, 5, 7, 4>>,
            std::tuple<std::index_sequence<1, 9, 0, 4>, std::index_sequence<9, 0, 4, 2>,
            std::index_sequence<0, 4, 2, 5>, std::index_sequence<4, 2, 5, 7>, std::index_sequence<2, 5, 7, 4>>>();

    execute<rotations_t<std::tuple<int, char, bool>>, std::tuple<std::tuple<int, char, bool>,
                        std::tuple<char, bool, int>, std::tuple<bool, int, char>>>();
    execute<rotations_t<std::index_sequence<1, 2, 3>>, std::tuple<std::index_sequence<1, 2, 3>,
                        std::index_sequence<2, 3, 1>, std::index_sequence<3, 1, 2>>>();

    execute<stride_t<2, std::tuple<int, char, double, int, char>>, std::tuple<int, double, char>>();
    execute<stride_t<3, std::index_sequence<1, 9, 0, 4, 2, 5, 7, 4>>, std::index_sequence<1, 4, 7>>();

    execute<take_nth_t<2, std::tuple<int, char, double, int, char>>, std::tuple<int, double, char>>();
    execute<take_nth_t<3, std::index_sequence<1, 9, 0, 4, 2, 5, 7, 4>>, std::index_sequence<1, 4, 7>>();

    execute<drop_nth_t<2, std::tuple<int, char, double, int, char>>, std::tuple<char, int>>();
    execute<drop_nth_t<3, std::index_sequence<1, 9, 0, 4, 2, 5, 7, 4>>, std::index_sequence<9, 0, 2, 5, 4>>();

    execute<count_v<c_1, std::integer_sequence<int, 1, 2, 3, 1>>, 2>();
    execute<count_v<char, std::tuple<char, double, char, int, float, char, int, double>>, 3>();

    execute<count_if_t<is_even, std::integer_sequence<int, 1, 2, 3, 1, 4>>, c_2>();
    execute<count_if_t<is_tuple, std::tuple<double, std::tuple<>, float, std::tuple<int>, double>>, c_2>();

    execute<count_if_v<is_even, std::integer_sequence<int, 1, 2, 3, 1, 4>>, 2>();
    execute<count_if_v<is_tuple, std::tuple<double, std::tuple<>, float, std::tuple<int>, double>>, 2>();

    execute<count_if_not_t<is_even, std::integer_sequence<int, 1, 2, 3, 1, 4>>, c_3>();
    execute<count_if_not_t<is_tuple, std::tuple<double, std::tuple<>, float, std::tuple<int>, double>>, c_3>();

    execute<count_if_not_v<is_even, std::integer_sequence<int, 1, 2, 3, 1, 4>>, 3>();
    execute<count_if_not_v<is_tuple, std::tuple<double, std::tuple<>, float, std::tuple<int>, double>>, 3>();

    execute<mode_v<std::integer_sequence<int, 1, 2, 3, 1>>, 1>();
    execute<monster::mode_t<std::integer_sequence<int, 1, 2, 3, 1>>, c_1>();
    execute<monster::mode_t<std::tuple<char, double, char, double, int, float, char>>, char>();

    execute<transform_t<std::add_pointer, std::tuple<int, double, char*>>,
            std::tuple<int*, double*, char**>>();
    execute<transform_t<succ, std::integer_sequence<int, 7, 5, -2, 3, 1>>,
            std::integer_sequence<int, 8, 6, -1, 4, 2>>();

    execute<transform_nth_t<1, std::add_pointer, std::tuple<int, double, char*>>,
            std::tuple<int, double*, char*>>();
    execute<transform_nth_t<2, succ, std::integer_sequence<int, 7, 5, -2, 3, 1>>,
            std::integer_sequence<int, 7, 5, -1, 3, 1>>();

    execute<transform_if_t<succ, is_even, std::integer_sequence<int, 2>,
            std::integer_sequence<int, 0, 3, 1, 2, 8, 4>>, std::integer_sequence<int, 2, 1, 3, 9, 5>>();
    execute<transform_if_not_t<succ, is_odd, std::integer_sequence<int, 3>,
            std::integer_sequence<int, 0, 3, 1, 2, 8, 4>>, std::integer_sequence<int, 3, 1, 3, 9, 5>>();

    execute<transform_maybe_t<succ, is_even,
            std::integer_sequence<int, 0, 3, 1, 2, 8, 4>>, std::integer_sequence<int, 1, 3, 9, 5>>();
    execute<transform_maybe_t<succ, is_odd,
            std::integer_sequence<int, 0, 3, 1, 2, 7, 5>>, std::integer_sequence<int, 4, 2, 8, 6>>();

    execute<transform_while_t<succ, is_even, std::integer_sequence<int>,
            std::integer_sequence<int, 0, 2, 4, 2, 1, 8, 4>>, std::integer_sequence<int, 1, 3, 5, 3>>();
    execute<transform_while_not_t<succ, is_even, std::integer_sequence<int>,
            std::integer_sequence<int, 7, 5, 3, 1, 2, 8, 4>>, std::integer_sequence<int, 8, 6, 4, 2>>();

    execute<generate_t<negate_t, std::integer_sequence<int, 4, -3, -6, 5, 0, -2>, 1, 4>,
            std::integer_sequence<int, 4, 3, 6, -5, 0, -2>>();
    execute<generate_t<std::add_pointer, std::tuple<int, char, int*, short, double, int*>, 2, 5>,
            std::tuple<int, char, int**, short*, double*, int*>>();

    execute<generate_n_t<negate_t, std::integer_sequence<int, 4, -3, -6, 5, 0, -2>, 3, 2>,
            std::integer_sequence<int, 4, -3, 6, -5, 0, -2>>();
    execute<generate_n_t<std::add_pointer, std::tuple<int, char, int*, short, double, int*>, 4>,
            std::tuple<int*, char*, int**, short*, double, int*>>();

    using sr1 = std::tuple<std::tuple<int, float, double>, std::tuple<char, short>, std::tuple<bool, nullptr_t>>;
    using sr2 = std::tuple<std::index_sequence<0, 1, 2, 3>, std::index_sequence<4, 5, 6>, std::index_sequence<7, 8, 9>>;
    execute<subranges_t<3, std::tuple<int, float, double, char, short, bool, nullptr_t>>, sr1>();
    execute<subranges_t<3, std::index_sequence<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>>, sr2>();

    execute<apply_subranges_t<tail, 3, std::tuple<int, float, double, char, short, bool, nullptr_t>>,
            std::tuple<std::tuple<float, double>, std::tuple<short>, std::tuple<nullptr_t>>>();
    execute<apply_subranges_t<max_element, 3, std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>>,
            std::tuple<c_3, c_6, c_9>>();

    execute<is_palindrome_v<std::tuple<int, double, int, int, double, int>>>();
    execute<is_palindrome_v<std::integer_sequence<int, 3, 0, 2, 1, 2, 0, 3>>>();
    execute<!is_palindrome_v<std::tuple<int, double, char, int, int, double, int>>>();
    execute<!is_palindrome_v<std::integer_sequence<int, 0, 2, 1, 2, 0, 3>>>();

    execute<is_subset_v<std::integer_sequence<int, 4>, std::integer_sequence<int, 4>>>();
    execute<!is_subset_v<std::integer_sequence<int, 4, 5, 6>, std::integer_sequence<int, 4>>>();
    execute<is_subset_v<std::integer_sequence<int, 4, 5, 6>,
            std::integer_sequence<int, 1, 2, 3, 4, 5, 6, 7>>>();
    execute<is_subset_v<std::tuple<float, char, double>,
            std::tuple<int, double, char, float, char, double, int>>>();

    execute<cartesian_product_t<std::tuple<int, double>, std::tuple<char, float>>,
            std::tuple<int, char, int, float, double ,char, double, float>>();
    execute<cartesian_product_t<std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>,
            std::integer_sequence<int, 1, 3, 1, 4, 1, 5, 2, 3, 2, 4, 2, 5>>();

    using tuples = std::tuple<std::tuple<int, char>, std::tuple<float, double>, std::tuple<short, bool, nullptr_t>>;
    using result = std::tuple<std::tuple<int, float, short>, std::tuple<int, float, bool>,
                              std::tuple<int, float, nullptr_t>, std::tuple<int, double, short>,
                              std::tuple<int, double, bool>, std::tuple<int, double, nullptr_t>,
                              std::tuple<char, float, short>, std::tuple<char, float, bool>,
                              std::tuple<char, float, nullptr_t>, std::tuple<char, double, short>,
                              std::tuple<char, double, bool>, std::tuple<char, double, nullptr_t>>;

    using pairs = std::tuple<std::tuple<pair_v<0, 0>, pair_v<1, 0>, pair_v<2, 0>>,
                             std::tuple<pair_v<0, 0>, pair_v<1, 0>, pair_v<2, 1>>,
                             std::tuple<pair_v<0, 0>, pair_v<1, 0>, pair_v<2, 2>>,
                             std::tuple<pair_v<0, 0>, pair_v<1, 1>, pair_v<2, 0>>,
                             std::tuple<pair_v<0, 0>, pair_v<1, 1>, pair_v<2, 1>>,
                             std::tuple<pair_v<0, 0>, pair_v<1, 1>, pair_v<2, 2>>,
                             std::tuple<pair_v<0, 1>, pair_v<1, 0>, pair_v<2, 0>>,
                             std::tuple<pair_v<0, 1>, pair_v<1, 0>, pair_v<2, 1>>,
                             std::tuple<pair_v<0, 1>, pair_v<1, 0>, pair_v<2, 2>>,
                             std::tuple<pair_v<0, 1>, pair_v<1, 1>, pair_v<2, 0>>,
                             std::tuple<pair_v<0, 1>, pair_v<1, 1>, pair_v<2, 1>>,
                             std::tuple<pair_v<0, 1>, pair_v<1, 1>, pair_v<2, 2>>>;

    execute<cartesian_product_indices_t<tuples>, pairs>();
    execute<expand_cartesian_product_t<pairs, tuples>, result>();

    execute<elements_t<std::index_sequence<2, 0, 1, 3>,
            std::tuple<std::tuple<int, char, int>,
                       std::tuple<double, float>,
                       std::tuple<short, int>,
                       std::tuple<float, char, int, nullptr_t>>>,
                       std::tuple<int, double, int, nullptr_t>>();

    execute<apply_indices_t<std::tuple<std::index_sequence<0, 1>, std::index_sequence<1, 0>>,
            std::tuple<std::index_sequence<1, 2, 3>, std::index_sequence<4, 5, 6>>>,
            std::tuple<std::index_sequence<1, 5>, std::index_sequence<2, 4>>>();

    execute<combinations_t<std::tuple<int, double>, std::tuple<char, float>>,
            std::tuple<std::tuple<int, char>,
                       std::tuple<int, float>,
                       std::tuple<double ,char>,
                       std::tuple<double, float>>>();

    execute<combinations_t<std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>,
            std::tuple<std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 1, 4>,
                       std::integer_sequence<int, 1, 5>,
                       std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 2, 4>,
                       std::integer_sequence<int, 2, 5>>>();

    execute<product_t<plus_t, std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>,
            std::tuple<c_4, c_5, c_6, c_5, c_6, c_7>>();
    execute<product_t<max, std::tuple<int, char>, std::tuple<short, uint64_t>>,
            std::tuple<int, uint64_t, short, uint64_t>>();

    execute<adjacent_transform_t<std::is_same, std::tuple<int, int, char, int, int>>,
            std::tuple<std::true_type, std::false_type, std::false_type, std::true_type>>();
    execute<adjacent_transform_t<plus_t, std::integer_sequence<int, 1, 2, 3, -4, 5, 6>>,
            std::integer_sequence<int, 3, 5, -1, 1, 11>>();

    execute<partial_fold_t<max, std::tuple<char, int, short, double, float>>,
            std::tuple<int, int, double, double>>();
    execute<partial_fold_t<plus_t, std::integer_sequence<int, 1, 2, 3, -4, 5, 6>>,
            std::integer_sequence<int, 3, 6, 2, 7, 13>>();

    execute<adjacent_filter_t<negaf<std::is_same>::template apply, std::tuple<int, int, char, int, int, short>>,
            std::tuple<int, char, int, short>>();
    execute<adjacent_filter_t<negaf<std::is_same>::template apply, std::integer_sequence<int, 1, 2, 2, 4, 5, 5>>,
            std::integer_sequence<int, 1, 2, 4, 5>>();

    execute<adjacent_remove_if_t<negaf<std::is_same>::template apply, std::tuple<int, int, char, int, int, short>>,
            std::tuple<int, char, int, short>>();
    execute<adjacent_remove_if_t<negaf<std::is_same>::template apply, std::integer_sequence<int, 1, 2, 2, 4, 5, 5>>,
            std::integer_sequence<int, 1, 2, 4, 5>>();

    using mat = std::tuple<std::index_sequence<1, 2, 3>,
                           std::index_sequence<4, 5, 6>,
                           std::index_sequence<7, 8, 9>>;

    execute<matrix_combinations_t<mat>,
            std::tuple<std::index_sequence<1, 5, 9>,
                       std::index_sequence<1, 6, 8>,
                       std::index_sequence<2, 4, 9>,
                       std::index_sequence<2, 6, 7>,
                       std::index_sequence<3, 4, 8>,
                       std::index_sequence<3, 5, 7>>>();

    execute<power_set_t<std::index_sequence<1, 2, 3, 4>>,
            std::tuple<std::index_sequence<>, std::index_sequence<1>,
            std::index_sequence<2>, std::index_sequence<1, 2>,
            std::index_sequence<3>, std::index_sequence<1, 3>,
            std::index_sequence<2, 3>, std::index_sequence<1, 2, 3>,
            std::index_sequence<4>, std::index_sequence<1, 4>,
            std::index_sequence<2, 4>, std::index_sequence<1, 2, 4>,
            std::index_sequence<3, 4>, std::index_sequence<1, 3, 4>,
            std::index_sequence<2, 3, 4>, std::index_sequence<1, 2, 3, 4>>>();

    execute<tokenize_t<19073>, std::integer_sequence<int, 1, 9, 0, 7, 3>>();
    execute<tokenize_t<19073, 100>, std::integer_sequence<int, 1, 90, 73>>();
    execute<tokenize_t<19073, 1000>, std::integer_sequence<int, 19, 73>>();

    execute<large_number_multiplier_t<tokenize_t<975>, tokenize_t<6084>>,
            std::integer_sequence<int, 5, 9, 3, 1, 9, 0, 0>>();

    execute<prefix_t<std::tuple<int, double>, float, char>,
            std::tuple<float, char, int, float, char, double>>();
    execute<prefix_t<std::integer_sequence<int, 1, 2>, c_3, c_4>,
            std::integer_sequence<int, 3, 4, 1, 3, 4, 2>>();
    execute<prefix_c<std::integer_sequence<int, 1, 2>, 3, 4>,
            std::integer_sequence<int, 3, 4, 1, 3, 4, 2>>();

    execute<suffix_t<std::tuple<int, double>, float, char>,
            std::tuple<int, float, char, double, float, char>>();
    execute<suffix_t<std::integer_sequence<int, 1, 2>, c_3, c_4>,
            std::integer_sequence<int, 1, 3, 4, 2, 3, 4>>();
    execute<suffix_c<std::integer_sequence<int, 1, 2>, 3, 4>,
            std::integer_sequence<int, 1, 3, 4, 2, 3, 4>>();

    execute<intersperse_t<std::tuple<int, double, short>, float, char>,
            std::tuple<int, float, char, double, float, char, short>>();
    execute<intersperse_t<std::integer_sequence<int, 1, 2, 5>, c_3, c_4>,
            std::integer_sequence<int, 1, 3, 4, 2, 3, 4, 5>>();
    execute<intersperse_c<std::integer_sequence<int, 1, 2, 5>, 3, 4>,
            std::integer_sequence<int, 1, 3, 4, 2, 3, 4, 5>>();

    execute<zip_t<std::tuple<int, double>, std::tuple<char, float, nullptr_t>>,
            std::tuple<int, char, double, float>>();
    execute<zip_t<std::integer_sequence<int, 1>, std::integer_sequence<int, 3>>,
            std::integer_sequence<int, 1, 3>>();
    execute<zip_t<std::integer_sequence<int, 1, 2>, std::integer_sequence<int, 3, 4, 5>>,
            std::integer_sequence<int, 1, 3, 2, 4>>();

    execute<zip_with_t<multiplies_t, std::integer_sequence<int, 1, 2, -3>,
            std::integer_sequence<int, 3, 4, 5>>, std::integer_sequence<int, 3, 8, -15>>();
    execute<zip_with_t<pair_t, std::tuple<int, char, short, double>, std::tuple<char, double, float>>,
            std::tuple<pair_t<int, char>, pair_t<char, double>, pair_t<short, float>>>();

    execute<zip_transform_t<mul, std::integer_sequence<int, 1, 2, -3>,
            std::integer_sequence<int, 3, 4, 5>>, std::integer_sequence<int, 3, 8, -15>>();
    execute<zip_transform_t<max_element, std::tuple<int, char, double>, std::tuple<char, double, float>>,
            std::tuple<int, double, double>>();

    execute<next_permutation_t<std::tuple<char, int, double>>, std::tuple<char, double, int>>();
    execute<next_permutation_t<std::tuple<char, double, int>>, std::tuple<int, char, double>>();
    execute<next_permutation_t<std::tuple<int, char, double>>, std::tuple<int, double, char>>();
    execute<next_permutation_t<std::tuple<int, double, char>>, std::tuple<double, char, int>>();
    execute<next_permutation_t<std::tuple<double, char, int>>, std::tuple<double, int, char>>();
    execute<next_permutation_t<std::tuple<double, int, char>>, std::tuple<double, int, char>>();

    using list_t = std::tuple<std::tuple<char, int, double>,
                              std::tuple<char, double, int>,
                              std::tuple<int, char, double>,
                              std::tuple<int, double, char>,
                              std::tuple<double, char, int>,
                              std::tuple<double, int, char>>;

    execute<get_matrix_element_t<3, 1, list_t>, double>();

    execute<matrix_transpose_t<list_t>,
            std::tuple<std::tuple<char, char, int, int, double, double>,
                       std::tuple<int, double, char, double, char, int>,
                       std::tuple<double, int, double, char, int, char>>>();

    execute<matrix_transpose_r_t<list_t>,
            std::tuple<std::tuple<char, int, char, double, int, double>,
                       std::tuple<int, char, double, char, double, int>,
                       std::tuple<double, double, int, int, char, char>>>();

    execute<get_matrix_row_t<1, list_t>, std::tuple<char, double, int>>();
    execute<get_matrix_col_t<1, list_t>, std::tuple<int, double, char, double, char, int>>();

    using nullt = std::tuple<nullptr_t, nullptr_t>;
    execute<sub_matrix_replace_t<4, 1, std::tuple<nullt, nullt>, list_t>,
            std::tuple<std::tuple<char, int, double>,
                       std::tuple<char, double, int>,
                       std::tuple<int, char, double>,
                       std::tuple<int, double, char>,
                       std::tuple<double, nullptr_t, nullptr_t>,
                       std::tuple<double, nullptr_t, nullptr_t>>>();

    execute<next_permutation_list<std::tuple<char, int, double>>, list_t>();
    execute<prev_permutation_list<std::tuple<double, int, char>>, reverse_t<list_t>>();

    execute<loop_permutation_t<std::tuple<char, int, double>>, list_t>();
    execute<loop_permutation_t<std::tuple<double, int, char>>, reverse_t<list_t>>();

    using index3 = std::tuple<std::index_sequence<0, 1, 2>,
                              std::index_sequence<0, 2, 1>,
                              std::index_sequence<1, 0, 2>,
                              std::index_sequence<1, 2, 0>,
                              std::index_sequence<2, 0, 1>,
                              std::index_sequence<2, 1, 0>>;

    using index4 = std::tuple<std::index_sequence<0, 1, 2>,
                              std::index_sequence<0, 1, 3>,
                              std::index_sequence<0, 1, 4>,
                              std::index_sequence<0, 2, 3>,
                              std::index_sequence<0, 2, 4>,
                              std::index_sequence<0, 3, 4>,
                              std::index_sequence<1, 2, 3>,
                              std::index_sequence<1, 2, 4>,
                              std::index_sequence<1, 3, 4>,
                              std::index_sequence<2, 3, 4>>;

    execute<permutation_index_t<3>, index3>();
    execute<combination_index_t<3, 5>, index4>();

    using list_n = std::tuple<std::integer_sequence<int, 1, 2, 3>,
                              std::integer_sequence<int, 1, 3, 2>,
                              std::integer_sequence<int, 2, 1, 3>,
                              std::integer_sequence<int, 2, 3, 1>,
                              std::integer_sequence<int, 3, 1, 2>,
                              std::integer_sequence<int, 3, 2, 1>>;

    execute<get_matrix_element_v<3, 1, list_n>, 3>();
    using sme = set_matrix_element_c<3, 1, 7, list_n>;
    execute<get_matrix_element_v<3, 1, sme>, 7>();

    execute<is_matrix_v<std::tuple<std::tuple<int, char>>>>();
    execute<is_matrix_v<std::tuple<std::index_sequence<0, 1>, std::index_sequence<2, 3>>>>();

    execute<matrix_t<3, 3, int>,
            std::tuple<std::tuple<int, int, int>,
                       std::tuple<int, int, int>,
                       std::tuple<int, int, int>>>();

    execute<square_matrix_t<3, c_0>,
            std::tuple<std::integer_sequence<int, 0, 0, 0>,
                       std::integer_sequence<int, 0, 0, 0>,
                       std::integer_sequence<int, 0, 0, 0>>>();

    execute<set_matrix_row_t<3, std::integer_sequence<int, 7, 8, 9>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 7, 8, 9>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<set_matrix_col_t<1, std::integer_sequence<int, 4, 5, 6, 7, 8, 9>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 4, 3>,
                       std::integer_sequence<int, 1, 5, 2>,
                       std::integer_sequence<int, 2, 6, 3>,
                       std::integer_sequence<int, 2, 7, 1>,
                       std::integer_sequence<int, 3, 8, 2>,
                       std::integer_sequence<int, 3, 9, 1>>>();

    execute<insert_matrix_row_t<2, std::integer_sequence<int, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 4, 5, 6>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<insert_matrix_col_t<1, std::integer_sequence<int, 7, 8, 9, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 7, 2, 3>,
                       std::integer_sequence<int, 1, 8, 3, 2>,
                       std::integer_sequence<int, 2, 9, 1, 3>,
                       std::integer_sequence<int, 2, 4, 3, 1>,
                       std::integer_sequence<int, 3, 5, 1, 2>,
                       std::integer_sequence<int, 3, 6, 2, 1>>>();

    execute<vertical_prepend_t<std::integer_sequence<int, 7, 8, 9>, list_n>,
            std::tuple<std::integer_sequence<int, 7, 8, 9>,
                       std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<vertical_append_t<std::integer_sequence<int, 7, 8, 9>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 7, 8, 9>>>();

    execute<horizontal_prepend_t<std::integer_sequence<int, 7, 8, 9, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 7, 1, 2, 3>,
                       std::integer_sequence<int, 8, 1, 3, 2>,
                       std::integer_sequence<int, 9, 2, 1, 3>,
                       std::integer_sequence<int, 4, 2, 3, 1>,
                       std::integer_sequence<int, 5, 3, 1, 2>,
                       std::integer_sequence<int, 6, 3, 2, 1>>>();

    execute<horizontal_append_t<std::integer_sequence<int, 7, 8, 9, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3, 7>,
                       std::integer_sequence<int, 1, 3, 2, 8>,
                       std::integer_sequence<int, 2, 1, 3, 9>,
                       std::integer_sequence<int, 2, 3, 1, 4>,
                       std::integer_sequence<int, 3, 1, 2, 5>,
                       std::integer_sequence<int, 3, 2, 1, 6>>>();

    execute<add_matrix_row_t<2, std::integer_sequence<int, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 6, 6, 9>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<add_matrix_col_t<1, std::integer_sequence<int, 7, 8, 9, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 9, 3>,
                       std::integer_sequence<int, 1, 11, 2>,
                       std::integer_sequence<int, 2, 10, 3>,
                       std::integer_sequence<int, 2, 7, 1>,
                       std::integer_sequence<int, 3, 6, 2>,
                       std::integer_sequence<int, 3, 8, 1>>>();

    execute<mul_matrix_row_t<2, std::integer_sequence<int, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 8, 5, 18>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<mul_matrix_col_t<1, std::integer_sequence<int, 7, 8, 9, 4, 5, 6>, list_n>,
            std::tuple<std::integer_sequence<int, 1, 14, 3>,
                       std::integer_sequence<int, 1, 24, 2>,
                       std::integer_sequence<int, 2, 9, 3>,
                       std::integer_sequence<int, 2, 12, 1>,
                       std::integer_sequence<int, 3, 5, 2>,
                       std::integer_sequence<int, 3, 12, 1>>>();

    execute<scale_matrix_row_t<3, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 4, 6, 2>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<scale_add_matrix_row_t<3, 2, 4, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 7, 7, 4>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<scale_add_row_t<3, 2, 4, list_n>, std::integer_sequence<int, 7, 7, 4>>();

    execute<scale_mul_matrix_row_t<3, 2, 4, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 12, 6, 4>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<scale_mul_row_t<3, 2, 4, list_n>, std::integer_sequence<int, 12, 6, 4>>();

    execute<scale_matrix_row_range_t<3, 5, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 4, 6, 2>,
                       std::integer_sequence<int, 6, 2, 4>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<scale_matrix_col_t<1, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 4, 3>,
                       std::integer_sequence<int, 1, 6, 2>,
                       std::integer_sequence<int, 2, 2, 3>,
                       std::integer_sequence<int, 2, 6, 1>,
                       std::integer_sequence<int, 3, 2, 2>,
                       std::integer_sequence<int, 3, 4, 1>>>();

    execute<scale_add_matrix_col_t<1, 2, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 7>,
                       std::integer_sequence<int, 1, 3, 8>,
                       std::integer_sequence<int, 2, 1, 5>,
                       std::integer_sequence<int, 2, 3, 7>,
                       std::integer_sequence<int, 3, 1, 4>,
                       std::integer_sequence<int, 3, 2, 5>>>();

    execute<scale_add_col_t<1, 2, 2, list_n>, std::integer_sequence<int, 7, 8, 5, 7, 4, 5>>();

    execute<scale_mul_matrix_col_t<1, 2, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 12>,
                       std::integer_sequence<int, 1, 3, 12>,
                       std::integer_sequence<int, 2, 1, 6>,
                       std::integer_sequence<int, 2, 3, 6>,
                       std::integer_sequence<int, 3, 1, 4>,
                       std::integer_sequence<int, 3, 2, 4>>>();

    execute<scale_mul_col_t<1, 2, 2, list_n>, std::integer_sequence<int, 12, 12, 6, 6, 4, 4>>();

    execute<scale_matrix_col_range_t<1, 3, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 4, 6>,
                       std::integer_sequence<int, 1, 6, 4>,
                       std::integer_sequence<int, 2, 2, 6>,
                       std::integer_sequence<int, 2, 6, 2>,
                       std::integer_sequence<int, 3, 2, 4>,
                       std::integer_sequence<int, 3, 4, 2>>>();

    execute<scale_matrix_t<2, list_n>,
            std::tuple<std::integer_sequence<int, 2, 4, 6>,
                       std::integer_sequence<int, 2, 6, 4>,
                       std::integer_sequence<int, 4, 2, 6>,
                       std::integer_sequence<int, 4, 6, 2>,
                       std::integer_sequence<int, 6, 2, 4>,
                       std::integer_sequence<int, 6, 4, 2>>>();

    execute<remove_matrix_row_t<2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<remove_matrix_col_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 1, 2>,
                       std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 2, 1>,
                       std::integer_sequence<int, 3, 2>,
                       std::integer_sequence<int, 3, 1>>>();

    execute<remove_matrix_row_col_t<3, 1, list_n>,
            std::tuple<std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 1, 2>,
                       std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 3, 2>,
                       std::integer_sequence<int, 3, 1>>>();

    execute<remove_matrix_col_row_t<1, 3, list_n>,
            std::tuple<std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 1, 2>,
                       std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 3, 2>,
                       std::integer_sequence<int, 3, 1>>>();

    execute<swap_matrix_row_t<2, 4, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<swap_matrix_col_t<0, 2, list_n>,
            std::tuple<std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 1, 2, 3>>>();

    execute<matrix_row_range_t<2, 5, list_n>,
            std::tuple<std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>>>();

    execute<matrix_col_range_t<0, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2>,
                       std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 2, 1>,
                       std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 3, 1>,
                       std::integer_sequence<int, 3, 2>>>();

    execute<matrix_row_erase_t<2, 4, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<matrix_col_erase_t<0, 2, list_n>,
            std::tuple<std::integer_sequence<int, 3>,
                       std::integer_sequence<int, 2>,
                       std::integer_sequence<int, 3>,
                       std::integer_sequence<int, 1>,
                       std::integer_sequence<int, 2>,
                       std::integer_sequence<int, 1>>>();

    execute<matrix_row_col_erase_t<1, 4, 1, 2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 3, 2>,
                       std::integer_sequence<int, 3, 1>>>();

    execute<matrix_col_row_erase_t<1, 2, 1, 4, list_n>,
            std::tuple<std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 3, 2>,
                       std::integer_sequence<int, 3, 1>>>();

    execute<drop_row_up_t<2, list_n>,
            std::tuple<std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<drop_row_down_t<2, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>>>();

    execute<drop_col_left_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 3, 2>,
                       std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 3, 1>,
                       std::integer_sequence<int, 1, 2>,
                       std::integer_sequence<int, 2, 1>>>();

    execute<drop_col_right_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2>,
                       std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 2, 1>,
                       std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 3, 1>,
                       std::integer_sequence<int, 3, 2>>>();

    execute<matrix_row_rotate_t<1, 3, 5, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<matrix_col_rotate_t<0, 1, 3, list_n>,
            std::tuple<std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 2, 1, 3>>>();

    execute<matrix_row_pivot_t<2, list_n>,
            std::tuple<std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>>>(),

    execute<matrix_col_pivot_t<2, list_n>,
            std::tuple<std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 1, 3, 2>>>();

    execute<matrix_shift_left_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 2, 1, 3>>>();

    execute<matrix_shift_right_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 1, 3, 2>>>();

    execute<matrix_shift_up_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 1, 2, 3>>>();

    execute<matrix_shift_down_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 1, 2>>>();

    execute<matrix_row_reverse_t<3, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<matrix_col_reverse_t<1, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 1, 2>,
                       std::integer_sequence<int, 2, 3, 3>,
                       std::integer_sequence<int, 2, 1, 1>,
                       std::integer_sequence<int, 3, 3, 2>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    using matrix = std::tuple<std::integer_sequence<int, 0, 1, 2, 3, 4>,
                              std::integer_sequence<int, 5, 6, 7, 8, 9>>;

    execute<matrix_rowwise_reverse_t<matrix>,
            std::tuple<std::integer_sequence<int, 4, 3, 2, 1, 0>,
                       std::integer_sequence<int, 9, 8, 7, 6, 5>>>();

    execute<matrix_colwise_reverse_t<matrix>,
            std::tuple<std::integer_sequence<int, 5, 6, 7, 8, 9>,
                       std::integer_sequence<int, 0, 1, 2, 3, 4>>>();

    execute<rotate_matrix_left_t<matrix>,
            std::tuple<std::integer_sequence<int, 4, 9>,
                       std::integer_sequence<int, 3, 8>,
                       std::integer_sequence<int, 2, 7>,
                       std::integer_sequence<int, 1, 6>,
                       std::integer_sequence<int, 0, 5>>>();

    execute<rotate_matrix_right_t<matrix>,
            std::tuple<std::integer_sequence<int, 5, 0>,
                       std::integer_sequence<int, 6, 1>,
                       std::integer_sequence<int, 7, 2>,
                       std::integer_sequence<int, 8, 3>,
                       std::integer_sequence<int, 9, 4>>>();

    execute<sub_matrix_t<0, 2, 1, 4, matrix>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 6, 7, 8>>>();

    execute<matrix_subset_t<1, 2, 1, 2, matrix>, std::tuple<std::integer_sequence<int, 7, 8>>>();

    execute<sub_matrix_transpose_t<0, 2, 1, 4, matrix>,
            std::tuple<std::integer_sequence<int, 1, 6>,
                       std::integer_sequence<int, 2, 7>,
                       std::integer_sequence<int, 3, 8>>>();

    execute<sub_matrix_reverse_t<0, 2, 1, 4, matrix>,
            std::tuple<std::integer_sequence<int, 8, 7, 6>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<matrix_row_col_reverse_t<1, 3, matrix>,
            std::tuple<std::integer_sequence<int, 0, 1, 2, 6, 4>,
                       std::integer_sequence<int, 9, 8, 7, 3, 5>>>();

    execute<matrix_col_row_reverse_t<3, 1, matrix>,
            std::tuple<std::integer_sequence<int, 0, 1, 2, 8, 4>,
                       std::integer_sequence<int, 9, 3, 7, 6, 5>>>();

    execute<matrix_row_reverse_range_t<2, 5, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 3, 1, 2>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 3, 2, 1>>>();

    execute<matrix_col_reverse_range_t<1, 3, list_n>,
            std::tuple<std::integer_sequence<int, 1, 2, 1>,
                       std::integer_sequence<int, 1, 1, 2>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 3, 3, 2>,
                       std::integer_sequence<int, 3, 2, 3>>>();

    execute<matrix_row_col_reverse_range_t<0, 2, 2, 4, matrix>,
            std::tuple<std::integer_sequence<int, 4, 3, 7, 6, 0>,
                       std::integer_sequence<int, 9, 8, 2, 1, 5>>>();

    execute<matrix_col_row_reverse_range_t<2, 4, 0, 2, matrix>,
            std::tuple<std::integer_sequence<int, 4, 8, 7, 1, 0>,
                       std::integer_sequence<int, 9, 3, 2, 6, 5>>>();

    using lhs = std::tuple<std::integer_sequence<int, 0, 1, 2, 3>,
                           std::integer_sequence<int, 4, 5, 6, 7>>;

    using rhs = std::tuple<std::integer_sequence<int, -2, 0, 4, 1>,
                           std::integer_sequence<int, 1, 6, -5, 3>>;

    execute<matrix_element_add_v<1, 3, lhs, rhs>, 10>();
    execute<matrix_element_sub_v<1, 2, lhs, rhs>, 11>();

    execute<matrix_add_t<lhs, rhs>,
            std::tuple<std::integer_sequence<int, -2, 1, 6, 4>,
                       std::integer_sequence<int, 5, 11, 1, 10>>>();

    execute<matrix_sub_t<lhs, rhs>,
            std::tuple<std::integer_sequence<int, 2, 1, -2, 2>,
                       std::integer_sequence<int, 3, -1, 11, 4>>>();

    execute<matrix_horizontal_concat_t<lhs, rhs>,
            std::tuple<std::integer_sequence<int, 0, 1, 2, 3, -2, 0, 4, 1>,
                       std::integer_sequence<int, 4, 5, 6, 7, 1, 6, -5, 3>>>();

    execute<matrix_vertical_concat_t<lhs, rhs>,
            std::tuple<std::integer_sequence<int, 0, 1, 2, 3>,
                       std::integer_sequence<int, 4, 5, 6, 7>,
                       std::integer_sequence<int, -2, 0, 4, 1>,
                       std::integer_sequence<int, 1, 6, -5, 3>>>();

    using mid = std::tuple<std::integer_sequence<int, -8, 9>,
                           std::integer_sequence<int, 4, 0>,
                           std::integer_sequence<int, -4, 2>,
                           std::integer_sequence<int, 5, 3>>;

    execute<matrix_row_sort_range_t<1, 3, mid>,
            std::tuple<std::integer_sequence<int, -8, 9>,
                       std::integer_sequence<int, 0, 4>,
                       std::integer_sequence<int, -4, 2>,
                       std::integer_sequence<int, 5, 3>>>();

    execute<matrix_col_sort_range_t<1, 2, mid>,
            std::tuple<std::integer_sequence<int, -8, 0>,
                       std::integer_sequence<int, 4, 2>,
                       std::integer_sequence<int, -4, 3>,
                       std::integer_sequence<int, 5, 9>>>();

    execute<matrix_rowwise_sort_t<mid>,
            std::tuple<std::integer_sequence<int, -8, 9>,
                       std::integer_sequence<int, 0, 4>,
                       std::integer_sequence<int, -4, 2>,
                       std::integer_sequence<int, 3, 5>>>();

    execute<matrix_colwise_sort_t<mid>,
            std::tuple<std::integer_sequence<int, -8, 0>,
                       std::integer_sequence<int, -4, 2>,
                       std::integer_sequence<int, 4, 3>,
                       std::integer_sequence<int, 5, 9>>>();

    execute<matrix_row_col_sort_t<mid>,
            std::tuple<std::integer_sequence<int, -8, 2>,
                       std::integer_sequence<int, -4, 4>,
                       std::integer_sequence<int, 0, 5>,
                       std::integer_sequence<int, 3, 9>>>();

    execute<matrix_col_row_sort_t<mid>,
            std::tuple<std::integer_sequence<int, -8, 0>,
                       std::integer_sequence<int, -4, 2>,
                       std::integer_sequence<int, 3, 4>,
                       std::integer_sequence<int, 5, 9>>>();

    execute<matrix_multiply_t<rhs, mid>,
            std::tuple<std::integer_sequence<int, 5, -7>,
                       std::integer_sequence<int, 51, 8>>>();

    execute<matrix_elementwise_multiply_t<lhs, rhs>,
            std::tuple<std::integer_sequence<int, 0, 0, 8, 3>,
                       std::integer_sequence<int, 4, 30, -30, 21>>>();

    execute<row_multiply_t<1, lhs, rhs>, std::integer_sequence<int, 4, 30, -30, 21>>();
    execute<col_multiply_t<2, lhs, rhs>, std::integer_sequence<int, 8, -30>>();

    execute<matrix_multiply_t<col_matrix_t<std::integer_sequence<int, 5, 4, 3>>,
                              row_matrix_t<std::integer_sequence<int, 6, 7, 8>>>,
            std::tuple<std::integer_sequence<int, 30, 35, 40>,
                       std::integer_sequence<int, 24, 28, 32>,
                       std::integer_sequence<int, 18, 21, 24>>>();

    execute<matrix_row_col_dot_v<2, 2, mid, rhs>, -26>();

    execute<matrix_col_row_dot_t<1, 0, mid, rhs>,
            std::tuple<std::integer_sequence<int, -18, 0, 36, 9>,
                       std::integer_sequence<int, 0, 0, 0, 0>,
                       std::integer_sequence<int, -4, 0, 8, 2>,
                       std::integer_sequence<int, -6, 0, 12, 3>>>();

    execute<zero_matrix_t<3>,
            std::tuple<std::integer_sequence<int, 0, 0, 0>,
                       std::integer_sequence<int, 0, 0, 0>,
                       std::integer_sequence<int, 0, 0, 0>>>();

    execute<identity_matrix_t<3>,
            std::tuple<std::integer_sequence<int, 1, 0, 0>,
                       std::integer_sequence<int, 0, 1, 0>,
                       std::integer_sequence<int, 0, 0, 1>>>();

    execute<pascal_matrix_t<4>,
            std::tuple<std::integer_sequence<int, 1, 1, 1, 1>,
                       std::integer_sequence<int, 1, 2, 3, 4>,
                       std::integer_sequence<int, 1, 3, 6, 10>,
                       std::integer_sequence<int, 1, 4, 10, 20>>>();

    execute<upper_triangular_matrix_t<pascal_matrix_t<4>>,
            std::tuple<std::integer_sequence<int, 1, 1, 1, 1>,
                       std::integer_sequence<int, 0, 2, 3, 4>,
                       std::integer_sequence<int, 0, 0, 6, 10>,
                       std::integer_sequence<int, 0, 0, 0, 20>>>();

    execute<lower_triangular_matrix_t<pascal_matrix_t<4>>,
            std::tuple<std::integer_sequence<int, 1, 0, 0, 0>,
                       std::integer_sequence<int, 1, 2, 0, 0>,
                       std::integer_sequence<int, 1, 3, 6, 0>,
                       std::integer_sequence<int, 1, 4, 10, 20>>>();

    using row = std::integer_sequence<int, 1, 2, 3, 4, 5>;
    using col = std::integer_sequence<int, 1, 6, 7, 8, 9>;

    execute<toeplitz_matrix_t<row, col>,
            std::tuple<std::integer_sequence<int, 1, 2, 3, 4, 5>,
                       std::integer_sequence<int, 6, 1, 2, 3, 4>,
                       std::integer_sequence<int, 7, 6, 1, 2, 3>,
                       std::integer_sequence<int, 8, 7, 6, 1, 2>,
                       std::integer_sequence<int, 9, 8, 7, 6, 1>>>();

    using mp = std::tuple<std::integer_sequence<int, 1, 0, 2, 1>,
                          std::integer_sequence<int, 0, 2, 3, 1>,
                          std::integer_sequence<int, 1, 2, 0, 3>,
                          std::integer_sequence<int, 1, 0, 0, 1>>;

    execute<matrix_power_t<mp, 3>,
            std::tuple<std::integer_sequence<int, 14, 12, 20, 22>,
                       std::integer_sequence<int, 22, 32, 38, 44>,
                       std::integer_sequence<int, 18, 24, 20, 38>,
                       std::integer_sequence<int, 6, 4, 4, 10>>>();

    execute<matrix_element_power_t<mp, 3>,
            std::tuple<std::integer_sequence<int, 1, 0, 8, 1>,
                       std::integer_sequence<int, 0, 8, 27, 1>,
                       std::integer_sequence<int, 1, 8, 0, 27>,
                       std::integer_sequence<int, 1, 0, 0, 1>>>();

    execute<matrix_negate_t<mp>,
            std::tuple<std::integer_sequence<int, -1, 0, -2, -1>,
                       std::integer_sequence<int, 0, -2, -3, -1>,
                       std::integer_sequence<int, -1, -2, 0, -3>,
                       std::integer_sequence<int, -1, 0, 0, -1>>>();

    execute<get_matrix_diagonal_t<identity_matrix_t<3>>,  std::integer_sequence<int, 1, 1, 1>>();

    execute<set_matrix_diagonal_t<fill_c<3, 4>, identity_matrix_t<3>>,
            std::tuple<std::integer_sequence<int, 4, 0, 0>,
                       std::integer_sequence<int, 0, 4, 0>,
                       std::integer_sequence<int, 0, 0, 4>>>();

    execute<trace_v<set_matrix_diagonal_t<fill_c<3, 5>, identity_matrix_t<3>>>, 15>();

    using matrix_ = std::tuple<std::integer_sequence<int, 1, 0, 2, -1>,
                               std::integer_sequence<int, 3, 0, 0, 5>,
                               std::integer_sequence<int, 2, 1, 4, -3>,
                               std::integer_sequence<int, 1, 0, 5, 0>>;

    execute<det_v<matrix_>, 30>();
    execute<det_v<std::tuple<std::integer_sequence<int, 4, 5>, std::integer_sequence<int, 7, 8>>>, -3>();

    execute<sum_row_v<0, matrix_>, 2>();
    execute<sum_col_v<0, matrix_>, 7>();

    execute<product_row_v<0, matrix_>, 0>();
    execute<product_col_v<0, matrix_>, 6>();

    execute<matrix_row_sum_t<matrix_>, std::integer_sequence<int, 7, 1, 11, 1>>();
    execute<matrix_col_sum_t<matrix_>, std::integer_sequence<int, 2, 8, 4, 6>>();

    execute<matrix_row_means_t<matrix_>, std::integer_sequence<int, 1, 0, 2, 0>>();
    execute<matrix_col_means_t<matrix_>, std::integer_sequence<int, 0, 2, 1, 1>>();

    execute<matrix_row_mul_t<matrix_>, std::integer_sequence<int, 6, 0, 0, 0>>();
    execute<matrix_col_mul_t<matrix_>, std::integer_sequence<int, 0, 0, -24, 0>>();

    execute<matrix_sum_v<matrix_>, 20>();
    execute<matrix_mul_v<matrix_>, 0>();

    execute<matrix_means_v<matrix_>, 1>();

    execute<matrix_row_maximum_t<matrix_>, std::integer_sequence<int, 2, 5, 4, 5>>();
    execute<matrix_col_maximum_t<matrix_>, std::integer_sequence<int, 3, 1, 5, 5>>();

    execute<matrix_row_minimum_t<matrix_>, std::integer_sequence<int, -1, 0, -3, 0>>();
    execute<matrix_col_minimum_t<matrix_>, std::integer_sequence<int, 1, 0, 0, -3>>();

    execute<matrix_row_midpoint_t<matrix_>, std::integer_sequence<int, 0, 0, 1, 0>>();
    execute<matrix_col_midpoint_t<matrix_>, std::integer_sequence<int, 3, 0, 0, 5>>();

    execute<next_permutation_list<std::integer_sequence<int, 1, 2, 3>>, list_n>();
    execute<prev_permutation_list<std::integer_sequence<int, 3, 2, 1>>, reverse_t<list_n>>();

    execute<loop_permutation_t<std::integer_sequence<int, 1, 2, 3>>, list_n>();
    execute<loop_permutation_t<std::integer_sequence<int, 3, 2, 1>>, reverse_t<list_n>>();

    execute<next_partial_permutation_list<3, std::tuple<char, int, double>>, list_t>();
    execute<prev_partial_permutation_list<3, std::tuple<double, int, char>>, reverse_t<list_t>>();

    using list_s = std::tuple<std::tuple<char, int>,
                              std::tuple<char, double>,
                              std::tuple<int, char>,
                              std::tuple<int, double>,
                              std::tuple<double, char>,
                              std::tuple<double, int>>;

    execute<next_partial_permutation_list<2, std::tuple<char, int, double>>, list_s>();
    execute<prev_partial_permutation_list<2, std::tuple<double, int, char>>, reverse_t<list_s>>();

    execute<loop_permutation_t<std::tuple<char, int, double>, 2>, list_s>();
    execute<loop_permutation_t<std::tuple<double, int, char>, 2>, reverse_t<list_s>>();

    execute<permutation_recursive_t<std::integer_sequence<int, 1, 2, 3>>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 3, 2>,
                       std::integer_sequence<int, 2, 1, 3>,
                       std::integer_sequence<int, 2, 3, 1>,
                       std::integer_sequence<int, 3, 2, 1>,
                       std::integer_sequence<int, 3, 1, 2>>>();

    execute<permutation_recursive_t<std::tuple<char, int, double>>,
            std::tuple<std::tuple<char, int, double>,
                       std::tuple<char, double, int>,
                       std::tuple<int, char, double>,
                       std::tuple<int, double, char>,
                       std::tuple<double, int, char>,
                       std::tuple<double, char, int>>>();

    using comb0 = std::tuple<char, short, int, double>;
    execute<range_t<0, 2, comb0>, std::tuple<char, short>>();
    using comb1 = next_combination_t<2, comb0>;
    execute<range_t<0, 2, comb1>, std::tuple<char, int>>();
    using comb2 = next_combination_t<2, comb1>;
    execute<range_t<0, 2, comb2>, std::tuple<char, double>>();
    using comb3 = next_combination_t<2, comb2>;
    execute<range_t<0, 2, comb3>, std::tuple<short, int>>();
    using comb4 = next_combination_t<2, comb3>;
    execute<range_t<0, 2, comb4>, std::tuple<short, double>>();
    using comb5 = next_combination_t<2, comb4>;
    execute<range_t<0, 2, comb5>, std::tuple<int, double>>();

    using comb_list = std::tuple<std::tuple<char, short>,
                                 std::tuple<char, int>,
                                 std::tuple<char, double>,
                                 std::tuple<short, int>,
                                 std::tuple<short, double>,
                                 std::tuple<int, double>>;

    execute<next_combination_list<2, comb0>, comb_list>();

    execute<prev_combination_list<2, reverse_t<comb0>>,
            std::tuple<std::tuple<double, int>,
                       std::tuple<double, short>,
                       std::tuple<double, char>,
                       std::tuple<int, short>,
                       std::tuple<int, char>,
                       std::tuple<short, char>>>();

    execute<next_combination_list<2, std::integer_sequence<int, 1, 2, 3, 4>>,
            std::tuple<std::integer_sequence<int, 1, 2>,
                       std::integer_sequence<int, 1, 3>,
                       std::integer_sequence<int, 1, 4>,
                       std::integer_sequence<int, 2, 3>,
                       std::integer_sequence<int, 2, 4>,
                       std::integer_sequence<int, 3, 4>>>();

    execute<prev_combination_list<2, std::integer_sequence<int, 4, 3, 2, 1>>,
            std::tuple<std::integer_sequence<int, 4, 3>,
                       std::integer_sequence<int, 4, 2>,
                       std::integer_sequence<int, 4, 1>,
                       std::integer_sequence<int, 3, 2>,
                       std::integer_sequence<int, 3, 1>,
                       std::integer_sequence<int, 2, 1>>>();

    execute<next_combination_list<3, std::integer_sequence<int, 1, 2, 3, 4, 5>>,
            std::tuple<std::integer_sequence<int, 1, 2, 3>,
                       std::integer_sequence<int, 1, 2, 4>,
                       std::integer_sequence<int, 1, 2, 5>,
                       std::integer_sequence<int, 1, 3, 4>,
                       std::integer_sequence<int, 1, 3, 5>,
                       std::integer_sequence<int, 1, 4, 5>,
                       std::integer_sequence<int, 2, 3, 4>,
                       std::integer_sequence<int, 2, 3, 5>,
                       std::integer_sequence<int, 2, 4, 5>,
                       std::integer_sequence<int, 3, 4, 5>>>();

    using counts_list = std::tuple<std::integer_sequence<int, 0, 0, 2>,
                                   std::integer_sequence<int, 0, 1, 1>,
                                   std::integer_sequence<int, 0, 2, 0>,
                                   std::integer_sequence<int, 1, 0, 1>,
                                   std::integer_sequence<int, 1, 1, 0>,
                                   std::integer_sequence<int, 2, 0, 0>>;

    execute<next_combination_counts_list<0, 3, std::integer_sequence<int, 0, 0, 2>>, counts_list>();
    execute<prev_combination_counts_list<0, 3, std::integer_sequence<int, 2, 0, 0>>,
            reverse_t<counts_list>>();

    using integer = integer_sequence_t<int, 3, 1, 0>;

    using indices_list = std::tuple<std::integer_sequence<int, 1, 1, 1>,
                                    std::integer_sequence<int, 1, 1, 2>,
                                    std::integer_sequence<int, 1, 2, 1>,
                                    std::integer_sequence<int, 1, 2, 2>,
                                    std::integer_sequence<int, 2, 1, 1>,
                                    std::integer_sequence<int, 2, 1, 2>,
                                    std::integer_sequence<int, 2, 2, 1>,
                                    std::integer_sequence<int, 2, 2, 2>>;

    execute<next_hypercube_indices_list<1, 3, integer>, indices_list>();
    execute<prev_hypercube_indices_list<1, 3, integer_sequence_t<int, 3, 2, 0>>, reverse_t<indices_list>>();

    execute<power_v<10, digit_v<1234>>, 10000>();

    /* this takes too long to compile
    execute<edit_distance_v<std::tuple<char, short, float, int, double, uint64_t>,
            std::tuple<char, double, nullptr_t, short, uint32_t, int, double, uint64_t>>, 3>();

    execute<edit_distance_v<std::integer_sequence<int, 1, 2, 3, 4, 5, 6>,
            std::integer_sequence<int, 1, 5, 8, 2, 0, 4, 5, 6>>, 3>();
    */

    execute<binomial_coeff_v<5, 2>, 10>();

    execute<element_t<4, nth_element_t<4, std::tuple<int, char, short, double, char>>>, double>();
    execute<element_v<3, nth_element_t<3, std::integer_sequence<int, -2, 1, 0, -7, 4, 3>>>, 1>();

    execute<median_v<std::integer_sequence<int, 2, -3, 4, 0, 7, 6>>, 3>();
    execute<median_v<std::integer_sequence<int, 2, -3, 4, 0, 7, 6, 8>>, 4>();

    execute<partial_sort_t<0, 4, std::integer_sequence<int, 6, -2, 8, 0, -7, 1, 7, -5, 4, 7, 3>>,
            std::integer_sequence<int, -7, -5, -2, 0, 6, 1, 7, 3, 4, 7, 8>>();
    execute<partial_sort_t<4, 6, std::tuple<int, uint64_t, short, char, short, double, int, short>>,
            std::tuple<short, char, short, short, int, int, double, uint64_t>>();

    execute<sort_subrange_t<3, 6, std::index_sequence<3, 1, 4, 0, 2, 5, 9, 7, 4, 8>>,
            std::index_sequence<0, 1, 2, 3, 4, 4, 9, 7, 8, 5>>();

    execute<partition_subrange_t<1, 6, std::index_sequence<4, 1, 8, 7, 0, 5, 3, 6, 2>>,
            std::index_sequence<0, 1, 3, 2, 4, 5, 6, 7, 8>>();

    execute<select_t<2, std::tuple<short, int, double, int, char>>, short>();
    execute<select_t<2, std::tuple<short, int, double, int, char>, greater_equal_t>, int>();

    execute<select_t<3, std::integer_sequence<int, 0, 3, 2, 1, 2, 6>>, c_2>();
    execute<select_v<4, std::integer_sequence<int, -2, 1, 0, -7, 4, 3>>, 1>();

    execute<select_t<3, std::integer_sequence<int, 0, 3, 4, 1, -2, 6>, greater_equal_t>, c_3>();
    execute<select_v<4, std::integer_sequence<int, -2, 1, 0, -7, 4, 3>, greater_equal_t>, 0>();

    execute<typeof_t<stable_partition_t<0, 2, std::tuple<int, std::tuple<int>>, is_tuple>>,
            std::tuple<std::tuple<int>, int>>();

    execute<typeof_t<stable_partition_t<1, 6, std::tuple<int, char, std::tuple<char>, double,
            std::tuple<uint64_t>, int, std::tuple<float>>, is_tuple>>, std::tuple<int, std::tuple<char>,
            std::tuple<uint64_t>, char, double, int, std::tuple<float>>>();

    execute<typeof_t<stable_partition_t<1, 7, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, is_odd>>,
            std::integer_sequence<int, 1, 3, 7, 1, 2, 8, 0, -2, 4, 5>>();

    execute<typeof_t<stable_partition_t<1, 6, std::integer_sequence<int, 1, 3, 2, 7, 8, 0, 1, -2, 4, 5>, is_even>>,
            std::integer_sequence<int, 1, 2, 8, 0, 3, 7, 1, -2, 4, 5>>();

    using gath = gather_t<0, 10, 4, std::index_sequence<0, 1, 2, 3, 4, 5, 6, 7, 8, 9>, is_even>;
    execute<gath, triple<2, 7, std::index_sequence<1, 3, 0, 2, 4, 6, 8, 5, 7, 9>>>();

    execute<partition_point_t<std::integer_sequence<int, 1, 2, 8, 0, 3, 7, 1, -2, 4, 5>,
            is_even, 1, 6>, c_4>();

    execute<partition_point_v<std::tuple<std::tuple<int>, std::tuple<int>, char, int>, is_tuple>, 2>();

    using part = partition_copy_t<is_even, std::index_sequence<5, 8, 0, 3, 2, 4, 7, 1, 6, 9>>;
    execute<first_t<part>, std::index_sequence<8, 0, 2, 4, 6>>();
    execute<second_t<part>, std::index_sequence<5, 3, 7, 1, 9>>();

    execute<find_first_of_v<std::tuple<int, char, short, double>, std::tuple<float, nullptr_t, char>>, 1>();
    execute<find_first_of_v<std::index_sequence<4, 0, 3, 7, 5>, std::index_sequence<9, 8, 3, 6>>, 2>();

    execute<find_first_not_of_v<std::tuple<int, char, short, double>, std::tuple<int, nullptr_t, char>>, 2>();
    execute<find_first_not_of_v<std::index_sequence<4, 0, 3, 7, 6>, std::index_sequence<4, 8, 3, 6>>, 1>();

    execute<find_first_last_of_v<std::tuple<int, char, short, double>, std::tuple<int, nullptr_t, char>>, 1>();
    execute<find_first_last_of_v<std::index_sequence<4, 0, 3, 7, 6>, std::index_sequence<4, 8, 3, 6>>, 0>();

    execute<find_last_of_v<std::tuple<int, char, short, double>, std::tuple<short, nullptr_t, char>>, 2>();
    execute<find_last_of_v<std::index_sequence<4, 0, 3, 7, 5>, std::index_sequence<7, 8, 3, 6>>, 3>();

    execute<find_last_not_of_v<std::tuple<int, double, char, float, int>, std::tuple<short, int, char>>, 3>();
    execute<find_last_not_of_v<std::index_sequence<4, 0, 3, 7, 0, 8>, std::index_sequence<7, 8, 3, 6>>, 4>();

    execute<find_last_first_of_v<std::tuple<int, double, char, float, int>, std::tuple<short, int, char>>, 4>();
    execute<find_last_first_of_v<std::index_sequence<4, 0, 3, 7, 0, 8>, std::index_sequence<7, 8, 3, 6>>, 5>();

    execute<trim_t<std::tuple<int, char, float, char, short>, std::tuple<int, short, char>>, std::tuple<float>>();
    execute<trim_t<std::index_sequence<0, 2, 7, 4, 9, 1>, std::index_sequence<1, 2, 0>>, std::index_sequence<7, 4, 9>>();

    execute<trim_left_t<std::tuple<int, char, float, char, short>, std::tuple<int, short, char>>, std::tuple<float, char, short>>();
    execute<trim_left_t<std::index_sequence<0, 2, 7, 4, 9, 1>, std::index_sequence<1, 2, 0>>, std::index_sequence<7, 4, 9, 1>>();

    execute<trim_right_t<std::tuple<int, char, float, char, short>, std::tuple<int, short, char>>, std::tuple<int, char, float>>();
    execute<trim_right_t<std::index_sequence<0, 2, 7, 4, 9, 1>, std::index_sequence<1, 2, 0>>, std::index_sequence<0, 2, 7, 4, 9>>();

    execute<lis_t<std::integer_sequence<int, 10, 22, 9, 33, 21, 50, 70, 60, 80>>, std::index_sequence<0, 1, 3, 5, 7, 8>>();

    execute<lcs_t<std::tuple<int, char, short, double, char, short, char, int>,
            std::tuple<char, double, short, int, char, short>>, std::tuple<char, short, char, short>>();
    execute<lcs_t<std::index_sequence<2, 5, 3, 1, 6, 7, 4, 8>, std::index_sequence<7, 2, 9, 3, 8, 6, 0, 4, 9, 8>>,
            std::index_sequence<2, 3, 6, 4, 8>>();

    execute<lps_t<std::tuple<int, short, int, int, short, int, double>>, pair_v<0, 6>>();
    execute<lps_t<std::index_sequence<1, 2, 3, 4, 5, 4, 3, 6, 6, 3>>, pair_v<2, 7>>();
    execute<lps_v<std::index_sequence<1, 2, 3, 4, 5, 4, 3, 6, 6, 3>>, 5>();

    execute<lcp_t<std::tuple<std::tuple<int, char>, std::tuple<int, char, short>, std::tuple<int, char, double, int>>>,
            std::tuple<int, char>>();
    execute<lcp_t<std::tuple<std::index_sequence<7, 6, 8, 1>, std::index_sequence<7, 6, 8, 4, 2>>>,
            std::index_sequence<7, 6, 8>>();

    execute<longest_common_suffix_t<std::tuple<std::tuple<char, int>, std::tuple<short, char, int>,
            std::tuple<int, double, char, int>>>, std::tuple<char, int>>();
    execute<longest_common_suffix_t<std::tuple<std::index_sequence<1, 8, 6, 7>,
            std::index_sequence<2, 4, 8, 6, 7>>>, std::index_sequence<8, 6, 7>>();

    execute<lbs_t<std::integer_sequence<int, 1, 11, 2, 10, 4, 5, 2, 1>>,
            std::integer_sequence<int, 1, 11, 10, 5, 2, 1>>();

    execute<main_lorentz_t<std::tuple<int, int, int, short, int, short, int>>,
            std::tuple<pair_v<0, 1>, pair_v<1, 2>, pair_v<3, 6>>>();
    execute<main_lorentz_t<std::integer_sequence<int, 2, 3, 3, 3, 0, 5, 6, 5, 6, 7>>,
            std::tuple<pair_v<1, 2>, pair_v<2, 3>, pair_v<5, 8>>>();

    execute<lrp_t<std::tuple<int, int, int, short, int, short, int>>,
            pair_v<3, 6>>();
    execute<lrp_t<std::integer_sequence<int, 2, 3, 3, 3, 0, 5, 6, 5, 6, 7>>,
            pair_v<5, 8>>();

    using mat1 = std::tuple<std::tuple<int[10], int[11], int[12], int[13], int[14]>,
                            std::tuple<int[20], int[21], int[22], int[23], int[24]>,
                            std::tuple<int[30], int[31], int[32], int[33], int[34]>,
                            std::tuple<int[40], int[41], int[42], int[43], int[44]>>;

    using mat2 = std::tuple<std::index_sequence<10, 11, 12, 13, 14>,
                            std::index_sequence<20, 21, 22, 23, 24>,
                            std::index_sequence<30, 31, 32, 33, 34>,
                            std::index_sequence<40, 41, 42, 43, 44>>;

    execute<is_in_matrix_v<mat1, std::tuple<int[31], int[21], int[22], int[23], int[13]>>>();
    execute<is_in_matrix_v<mat2, std::index_sequence<31, 21, 22, 23, 13>>>();

    execute<manacker_t<std::tuple<int, char, double, char, int, char>>,
            std::tuple<std::tuple<int>, std::tuple<char>, std::tuple<int, char, double, char, int>,
            std::tuple<char>, std::tuple<char, int, char>, std::tuple<char>>>();

    using pack1 = std::tuple<pair_v<1, 10>, pair_v<2, 10>, pair_v<5, 10>, pair_v<7, 10>, pair_v<9, 10>>;
    using pack2 = std::tuple<pair_v<0, 5>, pair_v<2, 5>, pair_v<6, 5>, pair_v<7, 5>, pair_v<11, 5>>;
    using pack3 = std::tuple<pair_v<0, 5>, pair_v<1, 10>, pair_v<2, 15>, pair_v<5, 10>, pair_v<6, 5>,
                             pair_v<7, 15>, pair_v<9, 10>, pair_v<11, 5>>;

    execute<merge_combine_t<comp, comb, pack1, pack2>, pack3>();
    execute<merge_advance_t<4, std::index_sequence<1, 3, 4, 7>, std::index_sequence<0, 2, 3, 4>>,
            std::index_sequence<0, 1, 2, 3>>();

    execute<stable_sort_t<std::tuple<double, uint64_t, double, float, int, char, float, char, double>>,
            std::tuple<char, char, float, int, float, double, uint64_t, double, double>>();

    execute<map_sort_t<std::tuple<double, uint64_t, double, float, int, char, float, char, double>>,
            std::tuple<char, char, float, int, float, double, uint64_t, double, double>>();

    execute<select_sort_t<std::tuple<int, int, double, char, int, char, double>>,
            std::tuple<char, char, int, int, int, double, double>>();

    execute<counting_sort_t<std::tuple<int, char, double, uint64_t, int>>,
            std::tuple<char, int, int, double, uint64_t>>();

    execute<radix_sort_t<std::tuple<int, char, double, uint64_t, int>>,
            std::tuple<char, int, int, double, uint64_t>>();

    execute<stooge_sort_t<std::tuple<int, double, int, float, char, double>>,
            std::tuple<char, int, int, float, double, double>>();

    execute<bubble_sort_t<std::tuple<int, double, char, int, char, float, double>>,
            std::tuple<char, char, int, int, float, double, double>>();

    execute<shaker_sort_t<std::tuple<uint64_t, int, double, char, int, char, float, double>>,
            std::tuple<char, char, int, int, float, uint64_t, double, double>>();

    execute<oddeven_sort_t<std::tuple<uint64_t, int, double, char, int, char, float, double>>,
            std::tuple<char, char, int, int, float, uint64_t, double, double>>();

    execute<gnome_sort_t<std::tuple<uint64_t, int, double, char, int, char, float, double>>,
            std::tuple<char, char, int, int, float, uint64_t, double, double>>();

    execute<selection_sort_t<std::tuple<int, int, double, char, int, char, double>>,
            std::tuple<char, char, int, int, int, double, double>>();

    execute<quick_sort_t<std::tuple<double, uint64_t, float, char, char, double>>,
            std::tuple<char, char, float, double, uint64_t, double>>();

    execute<quick_sort_iterative_t<std::tuple<double, uint64_t, float, char, char, double>>,
            std::tuple<char, char, float, double, uint64_t, double>>();

    execute<insert_sort_t<std::tuple<float, int, int, double, char, int, float, char, double>>,
            std::tuple<char, char, float, int, int, int, float, double, double>>();

    execute<insertion_sort_t<std::tuple<float, int, int, double, char, int, float, char, double>>,
            std::tuple<char, char, float, int, int, int, float, double, double>>();

    execute<merge_sort_t<std::tuple<double, char, double, int, float>>,
            std::tuple<char, int, float, double, double>>();

    execute<strand_sort_t<std::tuple<double, char, double, int, float>>,
            std::tuple<char, int, float, double, double>>();

    execute<heap_sort_t<std::tuple<uint64_t, double, float, char, char, double>>,
            std::tuple<char, char, float, double, double, uint64_t>>();

    using input1 = std::integer_sequence<int, 2, 1, 0, -3, 4, 1, -7, 5, -2>;
    using output1 = std::integer_sequence<int, -7, -3, -2, 0, 1, 1, 2, 4, 5>;
    using index1 = std::index_sequence<6, 3, 8, 2, 1, 5, 0, 4, 7>;

    execute<stable_sort_t<input1>, output1>();
    execute<select_sort_t<input1>, output1>();
    execute<rank_sort_t<input1>, output1>();
    execute<counting_sort_t<input1>, output1>();
    execute<radix_sort_t<input1>, output1>();
    execute<stooge_sort_t<input1>, output1>();
    execute<bubble_sort_t<input1>, output1>();
    execute<shaker_sort_t<input1>, output1>();
    execute<oddeven_sort_t<input1>, output1>();
    execute<gnome_sort_t<input1>, output1>();
    execute<selection_sort_t<input1>, output1>();
    execute<quick_sort_t<input1>, output1>();
    execute<quick_sort_iterative_t<input1>, output1>();
    execute<insert_sort_t<input1>, output1>();
    execute<insertion_sort_t<input1>, output1>();
    execute<merge_sort_t<input1>, output1>();
    execute<strand_sort_t<input1>, output1>();
    execute<heap_sort_t<input1>, output1>();
    execute<sort_index_t<input1>, index1>();

    execute<sort_v<input1, output1, stable_sort, select_sort, counting_sort,
            radix_sort, stooge_sort, bubble_sort, oddeven_sort, gnome_sort,
            shaker_sort, selection_sort, quick_sort, quick_sort_iterative,
            insert_sort, insertion_sort, merge_sort, strand_sort, heap_sort>>();

    using input2 = std::tuple<double, short, double, int, char, char, double>;
    using output2 = std::tuple<char, char, short, int, double, double, double>;
    using index2 = std::index_sequence<4, 5, 1, 3, 6, 2, 0>;

    execute<stable_sort_t<input2>, output2>();
    execute<select_sort_t<input2>, output2>();
    execute<counting_sort_t<input2>, output2>();
    execute<radix_sort_t<input2>, output2>();
    execute<stooge_sort_t<input2>, output2>();
    execute<bubble_sort_t<input2>, output2>();
    execute<shaker_sort_t<input2>, output2>();
    execute<oddeven_sort_t<input2>, output2>();
    execute<gnome_sort_t<input2>, output2>();
    execute<selection_sort_t<input2>, output2>();
    execute<quick_sort_t<input2>, output2>();
    execute<quick_sort_iterative_t<input2>, output2>();
    execute<insert_sort_t<input2>, output2>();
    execute<insertion_sort_t<input2>, output2>();
    execute<merge_sort_t<input2>, output2>();
    execute<strand_sort_t<input2>, output2>();
    execute<heap_sort_t<input2>, output2>();
    execute<sort_index_t<input2>, index2>();

    execute<sort_v<input2, output2, stable_sort, select_sort, counting_sort,
            radix_sort, stooge_sort, bubble_sort, oddeven_sort, gnome_sort,
            shaker_sort, selection_sort, quick_sort, quick_sort_iterative,
            insert_sort, insertion_sort, merge_sort, strand_sort, heap_sort>>();

    return 0;
}
```
