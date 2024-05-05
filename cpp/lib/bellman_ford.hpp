#include "base.hpp"

// 戻り値は負の閉路が検出されたかどうか
template <typename E, typename DistIt,
          typename Cost = decltype(declval<E>().cost)>
bool base_bellman_ford(const vector<E> g[], int n, DistIt d) {
  rep(k, n) {
    bool updated = false;
    rep(i, n) {
      for (auto& e : g[i]) {
        int j = e.to;
        if (d[i] + e.cost < d[j]) {
          d[j] = d[i] + e.cost;
          updated = true;
        }
      }
    }
    if (!updated) {
      return false;
    }
  }
  return true;
}

template <typename E, typename Cost = decltype(declval<E>().cost)>
bool has_negative_loop(const vector<E> g[], int n) {
  vector<Cost> d(n, 0);
  return base_bellman_ford(g, n, d);
}

// 戻り値の first は負の閉路が検出されたかどうか
template <typename E, typename Cost = decltype(declval<E>().cost)>
pair<bool, vector<Cost>> bellman_ford(const vector<E> g[], int n, int s,
                                      Cost inf) {
  vector<Cost> d(n, inf);
  d[s] = 0;
  bool has_negative_loop = base_bellman_ford(g, n, d);
  return {has_negative_loop, d};
}
