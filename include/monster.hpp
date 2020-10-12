//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef MONSTER_HPP
#define MONSTER_HPP

#define STRINGIZE(X) #X

/*
 *   MONSTER_VERSION
 *
 *   Identifies the API version of Monster.
 *   This is a simple integer that is incremented by one every
 *   time a set of code changes is merged to the master branch.
 */

#define MONSTER_VERSION 127

#define MONSTER_VERSION_STRING "Monster/" STRINGIZE(MONSTER_VERSION)

#include <tuple>
#include <utility>
#include <functional>

namespace monster
{    
    template <typename T>
    constexpr T e = T(2.7182818284590452353);

    template <typename T>
    constexpr T pi = T(3.1415926535897932385);

    template <auto N, typename T = std::remove_cvref_t<decltype(N)>>
    using c_ = std::integral_constant<T, N>;

    using c_0 = c_<0>;

    using c_1 = c_<1>;

    using c_2 = c_<2>;

    using c_3 = c_<3>;

    using c_4 = c_<4>;

    using c_5 = c_<5>;

    using c_6 = c_<6>;

    using c_7 = c_<7>;

    using c_8 = c_<8>;

    using c_9 = c_<9>;

    template <auto N>
    using bool_ = std::bool_constant<N>;

    template <size_t N>
    using index_t = c_<N, size_t>;

    template <typename... Args>
    using tuple_t = std::tuple<Args...>;

    template <typename T>
    inline constexpr auto typev = T::value;

    template <typename T>
    using value_t = typename T::value_type;

    template <typename T>
    inline constexpr auto negav = std::negation_v<T>;

    template <typename T, typename = std::void_t<>>
    struct typeof
    {
        using type = T;
        static constexpr auto value = 0;
    };

    template <typename T>
    struct typeof<T, std::void_t<typename T::type>>
    {
        using type = typename T::type;
        static constexpr auto value = 1;
    };

    template <typename T>
    using typeof_t = typename typeof<T>::type;

    template <typename T>
    inline constexpr auto typeof_v = typev<typeof_t<T>>;

    template <bool B, typename T, typename U>
    using type_if = typeof_t<std::conditional_t<B, T, U>>;

    template <bool B, typename T, typename U>
    inline constexpr auto type_if_v = typev<type_if<B, T, U>>;

    template <bool B, typename T, typename U>
    inline constexpr auto value_if = typev<std::conditional_t<B, T, U>>;

    template <typename T, typename U, typename V>
    using conditional_of = std::conditional_t<typev<T>, U, V>;

    template <typename T, typename = std::void_t<>>
    struct has_type : std::false_type
    {
    };

    template <typename T>
    struct has_type<T, std::void_t<typename T::type>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto has_type_v = typev<has_type<T>>;

    template <typename T, typename = std::void_t<>>
    struct has_value_type : std::false_type
    {
        using value_type = int;
    };

    template <typename T>
    struct has_value_type<T, std::void_t<value_t<T>>> : std::true_type
    {
        using value_type = value_t<T>;
    };

    template <typename T>
    using has_value_type_t = value_t<has_value_type<T>>;

    template <typename T>
    inline constexpr auto has_value_type_v = typev<has_value_type<T>>;

    template <typename T, typename = std::void_t<>>
    struct has_new : std::false_type
    {
    };

    template <typename T>
    struct has_new<T, std::void_t<decltype(T::operator new(0))>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto has_new_v = typev<has_new<T>>;

    template <typename T, typename = std::void_t<>>
    struct has_delete : std::false_type
    {
    };

    template <typename T>
    struct has_delete<T, std::void_t<decltype(T::operator delete(nullptr))>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto has_delete_v = typev<has_delete<T>>;

    template <typename T, typename = std::void_t<>>
    struct is_type_complete : std::false_type
    {
    };

    template <typename T>
    struct is_type_complete<T, std::void_t<decltype(sizeof(T))>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto is_type_complete_v = typev<is_type_complete<T>>;

    template <typename T, typename U>
    struct pair_t
    {
        using first = T;
        using second = U;
    };

    template <typename T>
    using first_t = typename T::first;

    template <typename T>
    using second_t = typename T::second;

    template <auto p, auto q>
    struct pair_v
    {
        static constexpr auto first = p;
        static constexpr auto second = q;
    };

    template <typename T>
    inline constexpr auto first_v = T::first;

    template <typename T>
    inline constexpr auto second_v = T::second;

    template <typename T>
    inline constexpr auto pair_diff = second_v<T> - first_v<T>;

    template <auto p, auto q, typename T>
    struct triple : std::type_identity<T>
    {
        static constexpr auto first = p;
        static constexpr auto second = q;
    };

    template <int N, typename T>
    struct identity
    {
        using type = T;
    };

    template <int N, typename T>
    using identity_t = typeof_t<identity<N, T>>;

    template <auto N, typename T>
    struct wrapper : wrapper<N - 1, std::type_identity<T>>
    {
    };

    template <typename T>
    struct wrapper<0, T> : std::type_identity<T>
    {
    };

    template <auto N, typename T>
    using wrapper_t = typeof_t<wrapper<N, T>>;

    template <auto N, typename T>
    struct index_type : std::type_identity<T>
    {
        static constexpr auto value = N;
    };

    template <auto N, typename T>
    using index_upper = wrapper_t<1, index_type<N, T>>;

    template <typename T, typename... Args>
    struct last : last<Args...>
    {
    };

    template <typename T>
    struct last<T> : std::type_identity<T>
    {
    };

    template <typename... Args>
    using last_t = typeof_t<last<Args...>>;

    template <typename T, typename ...>
    struct alias
    {
        using type = T;
    };

    template <typename... Args>
    using alias_t = typeof_t<alias<Args...>>;

    template <template <typename ...> typename F, typename... Args>
    struct wrapin
    {
        using type = tuple_t<F<Args>...>;
    };

    template <template <typename ...> typename F, typename... Args>
    using wrapin_t = typeof_t<wrapin<F, Args...>>;

    template <bool B, template <typename ...> typename F, typename T>
    using wrapin_if = std::conditional_t<B, F<T>, T>;

    template <typename... Args>
    struct contains : std::false_type
    {
    };

    template <typename T, typename... Args>
    struct contains<T, Args...> : bool_<(std::is_same_v<T, Args> || ...)>
    {
    };

    template <typename ...>
    inline constexpr auto contains_v = std::false_type{};

    template <typename T, typename... Args>
    inline constexpr auto contains_v<T, Args...> = (std::is_same_v<T, Args> || ...);

    template <auto... values>
    struct comprise : std::false_type
    {
    };

    template <auto value, auto... values>
    struct comprise<value, values...> : bool_<((value == values) || ...)>
    {
    };

    template <auto ...>
    inline constexpr auto comprise_v = std::false_type{};

    template <auto value, auto... values>
    inline constexpr auto comprise_v<value, values...> = ((value == values) || ...);

    template <typename B, typename ...>
    struct exists_type : B
    {
    };

    template <typename B, typename T, typename... Args>
    struct exists_type<B, T, Args...> : std::conditional_t<contains_v<T, Args...>, std::negation<B>, exists_type<B, Args...>>
    {
    };

    template <typename B, typename... Args>
    using exists_type_t = typeof_t<exists_type<B, Args...>>;

    template <typename B, typename... Args>
    inline constexpr auto exists_type_v = typev<exists_type_t<B, Args...>>;

    template <typename... Args>
    using is_unique_type = exists_type<std::true_type, Args...>;

    template <typename ...>
    inline constexpr auto is_unique_type_v = std::true_type{};

    template <typename T, typename... Args>
    inline constexpr auto is_unique_type_v<T, Args...> = !contains_v<T, Args...> && is_unique_type_v<Args...>;

    template <typename... Args>
    using has_duplicates_type = exists_type<std::false_type, Args...>;

    template <typename ...>
    inline constexpr auto has_duplicates_type_v = std::false_type{};

    template <typename T, typename... Args>
    inline constexpr auto has_duplicates_type_v<T, Args...> = contains_v<T, Args...> || has_duplicates_type_v<Args...>;

    template <typename B, auto ...>
    struct exists_value : B
    {
    };

    template <typename B, auto value, auto... values>
    struct exists_value<B, value, values...> : std::conditional_t<comprise_v<value, values...>, std::negation<B>, exists_value<B, values...>>
    {
    };

    template <typename B, auto... values>
    using exists_value_t = typeof_t<exists_value<B, values...>>;

    template <typename B, auto... values>
    inline constexpr auto exists_value_v = typev<exists_value_t<B, values...>>;

    template <auto... values>
    using is_unique_value = exists_value<std::true_type, values...>;

    template <auto ...>
    inline constexpr auto is_unique_value_v = std::true_type{};

    template <auto value, auto... values>
    inline constexpr auto is_unique_value_v<value, values...> = negav<comprise<value, values...>> && is_unique_value_v<values...>;

    template <auto... values>
    using has_duplicates_value = exists_value<std::false_type, values...>;

    template <auto ...>
    inline constexpr auto has_duplicates_value_v = std::false_type{};

    template <auto value, auto... values>
    inline constexpr auto has_duplicates_value_v<value, values...> = typev<comprise<value, values...>> || has_duplicates_value_v<values...>;

    template <bool B, typename T>
    struct exists;

    template <template <typename ...> typename T, typename... Args>
    struct exists<true, T<Args...>>
    {
        using type = is_unique_type<Args...>;
    };

    template <template <typename, auto ...> typename T, typename U, auto... values>
    struct exists<true, T<U, values...>>
    {
        using type = is_unique_value<values...>;
    };

    template <template <typename ...> typename T, typename... Args>
    struct exists<false, T<Args...>>
    {
        using type = has_duplicates_type<Args...>;
    };

    template <template <typename, auto ...> typename T, typename U, auto... values>
    struct exists<false, T<U, values...>>
    {
        using type = has_duplicates_value<values...>;
    };

    template <bool B, typename T>
    using exists_t = typeof_t<exists<B, T>>;

    template <bool B, typename T>
    inline constexpr auto exists_v = typev<exists_t<B, T>>;

    template <typename T>
    using is_unique = exists<true, T>;

    template <typename T>
    using is_unique_t = typeof_t<is_unique<T>>;

    template <typename T>
    inline constexpr auto is_unique_v = typev<is_unique_t<T>>;

    template <typename T>
    using has_duplicates = exists<false, T>;

    template <typename T>
    using has_duplicates_t = typeof_t<has_duplicates<T>>;

    template <typename T>
    inline constexpr auto has_duplicates_v = typev<has_duplicates_t<T>>;

    template <bool A, bool B, typename X, typename Y, typename Z>
    using ternary_conditional = std::conditional<A, std::conditional_t<B, X, Y>, Z>;

    template <bool A, bool B, typename X, typename Y, typename Z>
    using ternary_conditional_t = typeof_t<ternary_conditional<A, B, X, Y, Z>>;

    template <typename T>
    struct member_type;

    template <typename R, typename T, typename... Args>
    struct member_type<R (T::*)(Args...)>
    {
        using type = R;
    };

    template <typename R, typename T, typename... Args>
    struct member_type<R (T::*)(Args...) const>
    {
        using type = R;
    };

    template <typename T>
    using member_type_t = typeof_t<member_type<T>>;

    template <typename T>
    struct member_args;

    template <typename T, typename U, typename... Args>
    struct member_args<T (U::*)(Args...)>
    {
        using type = tuple_t<Args...>;
    };

    template <typename T>
    using member_args_t = typeof_t<member_args<T>>;

    template <typename... Args>
    struct inherit : Args...
    {
    };

    template <typename T, typename U = std::void_t<>>
    struct is_inheritable : std::false_type
    {
    };

    template <typename T>
    struct is_inheritable<T, std::void_t<inherit<T>>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto is_inheritable_v = typev<is_inheritable<T>>;

    template <typename... Args>
    struct is_inheritable_pack : bool_<(is_inheritable_v<Args> && ...)>
    {
    };

    template <typename... Args>
    inline constexpr auto is_inheritable_pack_v = typev<is_inheritable_pack<Args...>>;

    template <typename T>
    struct is_instantiable : std::negation<std::is_abstract<T>>
    {
    };

    template <typename T>
    inline constexpr auto is_instantiable_v = typev<is_instantiable<T>>;

    template <bool B, typename T = std::void_t<>>
    struct disable_if
    {
    };

    template <typename T>
    struct disable_if<false, T> : std::type_identity<T>
    {
    };

    template <bool B, typename T = std::void_t<>>
    using disable_if_t = typeof_t<disable_if<B, T>>;

    template <typename S, typename T, typename = std::void_t<>>
    struct is_streamable : std::false_type
    {
    };

    template <typename S, typename T>
    struct is_streamable<S, T, std::void_t<disable_if_t<std::is_same_v<S, T>>,
    decltype(std::declval<std::add_lvalue_reference_t<S>>() << std::declval<T>())>> : std::true_type
    {
    };

    template <typename S, typename T>
    using is_streamable_t = typeof_t<is_streamable<S, T>>;

    template <typename S, typename T>
    inline constexpr auto is_streamable_v = typev<is_streamable_t<S, T>>;

    template <typename T, typename = std::void_t<>>
    struct is_iterable : std::false_type
    {
    };

    template <typename T>
    struct is_iterable<
        T,
        std::void_t<
            decltype(std::begin(std::declval<T>())),
            decltype(std::end(std::declval<T>()))
        >
    > : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto is_iterable_v = typev<is_iterable<T>>;

    template <typename T, typename = std::void_t<>>
    struct is_container : std::false_type
    {
    };

    template <typename T>
    struct is_container<
        T,
        std::void_t<
            typename T::value_type,
            typename T::size_type,
            typename T::allocator_type,
            typename T::iterator,
            typename T::const_iterator,
            decltype(std::declval<T>().size()),
            decltype(std::declval<T>().begin()),
            decltype(std::declval<T>().end()),
            decltype(std::declval<T>().cbegin()),
            decltype(std::declval<T>().cend())
        >
    > : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto is_container_v = typev<is_container<T>>;

    template <typename T, typename U>
    struct is_pointer_of : std::is_same<T, std::add_pointer_t<U>>
    {
    };

    template <typename T, typename U>
    inline constexpr auto is_pointer_of_v = typev<is_pointer_of<T, U>>;

    template <template <typename ...> typename T, typename Args>
    struct is_instance_of : std::false_type
    {
    };

    template <template <typename ...> typename T, typename... Args>
    struct is_instance_of<T, T<Args...>> : std::true_type
    {
    };

    template <template <typename ...> typename T, typename Args>
    inline constexpr auto is_instance_of_v = typev<is_instance_of<T, Args>>;

    template <template <typename, auto ...> typename T, typename Args>
    struct is_sequence_of : std::false_type
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... values>
    struct is_sequence_of<T, T<U, values...>> : std::true_type
    {
    };

    template <template <typename, auto ...> typename T, typename Args>
    inline constexpr auto is_sequence_of_v = typev<is_sequence_of<T, Args>>;

    template <typename T>
    struct is_tuple : is_instance_of<std::tuple, T>
    {
    };

    template <typename T>
    inline constexpr auto is_tuple_v = typev<is_tuple<T>>;

    template <typename T>
    struct is_sequence : is_sequence_of<std::integer_sequence, T>
    {
    };

    template <typename T>
    inline constexpr auto is_sequence_v = typev<is_sequence<T>>;

    template <typename T>
    struct is_variadic_type : std::false_type
    {
    };

    template <template <typename ...> typename T, typename... Args>
    struct is_variadic_type<T<Args...>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto is_variadic_type_v = typev<is_variadic_type<T>>;

    template <typename T>
    struct is_variadic_value : std::false_type
    {
    };

    template <template <auto ...> typename T, auto... Args>
    struct is_variadic_value<T<Args...>> : std::true_type
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args>
    struct is_variadic_value<T<U, Args...>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr auto is_variadic_value_v = typev<is_variadic_value<T>>;

    template <typename T>
    struct is_variadic : bool_<is_variadic_type_v<T> || is_variadic_value_v<T>>
    {
    };

    template <typename T>
    inline constexpr auto is_variadic_v = typev<is_variadic<T>>;

    template <typename... Args>
    struct is_variadic_pack : bool_<(is_variadic_v<Args> && ...)>
    {
    };

    template <typename... Args>
    using is_variadic_pack_t = typeof_t<is_variadic_pack<Args...>>;

    template <typename... Args>
    inline constexpr auto is_variadic_pack_v = typev<is_variadic_pack_t<Args...>>;

    template <typename T>
    struct is_group : std::false_type
    {
    };

    template <template <typename ...> typename T, typename... Args>
    struct is_group<T<Args...>> : is_variadic_pack<Args...>
    {
    };

    template <typename T>
    inline constexpr auto is_group_v = typev<is_group<T>>;

    template <typename... Args>
    inline constexpr auto sizeof_v = sizeof...(Args);
    
    template <typename T, typename = std::void_t<>>
    struct sizeof_t : index_t<sizeof(T)>
    {
    };

    template <auto N, typename T>
    struct sizeof_t<index_type<N, T>> : sizeof_t<T>
    {
    };

    template <typename T>
    struct sizeof_t<T, std::void_t<decltype(T::size())>> : index_t<T::size()>
    {
    };

    template <typename T>
    struct sizeof_t<T, std::enable_if_t<is_tuple_v<T>>> : index_t<std::tuple_size_v<T>>
    {
    };

    template <typename T>
    struct sizeof_t<T, std::void_t<std::enable_if_t<!is_tuple_v<T>>, decltype(T::value + 1)>> : T
    {
    };

    template <typename T>
    inline constexpr auto sizeof_t_v = typev<sizeof_t<T>>;

    template <typename T>
    struct argument_size : argument_size<decltype(&T::operator())>
    {
    };

    template <typename R, typename T, typename... Args>
    struct argument_size<R (T::*)(Args...)> : index_t<sizeof_v<Args...>>
    {
    };

    template <typename R, typename... Args>
    struct argument_size<R (*)(Args...)> : index_t<sizeof_v<Args...>>
    {
    };

    template <typename R, typename T, typename... Args>
    struct argument_size<R (T::*)(Args...) const> : index_t<sizeof_v<Args...>>
    {
    };

    template <typename T>
    inline constexpr auto argument_size_v = typev<argument_size<T>>;

    template <auto N>
    using index_sequence_of_c = std::make_index_sequence<N>;

    template <typename T, auto N = 0>
    using index_sequence_of_t = index_sequence_of_c<sizeof_t_v<T> - N>;

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    using less_t = bool_<(p < q)>;

    template <typename T, typename U>
    inline constexpr auto less_v = typev<less_t<T, U>>;

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    using less_equal_t = bool_<(p <= q)>;

    template <typename T, typename U>
    inline constexpr auto less_equal_v = typev<less_equal_t<T, U>>;

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    using equal_t = bool_<p == q>;

    template <typename T, typename U>
    inline constexpr auto equal_v = typev<equal_t<T, U>>;

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    using greater_equal_t = bool_<(p >= q)>;

    template <typename T, typename U>
    inline constexpr auto greater_equal_v = typev<greater_equal_t<T, U>>;

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    using greater_t = bool_<(p > q)>;

    template <typename T, typename U>
    inline constexpr auto greater_v = typev<greater_t<T, U>>;

    template <typename T, typename U>
    inline constexpr auto size_diff = sizeof_t_v<T> - sizeof_t_v<U>;

    template <typename T>
    struct base_type : std::type_identity<T>
    {
    };

    template <template <typename... > typename T, typename... Args>
    struct base_type<T<Args...>> : std::type_identity<T<>>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args>
    struct base_type<T<U, Args...>> : std::type_identity<T<U>>
    {
    };

    template <typename T>
    using base_type_t = typeof_t<base_type<T>>;

    template <auto value, decltype(value)... values>
    struct homogeneous
    {
        using type = decltype(value);
        using value_type = type;

        auto static constexpr size()
        {
            return sizeof...(values) + 1;
        }
    };

    template <size_t N, typename T>
    struct get;

    template <template <typename, auto ...> typename T, typename U, auto value, auto... values>
    struct get<0, T<U, value, values...>> : c_<value, U>
    {
    };

    template <size_t N, template <typename, auto ...> typename T, typename U, auto value, auto... values>
    struct get<N, T<U, value, values...>> : c_<typev<get<N - 1, T<U, values...>>>, U>
    {
    };

    template <template <auto ...> typename T, auto value, auto... values>
    struct get<0, T<value, values...>> : c_<value, int>
    {
    };

    template <size_t N, template <auto ...> typename T, auto value, auto... values>
    struct get<N, T<value, values...>> : c_<typev<get<N - 1, T<values...>>>>
    {
    };

    template <size_t N, typename T>
    using get_t = typeof_t<get<N, T>>;

    template <size_t N, typename T>
    inline constexpr auto get_v = typev<get<N, T>>;

    template <typename T, auto N = 0>
    inline constexpr auto head_v = get_v<0, T> + N;

    template <bool B, typename T>
    struct collect;

    template <bool B, template <typename, auto ...> typename T, typename U, auto... values>
    struct collect<B, T<U, values...>> : c_<B ? (values + ...) : (values * ...), U>
    {
    };

    template <bool B, template <auto ...> typename T, auto... values>
    struct collect<B, T<values...>> : c_<B ? (values + ...) : (values * ...)>
    {
    };

    template <bool B, typename T>
    using collect_t = typeof_t<collect<B, T>>;

    template <bool B, typename T>
    inline constexpr auto collect_v = typev<collect_t<B, T>>;

    template <typename T>
    struct sum : collect<1, T>
    {
    };

    template <typename T>
    using sum_t = typeof_t<sum<T>>;

    template <typename T>
    inline constexpr auto sum_v = typev<sum_t<T>>;

    template <typename T>
    struct mul : collect<0, T>
    {
    };

    template <typename T>
    using mul_t = typeof_t<mul<T>>;

    template <typename T>
    inline constexpr auto mul_v = typev<mul_t<T>>;

    template <typename T>
    struct means : c_<sum_v<T> / sizeof_t_v<T>>
    {
    };

    template <typename T>
    using means_t = typeof_t<means<T>>;

    template <typename T>
    inline constexpr auto means_v = typev<means_t<T>>;

    template <typename L, typename R>
    struct rename : std::type_identity<L>
    {
    };

    template <template <typename ...> typename L, template <typename ...> typename R, typename... T, typename... U>
    struct rename<L<T...>, R<U...>> : std::type_identity<R<T...>>
    {
    };

    template <template <typename, auto ...> typename L, template <typename, auto ...> typename R, typename T, auto... t, typename U, auto... u>
    struct rename<L<T, t...>, R<U, u...>> : std::type_identity<R<U, t...>>
    {
    };

    template <typename L, typename R>
    using rename_t = typeof_t<rename<L, R>>;

    template <typename T>
    requires is_variadic_type_v<T>
    using as_tuple = rename<T, std::tuple<>>;

    template <typename T>
    using as_tuple_t = typeof_t<as_tuple<T>>;

    template <bool B, typename T>
    requires is_variadic_type_v<T>
    using as_tuple_if = std::conditional_t<B, as_tuple<T>, std::type_identity<T>>;

    template <bool B, typename T>
    using as_tuple_if_t = typeof_t<as_tuple_if<B, T>>;

    template <auto N, typename T>
    struct variadic_element
    {
        template <typename U, bool B>
        struct impl : std::type_identity<std::tuple_element<N, as_tuple_t<U>>>
        {
        };

        template <typename U>
        struct impl<U, false> : std::type_identity<get<N, U>>
        {
        };

        using type = typeof_t<impl<T, is_variadic_type_v<T>>>;
    };

    template <auto N, typename T>
    using element = typeof_t<variadic_element<N, T>>;

    template <auto N, typename T>
    using element_t = typeof_t<element<N, T>>;

    template <auto N, typename T>
    requires is_variadic_value_v<T>
    inline constexpr auto element_v = typev<element_t<N, T>>;

    template <auto N, typename T>
    using variadic_element_t =  element_t<N, T>;

    template <auto N, typename T>
    inline constexpr auto variadic_element_v = element_v<N, T>;

    template <bool B, auto N, typename T, typename U>
    using element_if = std::conditional_t<!B, U, element<N, T>>;

    template <bool B, auto N, typename T, typename U>
    using element_if_t = typeof_t<element_if<B, N, T, U>>;

    template <typename T>
    struct midpoint : element<(sizeof_t_v<T> + 1) /  2 - 1, T>
    {
    };

    template <typename T>
    using midpoint_t = typeof_t<midpoint<T>>;

    template <typename T>
    inline constexpr auto midpoint_v = typev<midpoint_t<T>>;

    template <typename T>
    using front = element<0, T>;

    template <typename T>
    using front_t = typeof_t<front<T>>;

    template <typename T>
    inline constexpr auto front_v = typev<front_t<T>>;

    template <typename T>
    using back = element<sizeof_t_v<T> - 1, T>;

    template <typename T>
    using back_t = typeof_t<back<T>>;

    template <typename T>
    inline constexpr auto back_v = typev<back_t<T>>;

    template <typename T, typename U>
    using plus_t = c_<typev<T> + typev<U>>;

    template <typename T, typename U>
    inline constexpr auto plus_v = typev<plus_t<T, U>>;

    template <typename T, typename U>
    using minus_t = c_<typev<T> - typev<U>>;

    template <typename T, typename U>
    inline constexpr auto minus_v = typev<minus_t<T, U>>;

    template <typename T, typename U>
    using multiplies_t = c_<typev<T> * typev<U>>;

    template <typename T, typename U>
    inline constexpr auto multiplies_v = typev<multiplies_t<T, U>>;

    template <typename T, typename U>
    using divides_t = c_<typev<T> / typev<U>>;

    template <typename T, typename U>
    inline constexpr auto divides_v = typev<divides_t<T, U>>;

    template <typename T, typename U>
    using modulus_t = c_<typev<T> % typev<U>>;

    template <typename T, typename U>
    inline constexpr auto modulus_v = typev<modulus_t<T, U>>;

    template <typename T>
    using negate_t = c_<-typev<T>>;

    template <typename T>
    inline constexpr auto negate_v = typev<negate_t<T>>;

    template <typename T>
    struct pred : c_<typev<T> - 1, value_t<T>>
    {
    };

    template <typename T>
    using pred_t = typeof_t<pred<T>>;

    template <typename T>
    inline constexpr auto pred_v = typev<pred_t<T>>;

    template <typename T>
    struct succ : c_<typev<T> + 1, value_t<T>>
    {
    };

    template <typename T>
    using succ_t = typeof_t<succ<T>>;

    template <typename T>
    inline constexpr auto succ_v = typev<succ_t<T>>;

    template <template <auto, typename> typename F, auto n, typename T, auto N = 1>
    using prev = F<n - N, T>;

    template <template <auto, typename> typename F, auto n, typename T, auto N = 1>
    using next = F<n + N, T>;

    template <auto n, typename T, auto N = 1>
    using prev_t = typeof_t<prev<element, n, T, N>>;

    template <auto n, typename T, auto N = 1>
    using next_t = typeof_t<next<element, n, T, N>>;

    template <auto n, typename T, auto N = 1>
    inline constexpr auto prev_v = typev<prev<get, n, T, N>>;

    template <auto n, typename T, auto N = 1>
    inline constexpr auto next_v = typev<next<get, n, T, N>>;

    template <auto x, auto y>
    struct gcd : gcd<y, x % y>
    {
    };

    template <auto y>
    struct gcd<0, y> : c_<y>
    {
    };

    template <auto x>
    struct gcd<x, 0> : c_<x>
    {
    };

    template <auto x, auto y>
    using gcd_t = typeof_t<gcd<x, y>>;

    template <auto x, auto y>
    inline constexpr auto gcd_v = typev<gcd_t<x, y>>;

    template <auto x, auto y>
    struct lcm : c_<x * y / gcd_v<x, y>>
    {
    };

    template <auto y>
    struct lcm<0, y> : c_0
    {
    };

    template <auto x>
    struct lcm<x, 0> : c_0
    {
    };

    template <auto x, auto y>
    using lcm_t = typeof_t<lcm<x, y>>;

    template <auto x, auto y>
    inline constexpr auto lcm_v = typev<lcm_t<x, y>>;

    template <template <typename ...> typename F, typename T>
    struct unpack;

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    struct unpack<F, T<Args...>>
    {
        using type = F<Args...>;
    };

    template <template <typename ...> typename F, typename T>
    using unpack_t = typeof_t<unpack<F, T>>;

    template <template <typename ...> typename F, typename... Args>
    struct bind_front
    {
        template <typename... args>
        using apply = F<Args..., args...>;
    };

    template <template <typename ...> typename F, typename... Args>
    struct bind_back
    {
        template <typename... args>
        using apply = F<args..., Args...>;
    };

    template <bool B1, bool B2, template <typename ...> typename F, typename... Args>
    struct bind_if
    {
        template <bool, typename... args>
        struct impl
        {
            using apply = std::conditional_t<B2, F<Args..., args...>, F<args..., Args...>>;
        };

        template <typename... args>
        struct impl<false, args...>
        {
            using apply = F<args...>;
        };

        template <typename... args>
        using apply = impl<B1, args...>::apply;
    };

    template <bool B, template <typename ...> typename F, typename... Args>
    struct bind_front_if : bind_if<B, 1, F, Args...>
    {
    };

    template <bool B, template <typename ...> typename F, typename... Args>
    struct bind_back_if : bind_if<B, 0, F, Args...>
    {
    };

    template <typename F, typename... Args>
    using call = typename F::template apply<Args...>;

    template <typename F, typename... Args>
    using call_t = typeof_t<call<F, Args...>>;

    template <bool B, typename T, typename F, typename... Args>
    struct call_if
    {
        template <typename f, typename... args>
        struct impl
        {
            using type = call_t<f, args...>;
        };

        using type = type_if<B, impl<F, Args...>, std::type_identity<T>>;
    };

    template <bool B, typename T, typename F, typename... Args>
    using call_if_t = typeof_t<call_if<B, T, F, Args...>>;

    template <typename F, typename... Args>
    using invoke = call<F, Args...>;

    template <typename F, typename... Args>
    inline constexpr auto invoke_v = typev<invoke<F, Args...>>;

    template <bool B, typename T, typename F, typename... Args>
    struct invoke_if
    {
        template <typename f, typename... args>
        struct impl
        {
            using type = call<f, args...>;
        };

        using type = type_if<B, impl<F, Args...>, std::type_identity<T>>;
    };

    template <bool B, typename T, typename F, typename... Args>
    using invoke_if_t = typeof_t<invoke_if<B, T, F, Args...>>;

    template <bool B, typename T, typename F, typename... Args>
    inline constexpr auto invoke_if_v = typev<invoke_if_t<B, T, F, Args...>>;

    template <typename F, typename T, typename ...>
    struct fold : std::type_identity<T>
    {
    };

    template <typename F, typename T, typename U, typename... Args>
    struct fold<F, T, U, Args...> : fold<F, call_t<F, T, U>, Args...>
    {
    };

    template <typename F, typename... Args>
    using fold_t = typeof_t<fold<F, Args...>>;

    template <template <typename, typename> typename F, typename... Args>
    using folded = fold<bind_front<F>, Args...>;

    template <template <typename, typename> typename F, typename... Args>
    using folded_t = typeof_t<folded<F, Args...>>;

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    struct recurse : std::type_identity<T<Args...>>
    {
        template <typename... args>
        using apply = recurse<F, T, Args..., typeof_t<F<args>>...>;
    };

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    using recurse_t = typeof_t<recurse<F, T, Args...>>;

    template <typename F, typename ...>
    struct curry : F
    {
    };

    template <typename F, typename T, typename... Args>
    struct curry<F, T, Args...> : curry<call<F, T>, Args...>
    {
    };

    template <typename F, typename... Args>
    using curry_t = typeof_t<curry<F, Args...>>;

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    using curried = curry<recurse<F, T>, Args...>;

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    using curried_t =  typeof_t<curried<F, T, Args...>>;

    template <template <typename ...> typename F, typename... Args>
    using currying = curried<F, std::tuple, Args...>;

    template <template <typename ...> typename F, typename... Args>
    using currying_t = typeof_t<currying<F, Args...>>;

    template <typename T, template <typename ...> typename... F>
    struct compose_left;

    template <typename T, template <typename ...> typename F>
    struct compose_left<T, F> : typeof<F<T>>
    {
    };

    template <typename T, template <typename ...> typename F, template <typename ...> typename... G>
    struct compose_left<T, F, G...> : compose_left<typeof_t<F<T>>, G...>
    {
    };

    template <typename T, template <typename ...> typename... F>
    using compose_left_t = typeof_t<compose_left<T, F...>>;

    template <typename T, template <typename ...> typename... F>
    struct compose_right;

    template <typename T, template <typename ...> typename F>
    struct compose_right<T, F> : typeof<F<T>>
    {
    };

    template <typename T, template <typename ...> typename F, template <typename ...> typename... G>
    struct compose_right<T, F, G...> : compose_right<typeof_t<compose_right<T, G...>>, F>
    {
    };

    template <typename T, template <typename ...> typename... F>
    using compose_right_t = typeof_t<compose_right<T, F...>>;

    template <template <template <typename ...> typename, typename ...> typename F, template <typename ...> typename f, typename... Args>
    struct eval
    {
        template <typename... args>
        using apply = F<f, Args..., args...>;
    };

    template <template <template <typename ...> typename, typename ...> typename F, template <typename ...> typename f, typename T, typename... Args>
    using eval_t = unpack_t<eval<F, f, Args...>::template apply, T>;

    template <typename T>
    using tuple_and = eval_t<folded_t, std::conjunction, T, std::true_type>;

    template <typename T>
    inline constexpr auto tuple_and_v = typev<tuple_and<T>>;

    template <typename F, template <typename ...> typename f>
    struct on
    {
        template <typename... Args>
        using apply = f<call_t<F, Args>...>;
    };

    template <template <typename ...> typename F, template <typename ...> typename f, typename... Args>
    using on_t = call_t<on<bind_front<F>, f>, Args...>;

    template <typename F, typename... Args>
    struct partial
    {
        template <typename... args>
        using apply = call<F, Args..., args...>;
    };

    template <template <typename ...> typename F, bool neg = true>
    struct negaf
    {
        template <typename... Args>
        using apply = wrapin_if<neg, std::negation, F<Args...>>;
    };

    template <template <template <typename ...> typename, typename, int, int> typename F>
    struct metaf
    {
        template <template <typename ...> typename f, typename T, int B, int E>
        using apply = F<f, T, B, E>;
    };

    template <typename F, template <typename ...> typename f, typename T, int B, int E>
    using apply = typename F::template apply<f, T, B, E>;

    template <typename F, template <typename ...> typename f, typename T, int B, int E>
    using apply_t = typeof_t<apply<F, f, T, B, E>>;

    template <template <template <typename ...> typename, typename, int, int> typename F,
    template <typename ...> typename f, typename T, int B, int E, bool neg = false,
    template <typename ...> typename U = negaf<f, neg>::template apply>
    using applyf = apply<metaf<F>, U, T, B, E>;

    template <template <template <typename ...> typename, typename, int, int> typename F,
    template <typename ...> typename f, typename T, int B, int E, bool neg = false>
    using applyf_t = typeof_t<applyf<F, f, T, B, E, neg>>;

    template <auto N>
    struct equal
    {
        template <typename T>
        struct apply : bool_<typev<T> == N>
        {
        };
    };

    template <template <typename ...> typename F, int N, int B, int E, bool>
    struct index_if;

    template <template <typename ...> typename F, int N, int B, int E>
    struct index_if<F, N, B, E, false>
    {
        template <typename T>
        using apply = call<index_if<F, N, B + N, E, typev<F<element_t<B, T>>>>, T>;
    };

    template <template <typename ...> typename F, int N, int B, int E>
    struct index_if<F, N, B, E, true>
    {
        template <typename ...>
        using apply = c_<B - N>;
    };

    template <template <typename ...> typename F, int N, int E>
    struct index_if<F, N, E, E, false>
    {
        template <typename ...>
        using apply = c_<E>;
    };

    template <template <typename ...> typename F, int N, int B, int E, typename T>
    using index_if_t = call<index_if<F, N, B, E, false>, T>;

    template <template <typename ...> typename F, int N, int B, int E, typename T>
    inline constexpr auto index_if_v = typev<index_if_t<F, N, B, E, T>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using next_index_if = index_if_t<F, 1, B, E, T>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto next_index_if_v = typev<next_index_if<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using prev_index_if = index_if_t<F, -1, B, E, T>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    inline constexpr auto prev_index_if_v = typev<prev_index_if<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using find_if = applyf<next_index_if, F, T, B, E>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using find_if_t = typeof_t<find_if<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto find_if_v = typev<find_if_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using find_if_backward = applyf<prev_index_if, F, T, B, E>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using find_if_backward_t = typeof_t<find_if_backward<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    inline constexpr auto find_if_backward_v = typev<find_if_backward_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using find_if_not = applyf<next_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using find_if_not_t = applyf_t<next_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto find_if_not_v = typev<find_if_not_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using find_if_not_backward = applyf<prev_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using find_if_not_backward_t = applyf_t<prev_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    inline constexpr auto find_if_not_backward_v = typev<find_if_not_backward_t<F, T, B, E>>;

    template <typename T, typename U, bool D = true, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    struct bound
    {
        template <typename X, typename Y>
        using comp = std::conditional_t<D, F<X, Y>, std::negation<F<Y, X>>>;

        template <int i, int j, bool = (i > 0)>
        struct impl
        {
            static constexpr auto half = i / 2;
            static constexpr auto value = typev<comp<element_t<j + half, U>, T>>;

            static constexpr auto delta = value * half + value;
            using type = typeof_t<impl<value ? i - delta : half, j + delta>>;
        };

        template <int i, int j>
        struct impl<i, j, false> : c_<j>
        {
        };

        using type = typeof_t<impl<E - B, B>>;
    };

    template <typename T, typename U, bool D = true, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    using bound_t = typeof_t<bound<T, U, D, B, E, F>>;

    template <typename T, typename U, bool D = true, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    inline constexpr auto bound_v = typev<bound_t<T, U, D, B, E, F>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    using lower_bound = bound<T, U, true, B, E, F>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    using lower_bound_t = typeof_t<lower_bound<T, U, B, E, F>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    inline constexpr auto lower_bound_v = typev<lower_bound_t<T, U, B, E, F>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    using upper_bound = bound<T, U, false, B, E, F>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    using upper_bound_t = typeof_t<upper_bound<T, U, B, E, F>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    inline constexpr auto upper_bound_v = typev<upper_bound_t<T, U, B, E, F>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    struct equal_range
    {
        using type = pair_v<lower_bound_v<T, U, B, E, F>, upper_bound_v<T, U, B, E, F>>;
    };

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>, template <typename, typename> typename F = less_t>
    using equal_range_t = typeof_t<equal_range<T, U, B, E, F>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct any_of
    {
        template <size_t i, size_t j>
        struct impl : conditional_of<F<element_t<i, T>>, std::true_type, impl<i + 1, j>>
        {
        };

        template <size_t j>
        struct impl<j, j> : std::false_type
        {
        };

        using type = typeof_t<impl<B, E>>;
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using any_of_t = typeof_t<any_of<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    inline constexpr auto any_of_v = typev<any_of_t<F, T, B, E>>;

    template <size_t N, typename... Args>
    struct nth_type;
    
    template <typename T, typename... Args>
    struct nth_type<0, T, Args...> : std::type_identity<T>
    {
    };
    
    template <size_t N, typename T, typename... Args>
    struct nth_type<N, T, Args...> : nth_type<N - 1, Args...>
    {
    };
    
    template <size_t N, typename... Args>
    using nth_type_t = typeof_t<nth_type<N, Args...>>;
    
    template <typename... Args>
    using first_type = nth_type_t<0, Args...>;

    template <typename... Args>
    using last_type = nth_type_t<sizeof_v<Args...> - 1, Args...>;

    template <auto N>
    struct arg
    {
        template <typename... Args>
        struct apply : nth_type<N, Args...>
        {
        };
    };

    template <typename T, typename... Args>
    using arg_t = call_t<T, Args...>;

    template <size_t N, typename T, typename... Args>
    requires (N == 0)
    decltype(auto) nth_value_v(T&& t, Args&&... args)
    {
        return std::forward<T>(t);
    }
    
    template <size_t N, typename T, typename... Args>
    requires (N > 0)
    decltype(auto) nth_value_v(T&& t, Args&&... args)
    {
        return std::forward<nth_type_t<N - 1, Args...>>(nth_value_v<N - 1>((std::forward<Args>(args))...));
    }
    
    template <typename... Args>
    decltype(auto) first_value(Args&&... args)
    {
        return std::forward<first_type<Args...>>(nth_value_v<0>((std::forward<Args>(args))...));
    }
    
    template <typename... Args>
    decltype(auto) last_value(Args&&... args)
    {
        return std::forward<last_type<Args...>>(nth_value_v<sizeof_v<Args...> - 1>((std::forward<Args>(args))...));
    }
    
    template <size_t... indices>
    struct index_tuple
    {
        template <size_t N>
        using apply = index_tuple<indices..., N>;
    };

    template <size_t N>
    struct next_index_tuple
    {
        using type = typeof_t<next_index_tuple<N - 1>>::template apply<N - 1>;
    };

    template <>
    struct next_index_tuple<0>
    {
        using type = index_tuple<>;
    };

    template <size_t N>
    using next_index_tuple_t = typeof_t<next_index_tuple<N>>;

    template <size_t N>
    using make_index_tuple = next_index_tuple_t<N>;

    template <typename... Args>
    using index_tuple_for = make_index_tuple<sizeof_v<Args...>>;

    template <size_t... indices>
    struct index_sequence
    {
    };

    template <typename T, bool B>
    struct duple;

    template <size_t... indices>
    struct duple<index_sequence<indices...>, false>
    {
        using type = index_sequence<indices..., (sizeof...(indices) + indices)...>;
    };

    template <size_t... indices>
    struct duple<index_sequence<indices...>, true>
    {
        using type = index_sequence<indices..., (sizeof...(indices) + indices)..., sizeof...(indices) * 2>;
    };

    template <size_t N>
    struct next_index_sequence : duple<typeof_t<next_index_sequence<N / 2>>, N % 2 != 0>
    {
    };

    template <>
    struct next_index_sequence<1>
    {
        using type = index_sequence<0>;
    };

    template <>
    struct next_index_sequence<0>
    {
        using type = index_sequence<>;
    };

    template <size_t N>
    using next_index_sequence_t = typeof_t<next_index_sequence<N>>;

    template <size_t N>
    using make_index_sequence = next_index_sequence_t<N>;

    template <typename... Args>
    using index_sequence_for = make_index_sequence<sizeof_v<Args...>>;

    template <typename T, T... values>
    struct index_list
    {
        using value_type = T;

        auto static constexpr size()
        {
            return sizeof...(values);
        }
    };
    
    template <typename T, T lower, T upper, T... values>
    struct range_generator;
    
    template <typename T, T lower, T... values>
    struct range_generator<T, lower, lower, values...> : std::type_identity<index_list<T, values...>>
    {
    };
    
    template <typename T, T lower, T upper, T... Args>
    struct range_generator : range_generator<T, lower, upper - 1, upper - 1, Args...>
    {
    };
    
    template <typename T, T lower, T upper>
    using range_generator_t = typeof_t<range_generator<T, lower, upper>>;

    template <size_t lower, size_t upper>
    using index_range = rename_t<range_generator_t<size_t, lower, upper>, std::index_sequence<>>;

    template <int lower, int upper>
    using integer_range = rename_t<range_generator_t<int, lower, upper>, std::integer_sequence<int>>;
    
    template <size_t N, typename T>
    struct base
    {
        template <typename F, typename Args>
        base(F&& f, Args&& args)
        {
            f(args);
        }
    };
    
    template <typename... T>
    struct invoker : base<typev<T>, typeof_t<T>>...
    {
        template <typename F, typename... Args>
        invoker(F&& f, Args&&... args) : base<typev<T>, typeof_t<T>>(std::forward<F>(f), std::forward<Args>(args))...
        {
        }
    };
    
    template <typename T, typename... Outer>
    void fmap(T&& t, Outer&&... outer)
    {
        []<typename F, template <typename U, auto ...> typename V, size_t... N, typename... Args>
        (F&& f, const V<size_t, N...>&, Args&&... args)
        {
            invoker<index_type<N, nth_type_t<N, Args...>>...>(std::forward<F>(f), (nth_value_v<N>(std::forward<Args>(args)...))...);
        }
        (std::forward<T>(t), index_range<0, sizeof_v<Outer...>>(), std::forward<Outer>(outer)...);
    }

    template <typename... Args>
    struct concat;

    template <template <typename ...> typename T, typename... Args>
    struct concat<T<Args...>> : std::type_identity<T<Args...>>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args>
    struct concat<T<U, Args...>> : std::type_identity<T<U, Args...>>
    {
    };

    template <template <typename ...> typename T, typename... Args, typename... args>
    struct concat<T<Args...>, T<args...>> : std::type_identity<T<Args..., args...>>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args, auto... args>
    struct concat<T<U, Args...>, T<U, args...>> : std::type_identity<T<U, Args..., args...>>
    {
    };

    template <template <typename ...> typename T, typename... Args, typename... args, typename... U>
    struct concat<T<Args...>, T<args...>, U...> : concat<T<Args..., args...>, U...>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args, auto... args, typename... V>
    struct concat<T<U, Args...>, T<U, args...>, V...> : concat<T<U, Args..., args...>, V...>
    {
    };

    template <typename... Args>
    using concat_t = typeof_t<concat<Args...>>;

    template <typename T>
    struct flat : std::type_identity<T>
    {
    };

    template <template <typename ...> typename T>
    struct flat<T<>> : std::type_identity<T<>>
    {
    };

    template <template <typename ...> typename T, typename... Args>
    struct flat<T<Args...>> : concat<type_if<is_variadic_pack_v<Args>, flat<Args>, std::type_identity<T<Args>>>...>
    {
    };

    template <typename T>
    using flat_t = typeof_t<flat<T>>;

    template <typename T, typename U, typename V>
    struct dedup
    {
        using uniq = std::conditional_t<negav<T>, U, base_type_t<U>>;
        using type = concat_t<uniq, typeof_t<V>>;
    };

    template <typename T, typename U, typename V>
    using dedup_t = typeof_t<dedup<T, U, V>>;

    template <typename T>
    struct unique;

    template <template <typename ...> typename T, typename... Args>
    struct unique<T<Args...>>
    {
        template <typename U, typename... args>
        struct impl : std::type_identity<T<args...>>
        {
        };

        template <template <typename ...> typename U, typename... prev, typename V, typename... args>
        struct impl<U<prev...>, V, args...>
        {
            using type = dedup_t<contains<V, prev...>, U<V>, impl<U<prev..., V>, args...>>;
        };

        using type = typeof_t<impl<T<>, Args...>>;
    };

    template <template <typename, auto ...> typename T, typename U, auto... values>
    struct unique<T<U, values...>>
    {
        template <typename V, auto... args>
        struct impl : std::type_identity<T<U, args...>>
        {
        };

        template <template <typename, auto ...> typename V, typename W, auto... prev, auto value, auto... args>
        struct impl<V<W, prev...>, value, args...>
        {
            using type = dedup_t<comprise<value, prev...>, V<W, value>, impl<V<W, prev..., value>, args...>>;
        };

        using type = typeof_t<impl<T<U>, values...>>;
    };

    template <typename T>
    using unique_t = typeof_t<unique<T>>;

    template <typename T>
    struct unique_index;

    template <template <typename ...> typename T, typename... Args>
    struct unique_index<T<Args...>>
    {
        template <size_t N, typename... args>
        struct impl : std::type_identity<std::index_sequence<>>
        {
        };

        template <size_t N, typename U, typename... args>
        struct impl<N, U, args...>
        {
            using type = dedup_t<contains<U, args...>, std::index_sequence<N>, impl<N + 1, args...>>;
        };

        using type = typeof_t<impl<0, Args...>>;
    };

    template <template <typename, auto ...> typename T, typename U, auto... values>
    struct unique_index<T<U, values...>>
    {
        template <size_t N, auto... args>
        struct impl : std::type_identity<std::index_sequence<>>
        {
        };

        template <size_t N, auto value, auto... args>
        struct impl<N, value, args...>
        {
            using type = dedup_t<comprise<value, args...>, std::index_sequence<N>, impl<N + 1, args...>>;
        };

        using type = typeof_t<impl<0, values...>>;
    };

    template <typename T>
    using unique_index_t = typeof_t<unique_index<T>>;

    template <auto p, auto q>
    inline constexpr auto abs_v = p > q ? p - q : q - p;

    template <auto p, auto q>
    inline constexpr auto min_v = p < q ? p : q;

    template <auto p, auto q>
    inline constexpr auto max_v = p > q ? p : q;

    template <typename T, typename U>
    struct min : std::conditional<less_v<T, U>, T, U>
    {
    };

    template <typename T, typename U>
    using min_t = typeof_t<min<T, U>>;

    template <typename T, typename U>
    struct max : std::conditional<less_v<T, U>, U, T>
    {
    };

    template <typename T, typename U>
    using max_t = typeof_t<max<T, U>>;

    template <typename... Args>
    using minimum = folded<min, Args...>;

    template <typename... Args>
    using minimum_t = typeof_t<minimum<Args...>>;

    template <typename... Args>
    using maximum = folded<max, Args...>;

    template <typename... Args>
    using maximum_t = typeof_t<maximum<Args...>>;

    template <bool B, typename T, typename... Args>
    struct push;

    template <bool B, template <typename ...> typename T, typename... Args, typename... args>
    struct push<B, T<Args...>, args...>
    {
         using type = std::conditional_t<B, T<args..., Args...>, T<Args..., args...>>;
    };

    template <bool B, template <typename, auto ...> typename T, typename U, auto... Args, typename... args>
    struct push<B, T<U, Args...>, args...>
    {
         using type = std::conditional_t<B, T<U, typev<args>..., Args...>, T<U, Args..., typev<args>...>>;
    };

    template <bool B, typename T, typename... Args>
    using push_t = typeof_t<push<B, T, Args...>>;

    template <typename T, typename... Args>
    using prepend = push<1, T, Args...>;

    template <typename T, typename... Args>
    using prepend_t = typeof_t<prepend<T, Args...>>;

    template <typename T, auto... values>
    using prepend_c = prepend_t<T, c_<values>...>;

    template <bool B, typename T, typename... Args>
    using prepend_if = std::conditional_t<!B, std::type_identity<T>, prepend<T, Args...>>;

    template <bool B, typename T, typename... Args>
    using prepend_if_t = typeof_t<prepend_if<B, T, Args...>>;

    template <typename T, typename... Args>
    using append = push<0, T, Args...>;

    template <typename T, typename... Args>
    using append_t = typeof_t<append<T, Args...>>;

    template <typename T, auto... values>
    using append_c = append_t<T, c_<values>...>;

    template <bool B, typename T, typename... Args>
    using append_if = std::conditional_t<B, append<T, Args...>, std::type_identity<T>>;

    template <bool B, typename T, typename... Args>
    using append_if_t = typeof_t<append_if<B, T, Args...>>;

    template <template <typename ...> typename F, typename T, typename... Args>
    using append_when = append_if<typev<F<Args...>>, T, Args...>;

    template <template <typename ...> typename F, typename T, typename... Args>
    using append_when_t = typeof_t<append_when<F, T, Args...>>;

    template <template <typename, typename> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct adjacent_difference
    {
        using base = base_type_t<T>;

        template <int i, int j, typename U, typename V>
        struct next
        {
            using curr = get<i, T>;
            using type = typeof_t<next<i + 1, j, curr, append_t<V, typeof_t<F<curr, U>>>>>;
        };

        template <int j, typename U, typename V>
        struct next<j, j, U, V> : std::type_identity<V>
        {
        };

        template <int i, int j>
        struct impl
        {
            using curr = get<i, T>;
            using type = typeof_t<next<i + 1, j, curr, append_t<base, curr>>>;
        };

        using type = type_if<B == E, std::type_identity<base>, impl<B, E>>;
    };

    template <template <typename, typename> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using adjacent_difference_t = typeof_t<adjacent_difference<F, T, B, E>>;

    template <template <typename, typename> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct adjacent_find
    {
        template <int i, int j>
        struct impl
        {
            static constexpr auto value = typev<F<element_t<i - 1, T>, element_t<i, T>>>;
            using type = type_if<value, c_<i - 1>, impl<i + 1, j>>;
        };

        template <int j>
        struct impl<j, j> : c_<E>
        {
        };

        using type = type_if<B == E, c_<E>, impl<B + 1, E>>;
    };

    template <template <typename, typename> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using adjacent_find_t = typeof_t<adjacent_find<F, T, B, E>>;

    template <template <typename, typename> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    inline constexpr auto adjacent_find_v = typev<adjacent_find_t<F, T, B, E>>;

    template <typename ...>
    struct invert_type;

    template <typename T, typename... Args>
    struct invert_type<T, Args...>
    {
        using type = typeof_t<invert_type<typeof_t<invert_type<Args...>>, T>>;
    };

    template <typename T>
    struct invert_type<T> : std::type_identity<T>
    {
    };

    template <typename T, typename U>
    struct invert_type<T, U> : std::type_identity<invert_type<U, T>>
    {
    };

    template <typename T, typename... Args>
    struct invert_type<invert_type<Args...>, T> : std::type_identity<invert_type<Args..., T>>
    {
    };

    template <typename... Args>
    using invert_type_t = typeof_t<invert_type<Args...>>;

    template <auto... Args>
    struct invert_value
    {
        template <typename T, auto ...>
        struct impl : std::type_identity<invert_value<>>
        {
        };

        template <typename T, auto value, auto... values>
        struct impl<T, value, values...>
        {
            using type = typeof_t<impl<typeof_t<impl<invert_value<>, values...>>, value>>;
        };

        template <auto value>
        struct impl<invert_value<>, value> : std::type_identity<invert_value<value>>
        {
        };

        template <auto value, auto... values>
        struct impl<invert_value<values...>, value> : std::type_identity<invert_value<values..., value>>
        {
        };

        using type = typeof_t<impl<invert_value<>, Args...>>;
    };

    template <auto... values>
    using invert_value_t = typeof_t<invert_value<values...>>;

    template <typename F, typename... Args>
    using fold_left = fold<F, Args...>;

    template <typename F, typename... Args>
    using fold_left_t = fold_t<F, Args...>;

    template <typename F, typename T, typename ...>
    struct fold_right_impl : std::type_identity<T>
    {
    };

    template <typename F, typename T, typename U>
    struct fold_right_impl<F, T, U> : fold_right_impl<F, call_t<F, T, U>>
    {
    };

    template <typename F, typename T, typename U, typename... Args>
    struct fold_right_impl<F, T, U, Args...> : fold_right_impl<F, call_t<F, U, T>, Args...>
    {
    };

    template <typename F, typename... Args>
    struct fold_right
    {
        template <typename... args>
        struct impl;

        template <typename... args>
        struct impl<invert_type<args...>> : fold_right_impl<F, args...>
        {
        };

        using type = typeof_t<impl<invert_type_t<Args...>>>;
    };

    template <typename F, typename... Args>
    using fold_right_t = typeof_t<fold_right<F, Args...>>;

    template <template <typename ...> typename F, typename... Args>
    struct flip
    {
        template <typename T>
        struct impl;

        template <typename... args>
        struct impl<invert_type<args...>>
        {
            using type = F<args...>;
        };

        using type = typeof_t<impl<invert_type_t<Args...>>>;
    };

    template <template <typename ...> typename F, typename... Args>
    using flip_t = typeof_t<flip<F, Args...>>;

    template <typename T>
    using is_bool_type = contains<T, std::true_type, std::false_type>;

    template <typename T>
    inline constexpr auto is_bool_type_v = typev<is_bool_type<T>>;

    template <template <auto, typename> typename F, typename T, typename U, auto V = 0>
    struct expand;

    template <template <auto, typename> typename F, template <typename ...> typename T, typename... Args, auto... N, auto V>
    struct expand<F, T<Args...>, std::index_sequence<N...>, V>
    {
        using type = T<typeof_t<F<N + V, T<Args...>>>...>;
    };

    template <template <auto, typename> typename F, template <typename ...> typename T, typename... Args, auto... N>
    struct expand<F, T<Args...>, std::index_sequence<N...>, true>
    {
        using args = T<Args...>;
        using head = typeof_t<F<head_v<std::index_sequence<N...>>, args>>;

        using type = std::integer_sequence<has_value_type_t<head>, sizeof_t_v<typeof_t<F<N, args>>>...>;
    };

    template <template <auto, typename> typename F, template <typename ...> typename T, typename... Args, auto... N>
    struct expand<F, T<Args...>, std::index_sequence<N...>, false>
    {
        using args = T<Args...>;
        using type = T<index_type<N, typeof_t<F<N, args>>>...>;
    };

    template <template <auto, typename> typename F, template <typename ...> typename T, auto... M, typename... Args, auto... N>
    struct expand<F, T<index_type<M, Args>...>, std::index_sequence<N...>, false>
    {
        using args = T<index_type<M, Args>...>;
        using type = std::index_sequence<typev<typeof_t<F<N, args>>>...>;
    };

    template <template <auto, typename> typename F, template <typename, auto ...> typename T, typename U, auto... values, auto... N, auto V>
    struct expand<F, T<U, values...>, std::index_sequence<N...>, V>
    {
        using args = T<U, values...>;
        using head = typeof_t<F<head_v<std::index_sequence<N...>, V>, args>>;

        static constexpr auto value = is_sequence_v<head>;

        template <typename W, bool b>
        struct next
        {
            using type = T<U, typev<F<N + V, W>>...>;
        };

        template <typename W>
        struct next<W, false>
        {
            using type = tuple_t<typeof_t<F<N + V, W>>...>;
        };

        template <typename W, bool B>
        struct impl
        {
            using type = typeof_t<next<W, !value>>;
        };

        template <typename W>
        struct impl<W, false>
        {
            using type = std::integer_sequence<U, typev<F<N + V, W>>...>;
        };

        using type = type_if<is_bool_type_v<head>, next<args, false>, impl<args, sizeof...(values) != 1 || value>>;
    };

    template <template <auto, typename> typename F, template <typename, auto ...> typename T, typename U, auto... values, auto... N>
    struct expand<F, T<U, values...>, std::index_sequence<N...>, true>
    {
        using args = T<U, values...>;
        using type = tuple_t<c_<typev<F<N, args>>, U>...>;
    };

    template <template <auto, typename> typename F, template <typename, auto ...> typename T, typename U, auto... values, auto... N>
    struct expand<F, T<U, values...>, std::index_sequence<N...>, false>
    {
        using args = T<U, values...>;
        using type = tuple_t<index_type<N, c_<typev<F<N, args>>, U>>...>;
    };

    template <template <auto, typename> typename F, template <typename ...> typename T, typename... Args, auto V>
    struct expand<F, T<Args...>, std::index_sequence<>, V>
    {
        using type = base_type_t<T<Args...>>;
    };

    template <template <auto, typename> typename F, template <typename, auto ...> typename T, typename U, auto... values, auto V>
    struct expand<F, T<U, values...>, std::index_sequence<>, V>
    {
        using type = base_type_t<T<U, values...>>;
    };

    template <template <auto, typename> typename F, typename T, auto... N, auto V>
    struct expand<F, T, std::index_sequence<N...>, V>
    {
        template <typename W, bool b>
        struct impl
        {
            using type = tuple_t<typeof_t<F<N + V, W>>...>;
        };

        template <typename W>
        struct impl<W, false>
        {
            using type = std::integer_sequence<W, typev<F<N + V, W>>...>;
        };

        using head = typeof_t<F<head_v<std::index_sequence<N...>, V>, T>>;
        using type = typeof_t<impl<T, negav<has_value_type<head>>>>;
    };

    template <template <auto, typename> typename F, typename T, auto V>
    struct expand<F, T, std::index_sequence<>, V>
    {
        using type = tuple_t<>;
    };

    template <template <auto, typename> typename F, typename T, typename U, auto V = 0>
    using expand_t = typeof_t<expand<F, T, U, V>>;

    template <bool B, template <auto, typename> typename F, typename T, typename U, auto V = 0>
    using expand_if = std::conditional_t<B, expand<F, T, U, V>, std::type_identity<T>>;

    template <bool B, template <auto, typename> typename F, typename T, typename U, auto V = 0>
    using expand_if_t = typeof_t<expand_if<B, F, T, U, V>>;

    template <typename T, typename U, auto V = 0>
    using expand_of = expand<element, T, U, V>;

    template <typename T, typename U, auto V = 0>
    using expand_of_t = typeof_t<expand_of<T, U, V>>;

    template <typename T, bool B, typename indices = index_sequence_of_t<T>>
    struct convert : std::conditional_t<is_tuple_v<T> == B, expand_of<T, indices, true>, std::type_identity<T>>
    {
    };

    template <typename T, bool B, typename indices = index_sequence_of_t<T>>
    using convert_t = typeof_t<convert<T, B, indices>>;

    template <typename T, typename indices = index_sequence_of_t<T>>
    using to_sequence = convert<T, true, indices>;

    template <typename T, typename indices = index_sequence_of_t<T>>
    using to_sequence_t = typeof_t<to_sequence<T, indices>>;

    template <typename T, typename indices = index_sequence_of_t<T>>
    using to_tuple = convert<T, false, indices>;

    template <typename T, typename indices = index_sequence_of_t<T>>
    using to_tuple_t = typeof_t<to_tuple<T, indices>>;

    template <typename T, typename indices = index_sequence_of_t<T>>
    using to_map = expand_of<T, indices, false>;

    template <typename T, typename indices = index_sequence_of_t<T>>
    using to_map_t = typeof_t<to_map<T, indices>>;

    template <auto i, auto j, auto N>
    inline constexpr auto swap_v = i == N ? j : j == N ? i : N;

    template <auto i, auto j, auto N>
    auto constexpr swap_index()
    {
        return swap_v<i, j, N>;
    };

    template <typename T, typename U>
    using invoke_of = type_if<is_variadic_pack_v<T>, U, std::type_identity<T>>;

    template <auto i, auto j, typename T>
    struct swap
    {
        template <auto N, typename U>
        using impl = element<swap_v<i, j, N>, U>;

        using type = invoke_of<T, expand<impl, T, index_sequence_of_t<T>>>;
    };

    template <auto i, auto j, typename T>
    using swap_t = type_if<i == j, std::type_identity<T>, swap<i, j, T>>;

    template <bool B, auto i, auto j, typename T>
    using swap_if = std::conditional_t<!B, std::type_identity<T>, swap<i, j, T>>;

    template <bool B, auto i, auto j, typename T>
    using swap_if_t = typeof_t<swap_if<B, i, j, T>>;

    template <auto n, auto lower, auto upper>
    struct within
    {
        template <auto i>
        struct impl
        {
            using cond = std::conditional_t<i + 1 >= upper, std::false_type, impl<i + 1>>;
            using type = type_if<n == i, std::true_type, cond>;
        };

        using type = typeof_t<impl<lower>>;
    };

    template <auto n, auto lower, auto upper>
    using within_t = typeof_t<within<n, lower, upper>>;

    template <auto n, auto lower, auto upper>
    inline constexpr auto within_v = typev<within_t<n, lower, upper>>;

    template <auto i, auto j, typename T, typename U, typename V, template <typename ...> typename F = std::is_same>
    struct gsub
    {
        template <auto N, typename W, typename X = element<N, W>>
        using cond = conditional_of<F<T, typeof_t<X>>, U, X>;

        template <auto N, typename W>
        using impl = element_if_t<!within_v<N, i, j>, N, W, cond<N, W>>;

        using type = expand_t<impl, V, index_sequence_of_t<V>>;
    };

    template <auto i, auto j, typename T, typename U, typename V, template <typename ...> typename F = std::is_same>
    using gsub_t = typeof_t<gsub<i, j, T, U, V, F>>;

    template <auto i, auto j, auto M, auto N, typename V, template <typename ...> typename F = std::is_same>
    using gsub_c = gsub_t<i, j, c_<M>, c_<N>, V, F>;

    template <typename T, typename U, typename V>
    using replace_with = gsub<0, sizeof_t_v<V>, T, U, V>;

    template <typename T, typename U, typename V>
    using replace_with_t = typeof_t<replace_with<T, U, V>>;

    template <auto M, auto N, typename V>
    using replace_with_c = replace_with_t<c_<M>, c_<N>, V>;

    template <auto i, auto j, typename T, typename U, template <typename ...> typename F, template <typename ...> typename G = std::is_same>
    struct adjust
    {
        template <auto N, typename W, typename X = element<N, W>, typename Y = typeof_t<X>>
        using cond = conditional_of<G<T, Y>, F<Y>, X>;

        template <auto N, typename W>
        using impl = element_if_t<!within_v<N, i, j>, N, W, cond<N, W>>;

        using type = expand_t<impl, U, index_sequence_of_t<U>>;
    };

    template <auto i, auto j, typename T, typename U, template <typename ...> typename F, template <typename ...> typename G = std::is_same>
    using adjust_t = typeof_t<adjust<i, j, T, U, F, G>>;

    template <auto i, auto j, typename U, template <typename ...> typename F, template <typename ...> typename G>
    struct adjust_if
    {
        template <typename V, typename W>
        using apply = G<W>;

        using type = adjust_t<i, j, U, U, F, apply>;
    };

    template <auto i, auto j, typename U, template <typename ...> typename F, template <typename ...> typename G>
    using adjust_if_t = typeof_t<adjust_if<i, j, U, F, G>>;

    template <auto i, auto j, typename T, typename U>
    struct substitute
    {
        template <auto N, typename V>
        using impl = element_if_t<!within_v<N, i, j>, N, V, T>;

        using type = expand_t<impl, U, index_sequence_of_t<U>>;
    };

    template <auto i, auto j, typename T, typename U>
    using substitute_t = typeof_t<substitute<i, j, T, U>>;

    template <auto i, auto j, auto N, typename U>
    using substitute_c = substitute_t<i, j, c_<N>, U>;

    template <auto i, typename T, typename U>
    using exchange = substitute<i, i + 1, T, U>;

    template <auto i, typename T, typename U>
    using exchange_t = typeof_t<exchange<i, T, U>>;

    template <auto i, auto N, typename U>
    using exchange_c = exchange_t<i, c_<N>, U>;

    template <bool B, auto i, typename T, typename U>
    using exchange_if = std::conditional_t<!B, std::type_identity<U>, exchange<i, T, U>>;

    template <bool B, auto i, typename T, typename U>
    using exchange_if_t = typeof_t<exchange_if<B, i, T, U>>;

    template <typename indices, typename T, typename U>
    requires less_equal_v<indices, U>
    struct exchange_with
    {
        template <typename V, typename W>
        struct impl;

        template <auto n, auto... N, typename W>
        struct impl<std::index_sequence<n, N...>, W> : impl<std::index_sequence<N...>, exchange_t<n, element_t<n, T>, W>>
        {
        };

        template <typename W>
        struct impl<std::index_sequence<>, W> : std::type_identity<W>
        {
        };

        using type = typeof_t<impl<indices, U>>;
    };

    template <typename indices, typename T, typename U>
    using exchange_with_t = typeof_t<exchange_with<indices, T, U>>;

    template <auto lower, auto upper, typename T>
    using range = invoke_of<T, std::type_identity<expand_of<T, index_sequence_of_c<upper - lower>, lower>>>;

    template <auto lower, auto upper, typename T>
    using range_t = typeof_t<range<lower, upper, T>>;

    template <bool B, auto lower, auto upper, typename T>
    using range_if = std::conditional_t<B, range<lower, upper, T>, std::type_identity<T>>;

    template <bool B, auto lower, auto upper, typename T>
    using range_if_t = typeof_t<range_if<B, lower, upper, T>>;

    template <auto pos, auto len, typename T>
    struct subset : range<pos, pos + len, T>
    {
    };

    template <auto pos, auto len, typename T>
    using subset_t = typeof_t<subset<pos, len, T>>;

    template <auto N, typename T>
    struct pivot : concat<range_t<N, sizeof_t_v<T>, T>, range_t<0, N, T>>
    {
    };

    template <auto N, typename T>
    using pivot_t = typeof_t<pivot<N, T>>;

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    requires (q <= p)
    struct starts_with : std::is_same<range_t<0, q, T>, U>
    {
    };

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    requires (q <= p)
    inline constexpr auto starts_with_v = typev<starts_with<T, U, p, q>>;

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    requires (q <= p)
    struct ends_with : std::is_same<range_t<p - q, p, T>, U>
    {
    };

    template <typename T, typename U, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    requires (q <= p)
    inline constexpr auto ends_with_v = typev<ends_with<T, U, p, q>>;

    template <bool B, auto lower, auto upper, typename T>
    using range_if = std::conditional_t<B, range<lower, upper, T>, std::type_identity<T>>;

    template <bool B, auto lower, auto upper, typename T>
    using range_if_t = typeof_t<range_if<B, lower, upper, T>>;

    template <auto i, auto j, typename T, typename U>
    struct swap_ranges
    {
        template <typename V>
        struct impl
        {
            template <auto k, typename W>
            using apply = element<k + i, V>;
        };

        using indices = index_sequence_of_c<j - i>;

        template <typename X, typename Y>
        struct swap
        {
            using curr = expand_t<impl<Y>::template apply, X, indices>;
            using type = concat_t<range_t<0, i, X>, curr, range_t<j, sizeof_t_v<X>, X>>;
        };

        using first = typeof_t<swap<T, U>>;
        using second = typeof_t<swap<U, T>>;
    };

    template <auto i, auto j, typename T, typename U>
    using swap_ranges_first = first_t<swap_ranges<i, j, T, U>>;

    template <auto i, auto j, typename T, typename U>
    using swap_ranges_second = second_t<swap_ranges<i, j, T, U>>;

    template <auto B1, auto E1, auto B2, auto E2, typename T, typename U>
    struct swap_extent
    {
        template <auto b1, auto e1, auto b2, auto e2, typename X, typename Y>
        using swap = concat_t<range_t<0, b1, X>, range_t<b2, e2, Y>, range_t<e1, sizeof_t_v<X>, X>>;

        using first = swap<B1, E1, B2, E2, T, U>;
        using second = swap<B2, E2, B1, E1, U, T>;
    };

    template <auto B1, auto E1, auto B2, auto E2, typename T, typename U>
    using swap_extent_first = first_t<swap_extent<B1, E1, B2, E2, T, U>>;

    template <auto B1, auto E1, auto B2, auto E2, typename T, typename U>
    using swap_extent_second = second_t<swap_extent<B1, E1, B2, E2, T, U>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct set_difference
    {
        template <int i, int j, int p, int q, typename V>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<p, U>;

            static constexpr auto cond1 = typev<F<lhs, rhs>>;
            static constexpr auto cond2 = negav<F<rhs, lhs>>;

            using type = typeof_t<impl<i + (cond1 || cond2), j, p + !cond1, q, append_if_t<cond1, V, lhs>>>;
        };

        template <int j, int p, int q, typename V>
        struct impl<j, j, p, q, V> : std::type_identity<V>
        {
        };

        template <int i, int j, int q, typename V>
        struct impl<i, j, q, q, V> : concat<V, range_t<i, j, T>>
        {
        };

        template <int j, int q, typename V>
        struct impl<j, j, q, q, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B1, E1, B2, E2, base_type_t<T>>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using set_difference_t = typeof_t<set_difference<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct set_symmetric_difference
    {
        template <int i, int j, int p, int q, typename V>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<p, U>;

            static constexpr auto cond1 = typev<F<lhs, rhs>>;
            static constexpr auto cond2 = typev<F<rhs, lhs>>;

            using next = type_if<cond1, append<V, lhs>, append_if<cond2, V, rhs>>;
            using type = typeof_t<impl<i + (cond1 || !cond2), j, p + !cond1, q, next>>;
        };

        template <int j, int p, int q, typename V>
        struct impl<j, j, p, q, V> : std::type_identity<V>
        {
        };

        template <int i, int j, int q, typename V>
        struct impl<i, j, q, q, V> : concat<V, range_t<i, j, T>>
        {
        };

        template <int j, int q, typename V>
        struct impl<j, j, q, q, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B1, E1, B2, E2, base_type_t<T>>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using set_symmetric_difference_t = typeof_t<set_symmetric_difference<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct set_intersection
    {
        template <int i, int j, int p, int q, typename V>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<p, U>;

            static constexpr auto cond1 = typev<F<lhs, rhs>>;
            static constexpr auto cond2 = negav<F<rhs, lhs>>;

            using next = append_if_t<!cond1 && cond2, V, lhs>;
            using type = typeof_t<impl<i + (cond1 || cond2), j, p + !cond1, q, next>>;
        };

        template <int j, int p, int q, typename V>
        struct impl<j, j, p, q, V> : std::type_identity<V>
        {
        };

        template <int i, int j, int q, typename V>
        struct impl<i, j, q, q, V> : std::type_identity<V>
        {
        };

        template <int j, int q, typename V>
        struct impl<j, j, q, q, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B1, E1, B2, E2, base_type_t<T>>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using set_intersection_t = typeof_t<set_intersection<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct set_union
    {
        template <int i, int j, int p, int q, typename V>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<p, U>;

            static constexpr auto cond1 = typev<F<rhs, lhs>>;
            static constexpr auto cond2 = negav<F<lhs, rhs>>;

            using next = append_t<V, std::conditional_t<cond1, rhs, lhs>>;
            using type = typeof_t<impl<i + !cond1, j, p + (cond1 || cond2), q, next>>;
        };

        template <int j, int p, int q, typename V>
        struct impl<j, j, p, q, V> : concat<V, range_t<p, q, U>>
        {
        };

        template <int i, int j, int q, typename V>
        struct impl<i, j, q, q, V> : concat<V, range_t<i, j, T>>
        {
        };

        template <int j, int q, typename V>
        struct impl<j, j, q, q, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B1, E1, B2, E2, base_type_t<T>>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using set_union_t = typeof_t<set_union<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct mismatch
    {
        template <int i, int j, int p, int q>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<p, U>;

            static constexpr auto value = typev<F<rhs, lhs>>;
            using type = type_if<value, impl<i + 1, j, p + 1, q>, std::type_identity<pair_v<i, p>>>;
        };

        template <int j, int p, int q>
        struct impl<j, j, p, q>
        {
            using type = pair_v<j, p>;
        };

        template <int i, int j, int q>
        struct impl<i, j, q, q>
        {
            using type = pair_v<i, q>;
        };

        template <int j, int q>
        struct impl<j, j, q, q>
        {
            using type = pair_v<j, q>;
        };

        using type = typeof_t<impl<B1, E1, B2, E2>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using mismatch_t = typeof_t<mismatch<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    inline constexpr auto mismatch_first = first_v<mismatch_t<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    inline constexpr auto mismatch_second = second_v<mismatch_t<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct includes
    {
        template <int i, int j, int p, int q>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<p, U>;

            static constexpr auto cond1 = typev<F<rhs, lhs>>;
            static constexpr auto cond2 = negav<F<lhs, rhs>>;

            using type = type_if<i == j || cond1, std::false_type, impl<i + 1, j, p + cond2, q>>;
        };

        template <int i, int j, int q>
        struct impl<i, j, q, q> : std::true_type
        {
        };

        using type = typeof_t<impl<B1, E1, B2, E2>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using includes_t = typeof_t<includes<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    inline constexpr auto includes_v = typev<includes_t<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct search
    {
        template <int i>
        struct impl
        {
            template <int j, int k>
            struct next
            {
                template <int p, int q>
                struct call
                {
                    using lhs = element_t<p, T>;
                    using rhs = element_t<q, U>;

                    static constexpr auto cond = negav<F<lhs, rhs>>;
                    using type = type_if<cond, impl<i + 1>, next<p + 1, q + 1>>;
                };

                static constexpr auto cond1 = k == E2;
                static constexpr auto cond2 = j == E1;

                using type = type_if<cond1 || cond2, c_<cond1 ? i : E1>, call<j, k>>;
            };

            using type = typeof_t<next<i, B2>>;
        };

        using type = typeof_t<impl<B1>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using search_t = typeof_t<search<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    inline constexpr auto search_v = typev<search_t<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, int N, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct search_n
    {
        template <int i, int j>
        struct impl
        {
            template <int k, int p, int q>
            struct next
            {
                template <int l>
                struct call
                {
                    static constexpr auto cond = negav<F<element_t<l, U>, T>>;
                    using type = type_if<cond, impl<l + 1, j>, next<l, p, q + 1>>;
                };

                static constexpr auto cond1 = q + 1 >= N;
                static constexpr auto cond2 = k + 1 == E;

                using type = type_if<cond1 || cond2, c_<cond1 ? p : E>, call<k + 1>>;
            };

            static constexpr auto value = negav<F<element_t<i, U>, T>>;
            using type = type_if<value, impl<i + 1, j>, next<i, i, 0>>;
        };

        template <int j>
        struct impl<j, j> : c_<E>
        {
        };

        using type = type_if<N <= 0, c_<B>, impl<B, E>>;
    };

    template <template <typename, typename> typename F, int N, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using search_n_t = typeof_t<search_n<F, N, T, U, B, E>>;

    template <template <typename, typename> typename F, int N, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    inline constexpr auto search_n_v = typev<search_n_t<F, N, T, U, B, E>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct find_end
    {
        template <int i, int j>
        struct impl
        {
            static constexpr auto value = search_v<F, T, U, i, E1, B2, E2>;
            using type = type_if<value == E1, c_<j>, impl<value + 1, value>>;
        };

        using type = type_if<B2 == E2, c_<E1>, impl<B1, E1>>;
    };

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    using find_end_t = typeof_t<find_end<F, T, U, B1, E1, B2, E2>>;

    template <template <typename, typename> typename F, typename T, typename U,
    auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    inline constexpr auto find_end_v = typev<find_end_t<F, T, U, B1, E1, B2, E2>>;

    template <typename T, typename U>
    struct lca
    {
        static constexpr auto M = sizeof_t_v<T>;
        static constexpr auto N = sizeof_t_v<U>;

        template <int i, int j, int k, int l, typename V, typename W>
        struct impl
        {
            using lhs = element_t<i, V>;
            using rhs = element_t<j, W>;

            using next = impl<i + 1, j + 1, k, l, V, W>;
            using type = type_if<std::is_same_v<lhs, rhs>, std::type_identity<lhs>, next>;
        };

        template <int k, int l, typename V, typename W>
        struct impl<k, l, k, l, V, W> : std::type_identity<V>
        {
        };

        static constexpr auto val = M > N;
        static constexpr auto len = abs_v<M, N>;

        using type = typeof_t<impl<val * len, !val * len, M, N, T, U>>;
    };

    template <typename T, typename U>
    using lca_t = typeof_t<lca<T, U>>;

    template <typename T, typename U>
    inline constexpr auto lca_v = typev<lca_t<T, U>>;

    template <template <typename> typename F, typename T>
    struct transform;

    template <template <typename> typename F, template <typename ...> typename T, typename... Args>
    struct transform<F, T<Args...>>
    {
        using type = T<typeof_t<F<Args>>...>;
    };

    template <template <typename> typename F, template <typename, auto ...> typename T, typename U, auto... Args>
    struct transform<F, T<U, Args...>>
    {
        using type = T<U, typev<F<c_<Args, U>>>...>;
    };

    template <template <typename> typename F, typename T>
    using transform_t = typeof_t<transform<F, T>>;

    template <template <typename> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct generate : concat<range_t<0, B, T>, transform_t<F, range_t<B, E, T>>, range_t<E, sizeof_t_v<T>, T>>
    {
    };

    template <template <typename> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using generate_t = typeof_t<generate<F, T, B, E>>;

    template <template <typename, typename> typename F, typename T,
    typename init = element_t<0, T>, auto B = 0, auto E = sizeof_t_v<T>>
    struct inclusive_scan
    {
        template <int i, int j, typename U, typename V>
        struct impl
        {
            using curr = typeof_t<F<U, element_t<i, T>>>;
            using type = typeof_t<impl<i + 1, j, curr, append_t<V, curr>>>;
        };

        template <int j, typename U, typename V>
        struct impl<j, j, U, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B + 1, E, init, append_t<base_type_t<T>, init>>>;
    };

    template <template <typename, typename> typename F, typename T,
    typename init = element_t<0, T>, auto B = 0, auto E = sizeof_t_v<T>>
    using inclusive_scan_t = typeof_t<inclusive_scan<F, T, init, B, E>>;

    template <template <typename, typename> typename F, typename T,
    typename init, auto B = 0, auto E = sizeof_t_v<T>>
    struct exclusive_scan
    {
        template <int i, int j, typename U, typename V>
        struct impl
        {
            using curr = typeof_t<F<U, element_t<i, T>>>;
            using type = typeof_t<impl<i + 1, j, curr, append_t<V, curr>>>;
        };

        template <int j, typename U, typename V>
        struct impl<j, j, U, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B, E - 1, init, append_t<base_type_t<T>, init>>>;
    };

    template <template <typename, typename> typename F, typename T,
    typename init, auto B = 0, auto E = sizeof_t_v<T>>
    using exclusive_scan_t = typeof_t<exclusive_scan<F, T, init, B, E>>;

    template <template <typename, typename> typename F, typename T, template <typename> typename U,
    typename init = typeof_t<U<element_t<0, T>>>, auto B = 0, auto E = sizeof_t_v<T>>
    struct transform_inclusive_scan
    {
        using type = inclusive_scan_t<F, transform_t<U, range_t<B, E, T>>, init, B, E>;
    };

    template <template <typename, typename> typename F, typename T, template <typename> typename U,
    typename init = typeof_t<U<element_t<0, T>>>, auto B = 0, auto E = sizeof_t_v<T>>
    using transform_inclusive_scan_t = typeof_t<transform_inclusive_scan<F, T, U, init, B, E>>;

    template <template <typename, typename> typename F, typename T, template <typename> typename U,
    typename init, auto B = 0, auto E = sizeof_t_v<T>>
    struct transform_exclusive_scan
    {
        using type = exclusive_scan_t<F, transform_t<U, range_t<B, E, T>>, init, B, E>;
    };

    template <template <typename, typename> typename F, typename T, template <typename> typename U,
    typename init, auto B = 0, auto E = sizeof_t_v<T>>
    using transform_exclusive_scan_t = typeof_t<transform_exclusive_scan<F, T, U, init, B, E>>;

    template <template <typename, typename> typename F, typename T, typename U, auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0>
    requires is_variadic_pack_v<T, U>
    struct transmute
    {
        template <int i, int j, int k, typename W>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<k, U>;

            using next = append_t<W, typeof_t<F<lhs, rhs>>>;
            using type = typeof_t<impl<i + 1, j, k + 1, next>>;
        };

        template <int j, int k, typename W>
        struct impl<j, j, k, W> : std::type_identity<W>
        {
        };

        using type = typeof_t<impl<B1, E1, B2, base_type_t<T>>>;
    };

    template <template <typename, typename> typename F, typename T, typename U, auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0>
    using transmute_t = typeof_t<transmute<F, T, U, B1, E1, B2>>;

    template <template <typename, typename> typename F1, template <typename, typename> typename F2,
    typename T, typename U, typename V, auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0>
    requires is_variadic_pack_v<T, U>
    struct inner_product
    {
        template <int i, int j, int k, typename W>
        struct impl
        {
            using lhs = element_t<i, T>;
            using rhs = element_t<k, U>;

            using curr = typeof_t<F2<lhs, rhs>>;
            using next = typeof_t<F1<W, curr>>;

            using type = typeof_t<impl<i + 1, j, k + 1, next>>;
        };

        template <int j, int k, typename W>
        struct impl<j, j, k, W> : std::type_identity<W>
        {
        };

        using type = typeof_t<impl<B1, E1, B2, V>>;
    };

    template <template <typename, typename> typename F1, template <typename, typename> typename F2,
    typename T, typename U, typename V, auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0>
    using inner_product_t = typeof_t<inner_product<F1, F2, T, U, V, B1, E1, B2>>;

    template <template <typename, typename> typename F1, template <typename, typename> typename F2,
    typename T, typename U, typename V, auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0>
    inline constexpr auto inner_product_v = typev<inner_product_t<F1, F2, T, U, V, B1, E1, B2>>;

    template <template <typename, typename> typename F, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct accumulate
    {
        template <int i, int j, typename V>
        struct impl
        {
            using next = typeof_t<F<V, element_t<i, U>>>;
            using type = typeof_t<impl<i + 1, j, next>>;
        };

        template <int j, typename V>
        struct impl<j, j, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B, E, T>>;
    };

    template <template <typename, typename> typename F, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using accumulate_t = typeof_t<accumulate<F, T, U, B, E>>;

    template <template <typename, typename> typename F, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    inline constexpr auto accumulate_v = typev<accumulate_t<F, T, U, B, E>>;

    template <template <typename> typename F, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct iota
    {
        template <int i, int j, typename V, typename W>
        struct impl
        {
            using next = typeof_t<F<V>>;
            using type = typeof_t<impl<i + 1, j, next, exchange_t<i, V, W>>>;
        };

        template <int j, typename V, typename W>
        struct impl<j, j, V, W> : std::type_identity<W>
        {
        };

        using type = typeof_t<impl<B, E, T, U>>;
    };

    template <template <typename> typename F, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using iota_t = typeof_t<iota<F, T, U, B, E>>;

    template <typename T>
    struct reverse
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <auto i, typename U>
        using impl = element<N - i - 1, U>;

        using type = invoke_of<T, expand<impl, T, index_sequence_of_c<N>>>;
    };

    template <typename T>
    using reverse_t = typeof_t<reverse<T>>;

    template <bool B, typename T>
    using reverse_if = std::conditional_t<B, reverse<T>, std::type_identity<T>>;

    template <bool B, typename T>
    using reverse_if_t = typeof_t<reverse_if<B, T>>;

    template <typename T, typename indices, bool B = false>
    struct apply_permutation : expand_of<reverse_if_t<B, T>, reverse_if_t<B, indices>>
    {
    };

    template <typename T, typename indices, bool B = false>
    using apply_permutation_t = typeof_t<apply_permutation<T, indices, B>>;

    template <typename T, template <typename ...> typename F>
    struct reverse_with
    {
        using call = std::conditional_t<is_tuple_v<T>, F<T>, std::type_identity<T>>;
        using type = type_if<is_sequence_v<T>, reverse<T>, call>;
    };

    template <typename T, template <typename ...> typename F>
    using reverse_with_t = typeof_t<reverse_with<T, F>>;

    template <typename T>
    struct reverse_recursive
    {
        template <typename U>
        using apply = reverse_with_t<U, reverse_recursive>;

        using type = reverse_t<eval_t<currying_t, apply, T>>;
    };

    template <typename T>
    using reverse_recursive_t = typeof_t<reverse_recursive<T>>;

    template <auto i, auto j, typename T>
    struct extent : reverse<range_t<i, j, T>>
    {
    };

    template <auto i, auto j, typename T>
    using extent_t = typeof_t<extent<i, j, T>>;

    template <auto i, auto j, typename T, auto N = sizeof_t_v<T>>
    using degree = extent<N - j, N - i, T>;

    template <auto i, auto j, typename T>
    using degree_t = typeof_t<degree<i, j, T>>;

    template <auto i, auto j, typename T>
    struct erase : concat<range_t<0, i, T>, range_t<j, sizeof_t_v<T>, T>>
    {
    };

    template <auto i, auto j, typename T>
    using erase_t = typeof_t<erase<i, j, T>>;

    template <auto i, typename T>
    using drop = erase<i, i + 1, T>;

    template <auto i, typename T>
    using drop_t = typeof_t<drop<i, T>>;

    template <auto n, typename T>
    using drop_front = range<n, sizeof_t_v<T>, T>;

    template <auto n, typename T>
    using drop_front_t = typeof_t<drop_front<n, T>>;

    template <auto n, typename T>
    using drop_back = range<0, sizeof_t_v<T> - n, T>;

    template <auto n, typename T>
    using drop_back_t = typeof_t<drop_back<n, T>>;

    template <auto n, typename T>
    using take_front = range<0, n, T>;

    template <auto n, typename T>
    using take_front_t = typeof_t<take_front<n, T>>;

    template <auto n, typename T>
    using take_back = range<sizeof_t_v<T> - n, sizeof_t_v<T>, T>;

    template <auto n, typename T>
    using take_back_t = typeof_t<take_back<n, T>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct unique_if
    {
        template <int i, int j, typename U, bool>
        struct impl
        {
            using lhs = element_t<j, U>;
            using rhs = element_t<i, U>;

            static constexpr auto value = negav<F<lhs, rhs>>;

            using next = exchange_if_t<value && j + 1 != i, j + 1, rhs, U>;
            using type = typeof_t<impl<i + 1, j + value, next, i + 1 != E>>;
        };

        template <int i, int j, typename U>
        struct impl<i, j, U, false>
        {
            using type = index_type<j + 1, U>;
        };

        template <typename U>
        struct call
        {
            using curr = typeof_t<impl<B + 1, B, U, B + 1 != E>>;
            using type = erase_t<typev<curr>, E, typeof_t<curr>>;
        };

        using type = type_if<B == E, std::type_identity<T>, call<T>>;
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using unique_if_t = typeof_t<unique_if<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct remove_if
    {
        static constexpr auto N = find_if_v<F, T, B, E>;

        template <int i, int j, typename U, bool>
        struct impl
        {
            using curr = element_t<j, U>;
            static constexpr auto value = negav<F<curr>>;

            using next = exchange_if_t<value, i, curr, U>;
            using type = typeof_t<impl<i + value, j + 1, next, j + 1 != E>>;
        };

        template <int i, int j, typename U>
        struct impl<i, j, U, false>
        {
            using type = index_type<i, U>;
        };

        template <typename U>
        struct call
        {
            using curr = typeof_t<impl<N, N + 1, U, N + 1 != E>>;
            using type = erase_t<typev<curr>, E, typeof_t<curr>>;
        };

        using type = type_if<N == E, std::type_identity<T>, call<T>>;
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using remove_if_t = typeof_t<remove_if<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct remove_if_not : remove_if<negaf<F>::template apply, T, B, E>
    {
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using remove_if_not_t = typeof_t<remove_if_not<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, auto B, auto E, bool value>
    struct copy
    {
        template <int i, int j, typename U>
        struct impl
        {
            using curr = element_t<i, T>;
            using type = typeof_t<impl<i + 1, j, append_if_t<value == typev<F<curr>>, U, curr>>>;
        };

        template <int j, typename U>
        struct impl<j, j, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<B, E, base_type_t<T>>>;
    };

    template <template <typename ...> typename F, typename T, auto B, auto E, bool value>
    using copy_t = typeof_t<copy<F, T, B, E, value>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct copy_if : copy<F, T, B, E, true>
    {
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using copy_if_t = typeof_t<copy_if<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct copy_if_not : copy<F, T, B, E, false>
    {
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using copy_if_not_t = typeof_t<copy_if_not<F, T, B, E>>;

    template <typename T, typename indices>
    struct exclude : expand_of<T, set_difference_t<less_t, index_sequence_of_t<T>, indices>>
    {
    };

    template <typename T, typename indices>
    using exclude_t = typeof_t<exclude<T, indices>>;

    template <auto i, typename T, typename ...>
    struct insert;

    template <auto i, template <typename ...> typename T, typename... Args, typename... args>
    struct insert<i, T<Args...>, args...>
    {
        using curr = T<Args...>;
        using type = concat_t<range_t<0, i, curr>, T<args...>, range_t<i, sizeof_t_v<curr>, curr>>;
    };

    template <auto i, template <typename, auto ...> typename T, typename U, auto... Args, typename... args>
    struct insert<i, T<U, Args...>, args...>
    {
        using curr = T<U, Args...>;
        using type = concat_t<range_t<0, i, curr>, T<U, typev<args>...>, range_t<i, sizeof_t_v<curr>, curr>>;
    };

    template <auto i, typename T, typename... Args>
    using insert_t = typeof_t<insert<i, T, Args...>>;

    template <auto i, typename T, auto... values>
    using insert_c = insert_t<i, T, c_<values>...>;

    template <auto i, auto j, template <typename ...> typename F, typename T, typename U>
    requires is_variadic_pack_v<T, U>
    struct extract
    {
        template <typename V, bool>
        struct impl
        {
            using type = unpack_t<bind_front<F, T>::template apply, V>;
        };

        template <typename V>
        struct impl<V, false>
        {
            using type = concat_t<range_t<0, i, T>, V, range_t<j, sizeof_t_v<T>, T>>;
        };

        using type = typeof_t<impl<U, is_tuple_v<U>>>;
    };

    template <auto i, auto j, template <typename ...> typename F, typename T, typename U>
    using extract_t = typeof_t<extract<i, j, F, T, U>>;

    template <auto i, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct insert_range
    {
        template <typename V, typename... Args>
        using apply = insert_t<i, V, Args...>;

        using type = extract_t<i, i, apply, T, range_t<B, E, U>>;
    };

    template <auto i, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using insert_range_t = typeof_t<insert_range<i, T, U, B, E>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    struct append_range : insert_range<sizeof_t_v<T>, T, U, B, E>
    {
    };

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    using append_range_t = typeof_t<append_range<T, U, B, E>>;

    template <bool B, typename T, typename U, int i = 0, int j = sizeof_t_v<U>>
    using append_range_if = type_if<B, append_range<T, U, i, j>, std::type_identity<T>>;

    template <bool B, typename T, typename U, int i = 0, int j = sizeof_t_v<U>>
    using append_range_if_t = typeof_t<append_range_if<B, T, U, i, j>>;

    template <auto i, auto j, typename T, typename... Args>
    struct replace : concat<append_t<range_t<0, i, T>, Args...>, range_t<j, sizeof_t_v<T>, T>>
    {
    };

    template <auto i, auto j, typename T, typename... Args>
    using replace_t = typeof_t<replace<i, j, T, Args...>>;

    template <auto i, auto j, typename T, auto... values>
    using replace_c = replace_t<i, j, T, c_<values>...>;

    template <auto i, auto j, template <typename ...> typename F, typename T, typename U>
    struct replace_if
    {
        template <typename V, typename W>
        using apply = F<W>;

        using type = gsub_t<i, j, T, T, U, apply>;
    };

    template <auto i, auto j, template <typename ...> typename F, typename T, typename U>
    using replace_if_t = typeof_t<replace_if<i, j, F, T, U>>;

    template <auto i, auto j, template <typename ...> typename F, auto N, typename U>
    using replace_if_c = replace_if_t<i, j, F, c_<N>, U>;

    template <auto i, auto j, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    requires is_variadic_pack_v<T, U>
    struct replace_range
    {
        template <typename V, typename... Args>
        using apply = replace_t<i, j, V, Args...>;

        using type = extract_t<i, j, apply, T, range_t<B, E, U>>;
    };

    template <auto i, auto j, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using replace_range_t = typeof_t<replace_range<i, j, T, U, B, E>>;

    template <typename T, typename U>
    struct copy_backward
    {
        template <bool, typename V>
        struct impl : concat<range_t<0, size_diff<U, V>, U>, V>
        {
        };

        template <typename V>
        struct impl<false, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<less_v<T, U>, T>>;
    };

    template <typename T, typename U>
    using copy_backward_t = typeof_t<copy_backward<T, U>>;

    template <auto i, auto j, typename T>
    struct reverse_range
    {
        using reversed = extent_t<i, j, T>;

        template <size_t N, bool B, bool E>
        struct impl : std::type_identity<reversed>
        {
        };

        template <size_t N>
        struct impl<N, true, false> : concat<reversed, range_t<j, N, T>>
        {
        };

        template <size_t N, bool E>
        struct impl<N, false, E>
        {
            using cond = type_if<E, base_type<T>, range<j, N, T>>;
            using type = concat_t<range_t<0, i, T>, reversed, cond>;
        };

        static constexpr auto N = sizeof_t_v<T>;
        using type = invoke_of<T, impl<N, i == 0, j == N>>;
    };

    template <auto i, auto j, typename T>
    using reverse_range_t = typeof_t<reverse_range<i, j, T>>;

    template <bool B, typename T>
    struct pop;

    template <bool B, template <typename, auto ...> typename T, typename U, auto value, auto... values>
    struct pop<B, T<U, value, values...>>
    {
        template <typename W, bool>
        struct impl
        {
            using type = T<U, values...>;
        };

        template <typename W>
        struct impl<W, false>
        {
            using type = reverse_t<typeof_t<pop<!B, reverse_t<W>>>>;
        };

        using type = typeof_t<impl<T<U, value, values...>, B>>;
    };

    template <bool B, template <typename, auto ...> typename T, typename U>
    struct pop<B, T<U>> : std::type_identity<T<U>>
    {
    };

    template <bool B, template <typename ...> typename T, typename U, typename... Args>
    struct pop<B, T<U, Args...>>
    {
        template <typename W, bool>
        struct impl
        {
            using type = T<Args...>;
        };

        template <typename W>
        struct impl<W, false>
        {
            using type = reverse_t<typeof_t<pop<!B, reverse_t<W>>>>;
        };

        using type = typeof_t<impl<T<U, Args...>, B>>;
    };

    template <bool B, template <typename ...> typename T>
    struct pop<B, T<>> : std::type_identity<T<>>
    {
    };

    template <bool B, typename T>
    using pop_t = typeof_t<pop<B, T>>;

    template <typename T>
    using pop_front = pop<1, T>;

    template <typename T>
    using pop_front_t = typeof_t<pop_front<T>>;

    template <typename T>
    using pop_back = pop<0, T>;

    template <typename T>
    using pop_back_t = typeof_t<pop_back<T>>;

    template <typename T, typename U = T, typename... Args>
    constexpr size_t typeindex()
    {
        return std::is_same<T, U>() ? 1 : typeindex<T, Args...>() + 1;
    }

    template <auto T, auto U = T, auto... Args>
    constexpr size_t valueindex()
    {
        return T == U ? 1 : valueindex<T, Args...>() + 1;
    }

    template <typename T, typename U>
    struct type_index;

    template <typename T, template <typename ...> typename U>
    struct type_index<T, U<>> : index_t<0>
    {
    };

    template <typename T, template <typename ...> typename U, typename... Args>
    struct type_index<T, U<T, Args...>> : index_t<0>
    {
    };

    template <typename T, template <typename ...> typename U, typename V, typename... Args>
    struct type_index<T, U<V, Args...>> : index_t<typev<type_index<T, U<Args...>>> + 1>
    {
    };

    template <typename T, typename U>
    inline constexpr auto type_index_v = typev<type_index<T, U>>;

    template <typename T, typename U>
    struct type_index_not;

    template <typename T, template <typename ...> typename U>
    struct type_index_not<T, U<>> : index_t<0>
    {
    };

    template <typename T, template <typename ...> typename U, typename V, typename... Args>
    struct type_index_not<T, U<V, Args...>> : index_t<0>
    {
    };

    template <typename T, template <typename ...> typename U, typename... Args>
    struct type_index_not<T, U<T, Args...>> : index_t<typev<type_index_not<T, U<Args...>>> + 1>
    {
    };

    template <typename T, typename U>
    inline constexpr auto type_index_not_v = typev<type_index_not<T, U>>;

    template <bool neg, typename T, typename U>
    using type_index_if = std::conditional_t<!neg, type_index<T, U>, type_index_not<T, U>>;

    template <bool neg, typename T, typename U>
    inline constexpr auto type_index_if_v = typev<type_index_if<neg, T, U>>;

    template <auto value, typename T>
    struct value_index;

    template <auto value, template <typename, auto ...> typename T, typename U>
    struct value_index<value, T<U>> : index_t<0>
    {
    };

    template <auto value, template <typename, auto ...> typename T, typename U, auto... values>
    struct value_index<value, T<U, value, values...>> : index_t<0>
    {
    };

    template <auto value, template <typename, auto ...> typename T, typename U, auto V, auto... values>
    struct value_index<value, T<U, V, values...>> : index_t<typev<value_index<value, T<U, values...>>> + 1>
    {
    };

    template <auto value, typename T>
    inline constexpr auto value_index_v = typev<value_index<value, T>>;

    template <auto value, typename T>
    struct value_index_not;

    template <auto value, template <typename, auto ...> typename T, typename U>
    struct value_index_not<value, T<U>> : index_t<0>
    {
    };

    template <auto value, template <typename, auto ...> typename T, typename U, auto V, auto... values>
    struct value_index_not<value, T<U, V, values...>> : index_t<0>
    {
    };

    template <auto value, template <typename, auto ...> typename T, typename U, auto... values>
    struct value_index_not<value, T<U, value, values...>> : index_t<typev<value_index_not<value, T<U, values...>>> + 1>
    {
    };

    template <auto value, typename T>
    inline constexpr auto value_index_not_v = typev<value_index_not<value, T>>;

    template <bool neg, auto value, typename T>
    using value_index_if = std::conditional_t<!neg, value_index<value, T>, value_index_not<value, T>>;

    template <bool neg, auto value, typename T>
    inline constexpr auto value_index_if_v = typev<value_index_if<neg, value, T>>;

    template <typename T, typename U, bool B = false, bool neg = false>
    requires is_variadic_value_v<U>
    consteval auto index_of()
    {
        using type = reverse_if_t<B, U>;
        constexpr auto index = value_index_if_v<neg, typev<T>, type>;

        constexpr auto size = sizeof_t_v<type>;
        return size == index ? size : B ? size - index - 1 : index;
    }

    template <typename T, typename U, bool B = false, bool neg = false>
    requires is_variadic_type_v<U>
    consteval auto index_of()
    {
        using type = reverse_if_t<B, U>;
        constexpr auto index = type_index_if_v<neg, T, type>;

        constexpr auto size = std::tuple_size_v<type>;
        return size == index ? size : B ? size - index - 1 : index;
    }

    template <typename T, typename U, int B, int E, bool B1, bool B2>
    consteval auto find_of()
    {
        return B + index_of<T, range_t<B, E, U>, B1, B2>();
    }

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    struct find
    {
        static constexpr auto value = find_of<T, U, B, E, false, false>();
    };

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    inline constexpr auto find_v = typev<find<T, U, B, E>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    struct find_backward
    {
        static constexpr auto value = find_of<T, U, B, E, true, false>();
    };

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    inline constexpr auto find_backward_v = typev<find_backward<T, U, B, E>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    struct find_not
    {
        static constexpr auto value = find_of<T, U, B, E, false, true>();
    };

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    inline constexpr auto find_not_v = typev<find_not<T, U, B, E>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    struct find_not_backward
    {
        static constexpr auto value = find_of<T, U, B, E, true, true>();
    };

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    inline constexpr auto find_not_backward_v = typev<find_not_backward<T, U, B, E>>;

    template <auto N, typename T>
    struct tuple_element_size
    {
        static constexpr auto value = sizeof_t_v<element_t<N, T>>;
    };

    template <auto N, typename T>
    inline constexpr auto tuple_element_size_v = typev<tuple_element_size<N, T>>;

    template <auto N, typename T>
    using element_size = std::conditional_t<negav<is_tuple<T>>, get<N, T>, tuple_element_size<N, T>>;

    template <auto N, typename T>
    inline constexpr auto element_size_v = typev<element_size<N, T>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct binary_search
    {
        static constexpr auto key = sizeof_t_v<T>;

        template <size_t i, size_t j>
        struct search
        {
             static constexpr auto half = i + (j - i - 1) / 2;
             static constexpr auto value = element_size_v<half, U>;

             using next = std::conditional_t<value < key, search<half + 1, j>, search<i, half>>;
             using type = type_if<value == key, std::true_type, next>;
        };

        template <size_t j>
        struct search<j, j> : std::false_type
        {
        };

        using type = typeof_t<search<B, E>>;
    };

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using binary_search_t = typeof_t<binary_search<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    inline constexpr auto binary_search_v = typev<binary_search_t<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct ternary_search
    {
        static constexpr auto key = sizeof_t_v<T>;

        template <size_t l, size_t m, size_t r, auto lower, template <size_t, size_t> typename search>
        struct impl
        {
             static constexpr auto mid = r - (r - l) / 3;
             static constexpr auto upper = element_size_v<mid, U>;

             using left = search<l, m - 1>;
             using middle = search<m + 1, mid - 1>;

             using right = search<mid + 1, r>;
             using next = ternary_conditional_t<key < upper, key < lower, left, middle, right>;

             using type = type_if<upper == key, std::true_type, next>;
        };

        template <size_t l, size_t r, bool = l <= r>
        struct search
        {
             static constexpr auto mid = l + (r - l) / 3;
             static constexpr auto lower = element_size_v<mid, U>;

             using type = type_if<lower == key, std::true_type, impl<l, mid, r, lower, search>>;
        };

        template <size_t l, size_t r>
        struct search<l, r, false> : std::false_type
        {
        };

        using type = typeof_t<search<B, E - 1>>;
    };

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using ternary_search_t = typeof_t<ternary_search<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    inline constexpr auto ternary_search_v = typev<ternary_search_t<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct exponential_search
    {
        static constexpr auto key = sizeof_t_v<T>;

        template <int i, bool = i < E>
        struct search
        {
            static constexpr auto cond = element_size_v<i, U> <= key;
            static constexpr auto value = value_if<cond, search<i * 2>, c_<i>>;
        };

        template <int i>
        struct search<i, false>
        {
            static constexpr auto value = i;
        };

        static constexpr auto value = typev<search<B + 1>>;
        static constexpr auto cond = element_size_v<B, U> == key;

        using impl = binary_search<T, U, value / 2, min_v<value, E>>;
        using type = type_if<cond, std::true_type, impl>;
    };

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using exponential_search_t = typeof_t<exponential_search<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    inline constexpr auto exponential_search_v = typev<exponential_search_t<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct interpolation_search
    {
        static constexpr auto key = sizeof_t_v<T>;

        template <size_t i, size_t j>
        struct search
        {
            template <auto p, auto q, bool = (key >= p && key <= q)>
            struct impl
            {
                static constexpr int pos = i + (j - i) * (key - p) / (q - p);
                static constexpr auto value = element_size_v<pos, U>;

                using next = std::conditional_t<value < key, search<pos + 1, j>, search<i, pos - 1>>;
                using type = type_if<value == key, std::true_type, next>;
            };

            template <auto p, auto q>
            struct impl<p, q, false> : std::false_type
            {
            };

            using type = typeof_t<impl<element_size_v<i, U>, element_size_v<j, U>>>;
        };

        template <size_t j>
        struct search<j, j> : bool_<element_size_v<j, U> == key>
        {
        };

        using type = typeof_t<search<B, E - 1>>;
    };

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using interpolation_search_t = typeof_t<interpolation_search<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    inline constexpr auto interpolation_search_v = typev<interpolation_search_t<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct fibonacci_search
    {
        static constexpr auto key = sizeof_t_v<T>;

        template <int i, int j, int k, int l, bool = (k > 1)>
        struct search
        {
            static constexpr int pos = min_v<l + i, E - 1>;
            static constexpr auto value = element_size_v<pos, U>;

            using next = std::conditional_t<value < key, search<j - i, i, j, pos>, search<i * 2 - j, j - i, i, l>>;
            using type = type_if<value == key, std::true_type, next>;
        };

        template <int i, int j, int k, int l>
        struct search<i, j, k, l, false>
        {
            template <int p, bool = p != 0>
            struct impl : bool_<element_size_v<l + 1, U> == key>
            {
            };

            template <int p>
            struct impl<p, false> : std::false_type
            {
            };

            using type = typeof_t<impl<j>>;
        };

        template <int i, int j, int k, bool = k < E>
        struct impl : impl<j, k, j + k>
        {
        };

        template <int i, int j, int k>
        struct impl<i, j, k, false>
        {
            using type = typeof_t<search<i, j, k, B - 1>>;
        };

        using type = typeof_t<impl<0, 1, 1>>;
    };

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using fibonacci_search_t = typeof_t<fibonacci_search<T, U, B, E>>;

    template <typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    inline constexpr auto fibonacci_search_v = typev<fibonacci_search_t<T, U, B, E>>;

    template <typename T>
    struct max_subarray
    {
        template <int i, int j, int k, int l, int m, int n, int p>
        struct impl
        {
            static constexpr auto value = element_size_v<n, T>;
            static constexpr auto B1 = j < 0;

            static constexpr auto curr = !B1 * j + value;
            static constexpr auto B2 = curr >= i;

            static constexpr auto q = B1 ? n : m;
            using type = typeof_t<impl<B2 ? curr : i, curr, B2 ? q : k, B2 ? n : l, q, n + 1, p>>;
        };

        template <int i, int j, int k, int l, int m, int p>
        struct impl<i, j, k, l, m, p, p>
        {
            using type = std::integer_sequence<int, k, l, i>;
        };

        static constexpr auto first = element_size_v<0, T>;
        using type = typeof_t<impl<first, first, 0, 0, 0, 1, sizeof_t_v<T>>>;
    };

    template <typename T>
    using max_subarray_t = typeof_t<max_subarray<T>>;

    template <auto n, auto N, typename T>
    using sub = exchange<n, c_<N>, T>;

    template <auto n, auto N, typename T>
    using sub_t = typeof_t<sub<n, N, T>>;

    template <auto n, auto N, typename T>
    inline constexpr auto add_v = get_v<n, T> + N;

    template <auto n, auto N, typename T>
    struct add : sub<n, add_v<n, N, T>, T>
    {
    };

    template <auto n, auto N, typename T>
    using add_t = typeof_t<add<n, N, T>>;

    template <auto n, typename T>
    using inc = add<n, 1, T>;

    template <auto n, typename T>
    using inc_t = typeof_t<inc<n, T>>;

    template <auto n, typename T>
    using dec = add<n, -1, T>;

    template <auto n, typename T>
    using dec_t = typeof_t<dec<n, T>>;

    template <auto n, typename T, typename U>
    inline constexpr auto dot_v = get_v<n, T> * get_v<n, U>;

    template <auto n, typename T, typename U>
    using dot = sub<n, dot_v<n, T, U>, T>;

    template <auto n, typename T, typename U>
    using dot_t = typeof_t<dot<n, T, U>>;

    template <typename T, typename U, bool B>
    struct inner_operator
    {
        template <auto i, typename V>
        struct call
        {
            static constexpr auto p = get_v<i, V>;
            static constexpr auto q = get_v<i, U>;

            static constexpr auto value = B ? p + q : p * q;
        };

        template <auto i, typename V>
        using impl = c_<typev<call<i, V>>>;

        using type = expand_t<impl, T, index_sequence_of_c<sizeof_t_v<min_t<T, U>>>>;
    };

    template <typename T, typename U, bool B>
    using inner_operator_t = typeof_t<inner_operator<T, U, B>>;

    template <typename T, typename U>
    struct inner_sum : inner_operator<T, U, 1>
    {
    };

    template <typename T, typename U>
    using inner_sum_t = typeof_t<inner_sum<T, U>>;

    template <typename T, typename U>
    struct inner_dot : inner_operator<T, U, 0>
    {
    };

    template <typename T, typename U>
    using inner_dot_t = typeof_t<inner_dot<T, U>>;

    template <auto n, typename T>
    struct inner_mul
    {
        template <auto i, typename U>
        using impl = c_<get_v<i, U> * n>;

        using type = expand_t<impl, T, index_sequence_of_t<T>>;
    };

    template <auto n, typename T>
    using inner_mul_t = typeof_t<inner_mul<n, T>>;

    template <auto lower, auto upper, auto M, typename T>
    struct inner_mul_range : inner_mul<M, range_t<lower, upper, T>>
    {
    };

    template <auto lower, auto upper, auto M, typename T>
    using inner_mul_range_t = typeof_t<inner_mul_range<lower, upper, M, T>>;

    template <typename... F>
    struct overload_set : F...
    {
        using F::operator()...;
    };

    template <typename... F>
    overload_set(F&&...) -> overload_set<std::remove_cvref_t<F>...>;

    template <typename... Args>
    struct overload_sequence;

    template <typename... Args>
    struct overload_sequence_selector;

    template <typename... T, typename... Args>
    struct overload_sequence_selector<overload_sequence<T...>, Args...>
    {
        using call = tuple_t<bool_<std::is_invocable_v<T, Args...>>...>;
        static constexpr auto value = type_index_v<std::true_type, call>;

        using type = element_t<value, tuple_t<T...>>;
    };

    template <typename... Args>
    using overload_sequence_selector_t = typeof_t<overload_sequence_selector<Args...>>;

    template <typename... T>
    struct overload_sequence
    {
        template <typename... Args>
        using selector = overload_sequence_selector<overload_sequence<T...>, Args...>;

        template <typename... Args>
        using selector_t = typeof_t<selector<Args...>>;

        template <typename... Args>
        static constexpr auto selector_v = typev<selector<Args...>>;

        template <typename... F>
        requires std::is_constructible_v<tuple_t<T...>, F...>
        constexpr overload_sequence(F&&... f) : sequence(std::forward<F>(f)...)
        {
        }

        template <typename... Args>
        constexpr std::invoke_result_t<selector_t<Args...>, Args...> operator()(Args&&... args)
        {
            return std::invoke(std::get<selector_v<Args...>>(sequence), std::forward<Args>(args)...);
        }

        private:
            tuple_t<T...> sequence;
    };

    template <typename... Args>
    overload_sequence(Args&&...) -> overload_sequence<Args...>;

    template <auto... N, typename F>
    constexpr void for_value(F&& f)
    {
        (f.template operator()<N>(), ...);
    }

    template <typename... Args, typename F>
    constexpr void for_type(F&& f)
    {
        [&]<auto... N>(const std::index_sequence<N...>&)
        {
            (f.template operator()<N, Args>(), ...);
        }
        (std::index_sequence_for<Args...>());
    }

    template <auto B, auto E, typename F>
    constexpr void for_range(F&& f)
    {
        using type = std::common_type_t<decltype(B), decltype(E)>;
        [&]<auto... N>(const std::integer_sequence<type, N...>&)
        {
            for_value<(B + N)...>(f);
        }
        (std::make_integer_sequence<type, E - B>());
    }

    template <typename... Args, typename F>
    requires is_variadic_pack_v<Args...>
    constexpr void for_pack(F&& f)
    {
        [&]<auto... N>(const std::index_sequence<N...>&)
        {
            if constexpr ((is_variadic_type_v<Args> && ...))
                ([&]<auto n, template <typename ...> typename T, typename... args>(const T<args...>&)
                {
                    for_type<args...>(f);
                }.template operator()<N>(Args()), ...);
            else
                ([&]<auto n, template <typename, auto ...> typename T, typename U, auto... args>(const T<U, args...>&)
                {
                    for_value<args...>(f);
                }.template operator()<N>(Args()), ...);
        }
        (std::index_sequence_for<Args...>());
    }

    struct universal
    {
        template <typename T>
        operator T(){}
    };

    template <typename T>
    consteval auto aggregate_arity(auto... Args)
    {
        if constexpr (! requires { T{ Args... }; })
            return sizeof...(Args) - 1;
        else
            return aggregate_arity<T>(Args..., universal{});
    }

    template <typename T>
    constexpr auto aggregate_arity_v = aggregate_arity<T>();

    template <auto N, typename F, typename... Args>
    void loop(F&& f, Args&&... args)
    {
        if constexpr(N > 1)
           loop<N - 1>(std::forward<F>(f), std::forward<Args>(args)...);
        std::forward<F>(f)(N - 1, std::forward<Args>(args)...);
    }

    template <auto N>
    struct unroller
    {
        template <typename F, typename... Args>
        decltype(auto) operator()(F&& f, Args&&... args)
        {
            if constexpr(N > 1)
               unroller<N - 1>()(std::forward<F>(f), std::forward<Args>(args)...);
            return std::forward<F>(f)(std::forward<Args>(args)...);
        }
    };

    template <size_t N, bool = (N < 2)>
    struct fib
    {
        static constexpr auto value = typev<fib<N - 1>> + typev<fib<N - 2>>;
    };

    template <size_t N>
    struct fib<N, true>
    {
        static constexpr auto value = N;
    };

    template <size_t N>
    struct fibonacci : fib<N, (N < 2)>
    {
    };

    template <int N, int base = 10>
    struct tokenize
    {
        template <int i, typename T, bool = i < base>
        struct impl : impl<i / base, prepend_c<T, i % base>>
        {
        };

        template <int i, typename T>
        struct impl<i, T, true> : std::type_identity<prepend_c<T, i>>
        {
        };

        using type = typeof_t<impl<N, std::integer_sequence<int>>>;
    };

    template <int N, int base = 10>
    using tokenize_t = typeof_t<tokenize<N, base>>;

    template <int N>
    struct digit
    {
        template <int i, bool = i < 10>
        struct impl
        {
            static constexpr auto value = 1 + typev<impl<i / 10>>;
        };

        template <int i>
        struct impl<i, true>
        {
            static constexpr auto value = 1;
        };

        static constexpr auto value = typev<impl<N>>;
    };

    template <int N>
    inline constexpr auto digit_v = typev<digit<N>>;

    template <int p, int q>
    struct power
    {
        template <int i, bool = i == 0>
        struct impl
        {
            static constexpr auto value = p * typev<impl<i - 1>>;
        };

        template <int i>
        struct impl<i, true>
        {
            static constexpr auto value = 1;
        };

        static constexpr auto value = typev<impl<q>>;
    };

    template <int p, int q>
    inline constexpr auto power_v = typev<power<p, q>>;

    template <auto N, int n>
    struct hb
    {
        static constexpr auto m = (N >> (n / 2));
        static constexpr int value = (m ? n / 2 : 0) + typev<hb<(m ? m : N), (m ? n - n / 2 : n / 2)>>;
    };

    template <auto N>
    struct hb<N, 1>
    {
        static constexpr int value = N ? 0 : -1;
    };

    template <auto N>
    struct highest_bit : hb<N, 8 * sizeof_t_v<size_t>>
    {
    };

    template <typename F, typename T>
    struct infinite_list
    {
        using type = T;
        using next = call_t<F, type>;
    };

    template <template <typename ...> typename F, typename T>
    struct infinite
    {
        struct impl
        {
            template <typename... Args>
            using apply = std::type_identity<infinite_list<impl, typeof_t<F<Args...>>>>;
        };

        using type = infinite_list<impl, T>;
    };

    template <template <typename ...> typename F, typename T>
    using infinite_t = typeof_t<infinite<F, T>>;

    template <size_t N, typename T>
    struct nth_infinite : nth_infinite<N - 1, typename T::next>
    {
    };

    template <typename T>
    struct nth_infinite<0, T>
    {
        using type = typeof_t<T>;
    };

    template <size_t N, typename T>
    using nth_infinite_t = typeof_t<nth_infinite<N, T>>;

    template <size_t N, typename T, template <typename ...> typename F>
    struct infinite_call : nth_infinite<N, infinite_t<F, T>>
    {
    };

    template <size_t N, typename T, template <typename ...> typename F>
    using infinite_call_t = typeof_t<infinite_call<N, T, F>>;

    template <size_t N, typename T, typename F>
    struct repeat : call<F, typeof_t<repeat<N - 1, T, F>>>
    {
    };

    template <typename T, typename F>
    struct repeat<0, T, F> : std::type_identity<T>
    {
    };

    template <size_t N, typename T, typename F>
    using repeat_t = typeof_t<repeat<N, T, F>>;

    struct pointer_type_of
    {
        template <typename T>
        using apply = std::add_pointer<T>;
    };

    template <typename T>
    using pointer_type_of_t = call_t<bind_front<std::add_pointer>, T>;

    template <size_t N, typename T>
    struct multi_level_pointer : repeat<N, T, pointer_type_of>
    {
    };

    template <size_t N, typename T>
    using multi_level_pointer_t = typeof_t<multi_level_pointer<N, T>>;

    template <bool... B>
    struct fast_and : std::is_same<fast_and<true, B...>, fast_and<B..., true>>
    {
    };

    template <bool... B>
    inline constexpr auto fast_and_v = typev<fast_and<B...>>;

    template <typename indices>
    struct sequence_and;

    template <template <typename, auto ...> typename T, typename U, auto... values>
    struct sequence_and<T<U, values...>> : fast_and<values...>
    {
    };

    template <typename indices>
    inline constexpr auto sequence_and_v = typev<sequence_and<indices>>;

    template <auto value, auto... values>
    inline constexpr auto value_v = value;

    template <typename ...>
    struct wrong : std::false_type
    {
    };

    template <typename T>
    inline constexpr T* nullptr_v = nullptr;

    template <typename T, typename... Args>
    using type_t = T;

    template <typename... Args>
    using void_t = type_t<void, Args...>;

    template <typename F, auto... N>
    void iterate(F&& f, std::integer_sequence<std::common_type_t<decltype(N)...>, N...>)
    {
        if constexpr((std::is_invocable_v<F&&, c_<N>>&& ...))
            (f(c_<N>()), ...);
        else
            (((void)N, f()), ...);
    }

    template <auto N, typename F>
    void iterate(F&& f)
    {
        iterate(f, std::make_integer_sequence<decltype(N), N>());
    }

    template <typename ...>
    inline constexpr bool true_v = true;

    template <typename ...>
    inline constexpr bool false_v = false;

    template <auto... values>
    using bool_sequence = std::integer_sequence<bool, values...>;

    template <typename T, auto value, typename>
    struct to_int;

    template <typename T, auto value>
    struct to_int<T, value, bool_sequence<>> : c_<value, T>
    {
    };

    template <typename T, auto value, auto b, auto... bs>
    struct to_int<T, value, bool_sequence<b, bs...>> : c_<typev<to_int<T, static_cast<T>((value << 1) | b), bool_sequence<bs...>>>, T>
    {
    };

    template <typename T, auto value, typename U>
    inline constexpr auto to_int_v = typev<to_int<T, value, U>>;

    template <size_t N, typename T>
    struct clamp;

    template <typename T, auto... values>
    struct clamp<0, std::integer_sequence<T, values...>>
    {
        using type = std::integer_sequence<T>;
    };

    template <size_t N, typename T, auto... values>
    struct clamp<N, std::integer_sequence<T, values...>>
    {
        using indices = std::integer_sequence<T, values...>;
        using type = prepend_t<typeof_t<clamp<N - 1, pop_front_t<indices>>>, get<0, indices>>;
    };

    template <size_t N, typename T>
    using clamp_t = typeof_t<clamp<N, T>>;

    template <typename state, typename taps>
    struct advance;

    template <typename state>
    struct advance<state, std::index_sequence<>> : bool_<false>
    {
    };

    template <typename state, auto tap, auto... taps>
    struct advance<state, std::index_sequence<tap, taps...>> :
    bool_<get_v<tap, state> ^ typev<advance<state, std::index_sequence<taps...>>>>
    {
    };

    template <typename state, typename taps>
    inline constexpr auto advance_v = typev<advance<state, taps>>;

    template <typename state, typename taps>
    struct lfsr
    {
        template <typename T>
        using apply = to_int<T, 0, state>;

        using next = lfsr<clamp_t<state::size(), prepend_t<state, advance<state, taps>>>, taps>;
    };

    template <size_t N, typename>
    struct nth_lfsr;

    template <typename state, typename taps>
    struct nth_lfsr<0, lfsr<state, taps>>
    {
        using type = std::integer_sequence<unsigned>;
    };

    template <size_t N, typename state, typename taps>
    struct nth_lfsr<N, lfsr<state, taps>>
    {
        using call = lfsr<state, taps>;
        using type = prepend_t<typeof_t<nth_lfsr<N - 1, typename call::next>>, c_<invoke_v<call, unsigned>>>;
    };

    template <size_t N, typename T>
    using nth_lfsr_t = typeof_t<nth_lfsr<N, T>>;

    template <size_t N, typename T>
    struct lfsr_prng
    {
        static constexpr auto value = get_v<N - 1, nth_lfsr_t<N, T>>;
    };

    template <size_t N, typename T>
    inline constexpr auto lfsr_prng_v = typev<lfsr_prng<N, T>>;

    template <int p, int r, typename T, typename U>
    struct rand
    {
        static constexpr auto value = lfsr_prng_v<sizeof_t_v<T>, U> % (r - p) + p;
    };

    template <int p, int r, typename T, typename U = lfsr<bool_sequence<true, false, true, true, false>, std::index_sequence<2, 4>>>
    inline constexpr auto rand_v = typev<rand<p, r, T, U>>;

    template <int p, int r, typename T>
    struct prng
    {
        using type = swap_t<rand_v<p, r, T>, r - 1, T>;
    };

    template <int p, int r, typename T>
    using prng_t = typeof_t<prng<p, r, T>>;

    template <auto n, typename T>
    struct fill
    {
        template <auto N, typename U>
        struct impl : U
        {
        };

        template <template <auto, typename> typename F>
        using call = expand<F, T, index_sequence_of_c<n>>;

        using type = type_if<!has_type_v<T> || !has_value_type_v<T>, call<identity>, call<impl>>;
    };

    template <auto n, typename T>
    using fill_t = typeof_t<fill<n, T>>;

    template <auto n, auto v>
    using fill_c = typeof_t<fill<n, c_<v>>>;

    template <size_t N>
    struct repeat_range
    {
        using base = std::index_sequence<>;

        template <size_t i, size_t j, typename T>
        struct impl : impl<i + 1, j, concat_t<T, rename_t<fill_c<i + 1, i + 1>, base>>>
        {
        };

        template <size_t j, typename T>
        struct impl<j, j, T> : std::type_identity<T>
        {
        };

        using type = typeof_t<impl<0, N, base>>;
    };

    template <size_t N>
    using repeat_range_t = typeof_t<repeat_range<N>>;

    template <auto n, auto v>
    using index_sequence_c = rename_t<fill_c<n, v>, std::index_sequence<>>;

    template <bool B, auto n, typename T>
    struct fill_if : std::conditional<B, fill_t<n, T>, T>
    {
    };

    template <bool B, auto n, typename T>
    using fill_if_t = typeof_t<fill_if<B, n, T>>;

    template <auto i, auto j, auto k, typename T>
    struct rotate
    {
        template <typename indices, auto V = 0>
        using impl = expand_t<element, T, indices, V>;

        template <size_t p, size_t q>
        using extend = impl<index_sequence_of_c<q - p>, p>;

        using type = concat_t<range_t<0, i, T>, extend<j, k>, extend<i, j>, range_t<k, sizeof_t_v<T>, T>>;
    };

    template <auto i, auto j, auto k, typename T>
    using rotate_t = typeof_t<rotate<i, j, k, T>>;

    template <auto N, typename T>
    struct shift_left : rotate<0, N, sizeof_t_v<T>, T>
    {
    };

    template <auto N, typename T>
    using shift_left_t = typeof_t<shift_left<N, T>>;

    template <auto N, typename T>
    struct shift_right : rotate<0, sizeof_t_v<T> - N, sizeof_t_v<T>, T>
    {
    };

    template <auto N, typename T>
    using shift_right_t = typeof_t<shift_right<N, T>>;

    template <typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct shuffle
    {
        template <int i, typename U>
        struct impl : impl<i - 1, swap_t<i, rand_v<B, i + 1, U>, U>>
        {
        };

        template <typename U>
        struct impl<0, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<E - B - 1, T>>;
    };

    template <typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using shuffle_t = typeof_t<shuffle<T, B, E>>;

    template <typename T, auto N, auto B = T(), auto D = 0>
    struct value_sequence
    {
        template <auto i, typename U>
        using impl = c_<B + D * i, U>;

        using type = expand_t<impl, T, index_sequence_of_c<N>>;
    };

    template <typename T, auto N, auto B = T(), auto D = 0>
    using value_sequence_t = typeof_t<value_sequence<T, N, B, D>>;

    template <typename T, auto N>
    using zero_sequence_t = value_sequence_t<T, N>;

    template <typename T, auto N, auto B, auto D>
    using integer_sequence_t = value_sequence_t<T, N, B, D>;

    template <typename T, auto B, auto N>
    struct parity : expand_of<T, integer_sequence_t<size_t, (sizeof_t_v<T> + N) / 2, B, 2>>
    {
    };

    template <typename T, auto B, auto N>
    using parity_t = typeof_t<parity<T, B, N>>;

    template <typename T>
    using odd = parity<T, 1, 0>;

    template <typename T>
    using odd_t = typeof_t<odd<T>>;

    template <typename T>
    using even = parity<T, 0, 1>;

    template <typename T>
    using even_t = typeof_t<even<T>>;

    template <typename T>
    struct is_odd : bool_<typev<T> % 2 == 1>
    {
    };

    template <typename T>
    inline constexpr auto is_odd_v = typev<is_odd<T>>;

    template <typename T>
    struct is_even : bool_<typev<T> % 2 == 0>
    {
    };

    template <typename T>
    inline constexpr auto is_even_v = typev<is_even<T>>;

    template <typename T>
    consteval auto index_value(T&& t)
    {
        return std::remove_cvref_t<decltype(t)>::value;
    }

    template <typename F, typename... Args>
    decltype(auto) tuple_apply(const std::tuple<Args...>& t, F&& f)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::invoke(std::forward<F>(f), std::get<N>(t)...);
        }
        (std::index_sequence_for<Args...>());
    }

    template <typename F, typename... Args, typename... args>
    void tuple_transform(F&& f, const std::tuple<Args...>& t, args&&... rest)
    {
        [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            (std::forward<F>(f)(std::get<N>(t), index_t<N>(), std::forward<args>(rest)...), ...);
        }
        (std::index_sequence_for<Args...>());
    }

    template <typename... Args>
    auto tuple_reverse(const std::tuple<Args...>& t)
    {
        constexpr auto size = sizeof_v<Args...>;
        auto reversed = reverse_t<std::tuple<Args...>>();

        tuple_transform([&](auto&& e, auto&& index, auto& tuple)
        {
            std::get<size - std::remove_cvref_t<decltype(index)>::value - 1>(tuple) = e;
        }, t, reversed);

        return reversed;
    };

    template <typename... Args, typename... T>
    std::tuple<std::remove_cvref_t<T>..., std::remove_cvref_t<Args>...> tuple_prepend(const std::tuple<Args...>& tuple, T&&... t)
    {
        return std::tuple_cat(std::make_tuple(std::forward<T>(t)...), tuple);
    }

    template <typename... Args, typename... T>
    std::tuple<std::remove_cvref_t<Args>..., std::remove_cvref_t<T>...> tuple_append(const std::tuple<Args...>& tuple, T&&... t)
    {
        return std::tuple_cat(tuple, std::make_tuple(std::forward<T>(t)...));
    }

    template <auto i, typename... Args>
    auto tuple_remove(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (drop_t<i, std::index_sequence_for<Args...>>());
    }

    template <auto i, auto j, typename... Args>
    auto tuple_swap(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<swap_index<i, j, N>()>(t)...);
        }
        (std::index_sequence_for<Args...>());
    }

    template <auto i, auto j, typename... Args>
    auto tuple_range(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (integer_sequence_t<size_t, j - i, i, 1>());
    }

    template <auto pos, auto len, typename... Args>
    auto tuple_subset(const std::tuple<Args...>& t)
    {
        return tuple_range<pos, pos + len>(t);
    }

    template <auto i, auto j, typename... Args>
    auto tuple_erase(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (erase_t<i, j, std::index_sequence_for<Args...>>());
    }

    template <auto i, auto j, typename... Args>
    auto tuple_reverse_range(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (reverse_range_t<i, j, std::index_sequence_for<Args...>>());
    }

    template <auto i, typename... Args, typename... T>
    auto tuple_insert(const std::tuple<Args...>& tuple, T&&... t)
    {
        return std::tuple_cat(tuple_range<0, i>(tuple),
               std::make_tuple(std::forward<T>(t)...), tuple_range<i, sizeof_v<Args...>>(tuple));
    }

    template <auto i, typename... Args, typename... T>
    auto tuple_replace(const std::tuple<Args...>& tuple, T&&... t)
    {
        return std::tuple_cat(tuple_range<0, i>(tuple),
               std::make_tuple(std::forward<T>(t)...), tuple_range<i + 1, sizeof_v<Args...>>(tuple));
    }

    template <typename... Args, typename T, typename U>
    auto tuple_replace(const std::tuple<Args...>& tuple, T&& t, U&& u)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple([&v = std::get<N>(tuple)]
            (auto&& src, auto&& dst)
            {
                return v == src ? dst : src;
            }
            (std::forward<T>(t), std::forward<U>(u))...);
        }
        (std::index_sequence_for<Args...>());
    }

    template <auto i, auto j, auto k, typename... Args>
    auto tuple_rotate(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (rotate_t<i, j, k, std::index_sequence_for<Args...>>());
    }

    template <auto i, typename... Args>
    auto tuple_shift_left(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (shift_left_t<i, std::index_sequence_for<Args...>>());
    }

    template <auto i, typename... Args>
    auto tuple_shift_right(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (shift_right_t<i, std::index_sequence_for<Args...>>());
    }

    template <auto n, typename... Args>
    auto tuple_take_front(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (index_sequence_of_c<n>());
    }

    template <auto n, typename... Args>
    auto tuple_take_back(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (integer_sequence_t<size_t, n, sizeof_v<Args...> - n, 1>());
    }

    template <auto n, typename... Args>
    auto tuple_drop_front(const std::tuple<Args...>& t)
    {
        return tuple_take_back<sizeof_v<Args...> - n>(t);
    }

    template <auto n, typename... Args>
    auto tuple_drop_back(const std::tuple<Args...>& t)
    {
        return tuple_take_front<sizeof_v<Args...> - n>(t);
    }

    template <size_t N, typename T>
    void tuple_fill(T& t)
    {
    };

    template <size_t N, typename T, typename U, typename... Args>
    void tuple_fill(T& t, U&& u, Args&&... args)
    {
        if constexpr(N < sizeof_t_v<T>)
        {
            std::get<N>(t) = u;
            tuple_fill<N + 1>(t, std::forward<Args>(args)...);
        }
    }

    template <auto i, auto n, typename... Args>
    auto tuple_splat(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<typev<identity_t<N, index_t<i>>>>(t)...);
        }
        (index_sequence_of_c<n>());
    }

    template <typename... Args>
    auto tuple_unique(const std::tuple<Args...>& t)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(std::get<N>(t)...);
        }
        (unique_index_t<std::tuple<Args...>>());
    }

    template <auto n, typename T, auto m>
    auto array_take_front(const std::array<T, m>& a)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::array<T, n>{std::get<N>(a)...};
        }
        (index_sequence_of_c<n>());
    }

    template <auto n, typename T, auto m>
    auto array_take_back(const std::array<T, m>& a)
    {
        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::array<T, n>{std::get<N>(a)...};
        }
        (integer_sequence_t<size_t, n, m - n, 1>());
    }

    template <auto n, typename T, auto m>
    auto array_drop_front(const std::array<T, m>& a)
    {
        return array_take_back<m - n>(a);
    }

    template <auto n, typename T, auto m>
    auto array_drop_back(const std::array<T, m>& a)
    {
        return array_take_front<m - n>(a);
    }

    template <typename F, typename T>
    requires is_tuple_v<T>
    struct invocable
    {
        template <auto N, typename U>
        struct impl;

        template <auto N, template <typename ...> typename U, typename... Args>
        struct impl<N, U<Args...>>
        {
            using type = type_if<std::is_invocable_v<F, Args...>, c_<N>, invocable<F, pop_back_t<T>>>;
        };

        using type = typeof_t<impl<sizeof_t_v<T>, T>>;
    };

    template <typename F, typename T>
    using invocable_t = typeof_t<invocable<F, T>>;

    template <typename F, typename T>
    inline constexpr auto invocable_v = typev<invocable_t<F, T>>;

    template <typename T, typename U = size_t>
    struct alter;

    template <template <typename, auto ...> typename T, typename V, auto... v, typename U>
    struct alter<T<V, v...>, U> : std::type_identity<T<U, v...>>
    {
    };

    template <typename T, typename U = size_t>
    using alter_t = typeof_t<alter<T, U>>;

    template <auto i, auto n, typename T>
    struct splat : expand_of<T, alter_t<fill_c<n, i>, size_t>>
    {
    };

    template <auto i, auto n, typename T>
    using splat_t = typeof_t<splat<i, n, T>>;

    template <bool B, typename T, typename U = size_t>
    using alter_if = std::conditional_t<B, alter<T, U>, std::type_identity<T>>;

    template <bool B, typename T, typename U = size_t>
    using alter_if_t = typeof_t<alter_if<B, T, U>>;

    template <typename limit, typename T, template <typename ...> typename F, bool ASC = true>
    requires is_sequence_v<limit>
    struct loop_indices
    {
        static constexpr auto depth = sizeof_t_v<limit>;

        template <int i, typename U, typename V, bool = (i >= 0)>
        struct impl
        {
            static constexpr auto curr = get_v<i, U> + 1;
            static constexpr int last = get_v<i, limit>;

            static constexpr auto cond = (ASC && curr >= last || !ASC && curr <= 1);
            static constexpr auto value = i + 1 >= depth;

            static constexpr auto j = cond ? i - 1 : i + !value;
            static constexpr auto end = !cond && value;

            using indices = sub_t<i, cond ? (ASC ? -1 : last) : curr - 2 * !ASC, U>;
            using type = typeof_t<impl<j, indices, type_if<end, F<V, alter_if_t<end, indices>>, std::type_identity<V>>>>;
        };

        template <int i, typename U, typename V>
        struct impl<i, U, V, false> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<0, std::conditional_t<ASC, fill_c<depth, -1>, limit>, T>>;
    };

    template <typename limit, typename T, template <typename ...> typename F, bool ASC = true>
    using loop_indices_t = typeof_t<loop_indices<limit, T, F, ASC>>;

    template <typename limit, typename T, template <typename ...> typename F, bool ASC = true>
    struct unique_indices
    {
        template <typename U, typename indices>
        struct impl
        {
            static constexpr auto value = is_unique_v<indices>;
            using type = type_if<value, F<U, indices>, std::type_identity<U>>;
        };

        using type = loop_indices_t<limit, T, impl, ASC>;
    };

    template <typename limit, typename T, template <typename ...> typename F, bool ASC = true>
    using unique_indices_t = typeof_t<unique_indices<limit, T, F, ASC>>;

    template <typename T, auto N = sizeof_t_v<T>>
    struct loop_permutation
    {
        static constexpr auto depth = sizeof_t_v<T>;

        template <typename U, typename indices>
        struct impl : append<U, range_t<0, N, expand_t<element, T, indices>>>
        {
        };

        using type = unique_indices_t<fill_c<depth, depth>, tuple_t<>, impl, true>;
    };

    template <typename T, auto N = sizeof_t_v<T>>
    using loop_permutation_t = typeof_t<loop_permutation<T, N>>;

    template <typename T, T depth, bool ASC = true>
    requires std::is_integral_v<T> && std::is_signed_v<T>
    struct loop_indices_generator
    {
        using indices_t = std::array<T, depth>;

        template <typename F>
        void operator()(F&& f)
        {
            indices_t asc;
            std::fill(asc.begin(), asc.end(), -1);

            indices_t curr(limit);
            if (ASC)
                curr.swap(asc);

            constexpr auto N = invocable_v<F, fill_t<depth, T>>;

            int i = 0;
            while (i >= 0)
            {
                auto upper = limit[i];
                if ((ASC && curr[i] + 1 >= upper) || (!ASC && curr[i] <= 0))
                {
                    curr[i] = ASC ? -1 : upper;
                    --i;
                    continue;
                }
                curr[i] += 1 - 2 * !ASC;
                if (i + 1 >= depth)
                    std::apply(std::forward<F>(f), array_take_front<N>(curr));
                else
                    ++i;
            }
        }

        indices_t limit;
    };

    template <bool ASC, typename... Args>
    auto loop_for(Args... indices)
    {
        return loop_indices_generator<std::common_type_t<Args...>, sizeof_v<Args...>, ASC>{indices...};
    }

    template <typename T, typename... Args>
    decltype(auto) call_apply(Args&&... args)
    {
        return T::template apply(std::forward<Args>(args)...);
    }

    template <size_t i, size_t j, typename indices>
    struct next_cartesian_product;

    template <size_t i, size_t j, auto... N>
    struct next_cartesian_product<i, j, std::index_sequence<N...>>
    {
        template <typename T, typename U>
        static auto apply(T&& t, U&& u)
        {
            using next = next_cartesian_product<i + 1, j, std::index_sequence<N...>>;

            return std::tuple_cat(std::make_tuple(std::make_pair(std::get<i>(t), std::get<N>(u)))...,
                   call_apply<next>(std::forward<T>(t), std::forward<U>(u)));
        }
    };

    template <size_t j, auto... N>
    struct next_cartesian_product<j, j, std::index_sequence<N...>>
    {
        template <typename T, typename U>
        static auto apply(T&& t, U&& u)
        {
            return std::tuple<>();
        }
    };

    template <typename T, typename U>
    auto tuple_cartesian_product(T&& t, U&& u)
    {
        using indices = index_sequence_of_t<std::remove_cvref_t<U>>;
        using next = next_cartesian_product<0, sizeof_t_v<std::remove_cvref_t<T>>, indices>;

        return call_apply<next>(std::forward<T>(t), std::forward<U>(u));
    }

    template <typename T, template <typename, bool> typename comp, bool b, typename... Args>
    using extreme = std::conditional_t<!sizeof_v<Args...>, std::type_identity<T>, comp<tuple_t<T, Args...>, b>>;

    template <typename T, typename U, bool B>
    using evaluate = std::conditional_t<B && less_v<T, U> || !B && less_v<U, T>, T, U>;

    template <auto p, auto q, bool B>
    using minmax_t = c_<B ? min_v<p, q> : max_v<p, q>>;

    template <typename T, bool B>
    struct minmax;

    template <template <typename ...> typename T, typename U, bool B>
    struct minmax<T<U>, B> : std::type_identity<U>
    {
    };

    template <template <typename ...> typename T, bool B, typename U, typename V, typename... Args>
    struct minmax<T<U, V, Args...>, B> : extreme<evaluate<U, V, B>, minmax, B, Args...>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... values, bool B>
    struct minmax<T<U, values...>, B>
    {
        template <typename V, typename W>
        struct comp : minmax_t<typev<V>, typev<W>, B>
        {
        };

        using type = eval_t<folded_t, comp, to_tuple_t<T<U, values...>>, get<0, T<U, values...>>>;
    };

    template <typename T>
    using min_element = minmax<T, true>;

    template <typename T>
    using min_element_t = typeof_t<min_element<T>>;

    template <typename T>
    inline constexpr auto min_element_v = typev<min_element_t<T>>;

    template <typename... Args>
    decltype(auto) tuple_zip(Args&&... args)
    {
        auto row = [&]<size_t n>(){ return std::make_tuple(std::get<n>(args)...); };
        using indices = std::index_sequence<std::tuple_size_v<std::remove_cvref_t<Args>>...>;

        return [&]<size_t... N>(const std::index_sequence<N...>&)
        {
            return std::make_tuple(row.template operator()<N>()...);
        }(index_sequence_of_c<min_element_v<indices>>());
    }

    template <typename... Args>
    decltype(auto) tuple_transpose(const std::tuple<Args...>& t)
    {
        return tuple_apply(t, [](auto&&... args) { return tuple_zip(args...); });
    }

    template <typename T>
    using max_element = minmax<T, false>;

    template <typename T>
    using max_element_t = typeof_t<max_element<T>>;

    template <typename T>
    inline constexpr auto max_element_v = typev<max_element_t<T>>;

    template <typename T>
    struct minmax_element : pair_t<min_element_t<T>, max_element_t<T>>
    {
    };

    template <template <typename ...> typename F, typename T>
    struct split
    {
        template <int i, int j, typename U>
        struct impl
        {
            static constexpr auto k = find_if_v<F, T, i, j>;

            using next = append_if_t<i != k, U, range_if_t<i != k, i, k, T>>;
            using type = typeof_t<impl<k != j ? k + 1 : j, j, next>>;
        };

        template <int j, typename U>
        struct impl<j, j, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<0, sizeof_t_v<T>, tuple_t<>>>;
    };

    template <template <typename ...> typename F, typename T>
    using split_t = typeof_t<split<F, T>>;

    template <int low, int mid, int high, typename T>
    struct find_max_crossing_subarray
    {
        template <int sum, int max, int index, int i, int j, int k>
        struct impl
        {
            static constexpr auto value = sum + element_size_v<i, T>;
            static constexpr auto B = value > max;

            using type = typeof_t<impl<value, B ? value : max, B ? i : index, i + k, j, k>>;
        };

        template <int sum, int max, int index, int j, int k>
        struct impl<sum, max, index, j, j, k>
        {
            using type = pair_v<index, max>;
        };

        static constexpr auto min = min_element_v<T>;
        using left = typeof_t<impl<0, min, 0, mid, low - 1, -1>>;

        using right = typeof_t<impl<0, min, 0, mid + 1, high + 1, 1>>;
        using type = std::integer_sequence<int, first_v<left>, first_v<right>, second_v<left> + second_v<right>>;
    };

    template <int low, int mid, int high, typename T>
    using find_max_crossing_subarray_t = typeof_t<find_max_crossing_subarray<low, mid, high, T>>;

    template <typename T>
    struct find_maximum_subarray
    {
        template <int low, int high>
        struct search
        {
            static constexpr auto mid = (low + high) / 2;
            using left = typeof_t<search<low, mid>>;

            using right = typeof_t<search<mid + 1, high>>;
            using cross = find_max_crossing_subarray_t<low, mid, high, T>;

            static constexpr auto left_low = get_v<0, left>;
            static constexpr auto left_high = get_v<1, left>;

            static constexpr auto left_sum = get_v<2, left>;
            static constexpr auto right_low = get_v<0, right>;

            static constexpr auto right_high = get_v<1, right>;
            static constexpr auto right_sum = get_v<2, right>;

            static constexpr auto cross_low = get_v<0, cross>;
            static constexpr auto cross_high = get_v<1, cross>;

            static constexpr auto cross_sum = get_v<2, cross>;
            static constexpr auto B1 = left_sum >= right_sum && left_sum >= cross_sum;

            static constexpr auto B2 = right_sum >= left_sum && right_sum >= cross_sum;
            using left_t = std::integer_sequence<int, left_low, left_high, left_sum>;

            using right_t = std::integer_sequence<int, right_low, right_high, right_sum>;
            using cross_t = std::integer_sequence<int, cross_low, cross_high, cross_sum>;

            using type = ternary_conditional_t<!B1, B2, right_t, cross_t, left_t>;
        };

        template <int low>
        struct search<low, low>
        {
            using type = std::integer_sequence<int, low, low, element_size_v<low, T>>;
        };

        using type = typeof_t<search<0, sizeof_t_v<T> - 1>>;
    };

    template <typename T>
    using find_maximum_subarray_t = typeof_t<find_maximum_subarray<T>>;

    template <typename T>
    struct kadane
    {
        template <typename U, typename V>
        using max_sum = max_t<plus_t<U, V>, V>;

        using type = max_element_t<inclusive_scan_t<max_sum, T>>;
    };

    template <typename T>
    using kadane_t = typeof_t<kadane<T>>;

    template <typename T>
    inline constexpr auto kadane_v = typev<kadane_t<T>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    struct count
    {
        template <typename V, typename W, typename X = typeof_t<V>>
        struct comp : index_upper<plus_v<V, std::is_same<X, W>>, X>
        {
        };

        using type = eval_t<folded_t, comp, to_tuple_t<range_t<B, E, U>>, index_type<0, T>>;
    };

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    using count_t = typeof_t<count<T, U, B, E>>;

    template <typename T, typename U, int B = 0, int E = sizeof_t_v<U>>
    inline constexpr auto count_v = typev<count_t<T, U, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    struct count_if
    {
        template <typename V, typename W>
        struct comp : plus_t<V, F<W>>
        {
        };

        using type = eval_t<folded_t, comp, to_tuple_t<range_t<B, E, T>>, c_0>;
    };

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using count_if_t = typeof_t<count_if<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto count_if_v = typev<count_if_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    struct count_if_not : count_if<negaf<F>::template apply, T, B, E>
    {
    };

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using count_if_not_t = typeof_t<count_if_not<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto count_if_not_v = typev<count_if_not_t<F, T, B, E>>;

    template <typename T>
    struct mode
    {
        template <typename U, typename V>
        struct comp : std::conditional<typev<U> < typev<V>, V, U>
        {
        };

        template <typename Args>
        struct impl
        {
            template <typename args>
            using apply = count<args, Args>;
        };

        template <typename U>
        using unique = eval_t<currying_t, impl<U>::template apply, to_tuple_t<unique_t<U>>>;

        using type = typeof_t<eval_t<folded_t, comp, unique<T>>>;
        static constexpr auto value = value_if<is_tuple_v<T>, std::false_type, type>;
    };

    template <typename T>
    using mode_t = typeof_t<mode<T>>;

    template <typename T>
    requires is_variadic_value_v<T>
    inline constexpr auto mode_v = typev<mode<T>>;

    template <template <typename> typename F, template <typename> typename P, typename T, typename U, auto B, auto E, bool W>
    struct transform_of
    {
        template <int i, int j, typename V>
        struct impl
        {
            using curr = element_t<i, U>;
            static constexpr auto value = typev<P<curr>>;

            using call = call_if_t<value, V, bind_front<F>, curr>;
            using next = call_if_t<value, V, bind_front<append_t, V>, call>;

            using type = typeof_t<impl<W || value ? i + 1 : j, j, next>>;
        };

        template <int j, typename V>
        struct impl<j, j, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<B, E, T>>;
    };

    template <template <typename> typename F, template <typename> typename P, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct transform_if : transform_of<F, P, T, U, B, E, true>
    {
    };

    template <template <typename> typename F, template <typename> typename P, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using transform_if_t = typeof_t<transform_if<F, P, T, U, B, E>>;

    template <template <typename> typename F, template <typename> typename P, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    struct transform_while : transform_of<F, P, T, U, B, E, false>
    {
    };

    template <template <typename> typename F, template <typename> typename P, typename T, typename U, auto B = 0, auto E = sizeof_t_v<U>>
    using transform_while_t = typeof_t<transform_while<F, P, T, U, B, E>>;

    template <auto i, auto j, typename T, typename U>
    struct is_same : std::is_same<element_t<i, T>, element_t<j, U>>
    {
    };

    template <auto i, auto j, typename T, typename U>
    inline constexpr auto is_same_v = typev<is_same<i, j, T, U>>;

    template <typename T>
    struct majority_search
    {
        static constexpr auto B = is_tuple_v<T>;

        template <int i, int j, int k, int l>
        struct search
        {
            template <int p, int q>
            struct impl
            {
                static constexpr auto n = 2 * is_same_v<p, q, T, T> - 1;
                using type = typeof_t<search<i + n, j, k + 1, l>>;
            };

            using type = type_if<i == 0, search<1, k, k, l>, impl<k, j>>;
        };

        template <int i, int j, int l>
        struct search<i, j, l, l> : element<j, T>
        {
        };

        using type = typeof_t<search<0, 0, 0, sizeof_t_v<T>>>;
    };

    template <typename T>
    using majority_search_t = typeof_t<majority_search<T>>;

    template <typename T>
    inline constexpr auto majority_search_v = typev<majority_search_t<T>>;

    template <typename... Args>
    struct logical_or : std::false_type
    {
    };

    template <typename T, typename... Args>
    struct logical_or<T, Args...> : conditional_of<T, std::true_type, logical_or<Args...>>
    {
    };

    template <typename... Args>
    inline constexpr auto logical_or_v = typev<logical_or<Args...>>;

    template <typename... Args>
    struct logical_and : std::true_type
    {
    };

    template <typename T, typename... Args>
    struct logical_and<T, Args...> : conditional_of<T, logical_and<Args...>, std::false_type>
    {
    };

    template <typename... Args>
    inline constexpr auto logical_and_v = typev<logical_and<Args...>>;

    template <typename T>
    using and_t = std::conditional_t<is_tuple_v<T>, tuple_and<T>, sequence_and<T>>;

    template <typename T>
    inline constexpr auto and_v = typev<and_t<T>>;

    template <typename T, auto N = sizeof_t_v<T>>
    struct is_palindrome
    {
        template <auto i, typename U>
        using impl = is_same<i, N - i - 1, T, U>;

        static constexpr auto value = and_v<expand_t<impl, T, index_sequence_of_c<N / 2>>>;
    };

    template <typename T>
    inline constexpr auto is_palindrome_v = std::is_same_v<T, reverse_t<T>>;

    template <bool B, template <typename ...> typename F, typename T>
    struct for_each
    {
        template <auto i, typename U>
        struct impl
        {
            static constexpr auto value = typev<F<element_t<i, U>>>;
            using type = bool_<B == value>;
        };

        using type = tuple_and<expand_t<impl, T, index_sequence_of_t<T>>>;
    };

    template <bool B, template <typename ...> typename F, typename T>
    using for_each_t = typeof_t<for_each<B, F, T>>;

    template <template <typename ...> typename F, typename T>
    inline constexpr auto all_of_v = typev<for_each_t<1, F, T>>;

    template <template <typename ...> typename F, typename T>
    inline constexpr auto none_of_v = typev<for_each_t<0, F, T>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct one_of
    {
        static constexpr auto i = find_if_v<F, T, B, E>;
        static constexpr auto j = type_if_v<i != E, find_if<F, T, i + 1, E>, c_<E>>;

        static constexpr auto value = i != E && j == E;
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    inline constexpr auto one_of_v = typev<one_of<F, T, B, E>>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct is_sorted_until
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <size_t i, size_t j>
        struct impl : std::conditional_t<typev<comparator<element_t<i, T>, element_t<i - 1, T>>>, c_<i>, impl<i + 1, j>>
        {
        };

        template <size_t j>
        struct impl<j, j> : c_<j>
        {
        };

        static constexpr auto value = type_if_v<N <= 1, c_<N>, impl<1, N>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    inline constexpr auto is_sorted_until_v = typev<is_sorted_until<T, comparator>>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct is_sorted : std::bool_constant<is_sorted_until_v<T, comparator> == sizeof_t_v<T>>
    {
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    inline constexpr auto is_sorted_v = typev<is_sorted<T, comparator>>;

    template <template <typename ...> typename F, typename T, bool P = false>
    struct is_partitioned
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <bool B, size_t i, size_t j>
        struct impl : std::conditional_t<typev<F<element_t<i, T>>> == B, impl<B, i + 1, j>, c_<i>>
        {
        };

        template <bool B, size_t j>
        struct impl<B, j, j> : c_<j>
        {
        };

        static constexpr auto l = typev<impl<1, 0, N>>;
        static constexpr auto r = typev<impl<0, l, N>>;

        static constexpr auto value = type_if_v<P, c_<l == N ? l : r>, std::bool_constant<l == N || r == N>>;
    };

    template <template <typename ...> typename F, typename T, bool P = false>
    inline constexpr auto is_partitioned_v = typev<is_partitioned<F, T, P>>;

    template <template <typename ...> typename F, typename T>
    struct is_partitioned_until : is_partitioned<F, T, true>
    {
    };

    template <template <typename ...> typename F, typename T>
    inline constexpr auto is_partitioned_until_v = typev<is_partitioned_until<F, T>>;

    template <typename T, typename U, auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    struct is_permutation
    {
        using p = mismatch_t<equal_t, T, U, B1, E1, B2, E2>;
        static constexpr auto q = first_v<p>;

        static constexpr auto l = second_v<p>;
        static constexpr auto r = l + E1 - q;

        template <size_t i, typename V, typename W>
        struct next
        {
            static constexpr size_t m = count_v<V, U, l, r>;
            static constexpr size_t n = type_if_v<m == 0, std::false_type, count<V, T, i, E1>>;

            using type = type_if<m != 0 && n == m, W, std::false_type>;
        };

        template <size_t i, size_t j>
        struct impl
        {
            using curr = element_t<i, T>;
            using type = type_if<find_v<curr, T, q, i> != i, impl<i + 1, j>, next<i, curr, impl<i + 1, j>>>;
        };

        template <size_t j>
        struct impl<j, j> : std::true_type
        {
        };

        static constexpr auto value = type_if_v<q == E1, std::true_type, impl<q, E1>>;
    };

    template <typename T, typename U, auto B1 = 0, auto E1 = sizeof_t_v<T>, auto B2 = 0, auto E2 = sizeof_t_v<U>>
    inline constexpr auto is_permutation_v = typev<is_permutation<T, U, B1, E1, B2, E2>>;

    template <typename T, typename U, auto B1 = 0, auto E1 = sizeof_t_v<T>,
    auto B2 = 0, auto E2 = sizeof_t_v<U>, template <typename ...> typename F = std::is_same>
    struct find_first_of
    {
        template <int i, int j, int k>
        struct inner : std::conditional_t<typev<F<element_t<k, T>, element_t<i, U>>>, index_upper<1, c_<k>>, inner<i + 1, j, k>>
        {
        };

        template <int j, int k>
        struct inner<j, j, k> : index_upper<0, c_<j>>
        {
        };

        template <int i, int j>
        struct outer
        {
            using curr = typeof_t<inner<B2, E2, i>>;
            using type = type_if<typev<curr>, curr, outer<i + 1, j>>;
        };

        template <int j>
        struct outer<j, j> : c_<j>
        {
        };

        static constexpr auto value = typeof_v<outer<B1, E1>>;
    };

    template <typename T, typename U, auto B1 = 0, auto E1 = sizeof_t_v<T>,
    auto B2 = 0, auto E2 = sizeof_t_v<U>, template <typename ...> typename F = std::is_same>
    inline constexpr auto find_first_of_v = typev<find_first_of<T, U, B1, E1, B2, E2, F>>;

    template <typename T, typename U>
    struct is_subset
    {
        static constexpr auto M = sizeof_t_v<T>;
        static constexpr auto N = sizeof_t_v<U>;

        template <size_t i, size_t j>
        struct impl
        {
            static constexpr auto cond = std::is_same_v<T, range_t<i, i + M, U>>;
            using type = type_if<cond, std::true_type, impl<i + 1, j>>;
        };

        template <size_t j>
        struct impl<j, j>
        {
            using type = std::is_same<T, range_t<j, j + M, U>>;
        };

        static constexpr auto value = type_if_v<N < M, std::false_type, impl<0, N - M + 1>>;
    };

    template <typename T, typename U>
    inline constexpr auto is_subset_v = typev<is_subset<T, U>>;

    template <typename... Args>
    struct store
    {
        using first = alias_t<Args...>;

        template <bool b, typename... args>
        struct impl
        {
            using type = tuple_t<args...>;
        };

        template <typename... args>
        struct impl<false, args...>
        {
            using type = std::integer_sequence<value_t<first>, typev<args>...>;
        };

        using type = typeof_t<impl<negav<has_value_type<first>>, Args...>>;
    };

    template <typename... Args>
    using store_t = typeof_t<store<Args...>>;

    template <auto N, typename... Args>
    struct cycle
    {
        template <int i, int j, typename T>
        struct impl : impl<i + 1, j, append_t<T, Args...>>
        {
        };

        template <int j, typename T>
        struct impl<j, j, T> : std::type_identity<T>
        {
        };

        using type = typeof_t<impl<0, N, base_type_t<store_t<alias_t<Args...>>>>>;
    };

    template <auto N, typename... Args>
    using cycle_t = typeof_t<cycle<N, Args...>>;

    template <auto N, auto... values>
    using cycle_c = cycle_t<N, c_<values>...>;

    template <template <typename ...> typename F, typename T, typename U>
    struct filter : std::conditional<typev<F<T>>, U, store_t<T>>
    {
    };

    template <template <typename ...> typename F, typename T, typename U>
    using filter_t = typeof_t<filter<F, T, U>>;

    template <template <typename ...> typename F, typename T>
    struct erase_if;

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    struct erase_if<F, T<Args...>>
    {
        using base = base_type_t<T<Args...>>;
        using type = concat_t<filter_t<F, Args, base>...>;
    };

    template <template <typename ...> typename F, template <typename, auto ...> typename T, typename U, auto... Args>
    struct erase_if<F, T<U, Args...>>
    {
        using base = base_type_t<T<U, Args...>>;
        using type = concat_t<filter_t<F, c_<Args, U>, base>...>;
    };

    template <template <typename ...> typename F, typename T>
    using erase_if_t = typeof_t<erase_if<F, T>>;

    template <template <typename ...> typename F, typename T>
    struct erase_if_not : erase_if<negaf<F>::template apply, T>
    {
    };

    template <template <typename ...> typename F, typename T>
    using erase_if_not_t = typeof_t<erase_if_not<F, T>>;

    template <typename T, typename U>
    struct remove_copy : erase_if<bind_front<std::is_same, T>::template apply, U>
    {
    };

    template <typename T, typename U>
    using remove_copy_t = typeof_t<remove_copy<T, U>>;

    template <auto N, typename T>
    using remove_copy_c = remove_copy_t<c_<N>, T>;

    template <template <typename ...> typename F, typename T>
    struct remove_copy_if : erase_if<negaf<F>::template apply, T>
    {
    };

    template <template <typename ...> typename F, typename T>
    using remove_copy_if_t = typeof_t<remove_copy_if<F, T>>;

    template <typename T, typename U>
    struct cartesian_product
    {
        template <size_t i, size_t j, typename>
        struct impl;

        template <size_t i, size_t j, auto... N>
        struct impl<i, j, std::index_sequence<N...>>
        {
            using conc = concat_t<store_t<element_t<i, T>, element_t<N, U>>...>;
            using type = concat_t<conc, typeof_t<impl<i + 1, j, std::index_sequence<N...>>>>;
        };

        template <size_t j, auto... N>
        struct impl<j, j, std::index_sequence<N...>>
        {
            using type = base_type_t<T>;
        };

        using type = typeof_t<impl<0, sizeof_t_v<T>, index_sequence_of_t<U>>>;
    };

    template <typename T, typename U>
    using cartesian_product_t = typeof_t<cartesian_product<T, U>>;

    template <typename T, typename U>
    struct large_number_multiplier
    {
        static constexpr auto M = sizeof_t_v<T>;
        static constexpr auto N = sizeof_t_v<U>;

        template <int i, typename V, bool = i < sizeof_t_v<V> - 1>
        struct next
        {
            static constexpr int m = get_v<i, V>;
            using type = typeof_t<next<i + 1, sub_t<i, m % 10, add_t<i + 1, m / 10, V>>>>;
        };

        template <int i, typename V>
        struct next<i, V, false>
        {
            static constexpr int m = get_v<i, V>;

            using curr = type_if<m < 10, std::type_identity<V>, sub<i, m % 10, V>>;
            using type = reverse_t<append_if_t<(m >= 10), curr, c_<m / 10>>>;
        };

        template <int i, int j, int k, int l, typename V>
        struct impl
        {
            static constexpr auto cond = i + j < sizeof_t_v<V>;
            static constexpr int m = get_v<M - i - 1, T> * get_v<N - j - 1, U>;

            using curr = type_if<cond, add<i + j, m, V>, append<V, c_<m>>>;
            using type = typeof_t<impl<i, j + 1, k, l, curr>>;
        };

        template <int i, int k, int l, typename V>
        struct impl<i, l, k, l, V> : impl<i + 1, 0, k, l, V>
        {
        };

        template <int j, int k, int l, typename V>
        struct impl<k, j, k, l, V> : next<0, V>
        {
        };

        using type = typeof_t<impl<0, 0, M, N, base_type_t<T>>>;
    };

    template <typename T, typename U>
    using large_number_multiplier_t = typeof_t<large_number_multiplier<T, U>>;

    template <typename T, typename... Args>
    struct prefix
    {
        template <auto i, typename U>
        using impl = store_t<Args..., element_t<i, U>>;

        using type = unpack_t<concat_t, expand_t<impl, T, index_sequence_of_t<T>>>;
    };

    template <typename T, typename... Args>
    using prefix_t = typeof_t<prefix<T, Args...>>;

    template <typename T, auto... values>
    using prefix_c = prefix_t<T, c_<values>...>;

    template <typename T, typename... Args>
    struct suffix
    {
        template <auto i, typename U>
        using impl = store_t<element_t<i, U>, Args...>;

        using type = unpack_t<concat_t, expand_t<impl, T, index_sequence_of_t<T>>>;
    };

    template <typename T, typename... Args>
    using suffix_t = typeof_t<suffix<T, Args...>>;

    template <typename T, auto... values>
    using suffix_c = suffix_t<T, c_<values>...>;

    template <typename T, typename U>
    requires is_variadic_pack_v<T, U>
    struct zip
    {
        static constexpr auto M = sizeof_t_v<T>;
        static constexpr auto N = sizeof_t_v<U>;

        template <auto i, typename V>
        using impl = store_t<element_t<i, V>, element_t<i, U>>;

        using type = unpack_t<concat_t, expand_t<impl, T, index_sequence_of_c<(M < N ? M : N)>>>;
    };

    template <typename T, typename U>
    using zip_t = typeof_t<zip<T, U>>;

    template <template <typename ...> typename F, typename T, typename U>
    requires is_variadic_pack_v<T, U>
    struct zip_with
    {
        static constexpr auto M = sizeof_t_v<T>;
        static constexpr auto N = sizeof_t_v<U>;

        template <auto i, typename V>
        using impl = F<element_t<i, V>, element_t<i, U>>;

        using type = expand_t<impl, T, index_sequence_of_c<(M < N ? M : N)>>;
    };

    template <template <typename ...> typename F, typename T, typename U>
    using zip_with_t = typeof_t<zip_with<F, T, U>>;

    template <typename T>
    struct row_type : base_type<element_t<0, T>>
    {
    };

    template <typename T>
    using row_type_t = typeof_t<row_type<T>>;

    template <auto row, auto col, typename T>
    struct matrix : fill<row, fill_t<col, T>>
    {
    };

    template <auto row, auto col, typename T>
    using matrix_t = typeof_t<matrix<row, col, T>>;

    template <typename T>
    struct matrix_row_size : sizeof_t<T>
    {
    };

    template <typename T>
    inline constexpr auto matrix_row_size_v = typev<matrix_row_size<T>>;

    template <typename T>
    struct matrix_col_size : sizeof_t<type_if<is_variadic_v<T> && sizeof_t_v<T>, element<0, T>, c_0>>
    {
    };

    template <typename T>
    inline constexpr auto matrix_col_size_v = typev<matrix_col_size<T>>;

    template <typename T>
    struct matrix_dim : c_<matrix_row_size_v<T> * matrix_col_size_v<T>>
    {
    };

    template <typename T>
    using matrix_dim_t = typeof_t<matrix_dim<T>>;

    template <typename T>
    inline constexpr auto matrix_dim_v = typev<matrix_dim_t<T>>;

    template <typename T>
    struct is_square_matrix : bool_<matrix_row_size_v<T> && matrix_col_size_v<T>>
    {
    };

    template <typename T>
    inline constexpr auto is_square_matrix_v = typev<is_square_matrix<T>>;

    template <auto row, auto col, typename T>
    struct get_matrix_element : element<col, element_t<row, T>>
    {
    };

    template <auto row, auto col, typename T>
    using get_matrix_element_t = typeof_t<get_matrix_element<row, col, T>>;

    template <auto row, auto col, typename T>
    inline constexpr auto get_matrix_element_v = typev<get_matrix_element_t<row, col, T>>;

    template <auto row, auto col, typename T, typename U>
    struct set_matrix_element : exchange<row, exchange_t<col, T, element_t<row, U>>, U>
    {
    };

    template <auto row, auto col, typename T, typename U>
    using set_matrix_element_t = typeof_t<set_matrix_element<row, col, T, U>>;

    template <auto row, auto col, auto v, typename U>
    using set_matrix_element_c = set_matrix_element_t<row, col, c_<v>, U>;

    template <auto row, auto col, typename T, typename U, int m = 1, int n = 1>
    struct matrix_element_summator : c_<m * get_matrix_element_v<row, col, T> + n * get_matrix_element_v<row, col, U>>
    {
    };

    template <auto row, auto col, typename T, typename U, int m = 1, int n = 1>
    using matrix_element_summator_t = typeof_t<matrix_element_summator<row, col, T, U, m, n>>;

    template <auto row, auto col, typename T, typename U, int m = 1, int n = 1>
    inline constexpr auto matrix_element_summator_v = typev<matrix_element_summator_t<row, col, T, U, m, n>>;

    template <auto row, auto col, typename T, typename U>
    struct matrix_element_add : matrix_element_summator<row, col, T, U>
    {
    };

    template <auto row, auto col, typename T, typename U>
    using matrix_element_add_t = typeof_t<matrix_element_add<row, col, T, U>>;

    template <auto row, auto col, typename T, typename U>
    inline constexpr auto matrix_element_add_v = typev<matrix_element_add_t<row, col, T, U>>;

    template <auto row, auto col, typename T, typename U>
    struct matrix_element_sub : matrix_element_summator<row, col, T, U, 1, -1>
    {
    };

    template <auto row, auto col, typename T, typename U>
    using matrix_element_sub_t = typeof_t<matrix_element_sub<row, col, T, U>>;

    template <auto row, auto col, typename T, typename U>
    inline constexpr auto matrix_element_sub_v = typev<matrix_element_sub_t<row, col, T, U>>;

    template <auto N, typename T, typename U, bool B = false>
    requires (matrix_row_size_v<T> == matrix_col_size_v<U> || B)
    struct set_matrix_row : exchange<N, T, U>
    {
    };

    template <auto N, typename T, typename U, bool B = false>
    using set_matrix_row_t = typeof_t<set_matrix_row<N, T, U, B>>;

    template <auto lower, auto upper, typename T, template <auto, auto, typename> typename F>
    struct matrix_row_transform : F<lower, upper, T>
    {
    };

    template <auto lower, auto upper, typename T, template <auto, auto, typename> typename F>
    using matrix_row_transform_t = typeof_t<matrix_row_transform<lower, upper, T, F>>;

    template <auto lower, auto upper, typename T, template <auto, auto, typename> typename F,
    bool B1 = false, bool B2 = false, bool B3 = false, bool B4 = false>
    struct matrix_col_transform
    {
        template <int i, int j, typename U>
        struct impl
        {
            using call = typeof_t<F<lower, upper, type_if<!B1, element<i, U>, index_upper<i, U>>>>;
            using type = typeof_t<impl<i + 1, j, type_if<!B2, set_matrix_row<i, call, U, 1>, std::type_identity<call>>>>;
        };

        template <int j, typename U>
        struct impl<j, j, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<B4 * lower, !B4 ? matrix_row_size_v<T> : upper, type_if<!B3, std::type_identity<T>, row_type<T>>>>;
    };

    template <auto lower, auto upper, typename T, template <auto, auto, typename> typename F,
    bool B1 = false, bool B2 = false, bool B3 = false, bool B4 = false>
    using matrix_col_transform_t = typeof_t<matrix_col_transform<lower, upper, T, F, B1, B2, B3, B4>>;

    template <auto N, typename T, typename U, bool B = false>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U> || B)
    struct set_matrix_col : exchange<N, T, U>
    {
        template <int i, int j, typename V>
        struct impl : set_matrix_element<typev<V>, N, element_t<typev<V>, T>, typeof_t<V>>
        {
        };

        using type = matrix_col_transform_t<N, N, U, impl, 1, 1>;
    };

    template <auto N, typename T, typename U, bool B = false>
    using set_matrix_col_t = typeof_t<set_matrix_col<N, T, U, B>>;

    template <auto row, auto col = row>
    struct zero_matrix : matrix<row, col, c_0>
    {
    };

    template <auto row, auto col = row>
    using zero_matrix_t = typeof_t<zero_matrix<row, col>>;

    template <auto N>
    struct identity_matrix
    {
        template <int i, int j, typename V>
        struct impl : set_matrix_element<typev<V>, typev<V>, c_1, typeof_t<V>>
        {
        };

        using type = matrix_col_transform_t<N, N, zero_matrix_t<N>, impl, 1, 1>;
    };

    template <auto N>
    using identity_matrix_t = typeof_t<identity_matrix<N>>;

    template <typename T>
    requires is_square_matrix_v<T>
    struct get_matrix_diagonal
    {
        template <int i, int j, typename V>
        struct impl : append<typeof_t<V>, get_matrix_element_t<typev<V>, typev<V>, T>>
        {
        };

        using type = matrix_col_transform_t<0, 0, T, impl, 1, 1, 1>;
    };

    template <typename T>
    using get_matrix_diagonal_t = typeof_t<get_matrix_diagonal<T>>;

    template <typename T, typename U>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U> && is_square_matrix_v<U>)
    struct set_matrix_diagonal
    {
        template <int i, int j, typename V>
        struct impl
        {
            static constexpr auto row = typev<V>;
            using type = set_matrix_element_t<row, row, element_t<row, T>, typeof_t<V>>;
        };

        using type = matrix_col_transform_t<0, 0, U, impl, 1, 1>;
    };

    template <typename T, typename U>
    using set_matrix_diagonal_t = typeof_t<set_matrix_diagonal<T, U>>;

    template <typename T>
    struct trace : sum<get_matrix_diagonal_t<T>>
    {
    };

    template <typename T>
    using trace_t = typeof_t<trace<T>>;

    template <typename T>
    inline constexpr auto trace_v = typev<trace_t<T>>;

    template <auto N, typename T>
    struct get_matrix_row : element<N, T>
    {
    };

    template <auto N, typename T>
    using get_matrix_row_t = typeof_t<get_matrix_row<N, T>>;

    template <auto N, typename T>
    struct get_matrix_col
    {
        template <int i, int j, typename U>
        struct impl : append<typeof_t<U>, get_matrix_element_t<typev<U>, N, T>>
        {
        };

        using type = matrix_col_transform_t<N, N, T, impl, 1, 1, 1>;
    };

    template <auto N, typename T>
    using get_matrix_col_t = typeof_t<get_matrix_col<N, T>>;

    template <auto N, typename T, typename U>
    requires (matrix_row_size_v<T> == matrix_col_size_v<U>)
    struct insert_matrix_row : insert<N, U, T>
    {
    };

    template <auto N, typename T, typename U>
    using insert_matrix_row_t = typeof_t<insert_matrix_row<N, T, U>>;

    template <auto N, typename T, typename U>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U>)
    struct insert_matrix_col
    {
        template <int i, int j, typename V>
        struct impl : insert<i, element_t<typev<V>, typeof_t<V>>, element_t<typev<V>, T>>
        {
        };

        using type = matrix_col_transform_t<N, N, U, impl, 1>;
    };

    template <auto N, typename T, typename U>
    using insert_matrix_col_t = typeof_t<insert_matrix_col<N, T, U>>;

    template <typename T, typename U>
    struct vertical_prepend : insert_matrix_row<0, T, U>
    {
    };

    template <typename T, typename U>
    using vertical_prepend_t = typeof_t<vertical_prepend<T, U>>;

    template <typename T, typename U>
    struct vertical_append : insert_matrix_row<matrix_row_size_v<U>, T, U>
    {
    };

    template <typename T, typename U>
    using vertical_append_t = typeof_t<vertical_append<T, U>>;

    template <typename T, typename U>
    struct horizontal_prepend : insert_matrix_col<0, T, U>
    {
    };

    template <typename T, typename U>
    using horizontal_prepend_t = typeof_t<horizontal_prepend<T, U>>;

    template <typename T, typename U>
    struct horizontal_append : insert_matrix_col<matrix_col_size_v<U>, T, U>
    {
    };

    template <typename T, typename U>
    using horizontal_append_t = typeof_t<horizontal_append<T, U>>;

    template <auto N, typename T>
    struct remove_matrix_row : drop<N, T>
    {
    };

    template <auto N, typename T>
    using remove_matrix_row_t = typeof_t<remove_matrix_row<N, T>>;

    template <auto N, typename T>
    struct remove_matrix_col
    {
        template <int i, int j, typename U>
        using impl = drop<i, U>;

        using type = matrix_col_transform_t<N, N, T, impl>;
    };

    template <auto N, typename T>
    using remove_matrix_col_t = typeof_t<remove_matrix_col<N, T>>;

    template <auto row, auto col, typename T>
    struct remove_matrix_row_col : remove_matrix_col<col, remove_matrix_row_t<row, T>>
    {
    };

    template <auto row, auto col, typename T>
    using remove_matrix_row_col_t = typeof_t<remove_matrix_row_col<row, col, T>>;

    template <auto col, auto row, typename T>
    struct remove_matrix_col_row : remove_matrix_row<row, remove_matrix_col_t<col, T>>
    {
    };

    template <auto col, auto row, typename T>
    using remove_matrix_col_row_t = typeof_t<remove_matrix_col_row<col, row, T>>;

    template <typename T>
    requires is_square_matrix_v<T>
    struct det
    {
        template <int i, int j, int k>
        struct impl
        {
            static constexpr auto value = get_matrix_element_v<0, i, T>;
            using next = type_if<value != 0, remove_matrix_row_col<0, i, T>, std::type_identity<T>>;

            static constexpr auto curr = (i % 2 ? -1 : 1) * value;
            using type = typeof_t<impl<i + 1, j, k + curr * type_if_v<value != 0, det<next>, c_0>>>;
        };

        template <int j, int k>
        struct impl<j, j, k> : c_<k>
        {
        };

        static constexpr auto row = matrix_row_size_v<T>;
        using type = type_if<row + matrix_col_size_v<T> == 2, get_matrix_element<0, 0, T>, impl<0, row, 0>>;
    };

    template <typename T>
    using det_t = typeof_t<det<T>>;

    template <typename T>
    inline constexpr auto det_v = typev<det_t<T>>;

    template <typename T, template <typename> typename F1, template <auto, typename> typename F2, template <typename> typename F3>
    struct line_summator
    {
        template <int i, int j, typename U>
        struct impl : append<typeof_t<U>, typeof_t<F3<typeof_t<F2<typev<U>, T>>>>>
        {
        };

        using type = matrix_col_transform_t<0, typev<F1<T>>, T, impl, 1, 1, 1, 1>;
    };

    template <typename T, template <typename> typename F1, template <auto, typename> typename F2, template <typename> typename F3>
    using line_summator_t = typeof_t<line_summator<T, F1, F2, F3>>;

    template <auto N, typename T>
    struct sum_row : sum<get_matrix_row_t<N, T>>
    {
    };

    template <auto N, typename T>
    using sum_row_t = typeof_t<sum_row<N, T>>;

    template <auto N, typename T>
    inline constexpr auto sum_row_v = typev<sum_row_t<N, T>>;

    template <auto N, typename T>
    struct sum_col : sum<get_matrix_col_t<N, T>>
    {
    };

    template <auto N, typename T>
    using sum_col_t = typeof_t<sum_col<N, T>>;

    template <auto N, typename T>
    inline constexpr auto sum_col_v = typev<sum_col_t<N, T>>;

    template <auto N, typename T>
    struct product_row : mul<get_matrix_row_t<N, T>>
    {
    };

    template <auto N, typename T>
    using product_row_t = typeof_t<product_row<N, T>>;

    template <auto N, typename T>
    inline constexpr auto product_row_v = typev<product_row_t<N, T>>;

    template <auto N, typename T>
    struct product_col : mul<get_matrix_col_t<N, T>>
    {
    };

    template <auto N, typename T>
    using product_col_t = typeof_t<product_col<N, T>>;

    template <auto N, typename T>
    inline constexpr auto product_col_v = typev<product_col_t<N, T>>;

    template <typename T>
    struct matrix_row_sum : line_summator<T, matrix_col_size, get_matrix_col, sum>
    {
    };

    template <typename T>
    using matrix_row_sum_t = typeof_t<matrix_row_sum<T>>;

    template <typename T>
    struct matrix_col_sum : line_summator<T, matrix_row_size, get_matrix_row, sum>
    {
    };

    template <typename T>
    using matrix_col_sum_t = typeof_t<matrix_col_sum<T>>;

    template <typename T>
    struct matrix_row_means : line_summator<T, matrix_col_size, get_matrix_col, means>
    {
    };

    template <typename T>
    using matrix_row_means_t = typeof_t<matrix_row_means<T>>;

    template <typename T>
    struct matrix_col_means : line_summator<T, matrix_row_size, get_matrix_row, means>
    {
    };

    template <typename T>
    using matrix_col_means_t = typeof_t<matrix_col_means<T>>;

    template <typename T>
    struct matrix_sum : sum<matrix_col_sum_t<T>>
    {
    };

    template <typename T>
    using matrix_sum_t = typeof_t<matrix_sum<T>>;

    template <typename T>
    inline constexpr auto matrix_sum_v = typev<matrix_sum_t<T>>;

    template <typename T>
    struct matrix_means : c_<matrix_sum_v<T> / matrix_dim_v<T>>
    {
    };

    template <typename T>
    using matrix_means_t = typeof_t<matrix_means<T>>;

    template <typename T>
    inline constexpr auto matrix_means_v = typev<matrix_means_t<T>>;

    template <typename T>
    struct matrix_row_mul : line_summator<T, matrix_col_size, get_matrix_col, mul>
    {
    };

    template <typename T>
    using matrix_row_mul_t = typeof_t<matrix_row_mul<T>>;

    template <typename T>
    struct matrix_col_mul : line_summator<T, matrix_row_size, get_matrix_row, mul>
    {
    };

    template <typename T>
    using matrix_col_mul_t = typeof_t<matrix_col_mul<T>>;

    template <typename T>
    struct matrix_mul : mul<matrix_col_mul_t<T>>
    {
    };

    template <typename T>
    using matrix_mul_t = typeof_t<matrix_mul<T>>;

    template <typename T>
    inline constexpr auto matrix_mul_v = typev<matrix_mul_t<T>>;

    template <template <typename> typename F, typename T>
    struct matrix_row_apply : line_summator<T, matrix_row_size, get_matrix_row, F>
    {
    };

    template <template <typename> typename F, typename T>
    using matrix_row_apply_t = typeof_t<matrix_row_apply<F, T>>;

    template <template <typename> typename F, typename T>
    struct matrix_col_apply : line_summator<T, matrix_col_size, get_matrix_col, F>
    {
    };

    template <template <typename> typename F, typename T>
    using matrix_col_apply_t = typeof_t<matrix_col_apply<F, T>>;

    template <typename T>
    struct matrix_row_maximum : matrix_row_apply<max_element, T>
    {
    };

    template <typename T>
    using matrix_row_maximum_t = typeof_t<matrix_row_maximum<T>>;

    template <typename T>
    struct matrix_col_maximum : matrix_col_apply<max_element, T>
    {
    };

    template <typename T>
    using matrix_col_maximum_t = typeof_t<matrix_col_maximum<T>>;

    template <typename T>
    struct matrix_row_minimum : matrix_row_apply<min_element, T>
    {
    };

    template <typename T>
    using matrix_row_minimum_t = typeof_t<matrix_row_minimum<T>>;

    template <typename T>
    struct matrix_col_minimum : matrix_col_apply<min_element, T>
    {
    };

    template <typename T>
    using matrix_col_minimum_t = typeof_t<matrix_col_minimum<T>>;

    template <typename T>
    struct matrix_row_midpoint : matrix_row_apply<midpoint, T>
    {
    };

    template <typename T>
    using matrix_row_midpoint_t = typeof_t<matrix_row_midpoint<T>>;

    template <typename T>
    struct matrix_col_midpoint : matrix_col_apply<midpoint, T>
    {
    };

    template <typename T>
    using matrix_col_midpoint_t = typeof_t<matrix_col_midpoint<T>>;

    template <auto row, typename T, typename U>
    struct row_multiply : inner_dot<get_matrix_row_t<row, T>, get_matrix_row_t<row, U>>
    {
    };

    template <auto row, typename T, typename U>
    using row_multiply_t = typeof_t<row_multiply<row, T, U>>;

    template <auto row, typename T, typename U>
    struct col_multiply : inner_dot<get_matrix_col_t<row, T>, get_matrix_col_t<row, U>>
    {
    };

    template <auto row, typename T, typename U>
    using col_multiply_t = typeof_t<col_multiply<row, T, U>>;

    template <typename T, typename U>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U> && matrix_col_size_v<T> == matrix_col_size_v<U>)
    struct matrix_elementwise_multiply
    {
        template <int i, int j, typename V>
        struct impl
        {
            static constexpr auto row = typev<V>;
            using type = set_matrix_row_t<row, row_multiply_t<row, T, U>, typeof_t<V>>;
        };

        using type = matrix_col_transform_t<0, 0, T, impl, 1, 1>;
    };

    template <typename T, typename U>
    using matrix_elementwise_multiply_t = typeof_t<matrix_elementwise_multiply<T, U>>;

    template <auto N, typename T, typename U, template <typename, typename> typename F>
    requires (matrix_row_size_v<T> == matrix_col_size_v<U>)
    struct matrix_row_operator : set_matrix_row<N, typeof_t<F<T, get_matrix_row_t<N, U>>>, U>
    {
    };

    template <auto N, typename T, typename U, template <typename, typename> typename F>
    using matrix_row_operator_t = typeof_t<matrix_row_operator<N, T, U, F>>;

    template <auto N, typename T, typename U, bool B>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U>)
    struct matrix_col_operator
    {
        template <int i, int j, typename V>
        struct impl
        {
            using curr = element_t<typev<V>, typeof_t<V>>;

            static constexpr auto p = element_v<i, curr>;
            static constexpr auto q = element_v<typev<V>, T>;

            using type = exchange_t<i, c_<B ? p + q : p * q>, curr>;
        };

        using type = matrix_col_transform_t<N, N, U, impl, 1>;
    };

    template <auto N, typename T, typename U, bool B>
    using matrix_col_operator_t = typeof_t<matrix_col_operator<N, T, U, B>>;

    template <auto N, typename T, typename U>
    struct add_matrix_row : matrix_row_operator<N, T, U, inner_sum>
    {
    };

    template <auto N, typename T, typename U>
    using add_matrix_row_t = typeof_t<add_matrix_row<N, T, U>>;

    template <auto N, typename T, typename U>
    struct add_matrix_col : matrix_col_operator<N, T, U, 1>
    {
    };

    template <auto N, typename T, typename U>
    using add_matrix_col_t = typeof_t<add_matrix_col<N, T, U>>;

    template <auto N, typename T, typename U>
    struct mul_matrix_row : matrix_row_operator<N, T, U, inner_dot>
    {
    };

    template <auto N, typename T, typename U>
    using mul_matrix_row_t = typeof_t<mul_matrix_row<N, T, U>>;

    template <auto N, typename T, typename U>
    struct mul_matrix_col : matrix_col_operator<N, T, U, 0>
    {
    };

    template <auto N, typename T, typename U>
    using mul_matrix_col_t = typeof_t<mul_matrix_col<N, T, U>>;

    template <auto N, auto M, typename T>
    struct scale_row : inner_mul<M, get_matrix_row_t<N, T>>
    {
    };

    template <auto N, auto M, typename T>
    using scale_row_t = typeof_t<scale_row<N, M, T>>;

    template <auto N, auto M, typename T>
    struct scale_col : inner_mul<M, get_matrix_col_t<N, T>>
    {
    };

    template <auto N, auto M, typename T>
    using scale_col_t = typeof_t<scale_col<N, M, T>>;

    template <auto N, auto M, auto P, typename T>
    struct scale_add_row : inner_sum<get_matrix_row_t<P, T>, inner_mul_t<M, get_matrix_row_t<N, T>>>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_add_row_t = typeof_t<scale_add_row<N, M, P, T>>;

    template <auto N, auto M, auto P, typename T>
    struct scale_add_col : inner_sum<get_matrix_col_t<P, T>, inner_mul_t<M, get_matrix_col_t<N, T>>>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_add_col_t = typeof_t<scale_add_col<N, M, P, T>>;

    template <auto N, auto M, auto P, typename T>
    struct scale_mul_row : inner_dot<get_matrix_row_t<P, T>, inner_mul_t<M, get_matrix_row_t<N, T>>>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_mul_row_t = typeof_t<scale_mul_row<N, M, P, T>>;

    template <auto N, auto M, auto P, typename T>
    struct scale_mul_col : inner_dot<get_matrix_col_t<P, T>, inner_mul_t<M, get_matrix_col_t<N, T>>>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_mul_col_t = typeof_t<scale_mul_col<N, M, P, T>>;

    template <auto lower, auto upper, auto M, typename T>
    struct scale_range : replace_range<lower, upper, T, inner_mul_range_t<lower, upper, M, T>>
    {
    };

    template <auto lower, auto upper, auto M, typename T>
    using scale_range_t = typeof_t<scale_range<lower, upper, M, T>>;

    template <auto N, auto M, typename T>
    struct scale_matrix_row : set_matrix_row<N, scale_row_t<N, M, T>, T>
    {
    };

    template <auto N, auto M, typename T>
    using scale_matrix_row_t = typeof_t<scale_matrix_row<N, M, T>>;

    template <auto N, auto M, typename T>
    struct scale_matrix_col : set_matrix_col<N, scale_col_t<N, M, T>, T>
    {
    };

    template <auto N, auto M, typename T>
    using scale_matrix_col_t = typeof_t<scale_matrix_col<N, M, T>>;

    template <auto lower, auto upper, auto M, typename T>
    struct scale_matrix_row_range
    {
        template <int i, int j, typename U>
        using impl = inner_mul<M, U>;

        using type = matrix_col_transform_t<lower, upper, T, impl, 0, 0, 0, 1>;
    };

    template <auto lower, auto upper, auto M, typename T>
    using scale_matrix_row_range_t = typeof_t<scale_matrix_row_range<lower, upper, M, T>>;

    template <auto lower, auto upper, auto M, typename T>
    struct scale_matrix_col_range
    {
        template <int i, int j, typename U>
        using impl = scale_range<i, j, M, U>;

        using type = matrix_col_transform_t<lower, upper, T, impl>;
    };

    template <auto lower, auto upper, auto M, typename T>
    using scale_matrix_col_range_t = typeof_t<scale_matrix_col_range<lower, upper, M, T>>;

    template <auto M, typename T>
    struct scale_matrix
    {
        template <int i, int j, typename U>
        using impl = inner_mul<M, U>;

        using type = matrix_col_transform_t<M, M, T, impl>;
    };

    template <auto M, typename T>
    using scale_matrix_t = typeof_t<scale_matrix<M, T>>;

    template <auto N, auto M, auto P, typename T, template <auto, auto, auto, typename> typename F1, template <auto, typename, typename> typename F2>
    struct scale_matrix_operator : F2<P, typeof_t<F1<N, M, P, T>>, T>
    {
    };

    template <auto N, auto M, auto P, typename T, template <auto, auto, auto, typename> typename F1, template <auto, typename, typename> typename F2>
    using scale_matrix_operator_t = typeof_t<scale_matrix_operator<N, M, P, T, F1, F2>>;

    template <auto N, auto M, auto P, typename T, template <auto, auto, auto, typename> typename F>
    using scale_row_operator  = scale_matrix_operator<N, M, P, T, F, set_matrix_row>;

    template <auto N, auto M, auto P, typename T, template <auto, auto, auto, typename> typename F>
    using scale_col_operator  = scale_matrix_operator<N, M, P, T, F, set_matrix_col>;

    template <auto N, auto M, auto P, typename T>
    struct scale_add_matrix_row : scale_row_operator<N, M, P, T, scale_add_row>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_add_matrix_row_t = typeof_t<scale_add_matrix_row<N, M, P, T>>;

    template <auto N, auto M, auto P, typename T>
    struct scale_add_matrix_col : scale_col_operator<N, M, P, T, scale_add_col>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_add_matrix_col_t = typeof_t<scale_add_matrix_col<N, M, P, T>>;

    template <auto N, auto M, auto P, typename T>
    struct scale_mul_matrix_row : scale_row_operator<N, M, P, T, scale_mul_row>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_mul_matrix_row_t = typeof_t<scale_mul_matrix_row<N, M, P, T>>;

    template <auto N, auto M, auto P, typename T>
    struct scale_mul_matrix_col : scale_col_operator<N, M, P, T, scale_mul_col>
    {
    };

    template <auto N, auto M, auto P, typename T>
    using scale_mul_matrix_col_t = typeof_t<scale_mul_matrix_col<N, M, P, T>>;

    template <auto M, auto N, typename T>
    struct swap_matrix_row : matrix_row_transform<M, N, T, swap>
    {
    };

    template <auto M, auto N, typename T>
    using swap_matrix_row_t = typeof_t<swap_matrix_row<M, N, T>>;

    template <auto M, auto N, typename T>
    struct swap_matrix_col : matrix_col_transform<M, N, T, swap>
    {
    };

    template <auto M, auto N, typename T>
    using swap_matrix_col_t = typeof_t<swap_matrix_col<M, N, T>>;

    template <auto lower, auto upper, typename T>
    struct matrix_row_range : matrix_row_transform<lower, upper, T, range>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_row_range_t = typeof_t<matrix_row_range<lower, upper, T>>;

    template <auto lower, auto upper, typename T>
    struct matrix_col_range : matrix_col_transform<lower, upper, T, range>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_col_range_t = typeof_t<matrix_col_range<lower, upper, T>>;

    template <auto N, typename T>
    struct drop_row_up : matrix_row_range<N, matrix_row_size_v<T>, T>
    {
    };

    template <auto N, typename T>
    using drop_row_up_t = typeof_t<drop_row_up<N, T>>;

    template <auto N, typename T>
    struct drop_row_down : matrix_row_range<0, matrix_row_size_v<T> - N, T>
    {
    };

    template <auto N, typename T>
    using drop_row_down_t = typeof_t<drop_row_down<N, T>>;

    template <auto N, typename T>
    struct drop_col_left : matrix_col_range<N, matrix_col_size_v<T>, T>
    {
    };

    template <auto N, typename T>
    using drop_col_left_t = typeof_t<drop_col_left<N, T>>;

    template <auto N, typename T>
    struct drop_col_right : matrix_col_range<0, matrix_col_size_v<T> - N, T>
    {
    };

    template <auto N, typename T>
    using drop_col_right_t = typeof_t<drop_col_right<N, T>>;

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    struct sub_matrix : matrix_col_range<col_lower, col_upper, matrix_row_range_t<row_lower, row_upper, T>>
    {
    };

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    using sub_matrix_t = typeof_t<sub_matrix<row_lower, row_upper, col_lower, col_upper, T>>;

    template <auto row, auto col, auto row_len, auto col_len, typename T>
    struct matrix_subset : sub_matrix<row, row + row_len, col, col + col_len, T>
    {
    };

    template <auto row, auto col, auto row_len, auto col_len, typename T>
    using matrix_subset_t = typeof_t<matrix_subset<row, col, row_len, col_len, T>>;

    template <auto lower, auto upper, typename T>
    struct matrix_row_erase : matrix_row_transform<lower, upper, T, erase>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_row_erase_t = typeof_t<matrix_row_erase<lower, upper, T>>;

    template <auto lower, auto upper, typename T>
    struct matrix_col_erase : matrix_col_transform<lower, upper, T, erase>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_col_erase_t = typeof_t<matrix_col_erase<lower, upper, T>>;

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    struct matrix_row_col_erase : matrix_col_erase<col_lower, col_upper, matrix_row_erase_t<row_lower, row_upper, T>>
    {
    };

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    using matrix_row_col_erase_t = typeof_t<matrix_row_col_erase<row_lower, row_upper, col_lower, col_upper, T>>;

    template <auto col_lower, auto col_upper, auto row_lower, auto row_upper, typename T>
    struct matrix_col_row_erase : matrix_row_erase<row_lower, row_upper, matrix_col_erase_t<col_lower, col_upper, T>>
    {
    };

    template <auto col_lower, auto col_upper, auto row_lower, auto row_upper, typename T>
    using matrix_col_row_erase_t = typeof_t<matrix_col_row_erase<col_lower, col_upper, row_lower, row_upper, T>>;

    template <auto pos, auto len, typename T>
    struct matrix_row_subset : matrix_row_range<pos, pos + len, T>
    {
    };

    template <auto pos, auto len, typename T>
    using matrix_row_subset_t = typeof_t<matrix_row_subset<pos, len, T>>;

    template <auto pos, auto len, typename T>
    struct matrix_col_subset : matrix_col_range<pos, pos + len, T>
    {
    };

    template <auto pos, auto len, typename T>
    using matrix_col_subset_t = typeof_t<matrix_col_subset<pos, len, T>>;

    template <auto i, auto j, auto k, typename T>
    struct matrix_row_rotate : rotate<i, j, k, T>
    {
    };

    template <auto i, auto j, auto k, typename T>
    using matrix_row_rotate_t = typeof_t<matrix_row_rotate<i, j, k, T>>;

    template <auto i, auto j, auto k, typename T>
    struct matrix_col_rotate
    {
        template <auto p, auto q, typename U>
        using impl = rotate<p, q, k, U>;

        using type = matrix_col_transform_t<i, j, T, impl>;
    };

    template <auto i, auto j, auto k, typename T>
    using matrix_col_rotate_t = typeof_t<matrix_col_rotate<i, j, k, T>>;

    template <auto i, typename T>
    struct matrix_row_pivot : matrix_row_rotate<0, i, matrix_row_size_v<T>, T>
    {
    };

    template <auto i, typename T>
    using matrix_row_pivot_t = typeof_t<matrix_row_pivot<i, T>>;

    template <auto i, typename T>
    struct matrix_col_pivot : matrix_col_rotate<0, i, matrix_col_size_v<T>, T>
    {
    };

    template <auto i, typename T>
    using matrix_col_pivot_t = typeof_t<matrix_col_pivot<i, T>>;

    template <auto N, typename T>
    struct matrix_shift_left : matrix_col_pivot<N, T>
    {
    };

    template <auto N, typename T>
    using matrix_shift_left_t = typeof_t<matrix_shift_left<N, T>>;

    template <auto N, typename T>
    struct matrix_shift_right : matrix_col_pivot<matrix_col_size_v<T> - N, T>
    {
    };

    template <auto N, typename T>
    using matrix_shift_right_t = typeof_t<matrix_shift_right<N, T>>;

    template <auto N, typename T>
    struct matrix_shift_up : matrix_row_pivot<N, T>
    {
    };

    template <auto N, typename T>
    using matrix_shift_up_t = typeof_t<matrix_shift_up<N, T>>;

    template <auto N, typename T>
    struct matrix_shift_down : matrix_row_pivot<matrix_row_size_v<T> - N, T>
    {
    };

    template <auto N, typename T>
    using matrix_shift_down_t = typeof_t<matrix_shift_down<N, T>>;

    template <auto N, typename T>
    struct reverse_row : reverse<get_matrix_row_t<N, T>>
    {
    };

    template <auto N, typename T>
    using reverse_row_t = typeof_t<reverse_row<N, T>>;

    template <auto N, typename T>
    struct reverse_col : reverse<get_matrix_col_t<N, T>>
    {
    };

    template <auto N, typename T>
    using reverse_col_t = typeof_t<reverse_col<N, T>>;

    template <auto N, typename T>
    struct matrix_row_reverse : set_matrix_row<N, reverse_row_t<N, T>, T>
    {
    };

    template <auto N, typename T>
    using matrix_row_reverse_t = typeof_t<matrix_row_reverse<N, T>>;

    template <auto N, typename T>
    struct matrix_col_reverse : set_matrix_col<N, reverse_col_t<N, T>, T>
    {
    };

    template <auto N, typename T>
    using matrix_col_reverse_t = typeof_t<matrix_col_reverse<N, T>>;

    template <auto p, auto q, typename T, template <auto, typename> typename F1, template <auto, typename> typename F2>
    struct matrix_reverse : F2<q, typeof_t<F1<p, T>>>
    {
    };

    template <auto p, auto q, typename T, template <auto, typename> typename F1, template <auto, typename> typename F2>
    using matrix_reverse_t = typeof_t<matrix_reverse<p, q, T, F1, F2>>;

    template <auto row, auto col, typename T>
    struct matrix_row_col_reverse : matrix_reverse<row, col, T, matrix_row_reverse, matrix_col_reverse>
    {
    };

    template <auto row, auto col, typename T>
    using matrix_row_col_reverse_t = typeof_t<matrix_row_col_reverse<row, col, T>>;

    template <auto col, auto row, typename T>
    struct matrix_col_row_reverse : matrix_reverse<col, row, T, matrix_col_reverse, matrix_row_reverse>
    {
    };

    template <auto col, auto row, typename T>
    using matrix_col_row_reverse_t = typeof_t<matrix_col_row_reverse<col, row, T>>;

    template <auto lower, auto upper, typename T, template <auto, typename> typename F>
    struct matrix_range_operator
    {
        template <int i, int j, typename U>
        struct impl : F<typev<U>, typeof_t<U>>
        {
        };

        using type = matrix_col_transform_t<lower, upper, T, impl, 1, 1, 0, 1>;
    };

    template <auto lower, auto upper, typename T, template <auto, typename> typename F>
    using matrix_range_operator_t = typeof_t<matrix_range_operator<lower, upper, T, F>>;

    template <auto lower, auto upper, typename T>
    struct matrix_row_reverse_range : matrix_range_operator<lower, upper, T, matrix_row_reverse>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_row_reverse_range_t = typeof_t<matrix_row_reverse_range<lower, upper, T>>;

    template <auto lower, auto upper, typename T>
    struct matrix_col_reverse_range : matrix_range_operator<lower, upper, T, matrix_col_reverse>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_col_reverse_range_t = typeof_t<matrix_col_reverse_range<lower, upper, T>>;

    template <typename T>
    struct matrix_rowwise_reverse : matrix_row_reverse_range<0, matrix_row_size_v<T>, T>
    {
    };

    template <typename T>
    using matrix_rowwise_reverse_t = typeof_t<matrix_rowwise_reverse<T>>;

    template <typename T>
    struct matrix_colwise_reverse : matrix_col_reverse_range<0, matrix_col_size_v<T>, T>
    {
    };

    template <typename T>
    using matrix_colwise_reverse_t = typeof_t<matrix_colwise_reverse<T>>;

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    struct matrix_row_col_reverse_range : matrix_col_reverse_range<col_lower, col_upper, matrix_row_reverse_range_t<row_lower, row_upper, T>>
    {
    };

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    using matrix_row_col_reverse_range_t = typeof_t<matrix_row_col_reverse_range<row_lower, row_upper, col_lower, col_upper, T>>; 

    template <auto col_lower, auto col_upper, auto row_lower, auto row_upper, typename T>
    struct matrix_col_row_reverse_range : matrix_row_reverse_range<row_lower, row_upper, matrix_col_reverse_range_t<col_lower, col_upper, T>>
    {
    };

    template <auto col_lower, auto col_upper, auto row_lower, auto row_upper, typename T>
    using matrix_col_row_reverse_range_t = typeof_t<matrix_col_row_reverse_range<col_lower, col_upper, row_lower, row_upper, T>>; 

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    struct sub_matrix_reverse
    {
        using curr = sub_matrix_t<row_lower, row_upper, col_lower, col_upper, T>;
        using type = matrix_col_reverse_range_t<0, col_upper - col_lower, matrix_row_reverse_range_t<0, row_upper - row_lower, curr>>;
    };

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    using sub_matrix_reverse_t = typeof_t<sub_matrix_reverse<row_lower, row_upper, col_lower, col_upper, T>>;

    template <auto row, auto col, typename T, template <auto, auto, typename> typename F>
    struct matrix_operator
    {
        template <int i, int j, int k, int l, typename U>
        struct impl : impl<i, j, k + 1, l, typeof_t<F<i, k, U>>>
        {
        };

        template <int i, int j, int l, typename U>
        struct impl<i, j, l, l, U> : impl<i + 1, j, 0, l, U>
        {
        };

        template <int j, int k, int l, typename U>
        struct impl<j, j, k, l, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<0, row, 0, col, T>>;
    };

    template <auto row, auto col, typename T, template <auto, auto, typename> typename F>
    using matrix_operator_t = typeof_t<matrix_operator<row, col, T, F>>;

    template <typename T, bool B = false>
    struct matrix_transpose
    {
        static constexpr auto row = matrix_row_size_v<T>;
        static constexpr auto col = matrix_col_size_v<T>;

        template <int i, int j, typename U>
        struct impl : set_matrix_element<B ? i : j, B ? j : i, get_matrix_element_t<B ? row - j - 1 : i, B ? col - i - 1 : j, T>, U>
        {
        };

        using type = matrix_operator_t<B ? col : row, B ? row : col, fill_t<col, get_matrix_col_t<0, T>>, impl>;
    };

    template <typename T, bool B = false>
    using matrix_transpose_t = typeof_t<matrix_transpose<T, B>>;

    template <typename T>
    struct matrix_transpose_l : matrix_transpose<T, false>
    {
    };

    template <typename T>
    using matrix_transpose_l_t = typeof_t<matrix_transpose_l<T>>;

    template <typename T>
    struct matrix_transpose_r : matrix_transpose<T, true>
    {
    };

    template <typename T>
    using matrix_transpose_r_t = typeof_t<matrix_transpose_r<T>>;

    template <typename T>
    struct rotate_matrix_left : matrix_colwise_reverse<matrix_transpose_t<T>>
    {
    };

    template <typename T>
    using rotate_matrix_left_t = typeof_t<rotate_matrix_left<T>>;

    template <typename T>
    struct rotate_matrix_right : matrix_rowwise_reverse<matrix_transpose_t<T>>
    {
    };

    template <typename T>
    using rotate_matrix_right_t = typeof_t<rotate_matrix_right<T>>;

    template <typename T, typename U, int m = 1, int n = 1>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U> && matrix_col_size_v<T> == matrix_col_size_v<U>)
    struct matrix_summator
    {
        template <int i, int j, typename V>
        struct impl : set_matrix_element<i, j, matrix_element_summator_t<i, j, T, U, m, n>, V>
        {
        };

        using type = matrix_operator_t<matrix_row_size_v<T>, matrix_col_size_v<T>, T, impl>;
    };

    template <typename T, typename U, int m = 1, int n = 1>
    using matrix_summator_t = typeof_t<matrix_summator<T, U, m, n>>;

    template <typename T, typename U>
    struct matrix_add : matrix_summator<T, U>
    {
    };

    template <typename T, typename U>
    using matrix_add_t = typeof_t<matrix_add<T, U>>;

    template <typename T, typename U>
    struct matrix_sub : matrix_summator<T, U, 1, -1>
    {
    };

    template <typename T, typename U>
    using matrix_sub_t = typeof_t<matrix_sub<T, U>>;

    template <auto row, auto col, typename T, typename U>
    requires (matrix_row_size_v<T> <= matrix_row_size_v<U> && matrix_col_size_v<T> <= matrix_col_size_v<U>)
    struct sub_matrix_replace
    {
        template <int i, int j, typename V>
        struct impl : set_matrix_element<row + i, col + j, get_matrix_element_t<i, j, T>, V>
        {
        };

        using type = matrix_operator_t<matrix_row_size_v<T>, matrix_col_size_v<T>, U, impl>;
    };

    template <auto row, auto col, typename T, typename U>
    using sub_matrix_replace_t = typeof_t<sub_matrix_replace<row, col, T, U>>;

    template <typename T, typename U>
    requires (matrix_col_size_v<T> == matrix_row_size_v<U>)
    struct matrix_multiply
    {
        static constexpr auto len = matrix_row_size_v<U>;

        template <int i, int j, typename V>
        struct impl
        {
            template <int p, int q, typename W>
            struct sum
            {
                static constexpr auto n = typev<W>;
                static constexpr auto m = get_matrix_element_v<i, n, T> * get_matrix_element_v<n, j, U>;

                using curr = typeof_t<W>;
                using type = set_matrix_element_c<i, j, get_matrix_element_v<i, j, curr> + m, curr>;
            };

            using type = matrix_col_transform_t<0, len, V, sum, 1, 1, 0, 1>;
        };

        static constexpr auto row = matrix_row_size_v<T>;
        static constexpr auto col = matrix_col_size_v<U>;

        using type = matrix_operator_t<row, col, matrix_t<row, col, c_0>, impl>;
    };

    template <typename T, typename U>
    using matrix_multiply_t = typeof_t<matrix_multiply<T, U>>;

    template <typename T, auto N>
    struct matrix_power
    {
        using half = typeof_t<matrix_power<T, N / 2>>;
        using curr = matrix_multiply_t<half, half>;

        using type = type_if<N % 2, matrix_multiply<T, curr>, std::type_identity<curr>>;
    };

    template <typename T>
    struct matrix_power<T, 1> : std::type_identity<T>
    {
    };

    template <typename T>
    struct matrix_power<T, 0> : identity_matrix<matrix_row_size_v<T>>
    {
    };

    template <typename T, auto N>
    using matrix_power_t = typeof_t<matrix_power<T, N>>;

    template <typename T, auto N>
    struct matrix_element_power
    {
        template <int i, int j, typename U>
        struct impl
        {
            using curr = power<get_matrix_element_v<i, j, U>, N>;
            using type = set_matrix_element_c<i, j, typev<curr>, U>;
        };

        using type = matrix_operator_t<matrix_row_size_v<T>, matrix_col_size_v<T>, T, impl>;
    };

    template <typename T, auto N>
    using matrix_element_power_t = typeof_t<matrix_element_power<T, N>>;

    template <auto N>
    struct pascal_matrix
    {
        template <int i, int j, typename T>
        struct impl
        {
            using prev = type_if<i && j, get_matrix_element<i, j - 1, T>, c_0>;
            using next = type_if<i && j, get_matrix_element<i - 1, j, T>, c_1>;

            using type = set_matrix_element_t<i, j, plus_t<prev, next>, T>;
        };

        using type = matrix_operator_t<N, N, identity_matrix_t<N>, impl>;
    };

    template <auto N>
    using pascal_matrix_t = typeof_t<pascal_matrix<N>>;

    template <typename T>
    struct matrix_negate
    {
        template <int i, int j, typename U>
        struct impl
        {
            using curr = get_matrix_element_t<i, j, U>;
            using type = set_matrix_element_c<i, j, -typev<curr>, U>;
        };

        using type = matrix_operator_t<matrix_row_size_v<T>, matrix_col_size_v<T>, T, impl>;
    };

    template <typename T>
    using matrix_negate_t = typeof_t<matrix_negate<T>>;

    template <typename T, bool B>
    struct triangular_matrix
    {
        template <int i, int j, typename U>
        struct impl
        {
            static constexpr auto value = B && i > j || !B && i < j;
            using type = type_if<value, set_matrix_element<i, j, c_0, U>, std::type_identity<U>>;
        };

        using type = matrix_operator_t<matrix_row_size_v<T>, matrix_col_size_v<T>, T, impl>;
    };

    template <typename T, bool B>
    using triangular_matrix_t = typeof_t<triangular_matrix<T, B>>;

    template <typename T>
    struct upper_triangular_matrix : triangular_matrix<T, true>
    {
    };

    template <typename T>
    using upper_triangular_matrix_t = typeof_t<upper_triangular_matrix<T>>;

    template <typename T>
    struct lower_triangular_matrix : triangular_matrix<T, false>
    {
    };

    template <typename T>
    using lower_triangular_matrix_t = typeof_t<lower_triangular_matrix<T>>;

    template <typename T, typename U>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U>)
    struct toeplitz_matrix
    {
        using w = reverse_t<U>;
        static constexpr auto N = matrix_row_size_v<T>;

        template <int i, int j, typename V>
        struct impl : impl<i + 1, j, append_t<V, concat_t<subset_t<N - i - 1, i, w>, drop_back_t<i, T>>>>
        {
        };

        template <int j, typename V>
        struct impl<j, j, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<1, N, tuple_t<T>>>;
    };

    template <typename T, typename U>
    using toeplitz_matrix_t = typeof_t<toeplitz_matrix<T, U>>;

    template <auto row, auto col, typename T, typename U>
    requires (matrix_col_size_v<T> == matrix_row_size_v<U>)
    struct matrix_row_col_dot : sum<inner_dot_t<get_matrix_row_t<row, T>, get_matrix_col_t<col, U>>>
    {
    };

    template <auto row, auto col, typename T, typename U>
    using matrix_row_col_dot_t = typeof_t<matrix_row_col_dot<row, col, T, U>>;

    template <auto row, auto col, typename T, typename U>
    inline constexpr auto matrix_row_col_dot_v = typev<matrix_row_col_dot_t<row, col, T, U>>;

    template <typename T>
    struct row_matrix : std::type_identity<std::tuple<T>>
    {
    };

    template <typename T>
    using row_matrix_t = typeof_t<row_matrix<T>>;

    template <typename T>
    struct col_matrix;

    template <template <typename ...> typename T, typename... Args>
    struct col_matrix<T<Args...>> : std::type_identity<T<T<Args>...>>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args>
    struct col_matrix<T<U, Args...>> : std::type_identity<std::tuple<T<U, Args>...>>
    {
    };

    template <typename T>
    using col_matrix_t = typeof_t<col_matrix<T>>;

    template <auto col, auto row, typename T, typename U>
    requires (matrix_row_size_v<T> == matrix_col_size_v<U>)
    struct matrix_col_row_dot : matrix_multiply<col_matrix_t<get_matrix_col_t<col, T>>, row_matrix_t<get_matrix_row_t<row, U>>>
    {
    };

    template <auto col, auto row, typename T, typename U>
    using matrix_col_row_dot_t = typeof_t<matrix_col_row_dot<col, row, T, U>>;

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    struct sub_matrix_transpose : matrix_transpose<sub_matrix_t<row_lower, row_upper, col_lower, col_upper, T>>
    {
    };

    template <auto row_lower, auto row_upper, auto col_lower, auto col_upper, typename T>
    using sub_matrix_transpose_t = typeof_t<sub_matrix_transpose<row_lower, row_upper, col_lower, col_upper, T>>;

    template <typename T>
    struct transpose
    {
        using base = row_type_t<T>;

        template <int i, int j, int k, int l, typename U, typename V>
        struct impl
        {
            using row = append_t<U, get_matrix_element_t<i, k, T>>;
            using type = typeof_t<impl<i + 1, j, k, l, row, V>>;
        };

        template <int j, int k, int l, typename U, typename V>
        struct impl<j, j, k, l, U, V>
        {
            using type = typeof_t<impl<0, j, k + 1, l, base, append_t<V, U>>>;
        };

        template <int i, int j, int l, typename U, typename V>
        struct impl<i, j, l, l, U, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<0, matrix_row_size_v<T>, 0, matrix_col_size_v<T>, base, base_type_t<T>>>;
    };

    template <typename T>
    using transpose_t = typeof_t<transpose<T>>;

    template <typename T, typename U>
    requires (matrix_row_size_v<T> == matrix_row_size_v<U>)
    struct matrix_horizontal_concat
    {
        template <int i, int j, typename V>
        struct impl
        {
            static constexpr auto row = typev<V>;

            using curr = typeof_t<V>;
            using type = set_matrix_row_t<row, append_range_t<element_t<row, curr>, get_matrix_row_t<row, U>>, curr, 1>;
        };

        using type = matrix_col_transform_t<0, 0, T, impl, 1, 1>;
    };

    template <typename T, typename U>
    using matrix_horizontal_concat_t = typeof_t<matrix_horizontal_concat<T, U>>;

    template <typename T, typename U>
    requires (matrix_col_size_v<T> == matrix_col_size_v<U>)
    struct matrix_vertical_concat : append_range<T, U>
    {
    };

    template <typename T, typename U>
    using matrix_vertical_concat_t = typeof_t<matrix_vertical_concat<T, U>>;

    template <typename T>
    struct is_variadic_tuple : unpack_t<is_variadic_pack, T>
    {
    };

    template <typename T>
    using is_variadic_tuple_t = typeof_t<is_variadic_tuple<T>>;

    template <typename T>
    inline constexpr auto is_variadic_tuple_v = typev<is_variadic_tuple_t<T>>;

    template <typename indices, typename T>
    requires (is_sequence_v<indices> && is_variadic_tuple_v<T> && sizeof_t_v<indices> == sizeof_t_v<T>)
    struct elements
    {
        template <typename U, typename V, typename W>
        struct impl;

        template <template <typename, auto ...> typename U, typename V, auto n, auto... N,
        template <typename ...> typename W, typename X, typename... Args, typename Y>
        struct impl<U<V, n, N...>, W<X, Args...>, Y> : impl<U<V, N...>, W<Args...>, append_t<Y, element_t<n, X>>>
        {
        };

        template <template <typename, auto ...> typename U, typename V, auto n,
        template <typename ...> typename W, typename X, typename Y>
        struct impl<U<V, n>, W<X>, Y> : append<Y, element_t<n, X>>
        {
        };

        using type = typeof_t<impl<indices, T, row_type_t<T>>>;
    };

    template <typename indices, typename T>
    using elements_t = typeof_t<elements<indices, T>>;

    template <typename T, typename U>
    requires (is_variadic_tuple_v<T> && is_variadic_tuple_v<U>)
    struct apply_indices
    {
        template <typename V, typename W>
        struct impl;

        template <template <typename ...> typename V, typename W, typename... Args, typename X>
        struct impl<V<W, Args...>, X> : impl<V<Args...>, append_t<X, elements_t<W, U>>>
        {
        };

        template <template <typename ...> typename V, typename W, typename X>
        struct impl<V<W>, X> : append<X, elements_t<W, U>>
        {
        };

        using type = typeof_t<impl<T, tuple_t<>>>;
    };

    template <typename T, typename U>
    using apply_indices_t = typeof_t<apply_indices<T, U>>;

    template <typename... Args>
    requires (is_variadic_v<Args> && ...)
    struct combinations
    {
        template <typename T, typename indices>
        struct impl : append<T, elements_t<indices, tuple_t<Args...>>>
        {
        };

        using type = loop_indices_t<std::integer_sequence<int, sizeof_t_v<Args>...>, tuple_t<>, impl, true>;
    };

    template <typename... Args>
    using combinations_t = typeof_t<combinations<Args...>>;

    template <template <size_t, typename ...> typename F, size_t N, typename T, typename... Args>
    struct do_while
    {
        using call = F<N, T>;
        using curr = typeof_t<call>;

        using args = std::type_identity<tuple_t<Args...>>;
        using next = type_if<typev<call>, range<0, N, curr>, std::type_identity<T>>;

        using type = type_if<typev<call>, do_while<F, N, curr, Args..., next>, args>;
    };

    template <template <size_t, typename ...> typename F, size_t N, typename T, typename... Args>
    using do_while_t = typeof_t<do_while<F, N, T, Args...>>;

    template <template <size_t, typename ...> typename F, typename T, auto N = sizeof_t_v<T>>
    using ranged_list = do_while<F, N, T, range_t<0, N, T>>;

    template <template <size_t, typename ...> typename F, typename T, auto N = sizeof_t_v<T>>
    using ranged_list_t = typeof_t<ranged_list<F, T, N>>;

    template <typename T, bool ASC>
    struct permutation
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <typename U, typename V, bool B>
        using comparator = std::conditional_t<B, less_t<U, V>, greater_t<U, V>>;

        template <int k, bool b>
        struct impl
        {
            static constexpr auto value = negav<comparator<element_t<k - 1, T>, element_t<k, T>, ASC>>;
            using type = type_if<k == 1 && value, index_upper<0, T>, impl<k == 1 ? -1 : k - 1, value>>;
        };

        template <int k>
        struct impl<k, false>
        {
            static constexpr auto n = k == -1 ? 0 : k;

            template <typename U>
            struct comp : comparator<element_t<n, T>, U, ASC>
            {
            };

            using type = index_type<1, reverse_range_t<n + 1, N, swap_t<find_if_backward_v<comp, T>, n, T>>>;
        };

        template <bool b>
        struct impl<0, b> : index_upper<0, T>
        {
        };

        using type = typeof_t<impl<N - 1, true>>;
    };

    template <typename T, bool ASC>
    using permutation_t = typeof_t<permutation<T, ASC>>;

    template <template <size_t, typename ...> typename F, typename T>
    using permute = typeof_t<F<sizeof_t_v<T>, T>>;

    template <size_t, typename T>
    using next_permutation = permutation_t<T, true>;

    template <size_t, typename T>
    using prev_permutation = permutation_t<T, false>;

    template <typename T>
    using next_permutation_t = permute<next_permutation, T>;

    template <typename T>
    using prev_permutation_t = permute<prev_permutation, T>;

    template <typename T>
    using next_permutation_list = ranged_list_t<next_permutation, T>;

    template <typename T>
    using prev_permutation_list = ranged_list_t<prev_permutation, T>;

    template <template <size_t, typename ...> typename F, size_t N, typename T>
    using partial_permutation = range<0, N, typeof_t<F<N, T>>>;

    template <template <size_t, typename ...> typename F, size_t N, typename T>
    using partial_permutation_t = typeof_t<partial_permutation<F, N, T>>;

    template <size_t N, typename T>
    using next_partial_permutation = next_permutation<N, reverse_range_t<N, sizeof_t_v<T>, T>>;

    template <size_t N, typename T>
    using next_partial_permutation_t = partial_permutation_t<next_partial_permutation, N, T>;

    template <size_t N, typename T>
    using next_partial_permutation_list = ranged_list_t<next_partial_permutation, T, N>;

    template <size_t N, typename T>
    struct prev_partial_permutation
    {
        using prev = prev_permutation<N, T>;
        static constexpr auto value = typev<prev>;

        using type = reverse_range_t<N, sizeof_t_v<T>, typeof_t<prev>>;
    };

    template <size_t N, typename T>
    using prev_partial_permutation_t = partial_permutation_t<prev_partial_permutation, N, T>;

    template <size_t N, typename T>
    using prev_partial_permutation_list = ranged_list_t<prev_partial_permutation, T, N>;

    template <typename T>
    struct permutation_recursive
    {
        template <int l, int r, typename U, typename V>
        struct impl
        {
            template <int i, int j, typename W, typename X>
            struct next
            {
                using call = typeof_t<impl<l + 1, r, swap_t<l, i, W>, X>>;
                using type = typeof_t<next<i + 1, j, swap_t<l, i, first_t<call>>, second_t<call>>>;
            };

            template <int j, typename W, typename X>
            struct next<j, j, W, X>
            {
                using type = pair_t<W, X>;
            };

            template <typename W, typename X>
            struct end
            {
                using type = pair_t<W, append_t<X, W>>;
            };

            using type = type_if<l == r - 1, end<U, V>, next<l, r, U, V>>;
        };

        using type = second_t<typeof_t<impl<0, sizeof_t_v<T>, T, tuple_t<>>>>;
    };

    template <typename T>
    using permutation_recursive_t = typeof_t<permutation_recursive<T>>;

    template <size_t B1, size_t E1, size_t B2, size_t E2, typename T, bool ASC>
    struct combination
    {
        template <typename U, typename V, bool B>
        using comparator = std::conditional_t<B, less_t<U, V>, greater_t<U, V>>;

        template <typename U, int M, size_t N, size_t i, size_t j>
        struct next
        {
            static constexpr auto cond = i - N != B1 && negav<comparator<element_t<i - N, T>, U, ASC ? N : !N>>;
            static constexpr auto value = value_if<cond, next<U, M, N, i + M, j>, index_t<i - N>>;
        };

        template <typename U, size_t N, size_t i, size_t j>
        struct exch
        {
            static constexpr auto value = i != N && j != E2;

            using curr = swap_if_t<value, i - 1, j, U>;
            using type = type_if<value, exch<curr, N, i - 1, j + 1>, std::type_identity<pair_t<U, pair_v<i, j>>>>;
        };

        template <typename U, size_t N, size_t i, size_t j, bool result>
        struct reverse
        {
            using curr = typeof_t<exch<U, N, i, j>>;
            using call = second_t<curr>;

            using rang = reverse_range_t<N, E1, reverse_range_t<N, first_v<call>, first_t<curr>>>;
            using type = index_type<!result, reverse_range_t<j, E2, reverse_range_t<second_v<call>, E2, rang>>>;
        };

        template <size_t i, size_t j>
        struct impl
        {
            using lhs = element_t<j, T>;

            static constexpr auto k = typev<next<lhs, -1, 1, i, j>>;
            static constexpr auto result = k == B1 && negav<comparator<element_t<B1, T>, lhs, ASC>>;

            using rhs = element_if_t<!result, k, T, std::type_identity<T>>;
            static constexpr auto value = value_if<!result, next<rhs, 1, 0, B2, j>, index_t<B2>>;

            using curr = swap_if_t<!result, k, value, T>;
            using call = std::conditional_t<!result, pair_v<k + 1, value + 1>, pair_v<B1, B2>>; 

            static constexpr auto cond = first_v<call>!= E1 && second_v<call> != E2;
            using type = type_if<cond, reverse<curr, first_v<call>, E1, second_v<call>, result>, index_upper<!result, curr>>;
        };

        using type = type_if<B1 == E1 || B2 == E2, index_upper<0, T>, impl<E1, E2 - 1>>;
    };

    template <size_t B1, size_t E1, size_t B2, size_t E2, typename T, bool ASC>
    using combination_t = typeof_t<combination<B1, E1, B2, E2, T, ASC>>;

    template <size_t N, typename T, bool ASC>
    using combinate = combination_t<0, N, N, sizeof_t_v<T>, T, ASC>;

    template <size_t N, typename T>
    using next_combination = combinate<N, T, true>;

    template <size_t N, typename T>
    using next_combination_t = typeof_t<next_combination<N, T>>;

    template <size_t N, typename T>
    using prev_combination = combinate<N, T, false>;

    template <size_t N, typename T>
    using prev_combination_t = typeof_t<prev_combination<N, T>>;

    template <size_t N, typename T>
    using next_combination_list = ranged_list_t<next_combination, T, N>;

    template <size_t N, typename T>
    using prev_combination_list = ranged_list_t<prev_combination, T, N>;

    template <template <size_t, size_t, typename> typename F, size_t B, size_t E, typename T, typename... Args>
    struct next_indices
    {
        using call = F<B, E, T>;
        using curr = typeof_t<call>;

        using args = std::type_identity<tuple_t<Args...>>;
        static constexpr auto value = typev<call>;

        using next = std::conditional_t<value, curr, T>;
        using type = type_if<value, next_indices<F, B, E, curr, Args..., next>, args>;
    };

    template <template <size_t, size_t, typename> typename F, size_t B, size_t E, typename T, typename... Args>
    using next_indices_t = typeof_t<next_indices<F, B, E, T, Args...>>;

    template <template <size_t, size_t, typename> typename F, size_t B, size_t E, typename T>
    using indices_list = next_indices<F, B, E, T, T>;

    template <template <size_t, size_t, typename> typename F, size_t B, size_t E, typename T>
    using indices_list_t = typeof_t<indices_list<F, B, E, T>>;

    template <size_t B, size_t E, typename T, bool ASC>
    struct combination_counts
    {
        template <size_t i>
        struct next
        {
            using curr = index_t<i>;
            static constexpr auto cont = value_if<i != B, get<i - 1, T>, curr> == 0;

            using type = std::conditional_t<cont, next<i - 1>, index_t<i - 1>>;
            static constexpr auto value = value_if<i != B, type, curr>;
        };

        struct exch
        {
            static constexpr auto cond = value_if<ASC, get<B, T>, index_t<B != E - 1>>;
            using type = index_type<0, swap_if_t<cond != 0, B, E - 1, T>>;
        };

        template <size_t i, bool b>
        struct calc
        {
            using type = index_type<1, inc_t<i - 1, swap_t<i, E - 1, dec_t<i, T>>>>;
        };

        template <size_t i>
        struct calc<i, false>
        {
            using curr = dec_t<i, T>;
            using cond = std::conditional_t<get_v<E - 1, curr>, swap<i + 1, E - 1, curr>, std::type_identity<curr>>;

            using type = index_type<1, inc_t<i + 1, typeof_t<cond>>>;
        };

        template <size_t N>
        struct impl
        {
            using cond = ternary_conditional_t<!ASC, N == B, get<N, T>, index_t<1>, index_t<N == B>>;
            static constexpr auto value = value_if<ASC, cond, index_t<N == E - 1 || negav<cond>>>;
        };

        static constexpr auto value = typev<next<E - !ASC>>;
        using curr = conditional_of<impl<value>, exch, calc<value, ASC>>;

        using type = type_if<B == E, index_upper<0, T>, curr>;
    };

    template <size_t B, size_t E, typename T, bool ASC>
    using combination_counts_t = typeof_t<combination_counts<B, E, T, ASC>>;

    template <size_t B, size_t E, typename T>
    using next_combination_counts = combination_counts_t<B, E, T, true>;

    template <size_t B, size_t E, typename T>
    using next_combination_counts_t = typeof_t<next_combination_counts<B, E, T>>;

    template <size_t B, size_t E, typename T>
    using next_combination_counts_list = indices_list_t<next_combination_counts, B, E, T>;

    template <size_t B, size_t E, typename T>
    using prev_combination_counts = combination_counts_t<B, E, T, false>;

    template <size_t B, size_t E, typename T>
    using prev_combination_counts_t = typeof_t<prev_combination_counts<B, E, T>>;

    template <size_t B, size_t E, typename T>
    using prev_combination_counts_list = indices_list_t<prev_combination_counts, B, E, T>;

    template <size_t B, size_t E, typename T, size_t M, size_t N, bool ASC>
    struct hypercube_indices
    {
        template <typename U, size_t i, size_t j>
        struct impl
        {
            static constexpr auto value = get_v<j - 1, U> + ASC;
            using curr = sub_t<j - 1, value != M ? value - !ASC : N, U>;

            using next = std::conditional_t<i != j - 1, impl<curr, i, j - 1>, index_upper<0, curr>>;
            using type = type_if<value != M, index_upper<1, curr>, next>;
        };

        using type = type_if<B == E, index_upper<0, T>, impl<T, 0, sizeof_t_v<T>>>;
    };

    template <size_t B, size_t E, typename T, size_t M, size_t N, bool ASC>
    using hypercube_indices_t = typeof_t<hypercube_indices<B, E, T, M, N, ASC>>;

    template <size_t B, size_t E, typename T>
    using next_hypercube_indices = hypercube_indices_t<B, E, T, E, B, true>;

    template <size_t B, size_t E, typename T>
    using next_hypercube_indices_t = typeof_t<next_hypercube_indices<B, E, T>>;

    template <size_t B, size_t E, typename T>
    using prev_hypercube_indices = hypercube_indices_t<B, E, T, B, E - 1, false>;

    template <size_t B, size_t E, typename T>
    using prev_hypercube_indices_t = typeof_t<prev_hypercube_indices<B, E, T>>;

    template <size_t B, size_t E, typename T>
    using next_hypercube_indices_list = indices_list_t<next_hypercube_indices, B, E, T>;

    template <size_t B, size_t E, typename T>
    using prev_hypercube_indices_list = indices_list_t<prev_hypercube_indices, B, E, T>;

    template <typename T>
    requires is_square_matrix_v<T>
    struct matrix_combinations : apply_indices<next_permutation_list<index_sequence_of_t<T>>, T>
    {
    };

    template <typename T>
    using matrix_combinations_t = typeof_t<matrix_combinations<T>>;

    template <typename T, auto N = 1>
    struct increase
    {
        template <auto n, typename U>
        using impl = c_<add_v<n, N, U>>;

        using type = expand_t<impl, T, index_sequence_of_t<T>>;
    };

    template <typename T, auto N = 1>
    using increase_t = typeof_t<increase<T, N>>;

    template <size_t B, size_t E, typename T, bool ASC>
    struct slide_indices
    {
        static constexpr auto N = sizeof_t_v<T>;
        static constexpr auto value = get_v<0, T>;

        static constexpr auto cond = value == B && !ASC || value + N == E && ASC;
        using type = index_type<!cond, type_if<cond, std::type_identity<T>, increase<T, 2 * ASC - 1>>>;
    };

    template <size_t B, size_t E, typename T, bool ASC>
    using slide_indices_t = typeof_t<slide_indices<B, E, T, ASC>>;

    template <size_t B, size_t E, typename T>
    using next_slide_indices = slide_indices_t<B, E, T, true>;

    template <size_t B, size_t E, typename T>
    using next_slide_indices_t = typeof_t<next_slide_indices<B, E, T>>;

    template <size_t B, size_t E, typename T>
    using prev_slide_indices = slide_indices_t<B, E, T, false>;

    template <size_t B, size_t E, typename T>
    using prev_slide_indices_t = typeof_t<prev_slide_indices<B, E, T>>;

    template <size_t B, size_t E, typename T>
    using next_slide_indices_list = indices_list_t<next_slide_indices, B, E, T>;

    template <size_t B, size_t E, typename T>
    using prev_slide_indices_list = indices_list_t<prev_slide_indices, B, E, T>;

    template <typename T>
    struct to_index_sequence;

    template <template <typename, auto ...> typename T, typename U, auto... values>
    struct to_index_sequence<T<U, values...>>
    {
        using type = std::index_sequence<values...>;
    };

    template <typename T>
    using to_index_sequence_t = typeof_t<to_index_sequence<T>>;

    template <size_t N, typename T>
    struct slide_list
    {
        using sequence = integer_sequence_t<int, N, 0, 1>;
        using indices = next_slide_indices_list<0, sizeof_t_v<T>, sequence>;

        template <auto i, typename U>
        using impl = expand_t<element, T, to_index_sequence_t<element_t<i, U>>>;

        using type = expand_t<impl, indices, index_sequence_of_t<indices>>;
    };

    template <size_t N, typename T>
    using slide_list_t = typeof_t<slide_list<N, T>>;

    template <size_t i, size_t j, typename T, template <typename, typename> typename comparator>
    struct compare : comparator<element_t<i, T>, element_t<j, T>>
    {
    };

    template <size_t i, typename T, template <typename, typename> typename comparator>
    struct compare<i, i, T, comparator> : std::false_type
    {
    };

    template <size_t i, size_t j, typename T, template <typename, typename> typename comparator>
    inline constexpr auto compare_v = typev<compare<i, j, T, comparator>>;

    template <typename T, template <typename> typename F, int B = 0, int E = sizeof_t_v<T>>
    struct partition_point
    {
        template <int i, int j, bool = (i > 0)>
        struct impl
        {
            static constexpr auto half = i / 2;
            static constexpr auto value = typev<F<element_t<j + half, T>>>;

            static constexpr auto delta = value * half + value;
            using type = typeof_t<impl<value ? i - delta : half, j + delta>>;
        };

        template <int i, int j>
        struct impl<i, j, false> : c_<j>
        {
        };

        using type = typeof_t<impl<E - B, B>>;
    };

    template <typename T, template <typename> typename F, int B = 0, int E = sizeof_t_v<T>>
    using partition_point_t = typeof_t<partition_point<T, F, B, E>>;

    template <typename T, template <typename> typename F, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto partition_point_v = typev<partition_point_t<T, F, B, E>>;

    template <template <typename ...> typename F, typename T>
    struct partition_copy
    {
        using base = base_type_t<T>;

        template <size_t i, size_t j, typename U, typename V>
        struct impl
        {
            using curr = element_t<i, T>;
            static constexpr auto B = typev<F<curr>>;

            using type = typeof_t<impl<i + 1, j, append_if_t<B, U, curr>, append_if_t<!B, V, curr>>>;
        };

        template <size_t j, typename U, typename V>
        struct impl<j, j, U, V> : std::type_identity<pair_t<U, V>>
        {
        };

        using type = typeof_t<impl<0, sizeof_t_v<T>, base, base>>;
    };

    template <template <typename ...> typename F, typename T>
    using partition_copy_t = typeof_t<partition_copy<F, T>>;

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct partition
    {
        using x = element_t<r - 1, T>;

        template <int i, int j, int k, typename V>
        struct impl
        {
            static constexpr auto value = typev<comparator<element_t<j, V>, x>>;

            using cond = swap_if_t<value, i + 1, j, V>;
            using type = typeof_t<impl<i + value, j + 1, k, cond>>;
        };

        template <int i, int k, typename V>
        struct impl<i, k, k, V>
        {
            using type = index_type<i + 1, swap_t<i + 1, r - 1, V>>;
        };

        using type = typeof_t<impl<p - 1, p, r - 1, T>>;
    };

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal_t>
    using partition_t = typeof_t<partition<p, r, T, comparator>>;

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct randomized_partition : partition<p, r, prng_t<p, r, T>, comparator>
    {
    };

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal_t>
    using randomized_partition_t = typeof_t<randomized_partition<p, r, T, comparator>>;

    template <int p, int r, int len, int size, typename T, template <typename ...> typename comparator>
    struct partition_adaptive
    {
        template <int i, int j, int k, typename V, typename W>
        struct next
        {
            using call = element_t<i, T>;
            static constexpr auto N = typev<comparator<call>>;

            template <bool B, typename X>
            using cond = append_if_t<B == N, X, call>;

            using type = typeof_t<next<i + 1, j, k + N, cond<1, V>, cond<0, W>>>;
        };

        template <int j, int k, typename V, typename W>
        struct next<j, j, k, V, W>
        {
            using type = index_type<k, concat_t<range_t<0, p, T>, V, W, range_t<r, sizeof_t_v<T>, T>>>;
        };

        template <int m>
        struct split
        {
            using left_split = typeof_t<partition_adaptive<p, m, len / 2, size, T, comparator>>;
            using left_partition = typeof_t<left_split>;

            static constexpr auto half = len - len / 2;
            static constexpr auto index = find_if_not_v<comparator, left_partition, m, m + half>;

            using right_partition = partition_adaptive<index, r, half, size, left_partition, comparator>;
            using right_split = type_if<half, right_partition, index_upper<index, left_partition>>;

            static constexpr auto b = typev<left_split>;
            static constexpr auto e = typev<right_split>;

            using type = index_type<b + e - m, rotate_t<b, m, e, typeof_t<right_split>>>;
        };

        template <int m, bool b>
        struct impl
        {
            using base = base_type_t<T>;
            using type = typeof_t<next<p + 1, r, p, base, append_t<base, element_t<p, T>>>>;
        };

        template <int m>
        struct impl<m, false>
        {
            using type = typeof_t<split<m>>;
        };

        using type = type_if<len == 1 || r <= p, index_upper<p, T>, impl<p + len / 2, len <= size>>;
    };

    template <int p, int r, int len, int size, typename T, template <typename ...> typename comparator>
    using partition_adaptive_t = typeof_t<partition_adaptive<p, r, len, size, T, comparator>>;

    template <int p, int r, typename T, template <typename ...> typename comparator>
    struct stable_partition
    {
        static constexpr auto N = find_if_not_v<comparator, T, p, r>;

        using part = partition_adaptive<N, r, r - N, (r - N) / 2, T, comparator>;
        using type = type_if<N == r, index_upper<r, T>, part>;
    };

    template <int p, int r, typename T, template <typename ...> typename comparator>
    using stable_partition_t = typeof_t<stable_partition<p, r, T, comparator>>;

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct randomized_stable_partition
    {
        using prng = prng_t<p, r, T>;
        using x = element_t<r - 1, prng>;

        template <typename U>
        struct comp : comparator<U, x>
        {
        };

        using type = stable_partition_t<p, r, prng, comp>;
    };

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal_t>
    using randomized_stable_partition_t = typeof_t<randomized_stable_partition<p, r, T>>;

    template <int b, int e, int p, typename T, template <typename ...> typename F>
    struct gather
    {
        using prev = stable_partition_t<b, p, T, negaf<F>::template apply>;
        using next = stable_partition_t<p, e, typeof_t<prev>, F>;

        using type = triple<typev<prev>, typev<next>, typeof_t<next>>;
    };

    template <int b, int e, int p, typename T, template <typename ...> typename F>
    using gather_t = typeof_t<gather<b, e, p, T, F>>;

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct nth_pivot
    {
        template <int p, int r, size_t i, typename U>
        struct impl
        {
            using pivot = randomized_partition_t<p, r, U, comparator>;
            using curr = typeof_t<pivot>;

            static constexpr auto q = typev<pivot>;
            static constexpr auto k = q - p + 1;

            using next = std::conditional_t<i < k, impl<p, q, i, curr>, impl<q + 1, r, i - k, curr>>;
            using type = type_if<i == k, std::type_identity<index_type<q, curr>>, next>;
        };

        template <int p, size_t i, typename U>
        struct impl<p, p, i, U> : std::type_identity<index_type<p, U>>
        {
        };

        using type = typeof_t<impl<0, sizeof_t_v<T>, n, T>>;
    };

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal_t>
    using nth_pivot_t = typeof_t<nth_pivot<n, T, comparator>>;

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct nth_element
    {
        using type = typeof_t<nth_pivot_t<n + 1, T, comparator>>;
    };

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal_t>
    using nth_element_t = typeof_t<nth_element<n, T, comparator>>;

    template <typename T>
    struct median
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <bool, typename U>
        struct impl
        {
            using curr = nth_element_t<(N - 1) / 2, U>;
            using type = c_<(element_v<(N - 1) / 2, curr> + element_v<N / 2, curr>) / 2>;
        };

        template <typename U>
        struct impl<false, U> : c_<element_v<N / 2, U>>
        {
        };

        using type = typeof_t<impl<N % 2 == 0, nth_element_t<N / 2, T>>>;
    };

    template <typename T>
    using median_t = typeof_t<median<T>>;

    template <typename T>
    inline constexpr auto median_v = typev<median_t<T>>;

    template <size_t p, size_t q, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct partial_sort
    {
        template <size_t i, size_t j, typename U>
        struct impl : impl<i + 1, j, nth_element_t<i, U, comparator>>
        {
        };

        template <size_t j, typename U>
        struct impl<j, j, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<p, q, T>>;
    };

    template <size_t p, size_t q, typename T, template <typename, typename> typename comparator = less_equal_t>
    using partial_sort_t = typeof_t<partial_sort<p, q, T, comparator>>;

    template <size_t p, size_t q, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct sort_subrange
    {
        using type = type_if<p == q, std::type_identity<T>, partial_sort<p, q, T, comparator>>;
    };

    template <size_t p, size_t q, typename T, template <typename, typename> typename comparator = less_equal_t>
    using sort_subrange_t = typeof_t<sort_subrange<p, q, T, comparator>>;

    template <size_t p, size_t q, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct partition_subrange
    {
        using next = type_if<p != 0, nth_element<p, T, comparator>, std::type_identity<T>>;
        using type = type_if<q != sizeof_t_v<T>, nth_element<q, next, comparator>, std::type_identity<next>>;
    };

    template <size_t p, size_t q, typename T, template <typename, typename> typename comparator = less_equal_t>
    using partition_subrange_t = typeof_t<partition_subrange<p, q, T, comparator>>;

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct select
    {
        using pivot = nth_pivot_t<n, T, comparator>;
        using type = element_t<typev<pivot>, typeof_t<pivot>>;
    };

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal_t>
    using select_t = typeof_t<select<n, T, comparator>>;

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal_t>
    inline constexpr auto select_v = typev<select_t<n, T, comparator>>;

    template <typename T, auto N = 0>
    struct normalize
    {
        template <typename U, bool B>
        struct impl
        {
            static constexpr auto value = 0;
            using type = U;
        };

        template <typename U>
        struct impl<U, false>
        {
            static constexpr auto delta = min_element_v<U>;
            static constexpr auto value = delta < 0 ? -delta : 0;

            using type = type_if<value || N, increase<U, N == 0 ? value : -N>, std::type_identity<U>>;
        };

        using call = impl<T, is_tuple_v<T>>;

        using type = typeof_t<call>;
        static constexpr auto value = typev<call>;
    };

    template <typename T, auto N = 0>
    using normalize_t = typeof_t<normalize<T, N>>;

    template <typename T, auto N = 0>
    inline constexpr auto normalize_v = typev<normalize<T, N>>;

    template <template <typename, template <typename, typename> typename> typename sort,
    typename T, template <typename, typename> typename comparator = less_t>
    using sort_t = typeof_t<sort<T, comparator>>;

    template <typename T, typename U, template <typename> typename... sort>
    inline constexpr auto sort_v = (std::is_same_v<typeof_t<sort<T>>, U> && ...);

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    struct select_sort
    {
        template <int i, int j, typename U>
        struct impl : impl<i + 1, j, append_t<U, select_t<i, T, comparator>>>
        {
        };

        template <int j, typename U>
        struct impl<j, j, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<1, sizeof_t_v<T> + 1, base_type_t<T>>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    using select_sort_t = sort_t<select_sort, T, comparator>;

    template <typename T>
    struct rank_sort;

    template <typename T, T... values>
    struct rank_sort<std::integer_sequence<T, values...>>
    {
        template <bool B, T value>
        static constexpr auto rank()
        {
            return ((B ? value > values : value == values) + ...);
        }

        template <size_t k>
        static constexpr auto nth()
        {
            T t{};
            size_t n = 0;
            ((n = rank<1, values>(), k >= n && k < n + rank<0, values>() ? t = values : T()), ...);

            return t;
        }

        using type = decltype([]<size_t... indices>(const std::index_sequence<indices...>&)
                     {
                         return std::integer_sequence<T, nth<indices>()...>();
                     }(std::make_index_sequence<sizeof...(values)>()));
    };

    template <typename T>
    using rank_sort_t = typeof_t<rank_sort<T>>;

    template <size_t key, typename T>
    struct field
    {
        T value;
    };

    template <typename... Args>
    struct mapping : Args...
    {
    };

    template <typename T>
    struct map_sort;

    template <typename... Args>
    struct map_sort<std::tuple<Args...>>
    {
        template <size_t key, typename value>
        static constexpr decltype(auto) get(const identity<key, value>& id)
        {
            return id;
        }

        template <typename indices, typename... args>
        struct impl;

        template <size_t... indices, typename... args>
        struct impl<std::index_sequence<indices...>, args...>
        {
            template <typename T>
            static constexpr auto value()
            {
                return sizeof(T::value);
            }

            template <size_t k, typename T>
            static constexpr auto rankof()
            {
                auto n = value<T>();
                return ((n > value<args>()) + ...) + ((n == value<args>() && indices < k) + ...);
            }

            static constexpr auto sort()
            {
                using ranking = mapping<identity<rankof<indices, args>(), args>...>;
                return std::tuple<typeof_t<std::decay_t<decltype(get<indices>(std::declval<ranking>()))>>...>{};
            }
        };

        using index = std::index_sequence_for<Args...>;

        using type = decltype(
                     []<size_t... indices, typename... args>(const std::tuple<field<indices, args>...>&)
                     {
                         return std::tuple<args...>{};
                     }
                     ([]<typename... args>(const std::tuple<args...>&)
                     {
                         return impl<index, args...>::sort();
                     }
                     ([]<size_t... indices>(std::index_sequence<indices...>)
                     {
                         return std::tuple<field<indices, Args>...>{};
                     }(index{})
                     )));

    };

    template <typename T>
    using map_sort_t = typeof_t<map_sort<T>>;

    template <typename T, template <typename, typename> typename comparator = less_t, int exp = 0, int base = 0>
    struct counting_sort
    {
        using call = normalize_t<T>;

        static constexpr auto N = sizeof_t_v<T>;
        static constexpr auto k = sizeof_t_v<max_element_t<call>>;

        static constexpr int p = exp ? exp : 1;
        static constexpr int q = base ? base : power_v<10, digit_v<k>>;

        using C = value_sequence_t<size_t, k + 1>;
        using B = fill_t<N, std::conditional_t<is_tuple_v<call>, int, c_0>>;

        template <size_t i, typename V, bool = true>
        struct count : inc<element_size_v<i, call> / p % q, V>
        {
        };

        template <size_t i, typename V>
        struct count<i, V, false> : sub<i + 1, get_v<i, V> + get_v<i + 1, V>, V>
        {
        };

        template <size_t i, size_t j, bool b, typename V>
        struct assign : assign<i + 1, j, b, typeof_t<count<i, V, b>>>
        {
        };

        template <size_t j, bool b, typename V>
        struct assign<j, j, b, V> : std::type_identity<V>
        {
        };

        template <size_t i, typename V, typename W>
        struct sort
        {
            using X = element_t<i - 1, call>;

            static constexpr auto n = sizeof_t_v<X> / p % q;
            static constexpr auto m = get_v<n, V> - 1;

            using type = typeof_t<sort<i - 1, sub_t<n, m, V>, exchange_t<m, X, W>>>;
        };

        template <typename V, typename W>
        struct sort<0, V, W> : std::type_identity<W>
        {
        };

        using impl = sort<N, typeof_t<assign<0, k, 0, typeof_t<assign<0, N, 1, C>>>>, B>;
        using type = normalize_t<typeof_t<impl>, normalize_v<T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using counting_sort_t = sort_t<counting_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct radix_sort
    {
        using call = normalize_t<T>;
        static constexpr auto k = sizeof_t_v<max_element_t<call>>;

        template <int exp, typename U, bool = (k / exp > 0)>
        struct impl : impl<exp * 10, typeof_t<counting_sort<U, less_t, exp, 10>>>
        {
        };

        template <int exp, typename U>
        struct impl<exp, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<1, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using radix_sort_t = sort_t<radix_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct stooge_sort
    {
        template <size_t i, size_t j, typename U, bool = (i + 1 < j)>
        struct sort
        {
            static constexpr auto k = (j - i + 1) / 3;

            using curr = typeof_t<sort<i, j, U, false>>;
            using prev = typeof_t<sort<i, j - k, curr>>;

            using next = typeof_t<sort<i + k, j, prev>>;
            using type = typeof_t<sort<i, j - k, next>>;
        };

        template <size_t i, size_t j, typename U>
        struct sort<i, j, U, false>
        {
            static constexpr auto value = compare_v<j, i, U, comparator>;
            using type = swap_if_t<value, i, j, U>;
        };

        using type = typeof_t<sort<0, sizeof_t_v<T> - 1, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using stooge_sort_t = sort_t<stooge_sort, T, comparator>;

    template <typename T, typename U, auto m = sizeof_t_v<T> + 1, auto n = sizeof_t_v<U> + 1>
    struct edit_distance
    {
        static constexpr auto B = is_tuple_v<T>;

        template <size_t i, size_t j, size_t k, typename V, bool>
        struct next
        {
            template <typename W, bool>
            struct impl
            {
                using type = sub_t<k, get_v<k - n - 1, W>, W>;
            };

            template <typename W>
            struct impl<W, false>
            {
                static constexpr auto value = min_v<get_v<k - 1, W>, get_v<k - n, W>>;
                using type = sub_t<k, 1 + min_v<value, get_v<k - n - 1, W>>, W>;
            };

            using type = typeof_t<impl<V, is_same_v<i - 1, j - 1, T, U>>>;
        };

        template <size_t i, size_t j, size_t k, typename V>
        struct next<i, j, k, V, false>
        {
            using type = sub_t<k, i == 0 ? j : i, V>;
        };

        template <size_t i, size_t j, size_t k, size_t l, typename V>
        struct impl
        {
            static constexpr auto N = i * j;

            using cond = typeof_t<next<i, j, i * n + j, V, N>>;
            using type = typeof_t<impl<i, j + 1, k, l, cond>>;
        };

        template <size_t i, size_t k, size_t l, typename V>
        struct impl<i, l, k, l, V> : impl<i + 1, 0, k, l, V>
        {
        };

        template <size_t k, size_t l, typename V>
        struct impl<k, 0, k, l, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<impl<0, 0, m, n, fill_c<m * n, 0>>>;
        static constexpr auto value = get_v<m * n - 1, type>;
    };

    template <typename T, typename U>
    inline constexpr auto edit_distance_v = typev<edit_distance<T, U>>;

    template <int p, int q, int m = p + 1, int n = q + 1>
    struct binomial_coeff
    {
        template <int k, typename T, bool>
        struct next : sub<k, 1, T>
        {
        };

        template <int k, typename T>
        struct next<k, T, false> : sub<k, get_v<k - n - 1, T> + get_v<k - n, T>, T>
        {
        };

        template <int i, int j, int k, int l, typename T>
        struct impl
        {
            using cond = typeof_t<next<i * n + j, T, j == 0 || j == i>>;
            using type = typeof_t<impl<i, j + 1, k, min_v<i, n - 1> + 1, cond>>;
        };

        template <int i, int k, int l, typename T>
        struct impl<i, l, k, l, T> : impl<i + 1, 0, k, l, T>
        {
        };

        template <int k, int l, typename T>
        struct impl<k, 0, k, l, T> : std::type_identity<T>
        {
        };

        using type = typeof_t<impl<0, 0, m, min_v<0, n - 1> + 1, fill_c<m * n, 0>>>;
        static constexpr auto value = get_v<m * n - 1, type>;
    };

    template <int p, int q>
    inline constexpr auto binomial_coeff_v = typev<binomial_coeff<p, q>>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct bubble_sort
    {
        template <size_t i, size_t j, size_t k, typename U>
        struct sort
        {
            static constexpr auto value = compare_v<j, j - 1, U, comparator>;
            using cond = swap_if_t<value, j, j - 1, U>;

            using type = typeof_t<sort<i, j - 1, k, cond>>;
        };

        template <size_t i, size_t k, typename U>
        struct sort<i, i, k, U> : sort<i + 1, k, k, U>
        {
        };

        template <size_t k, typename U>
        struct sort<k, k, k, U> : std::type_identity<U>
        {
        };

        static constexpr auto N = sizeof_t_v<T>;
        using type = typeof_t<sort<0, N - 1, N - 1, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using bubble_sort_t = sort_t<bubble_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct shaker_sort
    {
        template <int i, int j, int k, typename U, bool B>
        struct next
        {
            static constexpr auto value = compare_v<i + 1, i, U, comparator>;

            using cond = swap_if_t<value, i, i + 1, U>;
            using type = typeof_t<next<i + k, j, k, cond, B || value>>;
        };

        template <int j, int k, typename U, bool B>
        struct next<j, j, k, U, B> : std::type_identity<index_type<B, U>>
        {
        };

        template <int i, int j, typename U, bool B>
        struct sort
        {
            using call = typeof_t<next<i, j, 1, U, false>>;

            template <typename V, bool>
            struct impl
            {
                using curr = typeof_t<next<j - 2, i - 1, -1, V, false>>;
                using type = typeof_t<sort<i + 1, j - 1, typeof_t<curr>, typev<curr>>>;
            };

            template <typename V>
            struct impl<V, false> : std::type_identity<V>
            {
            };

            using type = typeof_t<impl<typeof_t<call>, typev<call>>>;
        };

        template <int i, int j, typename U>
        struct sort<i, j, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<0, sizeof_t_v<T> - 1, T, true>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using shaker_sort_t = sort_t<shaker_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct oddeven_sort
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <int i, typename U, bool B, bool = i <= N - 2>
        struct next
        {
            static constexpr auto value = compare_v<i + 1, i, U, comparator>;

            using cond = swap_if_t<value, i, i + 1, U>;
            using type = typeof_t<next<i + 2, cond, B || value>>;
        };

        template <int i, typename U, bool B>
        struct next<i, U, B, false> : std::type_identity<index_type<B, U>>
        {
        };

        template <typename U, bool B>
        struct sort
        {
            template <typename V, bool>
            struct impl
            {
                using call = typeof_t<next<1, V, false>>;
                using curr = typeof_t<next<0, typeof_t<call>, typev<call>>>;

                using type = typeof_t<sort<typeof_t<curr>, typev<curr>>>;
            };

            template <typename V>
            struct impl<V, false>
            {
                using type = typeof_t<type_if<N == 2, next<0, V, false>, index_upper<1, V>>>;
            };

            using type = typeof_t<impl<U, (N > 2)>>;
        };

        template <typename U>
        struct sort<U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<T, true>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using oddeven_sort_t = sort_t<oddeven_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    struct gnome_sort
    {
        template <int i, int j, typename U>
        struct sort
        {
            static constexpr auto value = compare_v<i - 1, i, U, comparator>;
            using next = swap_if_t<!value, i - 1, i, U>;

            using type = typeof_t<sort<value ? i + 1 : i == 1 ? i : i - 1, j, next>>;
        };

        template <int j, typename U>
        struct sort<j, j, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<1, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    using gnome_sort_t = sort_t<gnome_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct selection_sort
    {
        template <size_t i, size_t j, size_t k, typename U>
        struct sort
        {
            static constexpr auto value = compare_v<j, i, U, comparator>;
            using cond = swap_if_t<value, i, j, U>;

            using type = typeof_t<sort<i, j + 1, k, cond>>;
        };

        template <size_t i, size_t k, typename U>
        struct sort<i, k, k, U> : sort<i + 1, i + 2, k, U>
        {
        };

        template <size_t j, size_t k, typename U>
        struct sort<k, j, k, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<0, 1, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using selection_sort_t = sort_t<selection_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    struct quick_sort
    {
        template <int p, int r, typename U, bool = (p < r)>
        struct sort
        {
            using pivot = randomized_partition_t<p, r, U, comparator>;
            using left = typeof_t<sort<p, typev<pivot>, typeof_t<pivot>>>;

            using type = typeof_t<sort<typev<pivot> + 1, r, left>>;
        };

        template <int p, int r, typename U>
        struct sort<p, r, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<0, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    using quick_sort_t = sort_t<quick_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    struct quick_sort_iterative
    {
        template <bool B, typename U, int p, int r>
        using cond = type_if<B, prepend<U, c_<p>, c_<r>>, std::type_identity<U>>;

        template <int i, typename U, typename V>
        struct sort
        {
            static constexpr auto p = get_v<0, U>;
            static constexpr auto r = get_v<1, U>;

            using pivot = randomized_partition_t<p, r, V, comparator>;
            static constexpr int value = typev<pivot>;

            static constexpr auto B1 = value - 1 > p;
            static constexpr auto B2 = value + 1 < r - 1;

            using curr = pop_front_t<pop_front_t<U>>;
            using call = cond<B2, cond<B1, curr, p, value>, value + 1, r>;

            using type = typeof_t<sort<i + (B1 + B2 - 1) * 2, call, typeof_t<pivot>>>;
        };

        template <typename U, typename V>
        struct sort<-1, U, V> : std::type_identity<V>
        {
        };

        using type = typeof_t<sort<1, std::integer_sequence<int, 0, sizeof_t_v<T>>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    using quick_sort_iterative_t = sort_t<quick_sort_iterative, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    struct stable_sort
    {
        template <int p, int r, typename U, bool = (p < r)>
        struct sort
        {
            using pivot = randomized_stable_partition_t<p, r, U, comparator>;
            using left = typeof_t<sort<p, typev<pivot> - 1, typeof_t<pivot>>>;

            using type = typeof_t<sort<typev<pivot>, r, left>>;
        };

        template <int p, int r, typename U>
        struct sort<p, r, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<0, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    using stable_sort_t = sort_t<stable_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    struct sort_index
    {
        using type = to_map_t<stable_sort_t<to_map_t<T>, comparator>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    using sort_index_t = sort_t<sort_index, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct insert_sort
    {
        template <int i, int j, int k, typename U>
        struct sort
        {
            using curr = element_t<j, U>;
            static constexpr auto n = upper_bound_v<curr, U, i, j, comparator>;

            using type = typeof_t<sort<i, j + 1, k, rotate_t<n, j, j + 1, U>>>;
        };

        template <int i, int k, typename U>
        struct sort<i, k, k, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<0, 1, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using insert_sort_t = sort_t<insert_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct insertion_sort
    {
        template <size_t i, size_t j, size_t k, typename U, typename V>
        struct sort
        {
            using prev = element_t<j - 1, U>;

            template <typename W, bool B>
            struct next
            {
                using type = sort<i, j - 1, k, exchange_t<j, prev, W>, V>;
            };

            template <typename W>
            struct next<W, false>
            {
                using cond = element_if_t<i + 1 != k, i + 1, W, std::type_identity<W>>;
                using type = sort<i + 1, i + 1, k, exchange_t<j, V, W>, cond>;
            };

            using type = typeof_t<typeof_t<next<U, typev<comparator<V, prev>>>>>;
        };

        template <size_t i, size_t k, typename U, typename V>
        struct sort<i, 0, k, U, V>
        {
            using type = typeof_t<sort<i + 1, i + 1, k, exchange_t<0, V, U>, element_t<i + 1 == k ? i : i + 1, U>>>;
        };

        template <size_t k, typename U, typename V>
        struct sort<k, k, k, U, V> : std::type_identity<U>
        {
        };

        static constexpr auto N = sizeof_t_v<T>;
        using type = typeof_t<sort<1, 1, N, T, element_t<(N > 1), T>>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using insertion_sort_t = sort_t<insertion_sort, T, comparator>;

    template <size_t p, size_t q, size_t r, typename T, template <typename, typename> typename comparator = less_equal_t>
    struct merge
    {
        using max = max_element_t<T>;

        template <auto i, auto j, typename U>
        using split = append_t<expand_t<element, U, index_sequence_of_c<i>, j>, max>;

        using left = split<q - p + 1, p, T>;
        using right = split<r - q, q + 1, T>;

        template <size_t i, size_t j, size_t k, size_t l, typename U, bool = k <= l>
        struct assign
        {
            using first = element_t<i, left>;
            using second = element_t<j, right>;

            static constexpr auto value = typev<comparator<first, second>>;
            using swap = exchange_t<k, std::conditional_t<value, first, second>, U>;

            using type = typeof_t<assign<i + value, j + !value, k + 1, l, swap>>;
        };

        template <size_t i, size_t j, size_t k, size_t l, typename U>
        struct assign<i, j, k, l, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<assign<0, 0, p, r, T>>;
    };

    template <size_t p, size_t q, size_t r, typename T, template <typename, typename> typename comparator = less_equal_t>
    using merge_t = typeof_t<merge<p, q, r, T, comparator>>;

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    struct merge_sort
    {
        template <size_t p, size_t r, typename U, bool = (p < r)>
        struct sort
        {
            static constexpr auto q = (p + r) / 2;

            using left = typeof_t<sort<p, q, U>>;
            using right = typeof_t<sort<q + 1, r, left>>;

            using type = merge_t<p, q, r, right, comparator>;
        };

        template <size_t p, size_t r, typename U>
        struct sort<p, r, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<0, sizeof_t_v<T> - 1, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal_t>
    using merge_sort_t = sort_t<merge_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct strand_sort
    {
        using base = base_type_t<T>;

        template <int i, int j, int k, typename U, typename V>
        struct next
        {
            using curr = element_t<i, V>;
            static constexpr auto value = typev<comparator<back_t<U>, curr>>;

            using lhs = append_if_t<value, U, curr>;
            using rhs = type_if<value, drop<i, V>, std::type_identity<V>>;

            using type = typeof_t<next<i + !value, j + 1, k, lhs, rhs>>;
        };

        template <int i, int k, typename U, typename V>
        struct next<i, k, k, U, V>
        {
            using type = pair_t<U, V>;
        };

        template <typename U, typename V, auto N = sizeof_t_v<U>, bool = N != 0>
        struct sort
        {
            static constexpr auto n = sizeof_t_v<V>;

            using call = typeof_t<next<0, 0, N - 1, append_t<base, front_t<U>>, pop_front_t<U>>>;
            using first = first_t<call>;

            using curr = concat_t<V, first>;
            using dest = merge<0, n - 1, sizeof_t_v<curr> - 1, curr, less_equal_t>;

            using cond = type_if<!n, std::type_identity<first>, dest>;
            using type = typeof_t<sort<second_t<call>, cond>>;
        };

        template <typename U, typename V, auto N>
        struct sort<U, V, N, false> : std::type_identity<V>
        {
        };

        using type = typeof_t<sort<T, base>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using strand_sort_t = sort_t<strand_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct heap_sort
    {
        static constexpr auto N = sizeof_t_v<T> - 1;

        template <int i, int j, typename U, bool = true>
        struct max_heapify
        {
            static constexpr auto l = 2 * i + 1;
            static constexpr auto r = 2 * (i + 1);

            static constexpr auto k = compare_v<i, l <= j ? l : i, U, comparator> ? l : i;
            static constexpr auto m = compare_v<k, r <= j ? r : k, U, comparator> ? r : k;

            using type = typeof_t<max_heapify<m, j, swap_t<i, m, U>, m != i>>;
        };

        template <int i, int j, typename U>
        struct max_heapify<i, j, U, false> : std::type_identity<U>
        {
        };

        template <int i, typename U, bool = (i >= 0)>
        struct build_max_heap : build_max_heap<i - 1, typeof_t<max_heapify<i, N, U>>>
        {
        };

        template <int i, typename U>
        struct build_max_heap<i, U, false> : std::type_identity<U>
        {
        };

        template <int i, typename U, bool = (i >= 1)>
        struct sort : sort<i - 1, typeof_t<max_heapify<0, i - 1, swap_t<i, 0, U>>>>
        {
        };

        template <int i, typename U>
        struct sort<i, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<sort<N, typeof_t<build_max_heap<N / 2, T>>>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using heap_sort_t = sort_t<heap_sort, T, comparator>;

    template <auto N, typename T>
    struct sort_row : quick_sort<get_matrix_row_t<N, T>>
    {
    };

    template <auto N, typename T>
    using sort_row_t = typeof_t<sort_row<N, T>>;

    template <auto N, typename T>
    struct sort_col : quick_sort<get_matrix_col_t<N, T>>
    {
    };

    template <auto N, typename T>
    using sort_col_t = typeof_t<sort_col<N, T>>;

    template <auto N, typename T>
    struct matrix_row_sort : set_matrix_row<N, sort_row_t<N, T>, T>
    {
    };

    template <auto N, typename T>
    using matrix_row_sort_t = typeof_t<matrix_row_sort<N, T>>;

    template <auto N, typename T>
    struct matrix_col_sort : set_matrix_col<N, sort_col_t<N, T>, T>
    {
    };

    template <auto N, typename T>
    using matrix_col_sort_t = typeof_t<matrix_col_sort<N, T>>;

    template <auto lower, auto upper, typename T>
    struct matrix_row_sort_range : matrix_range_operator<lower, upper, T, matrix_row_sort>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_row_sort_range_t = typeof_t<matrix_row_sort_range<lower, upper, T>>;

    template <auto lower, auto upper, typename T>
    struct matrix_col_sort_range : matrix_range_operator<lower, upper, T, matrix_col_sort>
    {
    };

    template <auto lower, auto upper, typename T>
    using matrix_col_sort_range_t = typeof_t<matrix_col_sort_range<lower, upper, T>>;

    template <typename T>
    struct matrix_rowwise_sort : matrix_row_sort_range<0, matrix_row_size_v<T>, T>
    {
    };

    template <typename T>
    using matrix_rowwise_sort_t = typeof_t<matrix_rowwise_sort<T>>;

    template <typename T>
    struct matrix_colwise_sort : matrix_col_sort_range<0, matrix_col_size_v<T>, T>
    {
    };

    template <typename T>
    using matrix_colwise_sort_t = typeof_t<matrix_colwise_sort<T>>;

    template <typename T>
    struct matrix_row_col_sort : matrix_colwise_sort<matrix_rowwise_sort_t<T>>
    {
    };

    template <typename T>
    using matrix_row_col_sort_t = typeof_t<matrix_row_col_sort<T>>;

    template <typename T>
    struct matrix_col_row_sort : matrix_rowwise_sort<matrix_colwise_sort_t<T>>
    {
    };

    template <typename T>
    using matrix_col_row_sort_t = typeof_t<matrix_col_row_sort<T>>;

    template <typename P, typename T>
    struct kmp
    {
        static constexpr auto N = sizeof_t_v<P>;
        static constexpr auto value = is_tuple_v<P>;

        template <typename U, typename V, typename W, int k, int q>
        struct next
        {
            using nega = std::negation<is_same<k, q, U, V>>;
            using cond = std::conditional_t<0 < k, nega, std::false_type>;

            using curr = conditional_of<cond, get<k, W>, c_<k>>;
            using type = type_if<typev<cond>, next<U, V, W, typev<curr>, q>, c_<k>>;
        };

        template <bool B, typename U, typename V, typename W, int k, int q, int p>
        struct impl
        {
            using lhs = std::conditional_t<B, U, V>;
            using rhs = std::conditional_t<B, V, T>;

            static constexpr auto m = typev<typeof_t<next<lhs, rhs, W, k, q>>>;
            static constexpr int n = m + is_same_v<m, q, lhs, rhs>;

            using curr = append_if_t<!B && n == N, U, c_<q - N + 1>>;
            using dest = type_if<B, sub<q, n, W>, std::type_identity<W>>;

            using type = typeof_t<impl<B, curr, V, dest, value_if<!B && n == N, get<n - 1, W>, c_<n>>, q + 1, p>>;
        };

        template <bool B, typename U, typename V, typename W, int k, int p>
        struct impl<B, U, V, W, k, p, p>
        {
            using type = std::conditional_t<B, W, U>;
        };

        using call = typeof_t<impl<1, P, P, fill_c<N, 0>, 0, 1, N>>;
        using type = typeof_t<impl<0, std::index_sequence<>, P, call, 0, 0, sizeof_t_v<T>>>;
    };

    template <typename P, typename T>
    using kmp_t = typeof_t<kmp<P, T>>;

    template <typename T, auto N>
    struct offset
    {
        static constexpr auto distance = N;
    };

    template <typename T, typename U>
    struct find_index;

    template <typename T, template <typename ...> typename U, template <typename, auto> typename V, typename... Args, auto... args>
    struct find_index<T, U<V<Args, args>...>>
    {
        static constexpr auto value = index_of<T, U<Args...>>();
    };

    template <typename T, typename U>
    inline constexpr auto find_index_v = typev<find_index<T, U>>;

    template <typename T, typename U>
    struct shift_value
    {
        static constexpr auto index = find_index_v<T, U>;
        static constexpr auto last = index == sizeof_t_v<U>;

        using type = std::conditional_t<last, c_<index>, element<index, U>>;

        template <typename V, bool B>
        struct impl : V
        {
        };

        template <typename V>
        struct impl<V, false> : c_<typeof_t<V>::distance>
        {
        };

        static constexpr auto value = typev<impl<type, last>>;
    };

    template <typename T, typename U>
    inline constexpr auto shift_value_v = typev<shift_value<T, U>>;

    template <typename P, typename T, bool B1, bool B2 = false>
    struct boyer_moore_horspool
    {
        static constexpr auto N = sizeof_t_v<P>;

        template <int i, int j, int k, typename U>
        struct table
        {
            using curr = element_t<i, P>;

            static constexpr auto index = find_index_v<curr, U>;
            static constexpr auto last = index == k;

            using dest = offset<curr, N - i - 1>;
            using next = type_if<last, append<U, dest>, exchange<index, dest, U>>;

            using type = typeof_t<table<i + 1, j, k + last, next>>;
        };

        template <int j, int k, typename U>
        struct table<j, j, k, U> : std::type_identity<U>
        {
        };

        template <int i, int j, typename U>
        struct impl
        {
            using next = ternary_conditional_t<j == 0, B1, append<U, c_<i>>, erase<i, i + N, U>, impl<i, j - 1, U>>;
            using type = type_if<is_same_v<j, i + j, P, std::conditional_t<B1, T, U>>, next, std::type_identity<U>>;
        };

        using maps = typeof_t<table<N != 1, N - 1, 1, tuple_t<offset<element_t<0, P>, N - 1>>>>;

        template <int i, int j, typename U, bool = i <= j>
        struct search
        {
            using curr = typeof_t<impl<i, N - 1, U>>;
            using dest = element_if_t<N != 1, N + i - 1, std::conditional_t<B1, T, U>, U>;

            using next = std::conditional_t<N == 1, c_1, shift_value<dest, maps>>;

            static constexpr auto lhs = B1 && greater_v<curr, U>;
            static constexpr auto rhs = !B1 && greater_v<U, curr>;

            using cond = ternary_conditional_t<!lhs, rhs, c_0, next, c_1>;
            using type = type_if<(lhs || rhs) && B2, std::type_identity<curr>, search<i + typev<cond>, j - rhs * N, curr>>;
        };

        template <int i, int j, typename U>
        struct search<i, j, U, false> : std::type_identity<U>
        {
        };

        using type = typeof_t<search<0, sizeof_t_v<T> - N, std::conditional_t<!B1, T, std::index_sequence<>>>>;
    };

    template <typename P, typename T, bool B1, bool B2 = false>
    using boyer_moore_horspool_t = typeof_t<boyer_moore_horspool<P, T, B1, B2>>;

    template <typename P, typename T>
    using bmh = boyer_moore_horspool<P, T, true>;

    template <typename P, typename T>
    using bmh_t = typeof_t<bmh<P, T>>;

    template <typename P, typename T>
    using subtype_indices = bmh<P, T>;

    template <typename P, typename T>
    using subtype_indices_t = typeof_t<subtype_indices<P, T>>;

    template <typename P, typename T>
    using erase_subtype = boyer_moore_horspool<P, T, false>;

    template <typename P, typename T>
    using erase_subtype_t = typeof_t<erase_subtype<P, T>>;

    template <typename P, typename T>
    struct first_subtype_index : boyer_moore_horspool<P, T, true, true>
    {
    };

    template <typename P, typename T>
    using first_subtype_index_t = typeof_t<first_subtype_index<P, T>>;

    template <typename P, typename T>
    struct contains_subtype : bool_<sizeof_t_v<first_subtype_index_t<P, T>> == 1>
    {
    };

    template <typename P, typename T>
    using contains_subtype_t = typeof_t<contains_subtype<P, T>>;

    template <typename P, typename T>
    inline constexpr auto contains_subtype_v = typev<contains_subtype_t<P, T>>;

    template <typename P, typename T>
    struct eliminate_subtype
    {
        static constexpr auto N = sizeof_t_v<P>;

        template <int i, typename U, typename V>
        struct impl;

        template <int i, auto j, auto... n, typename V>
        struct impl<i, std::index_sequence<j, n...>, V>
        {
            static constexpr auto k = j - i * N;
            using type = typeof_t<impl<i + 1, std::index_sequence<n...>, erase_t<k, k + N, V>>>;
        };

        template <int i, typename U>
        struct impl<i, std::index_sequence<>, U> : std::type_identity<U>
        {
        };

        using type = typeof_t<impl<0, bmh_t<P, T>, T>>;
    };

    template <typename P, typename T>
    using eliminate_subtype_t = typeof_t<eliminate_subtype<P, T>>;

    template <typename P, typename U, typename T>
    struct replace_subtype
    {
        static constexpr auto M = sizeof_t_v<P>;
        static constexpr auto N = sizeof_t_v<U>;

        template <int i, typename V, typename W>
        struct impl;

        template <int i, auto j, auto... n, typename W>
        struct impl<i, std::index_sequence<j, n...>, W>
        {
            static constexpr auto k = j + i * (N - M);

            using next = insert_range_t<k, erase_t<k, k + M, W>, U>;
            using type = typeof_t<impl<i + 1, std::index_sequence<n...>, next>>;
        };

        template <int i, typename W>
        struct impl<i, std::index_sequence<>, W> : std::type_identity<W>
        {
        };

        using type = typeof_t<impl<0, bmh_t<P, T>, T>>;
    };

    template <typename P, typename U, typename T>
    using replace_subtype_t = typeof_t<replace_subtype<P, U, T>>;

    template <typename P, typename T, template <typename, typename> typename searcher = bmh>
    struct number_of
    {
        static constexpr auto value = sizeof_t_v<typeof_t<searcher<P, T>>>;
    };

    template <typename P, typename T, template <typename, typename> typename searcher = bmh>
    inline constexpr auto number_of_v = typev<number_of<P, T, searcher>>;

    template <typename T, bool B1, bool B2, bool B3 = false>
    struct arrange
    {
        using uniq = unique_t<T>;
        using base = base_type_t<T>;

        template <bool B, bool only, typename U, typename V>
        struct call
        {
            using type = type_if<B2 && only, U, V>;
        };

        template <bool only, typename U, typename V>
        struct call<false, only, U, V> : std::conditional<only == !B2, U, V>
        {
        };

        template <auto N, typename U>
        struct impl
        {
            using curr = element_t<N, U>;
            using next = append_t<base, curr>;

            static constexpr auto size = number_of_v<next, T>;
            static constexpr auto only = size == 1;

            using lhs = std::conditional_t<B1, std::type_identity<base>, next>;
            using rhs = std::conditional_t<B1, fill<size, curr>, base>;

            using type = typeof_t<call<B1, only, lhs, rhs>>;
        };

        using curr = expand_t<impl, uniq, index_sequence_of_t<uniq>>;
        using type = type_if<B3, unpack<tuple_t, curr>, unpack<concat_t, curr>>;
    };

    template <typename T, bool B1, bool B2, bool B3 = false>
    using arrange_t = typeof_t<arrange<T, B1, B2, B3>>;

    template <typename T>
    struct group : arrange<T, true, false, true>
    {
    };

    template <typename T>
    using group_t = typeof_t<group<T>>;

    template <typename T, typename U, template <typename ...> typename F = std::is_same, bool B = false>
    requires is_group_v<U>
    struct find_group
    {
        template <int i, int j>
        struct impl
        {
            using curr = element_t<i, U>;
            using func = bind_front_if<!B, F, T>;

            static constexpr auto n = find_if_v<func::template apply, curr>;
            static constexpr auto found = type_if_v<B, call<func, T>, std::false_type>;

            static constexpr auto value = n != sizeof_t_v<curr> && (!B || found);
            using type = type_if<value, std::type_identity<triple<i, n, curr>>, impl<i + 1, j>>;
        };

        template <int j>
        struct impl<j, j> : std::type_identity<triple<j, j, U>>
        {
        };

        using type = typeof_t<impl<0, sizeof_t_v<U>>>;
    };

    template <typename T, typename U, template <typename ...> typename F = std::is_same, bool B = false>
    using find_group_t = typeof_t<find_group<T, U, F, B>>;

    template <template <typename ...> typename F, typename T, typename U>
    struct find_group_if : find_group<T, U, F, 1>
    {
    };

    template <template <typename ...> typename F, typename T, typename U>
    using find_group_if_t = typeof_t<find_group_if<F, T, U>>;

    template <typename T>
    struct adjacent : arrange<T, true, false>
    {
    };

    template <typename T>
    using adjacent_t = typeof_t<adjacent<T>>;

    template <typename T>
    struct remove_unique : arrange<T, true, true>
    {
    };

    template <typename T>
    using remove_unique_t = typeof_t<remove_unique<T>>;

    template <typename T>
    struct remove_duplicate : arrange<T, false, false>
    {
    };

    template <typename T>
    using remove_duplicate_t = typeof_t<remove_duplicate<T>>;

    template <typename T>
    struct unique_elements : remove_duplicate<T>
    {
    };

    template <typename T>
    using unique_elements_t = typeof_t<unique_elements<T>>;

    template <typename T>
    struct duplicate_elements : arrange<T, false, true>
    {
    };

    template <typename T>
    using duplicate_elements_t = typeof_t<duplicate_elements<T>>;

    template <typename... Args>
    requires is_variadic_pack_v<Args...>
    struct intersect
    {
        template <typename... args>
        struct impl;

        template <typename T>
        struct impl<T> : std::type_identity<T>
        {
        };

        template <typename T, typename U, typename... args>
        struct impl<T, U, args...> : impl<duplicate_elements_t<concat_t<unique_t<T>, unique_t<U>>>, args...>
        {
        };

        using type = typeof_t<impl<Args...>>;
    };

    template <typename... Args>
    using intersect_t = typeof_t<intersect<Args...>>;

    template <int n = 3>
    struct hanoi
    {
        template <int i, typename pegs, int from, int to, int use, typename T, bool = (i > 0)>
        struct impl
        {
            using prev = typeof_t<impl<i - 1, pegs, from, use, to, T>>;

            using first = first_t<prev>;
            using second = second_t<prev>;

            using last = element_t<from, first>;
            using next = exchange_t<to, prepend_t<element_t<to, first>, get<0, last>>, first>;

            using curr = exchange_t<from, pop_front_t<last>, next>;
            using type = typeof_t<impl<i - 1, curr, use, to, from, append_t<second, c_<from>, c_<to>>>>;
        };

        template <int i, typename pegs, int from, int to, int use, typename T>
        struct impl<i, pegs, from, to, use, T, false>
        {
            using type = pair_t<pegs, T>;
        };

        using base = std::integer_sequence<int>;
        using pegs = tuple_t<integer_sequence_t<int, n, 1, 1>, base, base>;

        using type = second_t<typeof_t<impl<n, pegs, 0, 1, 2, base>>>;
    };

    template <int n = 3>
    using hanoi_t = typeof_t<hanoi<n>>;

    template <typename T, int B = 0, int E = sizeof_t_v<T>>
    struct lis
    {
        template <int i, int j, int k, typename U, bool = i <= j>
        struct search
        {
            static constexpr auto mid = (i + j) / 2;
            static constexpr auto value = less_v<element_t<B + element_v<mid, U>, T>, element_t<B + k, T>>;

            using type = type_if<value, search<mid + 1, j, k, U>, search<i, mid - 1, k, U>>;
        };

        template <int i, int j, int k, typename U>
        struct search<i, j, k, U, false> : c_<i>
        {
        };

        template <int i, int j, typename U, bool>
        struct update : exchange<j, c_<i>, U>
        {
        };

        template <int i, int j, typename U>
        struct update<i, j, U, false>
        {
            using type = exchange_if_t<less_v<element_t<B + i, T>, element_t<B + element_v<j, U>, T>>, j, c_<i>, U>;
        };

        template <int i, int j, int k, typename U, typename V>
        struct impl
        {
            static constexpr auto l = typeof_v<search<1, k, i, V>>;
            using type = typeof_t<impl<i + 1, j, max_v<l, k>, exchange_c<i, element_v<l - 1, V>, U>, typeof_t<update<i, l, V, k < l>>>>; 
        };

        template <int j, int k, typename U, typename V>
        struct impl<j, j, k, U, V> : std::type_identity<triple<k, element_v<k, V>, U>>
        {
        };

        using call = typeof_t<impl<B, E, 0, fill_c<E, 0>, fill_c<E + 1, 0>>>;

        template <int i, int j, typename U>
        struct reconstruct : reconstruct<i - 1, element_v<j, typeof_t<call>>, exchange_t<i, c_<B + j>, U>>
        {
        };

        template <int j, typename U>
        struct reconstruct<0, j, U> : exchange<0, c_<B + j>, U>
        {
        };

        static constexpr auto l = first_v<call>;
        using type = typeof_t<reconstruct<l - 1, second_v<call>, index_sequence_c<l, 0>>>;
    };

    template <typename T, int B = 0, int E = sizeof_t_v<T>>
    using lis_t = typeof_t<lis<T, B, E>>;

    template <int row, int col, auto v = 0>
    using indices_table = fill_t<row, index_sequence_c<col, v>>;

    template <typename T, typename U>
    struct lcs
    {
        static constexpr auto row = sizeof_t_v<T>;
        static constexpr auto col = sizeof_t_v<U>;

        template <int i, int j, typename V, bool>
        struct search : std::type_identity<pair_t<c_0, c_<get_matrix_element_v<i, j, V> + 1>>>
        {
        };

        template <int i, int j, typename V>
        struct search<i, j, V, false>
        {
            using curr = get_matrix_element_t<i, j + 1, V>;
            static constexpr auto value = get_matrix_element_v<i + 1, j, V> <= typev<curr>;

            using type = pair_t<c_<value ? 1 : 2>, type_if<value, curr, get_matrix_element<i + 1, j, V>>>;
        };

        template <int i, int j, int m, int n, typename V, typename W>
        struct next
        {
            using pair = typeof_t<search<i, m, W, is_same_v<i, m, T, U>>>;
            using lhst = set_matrix_element_t<i, m, first_t<pair>, V>;

            using rhst = set_matrix_element_t<i + 1, m + 1, second_t<pair>, W>;
            using type = typeof_t<next<i, j, m + 1, n, lhst, rhst>>;
        };

        template <int i, int j, int n, typename V, typename W>
        struct next<i, j, n, n, V, W> : next<i + 1, j, 0, n, V, W>
        {
        };

        template <int j, int m, int n, typename V, typename W>
        struct next<j, j, m, n, V, W> : std::type_identity<V>
        {
        };

        template <int i, int j, typename V, typename W>
        struct impl
        {
            static constexpr auto value = get_matrix_element_v<i, j, V>;

            using call = prepend_if_t<value == 0, W, element_if_t<value == 0, i, T, std::type_identity<T>>>;
            using type = typeof_t<impl<i - (value < 2), j - (value != 1), V, call>>;
        };

        template <int j, typename V, typename W>
        struct impl<-1, j, V, W> : std::type_identity<W>
        {
        };

        template <int i, typename V, typename W>
        struct impl<i, -1, V, W> : std::type_identity<W>
        {
        };

        using maps = typeof_t<next<0, row, 0, col, indices_table<row, col>, indices_table<row + 1, col + 1>>>;
        using type = typeof_t<impl<row - 1, col - 1, maps, base_type_t<T>>>;
    };

    template <typename T, typename U>
    using lcs_t = typeof_t<lcs<T, U>>;

    template <typename T, bool B = false>
    struct manacker
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <int i, int j, int l, int r, typename U>
        struct odd
        {
            static constexpr auto p = type_if_v<j <= r, get<l + r - j + i, U>, c_0>;
            static constexpr auto q = (j > r ? 0 : min_v<p, r - j + i>) + 1;

            template <int n, bool b>
            struct impl
            {
                static constexpr auto m = n + 1;
                static constexpr auto value = is_same_v<j - n, j + n - i, T, T>;

                using type = type_if<value, impl<m, j + m - i < N && j - m >= 0>, c_<n - 1>>;
            };

            template <int n>
            struct impl<n, false> : c_<n - 1>
            {
            };

            static constexpr auto mid = typeof_v<impl<q, j + q - i < N && j - q >= 0>>;
            static constexpr auto value = j + mid - i > r;

            static constexpr auto lhs = value ? j - mid : l;
            static constexpr auto rhs = value ? j + mid - i : r;

            using type = pair_t<index_type<j, exchange_c<j, mid, U>>, triple<lhs, rhs, pair_v<j - mid, j + mid + !i>>>;
        };

        template <int i, int l, int r, typename U>
        struct even
        {
            template <int p, int q, int m, int n, typename V>
            struct impl
            {
                using call = typeof_t<odd<1, p, m, n, V>>;
                using curr = second_t<call>;

                using maps = typeof_t<first_t<call>>;
                static constexpr auto value = get_v<p, maps> != 0;

                using type = type_if<value, std::type_identity<call>, impl<p + 1, q, first_v<curr>, second_v<curr>, maps>>;
            };

            template <int q, int m, int n, typename V>
            struct impl<q, q, m, n, V>
            {
                using type = pair_t<index_type<q, V>, triple<m, n, pair_v<N, N>>>;
            };

            using type = typeof_t<impl<i, N, l, r, U>>;
        };

        using table = fill_c<N, 0>;

        template <int i, int j, int l, int r, typename U, typename V>
        struct impl
        {
            using call = type_if<i == 0, odd<0, j, l, r, U>, even<j, l, r, U>>;
            using curr = first_t<call>;

            using trip = second_t<call>;
            using part = typeof_t<trip>;

            static constexpr auto lhs = pair_diff<std::conditional_t<B, V, part>>;
            static constexpr auto rhs = pair_diff<part>;

            using rang = range_if_t<!B, first_v<part>, second_v<part>, T>;
            using dest = type_if<B, std::conditional<lhs < rhs, part, V>, append_if<rhs != 0, V, rang>>;

            static constexpr auto value = typev<curr> + 1 == N;

            using maps = type_if<value, std::type_identity<table>, curr>;
            using prev = impl<i + value, 0, 0, -1, maps, dest>;

            using next = impl<i + value, typev<curr> + 1, first_v<trip>, second_v<trip>, maps, dest>;
            using type = type_if<rhs == 0, std::type_identity<dest>, std::conditional_t<value, prev, next>>;
        };

        using type = typeof_t<impl<0, 0, 0, -1, table, std::conditional_t<B, pair_v<0, 0>, std::tuple<>>>>;
    };

    template <typename T, bool B = false>
    using manacker_t = typeof_t<manacker<T, B>>;

    template <typename T>
    struct lps : manacker<T, true>
    {
    };

    template <typename T>
    using lps_t = typeof_t<lps<T>>;

    template <typename T>
    inline constexpr auto lps_v = pair_diff<lps_t<T>>;

    template <typename T>
    struct lcp
    {
        using base = row_type_t<T>;

        template <int i, int j, typename U, typename V, typename W, bool = i < j>
        struct next
        {
            using curr = element_t<i, U>;
            static constexpr auto value = std::is_same_v<curr, element_t<i, V>>;

            using type = type_if<value, next<i + 1, j, U, V, append_if_t<value, W, curr>>, std::type_identity<W>>;
        };

        template <int i, int j, typename U, typename V, typename W>
        struct next<i, j, U, V, W, false> : std::type_identity<W>
        {
        };

        template <int i, int j>
        struct impl
        {
            static constexpr auto m = i + (j - i) / 2;

            using lhs = type_if<i + 1 == m, element<i, T>, impl<i, m>>;
            using rhs = type_if<m + 1 == j, element<m, T>, impl<m, j>>;

            using type = typeof_t<next<0, min_v<sizeof_t_v<lhs>, sizeof_t_v<rhs>>, lhs, rhs, base>>;
        };

        using type = typeof_t<impl<0, sizeof_t_v<T>>>;
    };

    template <typename T>
    using lcp_t = typeof_t<lcp<T>>;

    template <typename T>
    struct lbs
    {
        static constexpr auto N = sizeof_t_v<T>;

        template <int i, int j, int k, int l, typename U>
        struct next
        {
            using lhs = element_t<j, T>;
            using rhs = element_t<i, T>;

            using curr = element_t<j, U>;
            static constexpr auto value = typev<lhs> < typev<rhs> && less_v<element_t<i, U>, curr>;

            using type = typeof_t<next<i, j + l, k, l, exchange_if_t<value, i, curr, U>>>;
        };

        template <int i, int k, int l, typename U>
        struct next<i, i, k, l, U>
        {
            using lhs = element_t<i, U>;
            using rhs = element_t<i, T>;

            using curr = type_if<l == 1, append<lhs, rhs>, prepend<lhs, rhs>>;
            using type = typeof_t<next<i + l, l == 1 ? 0 : N - 1, k, l, exchange_t<i, curr, U>>>;
        };

        template <int j, int k, int l, typename U>
        struct next<k, j, k, l, U> : std::type_identity<U>
        {
        };

        using base = base_type_t<T>;
        using init = fill_t<N - 1, base>;

        template <template <typename ...> typename F, auto M>
        using call = typeof_t<F<init, append_t<base, element_t<M, T>>>>;

        using lis = typeof_t<next<1, 0, N, 1, call<prepend, 0>>>;
        using lds = typeof_t<next<N - 2, N - 1, -1, -1, call<append, N - 1>>>;

        template <int i, int j, int k, int m>
        struct impl
        {
            static constexpr auto sum = element_size_v<i, lis> + element_size_v<i, lds> - 1;
            using type = typeof_t<impl<i + 1, j, (sum > m) ? i : k, max_v<m, sum>>>;
        };

        template <int j, int k, int m>
        struct impl<j, j, k, m>
        {
            using lhs = element_t<k, lis>;
            using rhs = element_t<k, lds>;

            using type = concat_t<range_t<0, sizeof_t_v<lhs> - 1, lhs>, range_t<0, sizeof_t_v<rhs>, rhs>>;
        };

        using type = typeof_t<impl<0, N, 0, 0>>;
    };

    template <typename T>
    using lbs_t = typeof_t<lbs<T>>;
}

#endif
