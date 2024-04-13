#include <gtest/gtest.h>

#include "bit.hpp"
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
