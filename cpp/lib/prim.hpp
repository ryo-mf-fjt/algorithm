#include <queue>

#include "base.hpp"

// E は to, cost を持つ
template <typename E, typename UsedIt,
          typename Cost = decltype(declval<E>().cost)>
Cost prim(const vector<E> g[], UsedIt used, int s,
          typename iterator_traits<UsedIt>::value_type used_mark = true) {
  using P = pair<Cost, int>;
  priority_queue<P, vector<P>, greater<P>> q;
  Cost c = 0;
  q.push({0, s});
  while (!q.empty()) {
    P p = q.top();
    q.pop();
    if (used[p.second] == used_mark) {
      continue;
    }
    used[p.second] = used_mark;
    c += p.first;
    for (auto& e : g[p.second]) {
      if (used[e.to] != used_mark) {
        q.push({e.cost, e.to});
      }
    }
  }
  return c;
}

// E は to, cost を持つ
template <typename E, typename Cost = decltype(declval<E>().cost)>
Cost prim(const vector<E> g[], int n, int s = 0) {
  vector<bool> used(n);
  return prim(g, used.begin(), s);
}
