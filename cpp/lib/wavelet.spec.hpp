#include <gtest/gtest.h>

#include "dynamic_bit_vec.hpp"
#include "wavelet.hpp"

TEST(Wavelet, get) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, BitVec<12>> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.debug(), x);
}

TEST(Wavelet, nth) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, BitVec<12>> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.nth(5, 3), 6);
}

TEST(Wavelet, nth_smallest) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, BitVec<12>> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.nth_smallest(1, 11, 7), 5);
}

TEST(Wavelet, range_count) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, BitVec<12>> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.range_count(1, 11, 5, 6), 4);
  EXPECT_EQ(wavelet.range_count(1, 11, 2, 5), 3);
}

TEST(Wavelet, next_value) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, BitVec<12>> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.next_value(1, 11, 2), 3);
  EXPECT_EQ(wavelet.next_value(0, 4, 0), 4);
}

TEST(Wavelet, prev_value) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, BitVec<12>> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.prev_value(1, 11, 5), 4);
  EXPECT_EQ(wavelet.prev_value(0, 4, 7), 5);
}

TEST(Wavelet, insert) {
  const int n = 12;
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, DynamicBitVec<n>> wavelet;
  for (int i = n - 1; i >= 0; --i) {
    wavelet.insert(0, x[i]);
  }
  EXPECT_EQ(wavelet.range_count(1, 11, 5, 6), 4);
  EXPECT_EQ(wavelet.range_count(1, 11, 2, 5), 3);
}

TEST(Wavelet, erase_insert) {
  const int n = 12;
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<3, DynamicBitVec<n * 2>> wavelet(n, 0);
  rep(i, n) {
    wavelet.erase(i);
    wavelet.insert(i, x[i]);
  }
  EXPECT_EQ(wavelet.range_count(1, 11, 5, 6), 4);
  EXPECT_EQ(wavelet.range_count(1, 11, 2, 5), 3);
}
