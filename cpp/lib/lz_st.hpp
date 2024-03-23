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
    init(v, _N);
  }

  void init() {
    fill_n(st, _N * 2 - 1, bottom);
    fill_n(op, _N * 2 - 1, noop);
  }
  void init(const T& v, int n) {
    vector<T> x(n, v);
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
      return st[k] = (first + l < last ? *(first + l) : bottom);
    }
    return st[k] = comp(_init(first, last, k * 2 + 1, l, (l + r) / 2),
                        _init(first, last, k * 2 + 2, (l + r) / 2, r)

           );
  }
};
