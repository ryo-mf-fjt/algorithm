#include <gtest/gtest.h>

#include "bit.hpp"
#include "debug.hpp"
#include "wavelet.hpp"

TEST(Wavelet, get) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<int, 12, 3> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.debug(), x);
}

TEST(Wavelet, get_bit) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<int, 12, 3, Bit<int, 12>> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.debug(), x);
}

TEST(Wavelet, count) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<int, 12, 3> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.count(0, 9, 5), 4);
}

TEST(Wavelet, nth) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<int, 12, 3> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.nth(5, 3), 6);
}

TEST(Wavelet, nth_smallest) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<int, 12, 3> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.nth_smallest(1, 11, 7), 5);
}

TEST(Wavelet, range_count) {
  vector<int> x = {5, 4, 5, 5, 2, 1, 5, 6, 1, 3, 5, 0};
  Wavelet<int, 12, 3> wavelet(x.begin(), x.end());
  EXPECT_EQ(wavelet.range_count(1, 11, 5, 6), 4);
  EXPECT_EQ(wavelet.range_count(1, 11, 2, 5), 3);
}
