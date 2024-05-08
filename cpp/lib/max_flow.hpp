#include <queue>

#include "base.hpp"

template <int N, typename Cap>
class MaxFlow {
 public:
  struct EE {
    int to;
    Cap cap;
    int rev;
  };

 public:
  int n;
  vector<EE> gg[N];
  int level[N];
  int iter[N];

 public:
  MaxFlow() : n(0) {}
  template <typename E>
  MaxFlow(vector<E> g[], int n) {
    init(g, n);
  }

  template <typename E>
  void init(vector<E> g[], int n) {
    this->n = n;
    rep(i, n) {
      for (auto& e : g[i]) {
        gg[i].push_back(EE({e.to, e.cap, int(gg[e.to].size())}));
        gg[e.to].push_back(EE({i, 0, int(gg[i].size()) - 1}));
      }
    }
  }

  void bfs(int s) {
    fill_n(level, n, -1);
    queue<int> q;
    level[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int i = q.front();
      q.pop();
      for (auto& e : gg[i]) {
        if (e.cap > 0 && level[e.to] == -1) {
          level[e.to] = level[i] + 1;
          q.push(e.to);
        }
      }
    }
  }

  Cap dfs(int i, int t, Cap c) {
    if (i == t) {
      return c;
    }
    for (int& k = iter[i]; k < int(gg[i].size()); ++k) {
      EE& e = gg[i][k];
      if (e.cap > 0 && level[i] < level[e.to]) {
        int f = dfs(e.to, t, c == -1 ? e.cap : min(e.cap, c));
        if (f > 0) {
          e.cap -= f;
          gg[e.to][e.rev].cap += f;
          return f;
        }
      }
    }
    return 0;
  }

  // s = t なら -1
  template <typename Flow = Cap>
  Flow max_flow(int s, int t) {
    if (s == t) {
      return -1;
    }
    Flow flow = 0;
    while (1) {
      bfs(s);
      if (level[t] == -1) {
        break;
      }
      fill_n(iter, n, 0);
      while (1) {
        int f = dfs(s, t, -1);
        if (f == 0) {
          break;
        }
        flow += f;
      }
    }
    return flow;
  }
};
