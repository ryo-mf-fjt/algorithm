#include <gtest/gtest.h>

#include <map>

#include "prime.hpp"

TEST(make_primes, normal) {
  vector<int> primes = make_primes(17);
  EXPECT_EQ(primes, vector<int>({2, 3, 5, 7, 11, 13, 17}));
}

TEST(prime_factorization, one) {
  using M = map<int, int>;
  EXPECT_EQ(prime_factorization(1), M());
}

TEST(prime_factorization, two) {
  using M = map<int, int>;
  EXPECT_EQ(prime_factorization(2), M({{2, 1}}));
}

TEST(prime_factorization, normal) {
  using M = map<int, int>;
  EXPECT_EQ(prime_factorization(360), M({{2, 3}, {3, 2}, {5, 1}}));
}
