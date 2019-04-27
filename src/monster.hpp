//
// Copyright (c) 2016-2019 DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Anti 996 License Version 1.0 (Draft).
// (See accompanying file LICENSE.md)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef MONSTER_HPP
#define MONSTER_HPP

#include <tuple>
#include <utility>
#include <functional>

namespace monster
{    
    template <auto N, typename T = decltype(N)>
    using int_ = std::integral_constant<T, N>;

    template <size_t N>
    using index_t = int_<N>;

    template <typename... Args>
    using tuple_t = std::tuple<Args...>;

    template <typename T>
    inline constexpr auto typev = T::value;

    template <typename T>
    inline constexpr auto negav = !typev<T>;

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
    inline constexpr auto typeof_v = typev<typeof<T>>;

    template <typename T, typename = std::void_t<>>
    struct has_value : std::false_type
    {
        using value_type = int;
    };

    template <typename T>
    struct has_value<T, std::void_t<typename T::value_type>> : std::true_type
    {
        using value_type = typename T::value_type;
    };

    template <typename T>
    using has_value_t = typename has_value<T>::value_type;

    template <typename T>
    inline constexpr auto has_value_v = typev<has_value<T>>;

    template <typename T, typename U>
    struct pair_t
    {
        using fst = T;
        using snd = U;
    };

    template <auto p, auto q>
    struct pair_v
    {
        static constexpr auto fst = p;
        static constexpr auto snd = q;
    };

    template <typename T, auto N = 0>
    struct identity
    {
        using type = T;
    };

    template <typename T, auto N = 0>
    using identity_t = typeof_t<identity<T, N>>;

    template <auto N, typename T>
    using identity_n = identity<T, N>;

    template <auto N, typename T>
    struct wrapper : wrapper<N - 1, identity<T>>
    {
    };

    template <typename T>
    struct wrapper<0, T> : identity<T>
    {
    };

    template <auto N, typename T>
    using wrapper_t = typeof_t<wrapper<N, T>>;

    template <auto N, typename T>
    struct index_type : identity<T>
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
    struct last<T> : identity<T>
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

    template <typename... Args>
    struct contains : std::false_type
    {
    };

    template <typename T, typename... Args>
    struct contains<T, Args...> : std::disjunction<std::is_same<T, Args>...>
    {
    };

    template <typename ...>
    inline constexpr auto contains_v = std::false_type{};

    template <typename T, typename... Args>
    inline constexpr auto contains_v<T, Args...> = std::disjunction_v<std::is_same<T, Args>...>;

    template <auto... values>
    struct includes : std::false_type
    {
    };

    template <auto value, auto... values>
    struct includes<value, values...> : std::disjunction<std::bool_constant<value == values>...>
    {
    };

    template <auto ...>
    inline constexpr auto includes_v = std::false_type{};

    template <auto value, auto... values>
    inline constexpr auto includes_v<value, values...> = std::disjunction_v<std::bool_constant<value == values>...>;

    template <typename ...>
    struct is_unique_type : std::true_type
    {
    };

    template <typename T, typename... Args>
    struct is_unique_type<T, Args...> : std::conditional_t<negav<contains<T, Args...>>, is_unique_type<Args...>, std::false_type>
    {
    };

    template <typename ...>
    inline constexpr auto is_unique_type_v = std::true_type{};

    template <typename T, typename... Args>
    inline constexpr auto is_unique_type_v<T, Args...> = negav<contains<T, Args...>> && is_unique_type_v<Args...>;

    template <auto ...>
    struct is_unique_value : std::true_type
    {
    };

    template <auto value, auto... values>
    struct is_unique_value<value, values...> : std::conditional_t<negav<includes<value, values...>>, is_unique_value<values...>, std::false_type>
    {
    };

    template <auto ...>
    inline constexpr auto is_unique_value_v = std::true_type{};

    template <auto value, auto... values>
    inline constexpr auto is_unique_value_v<value, values...> = negav<includes<value, values...>> && is_unique_value_v<values...>;

    template <typename T>
    struct is_unique;

    template <template <typename ...> typename T, typename... Args>
    struct is_unique<T<Args...>>
    {
        using type = is_unique_type<Args...>;
    };

    template <template <typename, auto...> typename T, typename U, auto... values>
    struct is_unique<T<U, values...>>
    {
        using type = is_unique_value<values...>;
    };

    template <typename T>
    using is_unique_t = typeof_t<is_unique<T>>;

    template <typename T>
    inline constexpr auto is_unique_v = typev<is_unique_t<T>>;

    template <typename T>
    struct member_type;

    template <typename T, typename U>
    struct member_type<T U::*>
    {
        using type = T;
    };

    template <typename T>
    using member_type_t = typeof_t<member_type<T>>;

    template <typename T>
    struct is_inheritable : std::bool_constant<std::is_class_v<T> && !std::is_final_v<T>>
    {
    };

    template <typename T>
    inline constexpr auto is_inheritable_v = typev<is_inheritable<T>>;

    template <typename T>
    struct is_instantiable : std::bool_constant<!std::is_abstract_v<T>>
    {
    };

    template <typename T>
    inline constexpr auto is_instantiable_v = typev<is_instantiable<T>>;

    template <typename T>
    struct remove_cvref : std::remove_cv<std::remove_reference<T>>
    {
    };

    template <typename T>
    using remove_cvref_t = typeof_t<remove_cvref<T>>;

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

    template <typename T, typename U>
    using meta_t = typeof_t<std::conditional_t<is_tuple_v<T> || is_sequence_v<T>, U, identity<T>>>;

    template <typename... Args>
    inline constexpr auto sizeof_v = sizeof...(Args);
    
    template <typename T, typename = std::void_t<>>
    struct sizeof_t : index_t<sizeof(T)>
    {
    };

    template <typename T>
    struct sizeof_t<T, std::void_t<decltype(T::value + 1)>> : T
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
    inline constexpr auto sizeof_t_v = typev<sizeof_t<T>>;

    template <auto N>
    using index_sequence_of_v = std::make_index_sequence<N>;

    template <typename T, auto N = 0>
    using index_sequence_of_t = index_sequence_of_v<sizeof_t_v<T> - N>;

    template <typename T, typename U, bool ASC = true, auto p = sizeof_t_v<T>, auto q = sizeof_t_v<U>>
    using less_t = std::bool_constant<ASC ? (p < q) : (p > q)>;

    template <typename T, typename U, bool ASC = true>
    inline constexpr auto less_v = typev<less_t<T, U, ASC>>;

    template <typename T, typename U>
    using less_equal = std::negation<less_t<U, T>>;

    template <typename T>
    struct base_type : identity<T>
    {
    };

    template <template <typename... > typename T, typename... Args>
    struct base_type<T<Args...>> : identity<T<>>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args>
    struct base_type<T<U, Args...>> : identity<T<U>>
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
    struct get<0, T<U, value, values...>> : int_<value, U>
    {
    };

    template <size_t N, template <typename, auto ...> typename T, typename U, auto value, auto... values>
    struct get<N, T<U, value, values...>> : int_<typev<get<N - 1, T<U, values...>>>, U>
    {
    };

    template <auto value, auto... values>
    struct get<0, homogeneous<value, values...>> : int_<value>
    {
    };

    template <size_t N, auto value, auto... values>
    struct get<N, homogeneous<value, values...>> : int_<typev<get<N - 1, homogeneous<values...>>>>
    {
    };

    template <size_t N, typename T>
    inline constexpr auto get_v = typev<get<N, T>>;

    template <typename indices, auto N = 0>
    inline constexpr auto fst_v = get_v<0, indices> + N;

    template <typename T>
    struct sum;

    template <template <typename, auto ...> typename T, typename U, auto value>
    struct sum<T<U, value>> : int_<value, U>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto value, auto... values>
    struct sum<T<U, value, values...>> : int_<value + typev<sum<T<U, values...>>>, U>
    {
    };

    template <auto value>
    struct sum<homogeneous<value>> : int_<value>
    {
    };

    template <auto value, auto... values>
    struct sum<homogeneous<value, values...>> : int_<value + typev<sum<homogeneous<values...>>>>
    {
    };

    template <typename T>
    inline constexpr auto sum_v = typev<sum<T>>;

    template <auto N, typename T>
    using element = std::conditional_t<negav<is_tuple<T>>, get<N, T>, std::tuple_element<N, T>>;

    template <auto N, typename T>
    using element_t = typeof_t<element<N, T>>;

    template <typename T>
    using pred = int_<typev<T> - 1, typename T::value_type>;

    template <typename T>
    using succ = int_<typev<T> + 1, typename T::value_type>;

    template <typename T>
    inline constexpr auto pred_v = typev<pred<T>>;

    template <typename T>
    inline constexpr auto succ_v = typev<succ<T>>;

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
    struct metaf
    {
        template <typename... args>
        using apply = F<Args..., args...>;
    };

    template <template <typename ...> typename F, typename... Args>
    struct bind
    {
        template <typename... args>
        using apply = F<args..., Args...>;
    };

    template <typename F, typename... Args>
    using call = typename F::template apply<Args...>;

    template <typename F, typename... Args>
    using call_t = typeof_t<call<F, Args...>>;

    template <typename F, typename... Args>
    using invoke = call<F, Args...>;

    template <typename F, typename... Args>
    inline constexpr auto invoke_v = typev<invoke<F, Args...>>;

    template <typename F, typename T, typename ...>
    struct fold : identity<T>
    {
    };

    template <typename F, typename T, typename U, typename... Args>
    struct fold<F, T, U, Args...> : fold<F, call_t<F, T, U>, Args...>
    {
    };

    template <typename F, typename... Args>
    using fold_t = typeof_t<fold<F, Args...>>;

    template <template <typename, typename> typename F, typename... Args>
    using folded = fold<metaf<F>, Args...>;

    template <template <typename, typename> typename F, typename... Args>
    using folded_t = typeof_t<folded<F, Args...>>;

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    struct recurse : identity<T<Args...>>
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
    using on_t = call_t<on<metaf<F>, f>, Args...>;

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
        using apply = std::conditional_t<neg, std::negation<F<Args...>>, F<Args...>>;
    };

    template <template <template <typename ...> typename, typename, int, int> typename F>
    struct metaft
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
    using applyf = apply<metaft<F>, U, T, B, E>;

    template <template <template <typename ...> typename, typename, int, int> typename F,
    template <typename ...> typename f, typename T, int B, int E, bool neg = false>
    using applyf_t = typeof_t<applyf<F, f, T, B, E, neg>>;

    template <auto N>
    struct equal
    {
        template <typename T>
        struct apply : std::bool_constant<typev<T> == N>
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
        using apply = int_<B - N>;
    };

    template <template <typename ...> typename F, int N, int E>
    struct index_if<F, N, E, E, false>
    {
        template <typename ...>
        using apply = int_<E>;
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
    using first_of = applyf<next_index_if, F, T, B, E>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using first_of_t = typeof_t<first_of<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto first_of_v = typev<first_of_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using last_of = applyf<prev_index_if, F, T, B, E>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using last_of_t = typeof_t<last_of<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    inline constexpr auto last_of_v = typev<last_of_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using first_not_of = applyf<next_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    using first_not_of_t = applyf_t<next_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = 0, int E = sizeof_t_v<T>>
    inline constexpr auto first_not_of_v = typev<first_not_of_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using last_not_of = applyf<prev_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    using last_not_of_t = applyf_t<prev_index_if, F, T, B, E, true>;

    template <template <typename ...> typename F, typename T, int B = sizeof_t_v<T> - 1, int E = -1>
    inline constexpr auto last_not_of_v = typev<last_not_of_t<F, T, B, E>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct any_of
    {
        template <size_t i, size_t j>
        struct impl : std::conditional_t<typev<F<element_t<i, T>>>, std::true_type, impl<i + 1, j>>
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
    struct nth_type<0, T, Args...> : identity<T>
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
    
    template <size_t N, typename T, typename... Args>
    requires N == 0
    decltype(auto) nth_value_v(T&& t, Args&&... args)
    {
        return std::forward<T>(t);
    }
    
    template <size_t N, typename T, typename... Args>
    requires N > 0
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
    struct range_generator<T, lower, lower, values...> : identity<index_list<T, values...>>
    {
    };
    
    template <typename T, T lower, T upper, T... Args>
    struct range_generator : range_generator<T, lower, upper - 1, upper - 1, Args...>
    {
    };
    
    template <typename T, T lower, T upper>
    using range_generator_t = typeof_t<range_generator<T, lower, upper>>;

    template <size_t lower, size_t upper>
    using index_range = typeof_t<range_generator<size_t, lower, upper>>;
    
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
        []<typename F, size_t... N, typename... Args>
        (F&& f, const index_list<size_t, N...>&, Args&&... args)
        {
            invoker<index_type<N, nth_type_t<N, Args...>>...>(f, (nth_value_v<N>(std::forward<Args>(args)...))...);
        }
        (t, index_range<0, sizeof_v<Outer...>>(), std::forward<Outer>(outer)...);
    }

    template <typename... Args>
    struct concat;

    template <template <typename ...> typename T, typename... Args>
    struct concat<T<Args...>> : identity<T<Args...>>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args>
    struct concat<T<U, Args...>> : identity<T<U, Args...>>
    {
    };

    template <template <typename ...> typename T, typename... Args, typename... args>
    struct concat<T<Args...>, T<args...>> : identity<T<Args..., args...>>
    {
    };

    template <template <typename, auto ...> typename T, typename U, auto... Args, auto... args>
    struct concat<T<U, Args...>, T<U, args...>> : identity<T<U, Args..., args...>>
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
        template <typename... args>
        struct impl : identity<T<args...>>
        {
        };

        template <typename U, typename... args>
        struct impl<U, args...>
        {
            using type = dedup_t<contains<U, args...>, T<U>, impl<args...>>;
        };

        using type = typeof_t<impl<Args...>>;
    };

    template <template <typename, auto...> typename T, typename U, auto... values>
    struct unique<T<U, values...>>
    {
        template <auto... args>
        struct impl : identity<T<U, args...>>
        {
        };

        template <auto value, auto... args>
        struct impl<value, args...>
        {
            using type = dedup_t<includes<value, args...>, T<U, value>, impl<args...>>;
        };

        using type = typeof_t<impl<values...>>;
    };

    template <typename T>
    using unique_t = typeof_t<unique<T>>;

    template <auto p, auto q>
    inline constexpr auto min_v = p < q ? p : q;

    template <auto p, auto q>
    inline constexpr auto max_v = p > q ? p : q;

    template <typename T, typename U>
    struct min : std::conditional<sizeof_t_v<T> < sizeof_t_v<U>, T, U>
    {
    };

    template <typename T, typename U>
    using min_t = typeof_t<min<T, U>>;

    template <typename T, typename U>
    struct max : std::conditional<sizeof_t_v<T> < sizeof_t_v<U>, U, T>
    {
    };

    template <typename T, typename U>
    using max_t = typeof_t<max<T, U>>;

    template <typename... Args>
    using min_type = folded<min, Args...>;

    template <typename... Args>
    using min_type_t = typeof_t<min_type<Args...>>;

    template <typename... Args>
    using max_type = folded<max, Args...>;

    template <typename... Args>
    using max_type_t = typeof_t<max_type<Args...>>;

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

    template <typename T, typename... Args>
    using append = push<0, T, Args...>;

    template <typename T, typename... Args>
    using append_t = typeof_t<append<T, Args...>>;

    template <typename ...>
    struct invert;

    template <typename T, typename... Args>
    struct invert<T, Args...>
    {
        using type = typeof_t<invert<typeof_t<invert<Args...>>, T>>;
    };

    template <typename T>
    struct invert<T> : identity<T>
    {
    };

    template <typename T, typename U>
    struct invert<T, U> : identity<invert<U, T>>
    {
    };

    template <typename T, typename... Args>
    struct invert<invert<Args...>, T> : identity<invert<Args..., T>>
    {
    };

    template <typename... Args>
    using invert_t = typeof_t<invert<Args...>>;

    template <typename T>
    using is_bool = std::disjunction<std::is_same<T, std::true_type>, std::is_same<T, std::false_type>>;

    template <typename T>
    inline constexpr auto is_bool_v = typev<is_bool<T>>;

    template <template <auto, typename> typename F, typename T, typename U, auto V = 0>
    struct expand;

    template <template <auto, typename> typename F, template <typename ...> typename T, typename... Args, auto... N, auto V>
    requires V >= 0
    struct expand<F, T<Args...>, std::index_sequence<N...>, V>
    {
        using type = T<typeof_t<F<N + V, T<Args...>>>...>;
    };

    template <template <auto, typename> typename F, template <typename ...> typename T, typename... Args, auto... N>
    struct expand<F, T<Args...>, std::index_sequence<N...>, -1>
    {
        using args = T<Args...>;
        using head = typeof_t<F<fst_v<std::index_sequence<N...>>, args>>;
        using type = std::integer_sequence<has_value_t<head>, sizeof_t_v<typeof_t<F<N, args>>>...>;
    };

    template <template <auto, typename> typename F, template <typename, auto ...> typename T, typename U, auto... values, auto... N, auto V>
    requires V >= 0
    struct expand<F, T<U, values...>, std::index_sequence<N...>, V>
    {
        using args = T<U, values...>;
        using head = typeof_t<F<fst_v<std::index_sequence<N...>, V>, args>>;

        static constexpr auto value = is_sequence_v<head>;

        template <typename W, bool b>
        struct next
        {
            using type = T<U, typev<F<N + V, W>>...>;
        };

        template <typename W>
        struct next<W, false>
        {
            using type = std::tuple<typeof_t<F<N + V, W>>...>;
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

        using type = typeof_t<std::conditional_t<is_bool_v<head>, next<args, false>,  impl<args, sizeof...(values) != 1 || value>>>;
    };

    template <template <auto, typename> typename F, template <typename, auto ...> typename T, typename U, auto... values, auto... N>
    struct expand<F, T<U, values...>, std::index_sequence<N...>, -1>
    {
        using type = std::tuple<int_<typev<F<N, T<U, values...>>>, U>...>;
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
    requires V >= 0
    struct expand<F, T, std::index_sequence<N...>, V>
    {
        template <typename W, bool b>
        struct impl
        {
            using type = std::tuple<typeof_t<F<N + V, W>>...>;
        };

        template <typename W>
        struct impl<W, false>
        {
            using type = std::integer_sequence<W, typev<F<N + V, W>>...>;
        };

        using head = typeof_t<F<fst_v<std::index_sequence<N...>, V>, T>>;
        using type = typeof_t<impl<T, negav<has_value<head>>>>;
    };

    template <template <auto, typename> typename F, typename T, typename U, auto V = 0>
    using expand_t = typeof_t<expand<F, T, U, V>>;

    template <typename T, typename U, auto V = 0>
    using expand_with = expand<element, T, U, V>;

    template <typename T, bool B, typename indices = index_sequence_of_t<T>>
    struct convert : std::conditional_t<is_tuple_v<T> == B, expand_with<T, indices, -1>, identity<T>>
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

    template <auto i, auto j, auto N>
    inline constexpr auto swap_v = N != i && N != j ? N : N == i ? j : i;

    template <auto i, auto j, typename T>
    struct swap
    {
        template <auto N, typename U>
        using impl = element<swap_v<i, j, N>, U>;

        using type = meta_t<T, expand<impl, T, index_sequence_of_t<T>>>;
    };

    template <auto i, auto j, typename T>
    using swap_t = typeof_t<std::conditional_t<i == j, identity<T>, swap<i, j, T>>>;

    template <auto n, auto lower, auto upper>
    struct within
    {
        template <auto i>
        struct impl
        {
            using cond = std::conditional_t<i + 1 >= upper, std::false_type, impl<i + 1>>;
            using type = typeof_t<std::conditional_t<n == i, std::true_type, cond>>;
        };

        using type = typeof_t<impl<lower>>;
    };

    template <auto n, auto lower, auto upper>
    using within_t = typeof_t<within<n, lower, upper>>;

    template <auto n, auto lower, auto upper>
    inline constexpr auto within_v = typev<within_t<n, lower, upper>>;

    template <auto i, auto j, typename T, typename U, typename V>
    struct gsub
    {
        template <auto N, typename W, typename X = element<N, W>>
        using cond = std::conditional_t<std::is_same_v<T, typeof_t<X>>, U, X>;

        template <auto N, typename W>
        using impl = std::conditional_t<within_v<N, i, j>, cond<N, W>, element<N, W>>;

        using type = expand_t<impl, V, index_sequence_of_t<V>>;
    };

    template <auto i, auto j, typename T, typename U, typename V>
    using gsub_t = typeof_t<gsub<i, j, T, U, V>>;

    template <auto i, auto j, typename T, typename U>
    struct substitute
    {
        template <auto N, typename V>
        using impl = std::conditional_t<within_v<N, i, j>, T, element<N, V>>;

        using type = expand_t<impl, U, index_sequence_of_t<U>>;
    };

    template <auto i, auto j, typename T, typename U>
    using substitute_t = typeof_t<substitute<i, j, T, U>>;

    template <auto i, typename T, typename U>
    using exchange = substitute<i, i + 1, T, U>;

    template <auto i, typename T, typename U>
    using exchange_t = typeof_t<exchange<i, T, U>>;

    template <auto lower, auto upper, typename T>
    using range = meta_t<T, identity<expand_with<T, index_sequence_of_v<upper - lower>, lower>>>;

    template <auto lower, auto upper, typename T>
    using range_t = typeof_t<range<lower, upper, T>>;

    template <auto i, auto j, typename T, typename U>
    struct swap_ranges
    {
        template <typename V>
        struct impl
        {
            template <auto k, typename W>
            using apply = element<k + i, V>;
        };

        using indices = index_sequence_of_v<j - i>;

        template <typename X, typename Y>
        struct swap
        {
            using curr = expand_t<impl<Y>::template apply, X, indices>;
            using type = concat_t<range_t<0, i, X>, curr, range_t<j, sizeof_t_v<X>, X>>;
        };

        using fst = typeof_t<swap<T, U>>;
        using snd = typeof_t<swap<U, T>>;
    };

    template <auto i, auto j, typename T, typename U>
    using swap_ranges_fst = typename swap_ranges<i, j, T, U>::fst;

    template <auto i, auto j, typename T, typename U>
    using swap_ranges_snd = typename swap_ranges<i, j, T, U>::snd;

    template <typename T, auto N = sizeof_t_v<T>>
    struct reverse
    {
        template <auto i, typename U>
        using impl = element<N - i - 1,  U>;

        using type = meta_t<T, expand<impl, T, index_sequence_of_v<N>>>;
    };

    template <typename T>
    using reverse_t = typeof_t<reverse<T>>;

    template <auto i, auto j, typename T>
    using extent = reverse<range_t<i, j, T>>;

    template <auto i, auto j, typename T>
    using extent_t = typeof_t<extent<i, j, T>>;

    template <auto i, auto j, typename T, auto N = sizeof_t_v<T>>
    using degree = extent<N - j, N - i, T>;

    template <auto i, auto j, typename T>
    using degree_t = typeof_t<degree<i, j, T>>;

    template <auto i, auto j, typename T>
    using erase = concat<range_t<0, i, T>, range_t<j, sizeof_t_v<T>, T>>;

    template <auto i, auto j, typename T>
    using erase_t = typeof_t<erase<i, j, T>>;

    template <auto i, typename T>
    using drop = erase<i, i + 1, T>;

    template <auto i, typename T>
    using drop_t = typeof_t<drop<i, T>>;

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    struct remove_if
    {
        static constexpr auto N = first_of_v<F, T, B, E>;

        template <int i, int j, typename U, bool>
        struct impl
        {
            using curr = element_t<j, U>;
            static constexpr auto value = negav<F<curr>>;

            using next = std::conditional_t<value, exchange<i, curr, U>, identity<U>>;
            using type = typeof_t<impl<i + value, j + 1, typeof_t<next>, j + 1 != E>>;
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

        using type = typeof_t<std::conditional_t<N == E, identity<T>, call<T>>>;
    };

    template <template <typename ...> typename F, typename T, auto B = 0, auto E = sizeof_t_v<T>>
    using remove_if_t = typeof_t<remove_if<F, T, B, E>>;

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

    template <auto i, auto j, typename T, typename... Args>
    using replace = concat<append_t<range_t<0, i, T>, Args...>, range_t<j, sizeof_t_v<T>, T>>;

    template <auto i, auto j, typename T, typename... Args>
    using replace_t = typeof_t<replace<i, j, T, Args...>>;

    template <auto i, auto j, typename T>
    struct reverse_range
    {
        using reversed = extent_t<i, j, T>;

        template <size_t N, bool B, bool E>
        struct impl : identity<reversed>
        {
        };

        template <size_t N>
        struct impl<N, true, false> : concat<reversed, range_t<j, N, T>>
        {
        };

        template <size_t N, bool E>
        struct impl<N, false, E>
        {
            using cond = typeof_t<std::conditional_t<E, base_type<T>, range<j, N, T>>>;
            using type = concat_t<range_t<0, i, T>, reversed, cond>;
        };

        static constexpr auto N = sizeof_t_v<T>;
        using type = meta_t<T, impl<N, i == 0, j == N>>;
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

    template <bool B, template <typename...> typename T, typename U, typename... Args>
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

    template <typename... Args>
    struct tuple_index;

    template <typename T, typename... Args>
    struct tuple_index<T, tuple_t<T, Args...>> : index_t<0>
    {
    };

    template <typename T, typename U, typename... Args>
    struct tuple_index<T, tuple_t<U, Args...>> : index_t<typev<tuple_index<T, tuple_t<Args...>>> + 1>
    {
    };

    template <typename T, typename U>
    inline constexpr auto tuple_index_v = typev<tuple_index<T, U>>;

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

    template <typename T, typename U>
    struct binary_search
    {
        static constexpr auto key = sizeof_t_v<T>;

        template <size_t i, size_t j>
        struct search
        {
             static constexpr auto half = i + (j - i - 1) / 2;
             static constexpr auto value = element_size_v<half, U>;

             using next = std::conditional_t<value < key, search<half + 1, j>, search<i, half>>;
             using type = typeof_t<std::conditional_t<value == key, std::true_type, next>>;
        };

        template <size_t j>
        struct search<j, j> : std::false_type
        {
        };

        using type = typeof_t<search<0, sizeof_t_v<U>>>;
    };

    template <typename T, typename U>
    using binary_search_t = typeof_t<binary_search<T, U>>;

    template <typename T, typename U>
    inline constexpr auto binary_search_v = typev<binary_search_t<T, U>>;

    template <auto n, auto N, typename T>
    using sub = exchange<n, int_<N>, T>;

    template <auto n, auto N, typename T>
    using sub_t = typeof_t<sub<n, N, T>>;

    template <auto n, auto N, typename T>
    inline constexpr auto add_v = get_v<n, T> + N;

    template <auto n, auto N, typename T>
    using add = sub<n, add_v<n, N, T>, T>;

    template <auto n, auto N, typename T>
    using add_t = typeof_t<add<n, N, T>>;

    template <auto n, typename T>
    inline constexpr auto inc_v = get_v<n, T> + 1;

    template <auto n, typename T>
    using inc = add<n, 1, T>;

    template <auto n, typename T>
    using inc_t = typeof_t<inc<n, T>>;

    template <auto n, typename T>
    inline constexpr auto dec_v = get_v<n, T> - 1;

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

    template <typename T, typename U>
    struct inner_dot
    {
        template <auto n, typename V>
        using impl = int_<dot_v<n, V, U>>;

        using type = expand_t<impl, T, index_sequence_of_v<min_v<sizeof_t_v<T>, sizeof_t_v<U>>>>;
    };

    template <typename T, typename U>
    using inner_dot_t = typeof_t<inner_dot<T, U>>;

    template <typename... T>
    struct overload : T...
    {
        template <typename... Args>
        overload(Args&&... args) : T{std::forward<Args>(args)}...
        {
        }

        using T::operator()...;
    };

    template <typename... Args>
    overload(Args&&...) -> overload<Args...>;

    template <typename... Args>
    struct overload_sequence;

    template <typename... Args>
    struct overload_sequence_selector;

    template <typename... T, typename... Args>
    struct overload_sequence_selector<overload_sequence<T...>, Args...>
    {
        using call = tuple_t<std::bool_constant<std::is_invocable_v<T, Args...>>...>;
        static constexpr auto value = tuple_index_v<std::true_type, call>;

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

        template <typename... F, typename = std::enable_if_t<std::is_constructible_v<tuple_t<T...>, F...>>>
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
        [&]<auto... N>(std::index_sequence<N...>)
        {
            (f.template operator()<N, Args>(), ...);
        }
        (std::index_sequence_for<Args...>());
    }

    template <auto B, auto E, typename F>
    constexpr void for_range(F&& f)
    {
        using type = std::common_type_t<decltype(B), decltype(E)>;
        [&]<auto... N>(std::integer_sequence<type, N...>)
        {
            for_value<(B + N)...>(f);
        }
        (std::make_integer_sequence<type, E - B>());
    }

    template <template <typename... > typename S, typename T>
    using stream_type = S<typename T::char_type, typename T::traits_type>;

    template <typename T>
    using istream_type = stream_type<std::basic_istream, T>;

    template <typename T>
    using ostream_type = stream_type<std::basic_ostream, T>;

    template <typename T, typename S>
    requires std::is_base_of_v<istream_type<T>, T>
    T&& operator>>(T&& os, const S& s)
    {
        static_cast<istream_type<T>&>(os) >> s;
        return std::move(os);
    }

    template <typename T, typename S>
    requires std::is_base_of_v<ostream_type<T>, T>
    T&& operator<<(T&& os, const S& s)
    {
        static_cast<ostream_type<T>&>(os) << s;
        return std::move(os);
    }

    template <size_t N, typename F, typename... Args>
    void loop(F&& f, Args&&... args)
    {
        if constexpr(N > 0)
           loop<N - 1>(f, std::forward<Args>(args)...);
        f(N, std::forward<Args>(args)...);
    }

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
            using apply = identity<infinite_list<impl, typeof_t<F<Args...>>>>;
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
    using infinite_call = nth_infinite<N, infinite_t<F, T>>;

    template <size_t N, typename T, template <typename ...> typename F>
    using infinite_call_t = typeof_t<infinite_call<N, T, F>>;

    template <size_t N, typename T, typename F>
    struct repeat : call<F, typeof_t<repeat<N - 1, T, F>>>
    {
    };

    template <typename T, typename F>
    struct repeat<0, T, F> : identity<T>
    {
    };

    struct pointer_type_of
    {
        template <typename T>
        using apply = std::add_pointer<T>;
    };

    template <typename T>
    using pointer_type_of_t = call_t<metaf<std::add_pointer>, T>;

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

    template <auto... values>
    inline constexpr auto void_v = value_v<0, values...>;

    template <typename ...>
    struct wrong : std::false_type
    {
    };

    template <typename T, typename... Args>
    using type_t = T;

    template <typename... Args>
    using void_t = type_t<void, Args...>;

    template <template <typename ...> typename T, template <typename ...> typename... Args>
    using template_t = T<>;

    template <template <typename ...> typename... Args>
    using void_template = template_t<std::void_t, Args...>;

    template <typename F, auto... N>
    void iterate(F&& f, std::integer_sequence<std::common_type_t<decltype(N)...>, N...>)
    {
        if constexpr((std::is_invocable_v<F&&, int_<N>>&& ...))
            (f(int_<N>()), ...);
        else
            (((void)N, f()), ...);
    }

    template <auto N, typename F>
    void iterate(F&& f)
    {
        iterate(f, std::make_integer_sequence<decltype(N), N>());
    }

    template <typename...>
    inline constexpr bool true_v = true;

    template <typename...>
    inline constexpr bool false_v = false;

    template <auto... values>
    using bool_sequence = std::integer_sequence<bool, values...>;

    template <typename T, auto value, typename>
    struct to_int;

    template <typename T, auto value>
    struct to_int<T, value, bool_sequence<>> : int_<value, T>
    {
    };

    template <typename T, auto value, auto b, auto... bs>
    struct to_int<T, value, bool_sequence<b, bs...>> : int_<typev<to_int<T, static_cast<T>((value << 1) | b), bool_sequence<bs...>>>, T>
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
    struct advance<state, std::index_sequence<>> : std::bool_constant<false>
    {
    };

    template <typename state, auto tap, auto... taps>
    struct advance<state, std::index_sequence<tap, taps...>> :
    std::bool_constant<get_v<tap, state> ^ typev<advance<state, std::index_sequence<taps...>>>>
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
        using type = prepend_t<typeof_t<nth_lfsr<N - 1, typename call::next>>, int_<invoke_v<call, unsigned>>>;
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

    template <int p, int r, typename T>
    struct prng
    {
        using lfsr_t = lfsr<bool_sequence<true, false, true, true, false>, std::index_sequence<2, 4>>;
        using type = swap_t<lfsr_prng_v<sizeof_t_v<T>, lfsr_t> % (r - p) + p, r - 1, T>;
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
        using call = expand<F, T, index_sequence_of_v<n>>;

        using type = typeof_t<std::conditional_t<has_value_v<T>, call<impl>, call<identity_n>>>;
    };

    template <auto n, typename T>
    using fill_t = typeof_t<fill<n, T>>;

    template <auto i, auto j, auto k, typename T>
    struct rotate
    {
        template <typename indices, auto V = 0>
        using impl = expand_t<element, T, indices, V>;

        template <size_t p, size_t q>
        using extend = impl<index_sequence_of_v<q - p>, p>;

        using type = concat_t<range_t<0, i, T>, extend<j, k>, extend<i, j>, range_t<k, sizeof_t_v<T>, T>>;
    };

    template <auto i, auto j, auto k, typename T>
    using rotate_t = typeof_t<rotate<i, j, k, T>>;

    template <auto N, typename T>
    struct shift : range<N, sizeof_t_v<T>, T>
    {
    };

    template <auto N, typename T>
    using shift_t = typeof_t<shift<N, T>>;

    template <typename T, auto N, auto B = T(), auto D = 0>
    struct value_sequence
    {
        template <auto i, typename U>
        using impl = int_<B + D * i, U>;

        using type = expand_t<impl, T, index_sequence_of_v<N>>;
    };

    template <typename T, auto N, auto B = T(), auto D = 0>
    using value_sequence_t = typeof_t<value_sequence<T, N, B, D>>;

    template <typename T, auto N>
    using zero_sequence_t = value_sequence_t<T, N>;

    template <typename T, auto N, auto B, auto D>
    using integer_sequence_n = value_sequence_t<T, N, B, D>;

    template <typename T, auto B, auto N>
    using parity = expand_with<T, integer_sequence_n<size_t, (sizeof_t_v<T> + N) / 2, B, 2>>;

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
    struct is_odd : std::bool_constant<typev<T> % 2>
    {
    };

    template <typename T>
    struct is_even : std::bool_constant<typev<T> % 2 == 0>
    {
    };

    template <typename T, template <typename, bool> typename comp, bool b, typename... Args>
    using extreme = std::conditional_t<!sizeof_v<Args...>, identity<T>, comp<tuple_t<T, Args...>, b>>;

    template <typename T, typename U, bool B>
    using evaluate = std::conditional_t<less_v<std::conditional_t<B, T, U>, std::conditional_t<B, U, T>>, T, U>;

    template <auto p, auto q, bool B>
    using minmax_t = int_<B ? min_v<p, q>  : max_v<p, q>>;

    template <typename T, bool B>
    struct minmax;

    template <template <typename ...> typename T, typename U, bool B>
    struct minmax<T<U>, B> : identity<U>
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
    using minimum = minmax<T, true>;

    template <typename T>
    using minimum_t = typeof_t<minimum<T>>;

    template <typename T>
    inline constexpr auto minimum_v = typev<minimum_t<T>>;

    template <typename T>
    using maximum = minmax<T, false>;

    template <typename T>
    using maximum_t = typeof_t<maximum<T>>;

    template <typename T>
    inline constexpr auto maximum_v = typev<maximum_t<T>>;

    template <typename T, typename U>
    struct count
    {
        template <typename V, typename W, typename X = typeof_t<V>>
        struct comp : identity<index_type<typev<V> + std::is_same_v<X, W>, X>>
        {
        };

        using type = eval_t<folded_t, comp, to_tuple_t<U>, index_type<0, T>>;
    };

    template <typename T, typename U>
    using count_t = typeof_t<count<T, U>>;

    template <typename T, typename U>
    inline constexpr auto count_v = typev<count_t<T, U>>;

    template <typename T>
    struct mode
    {
        template <typename U, typename V>
        struct comp : std::conditional<typev<U> < typev<V>, V, U>
        {
        };

        template <typename U>
        using unique = eval_t<currying_t, bind<count, U>::template apply, to_tuple_t<unique_t<U>>>;

        using type = typeof_t<eval_t<folded_t, comp, unique<T>>>;
        static constexpr auto value = typev<std::conditional_t<is_tuple_v<T>, std::false_type, type>>;
    };

    template <typename T>
    using mode_t = typeof_t<mode<T>>;

    template <typename T>
    inline constexpr auto mode_v = typev<mode<T>>;

    template <typename F, typename T>
    struct transform;

    template <typename F, template <typename ...> typename T, typename... Args>
    struct transform<F, T<Args...>>
    {
        using type = T<call_t<F, Args>...>;
    };

    template <typename F, typename T>
    using transform_t = typeof_t<transform<F, T>>;

    template <auto i, auto j, typename T, typename U, bool b>
    struct is_same : std::is_same<element_t<i, T>, element_t<j, U>>
    {
    };

    template <auto i, auto j, typename T, typename U>
    struct is_same<i, j, T, U, false> : std::bool_constant<get_v<i, T> == get_v<j, U>>
    {
    };

    template <typename T>
    using and_t = std::conditional_t<is_tuple_v<T>, tuple_and<T>, sequence_and<T>>;

    template <typename T>
    inline constexpr auto and_v = typev<and_t<T>>;

    template <typename T, auto N = sizeof_t_v<T>>
    struct is_palindromic
    {
        template <auto i, typename U>
        using impl = is_same<i, N - i - 1, T, U, is_tuple_v<T>>;

        static constexpr auto value = and_v<expand_t<impl, T, index_sequence_of_v<N / 2>>>;
    };

    template <typename T>
    inline constexpr auto is_palindromic_v = std::is_same_v<T, reverse_t<T>>;

    template <bool B, template <typename ...> typename F, typename T>
    struct for_each
    {
        template <auto i, typename U>
        struct impl
        {
            static constexpr auto value = typev<F<element_t<i, U>>>;
            using type = std::bool_constant<B == value>;
        };

        using type = tuple_and<expand_t<impl, T, index_sequence_of_v<sizeof_t_v<T>>>>;
    };

    template <bool B, template <typename ...> typename F, typename T>
    using for_each_t = typeof_t<for_each<B, F, T>>;

    template <template <typename ...> typename F, typename T>
    inline constexpr auto all_of_v = typev<for_each_t<1, F, T>>;

    template <template <typename ...> typename F, typename T>
    inline constexpr auto none_of_v = typev<for_each_t<0, F, T>>;

    template <typename T, typename U, auto M = sizeof_t_v<T>, auto N = sizeof_t_v<U>>
    struct subset
    {
        template <size_t i, size_t j>
        struct impl
        {
            static constexpr auto cond = std::is_same_v<T, range_t<i, i + M, U>>;
            using type = typeof_t<std::conditional_t<cond, std::true_type, impl<i + 1, j>>>;
        };

        template <size_t j>
        struct impl<j, j>
        {
            using type = std::is_same<T, range_t<j, j + M, U>>;
        };

        static constexpr auto value = typev<typeof_t<std::conditional_t<N < M, std::false_type, impl<0, N - M + 1>>>>;
    };

    template <typename T, typename U>
    inline constexpr auto subset_v = typev<subset<T, U>>;

    template <typename... Args>
    struct store
    {
        using fst = alias_t<Args...>;

        template <bool b, typename... args>
        struct impl
        {
            using type = tuple_t<args...>;
        };

        template <typename... args>
        struct impl<false, args...>
        {
            using type = std::integer_sequence<typename fst::value_type, typev<args>...>;
        };

        using type = typeof_t<impl<negav<has_value<fst>>, Args...>>;
    };

    template <typename... Args>
    using store_t = typeof_t<store<Args...>>;

    template <template <typename ...> typename F, typename T, typename U>
    using filter = std::conditional<typev<F<T>>, U, store_t<T>>;

    template <template <typename ...> typename F, typename T, typename U>
    using filter_t = typeof_t<filter<F, T, U>>;

    template <template <typename ...> typename F, typename T>
    struct remove;

    template <template <typename ...> typename F, template <typename ...> typename T, typename... Args>
    struct remove<F, T<Args...>>
    {
        using base = base_type_t<T<Args...>>;
        using type = concat_t<filter_t<F, Args, base>...>;
    };

    template <template <typename ...> typename F, template <typename, auto ...> typename T, typename U, auto... Args>
    struct remove<F, T<U, Args...>>
    {
        using base = base_type_t<T<U, Args...>>;
        using type = concat_t<filter_t<F, int_<Args, U>, base>...>;
    };

    template <template <typename ...> typename F, typename T>
    using remove_t = typeof_t<remove<F, T>>;

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

    template <typename T, typename U, auto M = sizeof_t_v<T>, auto N = sizeof_t_v<U>>
    struct zip
    {
        template <auto i, typename V>
        using impl = store_t<element_t<i, V>, element_t<i, U>>;

        using type = unpack_t<concat_t, expand_t<impl, T, index_sequence_of_v<(M < N ? M : N)>>>;
    };

    template <typename T, typename U>
    using zip_t = typeof_t<zip<T, U>>;

    template <typename L, typename R>
    struct swap_template;

    template <template <typename...> typename L, template <typename...> typename R, typename... T, typename... U>
    struct swap_template<L<T...>, R<U...>>
    {
        using fst = L<U...>;
        using snd = R<T...>;
    };

    template <template <typename, auto...> typename L, template <typename, auto...> typename R, typename T, auto... t, typename U, auto... u>
    struct swap_template<L<T, t...>, R<U, u...>>
    {
        using fst = L<U, u...>;
        using snd = R<T, t...>;
    };

    template <typename L, typename R>
    using swap_template_fst = typename swap_template<L, R>::fst;

    template <typename L, typename R>
    using swap_template_snd = typename swap_template<L, R>::snd;

    template <template <size_t, typename ...> typename F, size_t N, typename T, typename... Args>
    struct do_while
    {
        using call = F<N, T>;
        using curr = typeof_t<call>;

        using args = identity<tuple_t<Args...>>;
        using next = typeof_t<std::conditional_t<typev<call>, range<0, N, curr>, identity<T>>>;

        using type = typeof_t<std::conditional_t<typev<call>, do_while<F, N, curr, Args..., next>, args>>;
    };

    template <template <size_t, typename ...> typename F, size_t N, typename T, typename... Args>
    using do_while_t = typeof_t<do_while<F, N, T, Args...>>;

    template <template <size_t, typename ...> typename F, typename T, auto N = sizeof_t_v<T>>
    using ranged_list = do_while<F, N, T, range_t<0, N, T>>;

    template <template <size_t, typename ...> typename F, typename T, auto N = sizeof_t_v<T>>
    using ranged_list_t = typeof_t<ranged_list<F, T, N>>;

    template <typename T, bool ASC, auto N = sizeof_t_v<T>>
    struct permutation
    {
        template <int k, bool b>
        struct impl
        {
            static constexpr auto value = negav<less_t<element_t<k - 1, T>, element_t<k, T>, ASC>>;
            using type = typeof_t<std::conditional_t<k == 1 && value, index_upper<0, T>, impl<k == 1 ? -1 : k - 1, value>>>;
        };

        template <int k>
        struct impl<k, false>
        {
            static constexpr auto n = k == -1 ? 0 : k;

            template <typename U>
            struct comp : less_t<element_t<n, T>, U, ASC>
            {
            };

            using type = index_type<1, reverse_range_t<n + 1, N, swap_t<last_of_v<comp, T>, n, T>>>;
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

    template <size_t B1, size_t E1, size_t B2, size_t E2, typename T, bool ASC>
    struct combination
    {
        template <typename U, int M, size_t N, size_t i, size_t j>
        struct next
        {
            static constexpr auto cond = i - N != B1 && negav<less_t<element_t<i - N, T>, U, ASC ? N : !N>>;
            static constexpr auto value = typev<std::conditional_t<cond, next<U, M, N, i + M, j>, index_t<i - N>>>;
        };

        template <typename U, size_t N, size_t i, size_t j>
        struct exch
        {
            static constexpr auto value = i != N && j != E2;

            using curr = typeof_t<std::conditional_t<value, swap<i - 1, j, U>, identity<U>>>;
            using type = typeof_t<std::conditional_t<value, exch<curr, N, i - 1, j + 1>, identity<pair_t<U, pair_v<i, j>>>>>;
        };

        template <typename U, size_t N, size_t i, size_t j, bool result>
        struct reverse
        {
            using curr = typeof_t<exch<U, N, i, j>>;
            using call = typename curr::snd;

            using rang = reverse_range_t<N, E1, reverse_range_t<N, call::fst, typename curr::fst>>;
            using type = index_type<!result, reverse_range_t<j, E2, reverse_range_t<call::snd, E2, rang>>>;
        };

        template <size_t i, size_t j>
        struct impl
        {
            using lhs = element_t<j, T>;

            static constexpr auto k = typev<next<lhs, -1, 1, i, j>>;
            static constexpr auto result = k == B1 && !less_v<element_t<B1, T>, lhs, ASC>;

            using rhs = typeof_t<std::conditional_t<!result, element<k, T>, identity<T>>>;
            static constexpr auto value = typev<std::conditional_t<!result, next<rhs, 1, 0, B2, j>, index_t<B2>>>; 

            using curr = typeof_t<std::conditional_t<!result, swap<k, value, T>, identity<T>>>;
            using call = std::conditional_t<!result, pair_v<k + 1, value + 1>, pair_v<B1, B2>>; 

            static constexpr auto cond = call::fst != E1 && call::snd != E2;
            using type = typeof_t<std::conditional_t<cond, reverse<curr, call::fst, E1, call::snd, result>, index_upper<!result, curr>>>;
        };

        using type = typeof_t<std::conditional_t<B1 == E1 || B2 == E2, index_upper<0, T>, impl<E1, E2 - 1>>>;
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

        using args = identity<tuple_t<Args...>>;
        static constexpr auto value = typev<call>;

        using next = std::conditional_t<value, curr, T>;
        using type = typeof_t<std::conditional_t<value, next_indices<F, B, E, curr, Args..., next>, args>>;
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
            static constexpr auto cont = typev<std::conditional_t<i != B, get<i - 1, T>, curr>> == 0;

            using type = std::conditional_t<cont, next<i - 1>, index_t<i - 1>>;
            static constexpr auto value = typev<std::conditional_t<i != B, type, curr>>;
        };

        struct exch
        {
            using cond = std::conditional_t<ASC, get<B, T>, index_t<B != E - 1>>;
            using type = index_type<0, typeof_t<std::conditional_t<typev<cond>, swap<B, E - 1, T>, identity<T>>>>;
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
            using cond = std::conditional_t<get_v<E - 1, curr>, swap<i + 1, E - 1, curr>, identity<curr>>;

            using type = index_type<1, inc_t<i + 1, typeof_t<cond>>>;
        };

        template <size_t N>
        struct impl
        {
            using cond = std::conditional_t<ASC, index_t<N == B>, std::conditional_t<N == B, get<N, T>, index_t<1>>>;
            static constexpr auto value = typev<std::conditional_t<ASC, cond, index_t<N == E - 1 || negav<cond>>>>;
        };

        static constexpr auto value = typev<next<E - !ASC>>;
        using curr = std::conditional_t<typev<impl<value>>, exch, calc<value, ASC>>;

        using type = typeof_t<std::conditional_t<B == E, index_upper<0, T>, curr>>;
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
            using type = typeof_t<std::conditional_t<value != M, index_upper<1, curr>, next>>;
        };

        using type = typeof_t<std::conditional_t<B == E, index_upper<0, T>, impl<T, 0, sizeof_t_v<T>>>>;
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

    template <typename T, auto N = 1>
    struct increase
    {
        template <auto n, typename U>
        using impl = int_<add_v<n, N, U>>;

        using type = expand_t<impl, T, index_sequence_of_t<T>>;
    };

    template <typename T, auto N = 1>
    using increase_t = typeof_t<increase<T, N>>;

    template <size_t B, size_t E, typename T, bool ASC, auto N = sizeof_t_v<T>>
    struct slide_indices
    {
        static constexpr auto value = get_v<0, T>;
        static constexpr auto cond = value == B && !ASC || value + N == E && ASC;

        using type = index_type<!cond, typeof_t<std::conditional_t<cond, identity<T>, increase<T, 2 * ASC - 1>>>>;
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
        using indices = next_slide_indices_list<0, sizeof_t_v<T>, integer_sequence_n<int, N, 0, 1>>;

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

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal>
    struct partition
    {
        using x = element_t<r - 1, T>;

        template <int i, int j, int k, typename V>
        struct impl
        {
            static constexpr auto value = typev<comparator<element_t<j, V>, x>>;

            using cond = std::conditional_t<value, swap<i + 1, j, V>, identity<V>>;
            using type = typeof_t<impl<i + value, j + 1, k, typeof_t<cond>>>;
        };

        template <int i, int k, typename V>
        struct impl<i, k, k, V>
        {
            using type = index_type<i + 1, swap_t<i + 1, r - 1, V>>;
        };

        using type = typeof_t<impl<p - 1, p, r - 1, T>>;
    };

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal>
    using partition_t = typeof_t<partition<p, r, T, comparator>>;

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal>
    struct randomized_partition : partition<p, r, prng_t<p, r, T>, comparator>
    {
    };

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal>
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
            using cond = typeof_t<std::conditional_t<B == N, append<X, call>, identity<X>>>;

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
            static constexpr auto index = first_not_of_v<comparator, left_partition, m, m + half>;

            using right_partition = partition_adaptive<index, r, half, size, left_partition, comparator>;
            using right_split = typeof_t<std::conditional_t<half, right_partition, index_upper<index, left_partition>>>;

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

        using type = typeof_t<std::conditional_t<len == 1 || r <= p, index_upper<p, T>, impl<p + len / 2, len <= size>>>;
    };

    template <int p, int r, int len, int size, typename T, template <typename ...> typename comparator>
    using partition_adaptive_t = typeof_t<partition_adaptive<p, r, len, size, T, comparator>>;

    template <int p, int r, typename T, template <typename ...> typename comparator>
    struct stable_partition
    {
        static constexpr auto N = first_not_of_v<comparator, T, p, r>;

        using part = partition_adaptive<N, r, r - N, (r - N) / 2, T, comparator>;
        using impl = typeof_t<std::conditional_t<N == r, index_upper<r, T>, part>>;

        using type = typeof_t<impl>;
        static constexpr auto value = typev<impl>;
    };

    template <int p, int r, typename T, template <typename ...> typename comparator>
    using stable_partition_t = typeof_t<stable_partition<p, r, T, comparator>>;

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal>
    struct randomized_stable_partition
    {
        using prng = prng_t<p, r, T>;
        using x = element_t<r - 1, prng>;

        template <typename U>
        struct comp : comparator<U, x>
        {
        };

        using impl = typename stable_partition<p, r, prng, comp>::impl;

        using type = typeof_t<impl>;
        static constexpr auto value = typev<impl>;
    };

    template <int p, int r, typename T, template <typename, typename> typename comparator = less_equal>
    using randomized_stable_partition_t = typeof_t<randomized_stable_partition<p, r, T>>;

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal>
    struct select
    {
        template <int p, int r, size_t i, typename U>
        struct impl
        {
            using pivot = randomized_partition_t<p, r, U, comparator>;

            static constexpr auto q = typev<pivot>;
            static constexpr auto k = q - p + 1;

            using next = std::conditional_t<i < k, impl<p, q, i, U>, impl<q + 1, r, i - k, U>>;
            using type = typeof_t<std::conditional_t<i == k, element<q, U>, next>>;
        };

        template <int p, size_t i, typename U>
        struct impl<p, p, i, U> : element<p, U>
        {
        };

        using type = typeof_t<impl<0, sizeof_t_v<T>, n, T>>;
    };

    template <size_t n, typename T, template <typename, typename> typename comparator = less_equal>
    using select_t = typeof_t<select<n, T, comparator>>;

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
            static constexpr auto delta = minimum_v<U>;
            static constexpr auto value = delta < 0 ? -delta : 0;

            using type = typeof_t<std::conditional_t<value || N, increase<U, N == 0 ? value : -N>, identity<U>>>;
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
    inline constexpr auto sort_v = std::conjunction_v<std::is_same<typeof_t<sort<T>>, U>...>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct counting_sort
    {
        using call = normalize_t<T>;

        static constexpr auto N = sizeof_t_v<T>;
        static constexpr auto k = sizeof_t_v<maximum_t<call>>;

        using C = value_sequence_t<size_t, k + 1>;
        using B = fill_t<N, std::conditional_t<is_tuple_v<call>, int, int_<0>>>;

        template <size_t i, typename V, bool = true>
        struct count : inc<sizeof_t_v<element_t<i, call>>, V>
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
        struct assign<j, j, b, V> : identity<V>
        {
        };

        template <size_t i, typename V, typename W>
        struct sort
        {
            using X = element_t<i - 1, call>;

            static constexpr auto n = sizeof_t_v<X>;
            static constexpr auto m = get_v<n, V> - 1;

            using type = typeof_t<sort<i - 1, sub_t<n, m, V>, exchange_t<m, X, W>>>;
        };

        template <typename V, typename W>
        struct sort<0, V, W> : identity<W>
        {
        };

        using impl = sort<N, typeof_t<assign<0, k, 0, typeof_t<assign<0, N, 1, C>>>>, B>;
        using type = normalize_t<typeof_t<impl>, normalize_v<T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using counting_sort_t = sort_t<counting_sort, T, comparator>;

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
            using type = typeof_t<std::conditional_t<value, swap<i, j, U>, identity<U>>>;
        };

        using type = typeof_t<sort<0, sizeof_t_v<T> - 1, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using stooge_sort_t = sort_t<stooge_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct bubble_sort
    {
        template <size_t i, size_t j, size_t k, typename U>
        struct sort
        {
            static constexpr auto value = compare_v<j, j - 1, U, comparator>;
            using cond = typeof_t<std::conditional_t<value, swap<j, j - 1, U>, identity<U>>>;

            using type = typeof_t<sort<i, j - 1, k, cond>>;
        };

        template <size_t i, size_t k, typename U>
        struct sort<i, i, k, U> : sort<i + 1, k, k, U>
        {
        };

        template <size_t k, typename U>
        struct sort<k, k, k, U> : identity<U>
        {
        };

        static constexpr auto N = sizeof_t_v<T>;
        using type = typeof_t<sort<0, N - 1, N - 1, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using bubble_sort_t = sort_t<bubble_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_t>
    struct selection_sort
    {
        template <size_t i, size_t j, size_t k, typename U>
        struct sort
        {
            static constexpr auto value = compare_v<j, i, U, comparator>;
            using cond = typeof_t<std::conditional_t<value, swap<i, j, U>, identity<U>>>;

            using type = typeof_t<sort<i, j + 1, k, cond>>;
        };

        template <size_t i, size_t k, typename U>
        struct sort<i, k, k, U> : sort<i + 1, i + 2, k, U>
        {
        };

        template <size_t j, size_t k, typename U>
        struct sort<k, j, k, U> : identity<U>
        {
        };

        using type = typeof_t<sort<0, 1, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using selection_sort_t = sort_t<selection_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_equal>
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
        struct sort<p, r, U, false> : identity<U>
        {
        };

        using type = typeof_t<sort<0, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal>
    using quick_sort_t = sort_t<quick_sort, T, comparator>;

    template <typename T, template <typename, typename> typename comparator = less_equal>
    struct stable_sort
    {
        template <int p, int r, typename U, bool = (p < r)>
        struct sort
        {
            using pivot = typename randomized_stable_partition<p, r, U, comparator>::impl;
            using left = typeof_t<sort<p, typev<pivot> - 1, typeof_t<pivot>>>;

            using type = typeof_t<sort<typev<pivot>, r, left>>;
        };

        template <int p, int r, typename U>
        struct sort<p, r, U, false> : identity<U>
        {
        };

        using type = typeof_t<sort<0, sizeof_t_v<T>, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal>
    using stable_sort_t = typeof_t<stable_sort<T, comparator>>;

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
                using cond = typeof_t<std::conditional_t<i + 1 == k, identity<W>, element<i + 1, W>>>;
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
        struct sort<k, k, k, U, V> : identity<U>
        {
        };

        static constexpr auto N = sizeof_t_v<T>;
        using type = typeof_t<sort<1, 1, N, T, element_t<(N > 1), T>>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using insertion_sort_t = sort_t<insertion_sort, T, comparator>;

    template <size_t p, size_t q, size_t r, typename T, template <typename, typename> typename comparator = less_equal>
    struct merge
    {
        using max = maximum_t<T>;

        template <auto i, auto j, typename U>
        using split = append_t<expand_t<element, U, index_sequence_of_v<i>, j>, max>;

        using left = split<q - p + 1, p, T>;
        using right = split<r - q, q + 1, T>;

        template <size_t i, size_t j, size_t k, size_t l, typename U>
        struct assign
        {
            using fst = element_t<i, left>;
            using snd = element_t<j, right>;

            static constexpr auto value = typev<comparator<fst, snd>>;
            using swap = exchange<k, std::conditional_t<value, fst, snd>, U>;

            using cond = typeof_t<std::conditional_t<k == l, identity<U>, swap>>;
            using type = typeof_t<std::conditional_t<k == l, swap, assign<i + value, j + !value, k + 1, l, cond>>>;
        };

        using type = typeof_t<assign<0, 0, p, r, T>>;
    };

    template <size_t p, size_t q, size_t r, typename T, template <typename, typename> typename comparator = less_equal>
    using merge_t = typeof_t<merge<p, q, r, T, comparator>>;

    template <typename T, template <typename, typename> typename comparator = less_equal>
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
        struct sort<p, r, U, false> : identity<U>
        {
        };

        using type = typeof_t<sort<0, sizeof_t_v<T> - 1, T>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_equal>
    using merge_sort_t = sort_t<merge_sort, T, comparator>;

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
        struct max_heapify<i, j, U, false> : identity<U>
        {
        };

        template <int i, typename U, bool = (i >= 0)>
        struct build_max_heap : build_max_heap<i - 1, typeof_t<max_heapify<i, N, U>>>
        {
        };

        template <int i, typename U>
        struct build_max_heap<i, U, false> : identity<U>
        {
        };

        template <int i, typename U, bool = (i >= 1)>
        struct sort : sort<i - 1, typeof_t<max_heapify<0, i - 1, swap_t<i, 0, U>>>>
        {
        };

        template <int i, typename U>
        struct sort<i, U, false> : identity<U>
        {
        };

        using type = typeof_t<sort<N, typeof_t<build_max_heap<N / 2, T>>>>;
    };

    template <typename T, template <typename, typename> typename comparator = less_t>
    using heap_sort_t = sort_t<heap_sort, T, comparator>;

    template <typename P, typename T, auto N = sizeof_t_v<P>, auto value = is_tuple_v<P>>
    struct kmp
    {
        template <typename U, typename V, typename W, int k, int q>
        struct next
        {
            using nega = std::negation<is_same<k, q, U, V, value>>;
            using cond = std::conditional_t<0 < k, nega, std::false_type>;

            using curr = std::conditional_t<typev<cond>, get<k, W>, int_<k>>;
            using type = typeof_t<std::conditional_t<typev<cond>, next<U, V, W, typev<curr>, q>, int_<k>>>;
        };

        template <bool B, typename U, typename V, typename W, int k, int q, int p>
        struct impl
        {
            using lhs = std::conditional_t<B, U, V>;
            using rhs = std::conditional_t<B, V, T>;

            static constexpr auto m = typev<typeof_t<next<lhs, rhs, W, k, q>>>;
            static constexpr auto n = m + typev<is_same<m, q, lhs, rhs, value>>;

            using curr = typeof_t<std::conditional_t<!B && n == N, append<U, int_<q - N + 1>>, identity<U>>>;
            using cond = std::conditional_t<!B && n == N, get<n - 1, W>, int_<n>>;

            using dest = typeof_t<std::conditional_t<B, sub<q, n, W>, identity<W>>>;
            using type = typeof_t<impl<B, curr, V, dest, typev<cond>, q + 1, p>>;
        };

        template <bool B, typename U, typename V, typename W, int k, int p>
        struct impl<B, U, V, W, k, p, p>
        {
            using type = std::conditional_t<B, W, U>;
        };

        using call = typeof_t<impl<1, P, P, fill_t<N, int_<0>>, 0, 1, N>>;
        using type = typeof_t<impl<0, std::index_sequence<>, P, call, 0, 0, sizeof_t_v<T>>>;
    };

    template <typename P, typename T>
    using kmp_t = typeof_t<kmp<P, T>>;
}

#endif
