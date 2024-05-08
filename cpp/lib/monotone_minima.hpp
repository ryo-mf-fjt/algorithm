#include <functional>

#include "base.hpp"

// f_i が最小値を達成する最左位置を m_i とすると、m_i が広義単調増加であれば良い
// 位置 p, q を固定すると、f_i の平均の傾きが i に関して広義単調減少であれば十分
template <typename T>
vector<int> monotone_minima(const function<T(int)> f[], int n, int m, int i = 0,
                            int j = 0) {
  if (i == n) {
    return {};
  }
  int p = (i + n) / 2;
  int q = j;
  T vq = f[p](j);
  for (int k = j + 1; k < m; ++k) {
    int vk = f[p](k);
    if (vk < vq) {
      q = k;
      vq = vk;
    }
  }
  vector<int> a = monotone_minima(f, p, q + 1, i, j);
  int an = a.size();
  vector<int> b = monotone_minima(f, n, m, p + 1, q);
  int bn = b.size();
  a.resize(an + bn + 1);
  a[an] = q;
  copy(b.begin(), b.end(), a.begin() + an + 1);
  return a;
}
