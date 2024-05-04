#include "base.hpp"
#include "util/graph_to.hpp"

template <int N>
class HLD {
 public:
  int subtree_size[N];
  int heavy_to[N];

 public:
  int parent[N];
  int heavy_head[N];  // i を含む heavy path の端点
  int postorder[N];   // i が帰りがけ順で何番目か

 public:
  template <typename E>
  void init(vector<E> t[], int s = 0) {
    main_dfs(t, s);
    int ord = 0;
    sub_dfs(t, s, ord);
  }

  vector<pair<int, int>> path(int u, int v, bool vertex = true) {
    vector<pair<int, int>> path;
    while (1) {
      if (postorder[u] > postorder[v]) {
        swap(u, v);
      }
      if (heavy_head[u] == heavy_head[v]) {
        break;
      }
      path.emplace_back(postorder[u], postorder[heavy_head[u]] + 1);
      u = parent[heavy_head[u]];
    }
    path.emplace_back(postorder[u], postorder[v] + vertex);
    return path;
  }

  int lca(int u, int v) {
    while (1) {
      if (postorder[u] > postorder[v]) {
        swap(u, v);
      }
      if (heavy_head[u] == heavy_head[v]) {
        break;
      }
      u = parent[heavy_head[u]];
    }
    return v;
  }

 private:
  // heavy path を先頭にする
  template <typename E>
  void main_dfs(vector<E> t[], int i, int p = -1) {
    subtree_size[i] = 1;
    heavy_to[i] = -1;
    for (auto& e : t[i]) {
      int j = graph_to(e);
      if (j != p) {
        main_dfs(t, j, i);
        if (heavy_to[i] == -1 || subtree_size[heavy_to[i]] < subtree_size[j]) {
          heavy_to[i] = j;
        }
        subtree_size[i] += subtree_size[j];
      }
    }
  }

  // parent, heavy_head, postorder の計算
  template <typename E>
  void sub_dfs(vector<E> t[], int i, int& ord, int p = -1,
               bool is_heavy = false) {
    parent[i] = p;
    heavy_head[i] = is_heavy ? heavy_head[p] : i;
    for (auto& e : t[i]) {
      int j = graph_to(e);
      if (j != p && j != heavy_to[i]) {
        sub_dfs(t, j, ord, i, false);
      }
    }
    if (heavy_to[i] != -1) {
      sub_dfs(t, heavy_to[i], ord, i, true);
    }
    postorder[i] = ord++;
  }
};
