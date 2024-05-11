#include "base.hpp"

constexpr ull ull_alt_mask_of(int k) {
  ull mask = (ull(1) << k) - 1;
  ull s = 0;
  for (int i = 0; i < 64; i += k * 2) {
    s += mask << i;
  }
  return s;
}

const ull ull_alt_mask_1 = ull_alt_mask_of(1);
const ull ull_alt_mask_2 = ull_alt_mask_of(2);
const ull ull_alt_mask_4 = ull_alt_mask_of(4);
const ull ull_alt_mask_8 = ull_alt_mask_of(8);
const ull ull_alt_mask_16 = ull_alt_mask_of(16);
const ull ull_alt_mask_32 = ull_alt_mask_of(32);

const uint alt_mask_1 = uint(ull_alt_mask_1);
const uint alt_mask_2 = uint(ull_alt_mask_2);
const uint alt_mask_4 = uint(ull_alt_mask_4);
const uint alt_mask_8 = uint(ull_alt_mask_8);
const uint alt_mask_16 = uint(ull_alt_mask_16);

template <typename T>
constexpr inline enable_if_t<sizeof(T) == 4, int> bit_popcount(T v) {
  v = (v & alt_mask_1) + (v >> 1 & alt_mask_1);
  v = (v & alt_mask_2) + (v >> 2 & alt_mask_2);
  v = (v & alt_mask_4) + (v >> 4 & alt_mask_4);
  v = (v & alt_mask_8) + (v >> 8 & alt_mask_8);
  v = (v & alt_mask_16) + (v >> 16 & alt_mask_16);
  return v;
}
template <typename T>
constexpr inline enable_if_t<sizeof(T) == 8, int> bit_popcount(T v) {
  v = (v & ull_alt_mask_1) + (v >> 1 & ull_alt_mask_1);
  v = (v & ull_alt_mask_2) + (v >> 2 & ull_alt_mask_2);
  v = (v & ull_alt_mask_4) + (v >> 4 & ull_alt_mask_4);
  v = (v & ull_alt_mask_8) + (v >> 8 & ull_alt_mask_8);
  v = (v & ull_alt_mask_16) + (v >> 16 & ull_alt_mask_16);
  v = (v & ull_alt_mask_32) + (v >> 32 & ull_alt_mask_32);
  return v;
}

template <typename T>
constexpr inline enable_if_t<sizeof(T) == 4, int> bit_msb(T v) {
  int s = 0;
  if (v >> 16) {
    s |= 16;
    v >>= 16;
  }
  if (v >> 8) {
    s |= 8;
    v >>= 8;
  }
  if (v >> 4) {
    s |= 4;
    v >>= 4;
  }
  if (v >> 2) {
    s |= 2;
    v >>= 2;
  }
  if (v >> 1) {
    s |= 1;
  }
  return s;
}
template <typename T>
constexpr inline enable_if_t<sizeof(T) == 8, int> bit_msb(T v) {
  int s = 0;
  if (v >> 32) {
    s |= 32;
    v >>= 32;
  }
  if (v >> 16) {
    s |= 16;
    v >>= 16;
  }
  if (v >> 8) {
    s |= 8;
    v >>= 8;
  }
  if (v >> 4) {
    s |= 4;
    v >>= 4;
  }
  if (v >> 2) {
    s |= 2;
    v >>= 2;
  }
  if (v >> 1) {
    s |= 1;
  }
  return s;
}

template <typename T>
constexpr inline enable_if_t<sizeof(T) == 4, T> bit_msb_exp(T v) {
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return v ^ (v >> 1);
}
template <typename T>
constexpr inline enable_if_t<sizeof(T) == 8, T> bit_msb_exp(T v) {
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v |= v >> 32;
  return v ^ (v >> 1);
}

template <typename T>
constexpr inline enable_if_t<sizeof(T) == 4, int> bit_reverse(T v) {
  v = (v & alt_mask_1) << 1 | (v >> 1 & alt_mask_1);
  v = (v & alt_mask_2) << 2 | (v >> 2 & alt_mask_2);
  v = (v & alt_mask_4) << 4 | (v >> 4 & alt_mask_4);
  v = (v & alt_mask_8) << 8 | (v >> 8 & alt_mask_8);
  v = (v & alt_mask_16) << 16 | (v >> 16 & alt_mask_16);
  return v;
}
template <typename T>
constexpr inline enable_if_t<sizeof(T) == 8, int> bit_reverse(T v) {
  v = (v & ull_alt_mask_1) << 1 | (v >> 1 & ull_alt_mask_1);
  v = (v & ull_alt_mask_2) << 2 | (v >> 2 & ull_alt_mask_2);
  v = (v & ull_alt_mask_4) << 4 | (v >> 4 & ull_alt_mask_4);
  v = (v & ull_alt_mask_8) << 8 | (v >> 8 & ull_alt_mask_8);
  v = (v & ull_alt_mask_16) << 16 | (v >> 16 & ull_alt_mask_16);
  v = (v & ull_alt_mask_32) << 32 | (v >> 32 & ull_alt_mask_32);
  return v;
}

template <typename T>
constexpr inline enable_if_t<sizeof(T) == 4, int> bit_level(T v) {
  T w = v >> 1 & alt_mask_1;
  v = (v & alt_mask_1) + (v >> 1 & alt_mask_1);
  w = (w & alt_mask_2) + (w >> 2 & alt_mask_2) + ((v >> 2 & alt_mask_2) << 1);
  v = (v & alt_mask_2) + (v >> 2 & alt_mask_2);
  w = (w & alt_mask_4) + (w >> 4 & alt_mask_4) + ((v >> 4 & alt_mask_4) << 2);
  v = (v & alt_mask_4) + (v >> 4 & alt_mask_4);
  w = (w & alt_mask_8) + (w >> 8 & alt_mask_8) + ((v >> 8 & alt_mask_8) << 3);
  v = (v & alt_mask_8) + (v >> 8 & alt_mask_8);
  w = (w & alt_mask_16) + (w >> 16 & alt_mask_16) +
      ((v >> 16 & alt_mask_16) << 4);
  return w;
}
template <typename T>
constexpr inline enable_if_t<sizeof(T) == 8, int> bit_level(T v) {
  T w = v >> 1 & ull_alt_mask_1;
  v = (v & ull_alt_mask_1) + (v >> 1 & ull_alt_mask_1);
  w = (w & ull_alt_mask_2) + (w >> 2 & ull_alt_mask_2) +
      ((v >> 2 & ull_alt_mask_2) << 1);
  v = (v & ull_alt_mask_2) + (v >> 2 & ull_alt_mask_2);
  w = (w & ull_alt_mask_4) + (w >> 4 & ull_alt_mask_4) +
      ((v >> 4 & ull_alt_mask_4) << 2);
  v = (v & ull_alt_mask_4) + (v >> 4 & ull_alt_mask_4);
  w = (w & ull_alt_mask_8) + (w >> 8 & ull_alt_mask_8) +
      ((v >> 8 & ull_alt_mask_8) << 3);
  v = (v & ull_alt_mask_8) + (v >> 8 & ull_alt_mask_8);
  w = (w & ull_alt_mask_16) + (w >> 16 & ull_alt_mask_16) +
      ((v >> 16 & ull_alt_mask_16) << 4);
  v = (v & ull_alt_mask_16) + (v >> 16 & ull_alt_mask_16);
  w = (w & ull_alt_mask_32) + (w >> 32 & ull_alt_mask_32) +
      ((v >> 32 & ull_alt_mask_32) << 5);
  return w;
}
