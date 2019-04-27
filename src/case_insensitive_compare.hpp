#ifndef CASE_INSENSITIVE_COMPARE_HPP
#define CASE_INSENSITIVE_COMPARE_HPP

#include <string>
#include <algorithm>

namespace monster
{
    template <typename T>
    struct case_insensitive_compare
    {
        bool operator() (const std::string& s1, const std::string& s2) const
        {
            return std::lexicographical_compare(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), [](const auto& c1, const auto& c2){ 
                return T()(std::tolower(c1), std::tolower(c2)); 
            });
        }
    };
}

#endif
