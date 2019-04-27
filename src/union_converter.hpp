#ifndef UNION_CONVERTER_HPP
#define UNION_CONVERTER_HPP

#include <type_traits>

namespace monster
{
    template <typename S, typename D>
    union union_converter
    {
        S s;
        D d[sizeof(S) / sizeof(D)];
    };

    template <typename T>
    constexpr auto to_underlying(T t) noexcept
    {
        return static_cast<std::underlying_type_t<T>>(t);
    }
}

#endif
