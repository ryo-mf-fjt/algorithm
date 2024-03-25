#include "base.hpp"

template <int N>
class UnionFind {
 public:
  int parent[N];
  int rank[N];

 public:
  UnionFind() {
    rep(i, N) { parent[i] = i; }
    fill_n(rank, N, 0);
  }

  int find(int i) {
    if (parent[i] == i) {
      return i;
    }
    return parent[i] = find(parent[i]);
  }

  bool same(int i, int j) { return find(i) == find(j); }

  void unite(int i, int j) {
    int p = find(i);
    int q = find(j);
    if (p == q) {
      return;
    }
    if (rank[p] < rank[q]) {
      parent[p] = q;
    } else {
      parent[q] = p;
      if (rank[p] == rank[q]) {
        ++rank[p];
      }
    }
  }

  vector<int> debug(int n) {
    vector<int> x(n);
    rep(i, n) { x[i] = find(i); }
    return x;
  }
};
