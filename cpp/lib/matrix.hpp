#include "base.hpp"

template <typename M,
          typename T = remove_reference_t<decltype(declval<M>()[0][0])>>
vector<int> row_reduction(M& a, int n, int m) {
  vector<int> pivots;
  int p = 0;
  rep(q, m) {
    int x = -1;
    for (int i = p; i < n; ++i) {
      if (a[i][q] != T(0)) {
        x = i;
        break;
      }
    }
    if (x == -1) {
      continue;
    }
    pivots.push_back(q);
    // row_p と row_x を入れ替える
    for (int j = q; j < m; ++j) {
      swap(a[p][j], a[x][j]);
    }
    T v = a[p][q];
    T inv_v = T(1) / v;
    for (int j = q; j < m; ++j) {
      a[p][j] *= inv_v;
    }
    for (int i = p + 1; i < n; ++i) {
      T t = a[i][q];
      for (int j = q; j < m; ++j) {
        a[i][j] -= a[p][j] * t;
      }
    }
    ++p;
  }
  return pivots;
}
