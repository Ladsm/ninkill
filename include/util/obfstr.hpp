#pragma once
#include <array>
#include <cstdint>
#include <string>
namespace obf {
constexpr char xor_key = 0x5A;
constexpr int shift = 3;
constexpr char enc_char(char c) {
  if (c >= 32 && c <= 126)
    c = 32 + (c - 32 + shift) % 95;
  return c ^ xor_key;
}
constexpr char dec_char(char c) {
  c ^= xor_key;

  if (c >= 32 && c <= 126)
    c = 32 + (c - 32 - shift + 95) % 95;
  return c;
}
template <std::uint64_t N> class ObfString {
  std::array<char, N> data{};

public:
  consteval ObfString(const char (&str)[N]) {
    for (size_t i = 0; i < N; ++i)
      data[i] = enc_char(str[i]);
  }
  std::string decode() const {
    std::string out;
    out.resize(N - 1);
    for (int i = 0; i < N - 1; ++i) {
      out[i] = dec_char(data[i]);
    }
    return out;
  }
};
} // namespace obf
#define H(str) obf::ObfString<sizeof(str)>(str).decode()
#define SAFESTR(x) H(x)
#define STATIC_DEF(x) H(x)
#define PROTECT(x) H(x)
