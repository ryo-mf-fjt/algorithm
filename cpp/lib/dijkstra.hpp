#include <queue>

#include "base.hpp"

// E は to, cost を持つ
// 到達できない場合は -1
template <typename E, typename Cost = decltype(declval<E>().cost)>
vector<Cost> dijkstra(const vector<E> g[], int n, int s) {
  using P = pair<Cost, int>;
  vector<Cost> d(n, -1);
  priority_queue<P, vector<P>, greater<P>> q;
  d[s] = 0;
  q.push({d[s], s});
  while (!q.empty()) {
    P p = q.top();
    q.pop();
    if (p.first > d[p.second]) {
      continue;
    }
    for (auto& e : g[p.second]) {
      if (d[e.to] == -1 || d[e.to] > d[p.second] + e.cost) {
        d[e.to] = d[p.second] + e.cost;
        q.push({d[e.to], e.to});
      }
    }
  }
  return d;
}
