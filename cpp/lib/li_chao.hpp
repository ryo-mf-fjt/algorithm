#include <functional>

#include "base.hpp"
#include "util/pow2_ceil.hpp"

// f たちが互いに、定義域の共通部分で差が広義単調であれば良い
// 例えば、f たちが 1 つの広義凸 (凹) 関数の平行移動の制限ならば十分
template <typename T, int N>
class LiChao {
 public:
  constexpr static const int _N = pow2_ceil(N, 1);
  using F = function<T(int)>;
  using Comp = function<bool(const T&, const T&)>;

 public:
  const T bottom;
  const Comp comp;

 public:
  F st_f[_N * 2 - 1];

 public:
  // デフォルトでは最小値を計算する
  LiChao(const T& bottom, const Comp& comp = less<T>())
      : bottom(bottom), comp(comp) {
    init();
  }

  void init() {
    fill_n(st_f, _N * 2 - 1, [&](int) { return bottom; });
  }

  T get(int i) {
    int k = i + _N - 1;
    T v = st_f[k](i);
    while (k > 0) {
      k = (k - 1) / 2;
      T w = st_f[k](i);
      if (comp(w, v)) {
        v = w;
      }
    }
    return v;
  }

  // f は [a, b) で定義されている
  void add(int a, int b, const F& f, int k = 0, int l = 0, int r = _N) {
    if (b <= l || r <= a) {
      return;
    }
    if (a <= l && r <= b) {
      T cl = st_f[k](l);
      T cr = st_f[k](r - 1);
      T fl = f(l);
      T fr = f(r - 1);
      bool bl = comp(cl, fl);
      bool br = comp(cr, fr);
      if (bl && br) {
        return;
      }
      if (!bl && !br) {
        st_f[k] = f;
        return;
      }
    }
    add(a, b, f, k * 2 + 1, l, (l + r) / 2);
    add(a, b, f, k * 2 + 2, (l + r) / 2, r);
  }

  vector<T> debug(int n) {
    vector<T> x(n);
    rep(i, n) { x[i] = get(i); }
    return x;
  }
};
