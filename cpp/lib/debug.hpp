#include "base.hpp"

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  return os << p.first << ' ' << p.second;
}

template <typename T>
ostream &operator<<(ostream &os, const tuple<T> &t) {
  return os << get<0>(t);
}

template <typename T, typename U, typename... Rest>
ostream &operator<<(ostream &os, const tuple<T, U, Rest...> &t) {
  return os << get<0>(t) << ' ' << tail(t);
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
