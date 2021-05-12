#pragma once
#include <cstdint>

using std::uint16_t;




// NONE
// ----
// Zero size type.

#ifndef NONE
struct None {
  friend bool operator==(None a, None b) noexcept { return true; }

  template <class T>
  friend bool operator==(None a, const T& b) noexcept { return false; }

  template <class T>
  friend bool operator==(const T& a, None b) noexcept { return false; }
};
#define NONE None
#endif




// Bfloat16
// --------
// 16-bit floating point (storage type only).

class Bfloat16 {
  uint16_t x;

  static uint16_t from(float v) { return reinterpret_cast<uint32_t&>(v)>>16; }
  static float to(uint32_t v) { v <<=16; return reinterpret_cast<float&>(v); }

  public:
  Bfloat16() : x(0) {}
  Bfloat16(const Bfloat16&) = default;
  Bfloat16(Bfloat16&&)      = default;
  Bfloat16(const float& v) : x(from(v)) {}
  operator float() const { return to(x); }
  Bfloat16& operator=(const Bfloat16&) = default;
  Bfloat16& operator=(Bfloat16&&) = default;
  Bfloat16& operator=(const float& v) { x = from(v); return *this; }

  friend istream& operator>>(istream& s, Bfloat16& v) {
    float f; s >> f; v = Bfloat16(f);
    return s;
  }
};
