#include <functional>

#include "base.hpp"

// E は int または to を持つ構造体
template <typename S, typename E>
class CentroidSolver {
 public:
  // 木, 根, 根に繋がる頂点に対しては部分木の解を格納した配列
  using Merge = function<S(const vector<E>[], int, const S[])>;

 public:
  vector<vector<E>> t;
  const Merge merge;

 public:
  vector<S> s;
  vector<int> subtree_size;
  vector<E> detached;

 public:
  CentroidSolver(const vector<E> t[], int n, const Merge& merge)
      : merge(merge) {
    this->t.resize(n);
    copy(t, t + n, this->t.begin());
    s.resize(n);
    subtree_size.resize(n);
    detached.resize(n);
  }

  S solve(int iv = 0) {
    calculate_subtree_size(iv);

    int u = search_centroid(subtree_size[iv], iv).second;

    // u への辺を消す
    for (auto& e : t[u]) {
      int v = to(e);
      auto it = find_if(t[v].begin(), t[v].end(),
                        [&](const E& x) { return to(x) == u; });
      detached[v] = *it;
      t[v].erase(it);
    }

    for (auto& e : t[u]) {
      int v = to(e);
      s[v] = solve(v);
    }

    // u への辺を戻す
    for (auto& e : t[u]) {
      int v = to(e);
      t[v].push_back(detached[v]);
    }

    return merge(t.data(), u, s.data());
  }

 private:
  template <typename _E>
  static int to(const _E& e) {
    return e.to;
  }
  static int to(int e) { return e; }

  int calculate_subtree_size(int u, int p = -1) {
    int c = 1;
    for (auto& e : t[u]) {
      int v = to(e);
      if (v != p) {
        c += calculate_subtree_size(v, u);
      }
    }
    return subtree_size[u] = c;
  }

  // n: 木のサイズ
  // u 以下の頂点から
  // 「その頂点を削除した時の部分木のサイズの最大」が最小のものを返す
  pair<int, int> search_centroid(int n, int u, int p = -1) {
    // u を削除した時の部分木のサイズの最大
    int m = n - subtree_size[u];
    for (auto& e : t[u]) {
      int v = to(e);
      if (v != p) {
        m = max(m, subtree_size[v]);
      }
    }

    pair<int, int> x(m, u);
    for (auto& e : t[u]) {
      int v = to(e);
      if (v != p) {
        x = min(x, search_centroid(n, v, u));
      }
    }
    return x;
  }
};

// E は int または to を持つ構造体
template <typename S, typename E = int>
S centroid_solve(const vector<E> t[], int n,
                 const typename CentroidSolver<S, E>::Merge& merge) {
  CentroidSolver<S, E> solver(t, n, merge);
  return solver.solve();
}
