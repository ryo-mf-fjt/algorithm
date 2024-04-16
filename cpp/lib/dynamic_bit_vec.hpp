#include "base.hpp"
#include "dynamic_st.hpp"

template <int N>
class DynamicBitVec {
 public:
  DynamicSt<int, N> st;

 public:
  DynamicBitVec() : st(0, [](int a, int b) { return a + b; }) {}

  template <typename It>
  void init(It first, It last) {
    st.init(first, last);
  }

  // 0 から i - 1 までの和
  int sum(int i) { return st.query(0, i); }

  void insert(int i, int v) { st.insert(i, v); }

  void erase(int i) { st.erase(i); }
};
