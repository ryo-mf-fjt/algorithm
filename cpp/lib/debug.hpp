#include "base.hpp"

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  return os << p.first << ' ' << p.second;
}

ostream &operator<<(ostream &os, const tuple<> &) { return os; }

template <typename T, typename... Rest>
ostream &operator<<(ostream &os, const tuple<T, Rest...> &t) {
  os << get<0>(t);
  if (sizeof...(Rest) > 0) {
    os << ' ';
  }
  tuple<Rest...> tail = apply(
      [](const T &, const Rest &...rest) { return make_tuple(rest...); }, t);
  return os << tail;
}

template <typename T>
ostream &operator<<(ostream &os, const vector<T> &x) {
  for (auto it = x.begin(); it != x.end(); ++it) {
    if (it != x.begin()) {
      os << ' ' << flush;
    }
    os << *it << flush;
  }
  return os;
}
