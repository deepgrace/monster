#ifndef ENDIANNESS_HPP
#define ENDIANNESS_HPP

#define _INIT_ENDIAN_   0
#define _LITTLE_ENDIAN_ 1
#define _BIG_ENDIAN_    2

#include <cstdint>
#include <algorithm>
#include <union_converter.hpp>

namespace monster
{
    inline bool is_little_endian() 
    {
        short int value = 0x01;
        return reinterpret_cast<char*>(&value)[0] == 1;
    }

    inline uint64_t _htonll(uint64_t value) 
    {
        static int type = _INIT_ENDIAN_;
        union_converter<uint64_t, uint8_t> conv;
        if (type == _INIT_ENDIAN_)
        {
            conv.s = 0x01;
            type = (conv.d[7] == 0x01ULL) ? _BIG_ENDIAN_ : _LITTLE_ENDIAN_;
        }
        if (type == _BIG_ENDIAN_)
            return value;
        conv.s = value;
        for (size_t i = 0; i != 4; ++i)
             std::swap(conv.d[i], conv.d[7-i]);
        return conv.s;
    }

    inline uint64_t _ntohll(uint64_t value)
    {
        return _htonll(value);
    }
}

#endif
