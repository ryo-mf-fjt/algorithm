#include "base.hpp"

constexpr ull ull_alt_mask_of(int k) {
  ull mask = (1 << k) - 1;
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
constexpr inline enable_if_t<sizeof(T) == 4, T> bit_msb(T v) {
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  return v ^ (v >> 1);
}
template <typename T>
constexpr inline enable_if_t<sizeof(T) == 8, T> bit_msb(T v) {
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
