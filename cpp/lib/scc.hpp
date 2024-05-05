#include <functional>

#include "base.hpp"
#include "util/graph_to.hpp"

template <typename E>
pair<int, vector<int>> scc(const vector<E> g[], int n) {
  vector<bool> used(n);
  vector<int> postorder;
  vector<int> comp(n, -1);
  vector<vector<int>> rg(n);
  rep(i, n) {
    for (auto& e : g[i]) {
      int j = graph_to(e);
      rg[j].push_back(i);
    }
  }

  function<void(int)> postorder_dfs = [&](int i) {
    used[i] = true;
    for (auto& e : g[i]) {
      int j = graph_to(e);
      if (!used[j]) {
        postorder_dfs(j);
      }
    }
    postorder.push_back(i);
  };

  function<void(int, int)> comp_dfs = [&](int i, int comp_n) {
    comp[i] = comp_n;
    for (int j : rg[i]) {
      if (comp[j] == -1) {
        comp_dfs(j, comp_n);
      }
    }
  };

  rep(i, n) {
    if (!used[i]) {
      postorder_dfs(i);
    }
  }

  int comp_n = 0;
  for (int k = n - 1; k >= 0; --k) {
    int i = postorder[k];
    if (comp[i] == -1) {
      comp_dfs(i, comp_n++);
    }
  }
  return {comp_n, comp};
}
