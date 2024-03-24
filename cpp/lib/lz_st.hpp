#include <functional>

#include "base.hpp"

template <typename T, typename Op, int N>
class LzSt {
 private:
  constexpr static int pow2_ceil(int n, int _n) {
    return n <= _n ? _n : pow2_ceil(n, _n * 2);
  }

 public:
  constexpr static const int _N = pow2_ceil(N, 1);
  using Comp = function<T(const T&, const T&)>;
  using OpComp = function<Op(const Op&, const Op&)>;
  using Apply = function<T(const Op&, const T&)>;

 public:
  T bottom;
  Comp comp;
  Op noop;
  OpComp op_comp;
  Apply apply;

 public:
  T st[_N * 2 - 1];
  Op op[_N * 2 - 1];

 public:
  LzSt(const T& bottom, const Comp& comp, const Op& noop, const OpComp& op_comp,
       const Apply& apply)
      : bottom(bottom), comp(comp), noop(noop), op_comp(op_comp), apply(apply) {
    init();
  }
  LzSt(const T& bottom, const Comp& comp, const Op& noop, const OpComp& op_comp,
       const Apply& apply, const T& v)
      : bottom(bottom), comp(comp), noop(noop), op_comp(op_comp), apply(apply) {
    init(v);
  }

  void init() {
    fill_n(st, _N * 2 - 1, bottom);
    fill_n(op, _N * 2 - 1, noop);
  }
  void init(const T& v) {
    vector<T> x(_N, v);
    _init(x.begin(), x.end());
    fill_n(op, _N * 2 - 1, noop);
  }
  template <typename It>
  void init(It first, It last) {
    _init(first, last);
    fill_n(op, _N * 2 - 1, noop);
  }

  T get(int i) { return query(i, i + 1); }

  T set(int i, const T& x, int k = 0, int l = 0, int r = _N) {
    propagate(k);
    if (i < l || r <= i) {
      return st[k];
    }
    if (l == i && r == i + 1) {
      return st[k] = x;
    }
    return st[k] = comp(set(i, x, k * 2 + 1, l, (l + r) / 2),
                        set(i, x, k * 2 + 2, (l + r) / 2, r)

           );
  }

  T operate(int a, int b, const Op& z, int k = 0, int l = 0, int r = _N) {
    propagate(k);
    if (b <= l || r <= a) {
      return st[k];
    }
    if (a <= l && r <= b) {
      op[k] = z;
      return apply(z, st[k]);
    }
    return st[k] = comp(operate(a, b, z, k * 2 + 1, l, (l + r) / 2),
                        operate(a, b, z, k * 2 + 2, (l + r) / 2, r));
  }

  T query(int a, int b, int k = 0, int l = 0, int r = _N) {
    propagate(k);
    if (b <= l || r <= a) {
      return bottom;
    }
    if (a <= l && r <= b) {
      return st[k];
    }
    return comp(query(a, b, k * 2 + 1, l, (l + r) / 2),
                query(a, b, k * 2 + 2, (l + r) / 2, r)

    );
  }

  vector<T> debug(int n) {
    vector<T> x(n);
    rep(i, n) { x[i] = get(i); }
    return x;
  }

 private:
  void propagate(int k) {
    st[k] = apply(op[k], st[k]);
    if (k < _N - 1) {
      op[k * 2 + 1] = op_comp(op[k * 2 + 1], op[k]);
      op[k * 2 + 2] = op_comp(op[k * 2 + 2], op[k]);
    }
    op[k] = noop;
  }

  template <typename It>
  T _init(It first, It last, int k = 0, int l = 0, int r = _N) {
    if (r - l == 1) {
      return st[k] = (first + l < last ? first[l] : bottom);
    }
    return st[k] = comp(_init(first, last, k * 2 + 1, l, (l + r) / 2),
                        _init(first, last, k * 2 + 2, (l + r) / 2, r)

           );
  }
};

template <typename T, typename Op, int N>
class CntLzSt {
 public:
  using Comp = function<T(const T&, const T&)>;
  using OpComp = function<Op(const Op&, const Op&)>;
  using Apply = function<T(const Op&, const T&, int)>;

 public:
  using P = pair<T, int>;
  using LzSt = LzSt<P, Op, N>;

 public:
  LzSt lz_st;

 public:
  inline CntLzSt(const T& bottom, const Comp& comp, const Op& noop,
                 const OpComp& op_comp, const Apply& apply)
      : CntLzSt(bottom, comp, noop, op_comp, apply, bottom) {}
  inline CntLzSt(const T& bottom, const Comp& comp, const Op& noop,
                 const OpComp& op_comp, const Apply& apply, const T& v)
      : lz_st(
            P(bottom, 0),
            [=](const P& a, const P& b) {
              return P(comp(a.first, b.first), a.second + b.second);
            },
            noop, op_comp,
            [=](const Op& z, const P& a) {
              return P(apply(z, a.first, a.second), a.second);
            },
            P(v, 1)) {}

  inline void init() { init(lz_st.bottom.first); }
  inline void init(const T& v) { lz_st.init(P(v, 1)); }
  template <typename It>
  inline void init(It first, It last) {
    vector<P> x;
    transform(first, last, back_inserter(x),
              [](const T& v) { return P(v, 1); });
    lz_st.init(x.begin(), x.end());
  }

  inline T get(int i) { return lz_st.get(i).first; }

  inline void set(int i, const T& x) { return lz_st.set(i, P(x, 1)); }

  inline void operate(int a, int b, const Op& z) { lz_st.operate(a, b, z); }

  inline T query(int a, int b) { return lz_st.query(a, b).first; }

  inline vector<T> debug(int n) {
    auto x = lz_st.debug();
    vector<T> y;
    transform(x.begin(), x.end(), back_inserter(y),
              [](const P& v) { return v.first; });
    return y;
  }
};
