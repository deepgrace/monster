#ifndef CRTP_HPP
#define CRTP_HPP

#include <utility>

namespace monster
{
    class crtp
    {
        public:
            template <typename T>
            struct base;

            template <bool sub, typename T>
            class subinfo_selector;

            template <typename T>
            struct base<subinfo_selector<true, T>>
            {
                template <typename... Args>
                auto sub(Args... args);
            };

            template <typename T>
            struct base<subinfo_selector<false, T>>
            {
                template <typename... Args>
                auto sub(Args... args);
            };

            template <bool sub, typename T>
            class subinfo_selector : public base<subinfo_selector<sub, T>>
            {
                public:
                    subinfo_selector(T& outer);
                private:
                    T& inner;
                    friend base<subinfo_selector<sub, T>>;
            };

            template <bool sub, typename... Args>
            auto sub(Args... args);

        private:
            size_t data = 1;
    };

    template <bool sub, typename T>
    using subinfo_type = crtp::subinfo_selector<sub, T>;

    template <bool sub, typename T>
    crtp::subinfo_selector<sub, T>::subinfo_selector(T& outer) : inner(outer)
    {
    }

    template <typename T>
    template <typename... Args>
    auto crtp::base<subinfo_type<true, T>>::sub(Args... args)
    {
        auto& data = static_cast<subinfo_selector<true, T>*>(this)->inner.data;
    }

    template <typename T>
    template <typename... Args>
    auto crtp::base<subinfo_type<false, T>>::sub(Args... args)
    {
        auto& data = static_cast<subinfo_selector<false, T>*>(this)->inner.data;
    }

    template <bool sub, typename... Args>
    auto crtp::sub(Args... args)
    {
        return subinfo_selector<sub, crtp>(*this).sub(args...);
    }
}

#endif
