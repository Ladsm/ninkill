#pragma once
#include <string>
#include <array>

namespace obf
{
    constexpr char key = 0x5A;
    template<size_t N>
    struct ObfString
    {
        std::array<char, N> data;
        consteval ObfString(const char(&str)[N]) : data{}
        {
            for (size_t i = 0; i < N; ++i)
                data[i] = str[i] ^ key;
        }
        std::string decrypt() const
        {
            std::string out;
            out.resize(N - 1);

            for (size_t i = 0; i < N - 1; ++i)
                out[i] = data[i] ^ key;

            return out;
        }
    };
}
#define H(str) obf::ObfString<sizeof(str)>(str).decrypt()
#define SAFESTR(x) H(x)
#define STATIC_DEF(x) H(x)
#define PROTECT(x) H(x)