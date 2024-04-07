#include <gtest/gtest.h>

#include <random>

#include "centroid_solve.hpp"

vector<int> merge_vector(const vector<int>& a, const vector<int>& b) {
  vector<int> result;
  merge(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
  return result;
}

TEST(centroid_solve, merge_sort) {
  const int n = 100000;

  vector<int> sorted(n);
  rep(i, n) { sorted[i] = i; }

  vector<int> x(sorted.begin(), sorted.end());
  random_device seed_gen;
  mt19937 engine(seed_gen());
  shuffle(x.begin(), x.end(), engine);

  vector<int> t[n];
  rep(i, n - 1) {
    t[i].push_back(i + 1);
    t[i + 1].push_back(i);
  }

  auto result = centroid_solve<vector<int>>(
      t, n, [&](const vector<int> _t[], int u, const vector<int> s[]) {
        vector<int> r{x[u]};
        for (int v : _t[u]) {
          r = merge_vector(r, s[v]);
        }
        return r;
      });
  EXPECT_EQ(result, sorted);
}
