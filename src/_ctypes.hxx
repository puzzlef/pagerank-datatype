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




// FP16
// ----
// 16-bit floating point (storage type only).

class Fp16 {
  uint16_t x;

  public:
  Fp16() : x(0) {}
  Fp16(const Fp16&) = default;
  Fp16(Fp16&&)      = default;
  Fp16(const float& v) : x(*((uint16_t*)&v)) {}
  operator float() const { uint32_t b = x; return *((float*)&b); }
  Fp16& operator = (const Fp16&) = default;
  Fp16& operator = (Fp16&&) = default;
  Fp16& operator = (const float& v) { x = *((uint16_t*)&v); return *this; }
};
