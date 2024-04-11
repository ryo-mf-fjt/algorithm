#include <functional>

#include "base.hpp"
#include "lz_st.hpp"

template <typename T, typename Op, int N>
class StBeats : public LzSt<T, Op, N> {
 public:
  using Applicable = function<bool(const Op&, const T&)>;

 public:
  const Applicable applicable;

 public:
  StBeats(const T& bottom, const typename LzSt<T, Op, N>::Comp& comp,
          const Op& noop, const typename LzSt<T, Op, N>::OpComp& op_comp,
          const typename LzSt<T, Op, N>::Apply& apply,
          const Applicable& applicable)
      : LzSt<T, Op, N>(bottom, comp, noop, op_comp, apply),
        applicable(applicable) {}
  StBeats(const T& bottom, const typename LzSt<T, Op, N>::Comp& comp,
          const Op& noop, const typename LzSt<T, Op, N>::OpComp& op_comp,
          const typename LzSt<T, Op, N>::Apply& apply,
          const Applicable& applicable, const T& v)
      : LzSt<T, Op, N>(bottom, comp, noop, op_comp, apply, v),
        applicable(applicable) {}

  T operate(int a, int b, const Op& z, int k = 0, int l = 0,
            int r = LzSt<T, Op, N>::_N) {
    this->propagate(k);
    if (b <= l || r <= a) {
      return this->st[k];
    }
    if (a <= l && r <= b && applicable(z, this->st[k])) {  // ここだけ変更
      this->op[k] = z;
      return this->apply(z, this->st[k]);
    }
    return this->st[k] =
               this->comp(operate(a, b, z, k * 2 + 1, l, (l + r) / 2),
                          operate(a, b, z, k * 2 + 2, (l + r) / 2, r));
  }
};

template <typename T, typename Sum>
struct ChminStNode {
  T max;
  T max2;
  int max_cnt;
  Sum sum;
};

template <typename T, typename Sum, int N>
class ChminSt : public StBeats<ChminStNode<T, Sum>, T, N> {
  // inf <= * <= sup
  ChminSt(T inf, T sup)
      : StBeats<ChminStNode<T, Sum>, T, N>(
            ChminStNode<T, Sum>{inf, inf, 0, 0},
            [](const ChminStNode<T, Sum>& a, const ChminStNode<T, Sum>& b) {
              return ChminStNode<T, Sum>{
                  max(a.max, b.max),
                  a.max > b.max   ? max(b.max, a.max2)
                  : a.max < b.max ? max(a.max, b.max2)
                                  : max(a.max2, b.max2),
                  a.max > b.max   ? a.max_cnt
                  : a.max < b.max ? b.max_cnt
                                  : a.max_cnt + b.max_cnt,
                  a.sum + b.sum,
              };
            },
            sup, [](const T& a, const T& b) { return min(a, b); },
            [](const T& z, const ChminStNode<T, Sum>& v) {
              if (z >= v.max) {
                return v;
              }
              return ChminStNode<T, Sum>{
                  z,
                  v.max2,
                  v.max_cnt,
                  v.sum - (Sum(v.max) - Sum(z)) * Sum(v.max_cnt),
              };
            },
            [](const T& z, const ChminStNode<T, Sum>& v) { return z > v.max2; },
            ChminStNode<T, Sum>{sup, inf, 1, sup}) {}
};
