#include <gtest/gtest.h>

#include "./fft.hpp"

TEST(FFT, t) {
  using F = FFT<>;
  vector<int> x = {1, 2, 3, 4};
  EXPECT_EQ(F::round(F::t(x, 4)),
            vector<complex<int>>({{10, 0}, {-2, -2}, {-2, 0}, {-2, 2}}));
}

TEST(FFT, conv) {
  using F = FFT<>;
  vector<int> x = {1, 2};
  vector<int> y = {3, 4};
  EXPECT_EQ(F::round(F::conv(x, y)),
            vector<complex<int>>({{3, 0}, {10, 0}, {8, 0}, {0, 0}}));
}
