#include "base.hpp"
#include "st.hpp"
#include "util/graph_to.hpp"

template <int N>
class LCA {
 public:
  using P = pair<int, int>;  // 深さ, 頂点

 public:
  P euler_tour[2 * N - 1];

 public:
  int first_index[N];
  St<P, 2 * N - 1> st;

 public:
  LCA() : st(P(N, 0), [](const P& a, const P& b) { return min(a, b); }) {}

  template <typename E>
  void init(vector<E> t[], int n, int s = 0) {
    int euler_tour_i = 0;
    dfs(t, s, euler_tour_i);
    st.init(euler_tour, euler_tour + 2 * n - 1);
  }

  int lca(int i, int j) {
    int a = first_index[i];
    int b = first_index[j];
    return st.query(min(a, b), max(a, b) + 1).second;
  }

 private:
  template <typename E>
  void dfs(vector<E> t[], int i, int& euler_tour_i, int p = -1, int d = 0) {
    first_index[i] = euler_tour_i;
    euler_tour[euler_tour_i].first = d;
    euler_tour[euler_tour_i++].second = i;
    for (auto& e : t[i]) {
      int j = graph_to(e);
      if (j != p) {
        dfs(t, j, euler_tour_i, i, d + 1);
        euler_tour[euler_tour_i].first = d;
        euler_tour[euler_tour_i++].second = i;
      }
    }
  }
};
