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
