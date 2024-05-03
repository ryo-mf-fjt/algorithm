#include "../base.hpp"

template <typename It, typename ByIt, typename ByCntIt>
void stable_counting_sort_by(It first, int n, ByIt by, It result, int by_from,
                             int by_to, ByCntIt tmp_tc, ByCntIt tmp_c) {
  int by_n = by_to - by_from;
  fill_n(tmp_tc, by_n, 0);
  fill_n(tmp_c, by_n, 0);
  rep(i, n) { ++tmp_tc[by[first[i]] - by_from]; }
  rep(i, by_n - 1) { tmp_tc[i + 1] += tmp_tc[i]; }
  rep(i, n) {
    int k = by[first[i]] - by_from;
    result[(k > 0 ? tmp_tc[k - 1] : 0) + tmp_c[k]] = first[i];
    ++tmp_c[k];
  }
}
