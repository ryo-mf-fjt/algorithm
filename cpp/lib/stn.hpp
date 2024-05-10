#include "base.hpp"
#include "util/pow2_ceil.hpp"

template <typename _T, int N>
class St1 {
 public:
  using T = _T;
  using Comp = typename St<T, N>::Comp;

 public:
  St<T, N> st;

 public:
  St1(const T& bottom, const Comp& comp) : st(bottom, comp) {}

  T get(int i) { return st.get(i); }

  // v, i の順
  void set(const T& v, int i) { st.set(i, v); }

  T query(int a, int b) const { return st.query(a, b); }

  vector<T> debug(int n) { return st.debug(n); }
};

template <typename SubSt, int N>
class StN {
 public:
  constexpr static const int _N = pow2_ceil(N, 1);
  using T = typename SubSt::T;
  using Comp = typename SubSt::Comp;

 public:
  T bottom;
  Comp comp;

 public:
  char st_buf[sizeof(SubSt) * (_N * 2 - 1)];

 public:
  const SubSt* st() const { return reinterpret_cast<const SubSt*>(st_buf); }
  SubSt* st() { return reinterpret_cast<SubSt*>(st_buf); }

 public:
  StN(const T& bottom, const Comp& comp) : bottom(bottom), comp(comp) {
    rep(i, _N * 2 - 1) { new (st() + i) SubSt(bottom, comp); }
  }

  template <typename... Rest>
  T get(int i, Rest... rest) {
    return st()[i + _N - 1].get(rest...);
  }

  template <typename... Rest>
  void set(const T& x, int i, Rest... rest) {
    int k = i + _N - 1;
    st()[k].set(x, rest...);
    while (k > 0) {
      k = (k - 1) / 2;
      st()[k].set(
          comp(st()[k * 2 + 1].get(rest...), st()[k * 2 + 2].get(rest...)),
          rest...);
    }
  }

  template <typename... Rest>
  T query(int a, int b, Rest... rest) const {
    return _query<Rest...>(a, b, 0, 0, _N, rest...);
  }

  template <typename... Rest>
  T _query(int a, int b, int k, int l, int r, Rest... rest) const {
    if (b <= l || r <= a) {
      return bottom;
    }
    if (a <= l && r <= b) {
      return st()[k].query(rest...);
    }
    return comp(_query(a, b, k * 2 + 1, l, (l + r) / 2, rest...),
                _query(a, b, k * 2 + 2, (l + r) / 2, r, rest...)

    );
  }

  template <typename... Rest,
            typename V = decltype(declval<SubSt>().debug(declval<Rest>()...))>
  vector<V> debug(int n, Rest... rest) {
    vector<V> x(n);
    rep(i, n) { x[i] = st()[_N - 1 + i].debug(rest...); }
    return x;
  }
};
