#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)

using ll = long long;

using ld = long double;

template <typename T, typename U>
pair<T, U> operator+(const pair<T, U>& a, const pair<T, U>& b) {
  return make_pair(a.first + b.first, a.second + b.second);
}

template <typename T, typename U>
pair<T, U> operator-(const pair<T, U>& a, const pair<T, U>& b) {
  return make_pair(a.first - b.first, a.second - b.second);
}

template <typename T, typename... Rest>
tuple<Rest...> tail(const tuple<T, Rest...>& t) {
  return apply(
      [](const T&, const Rest&... rest) { return make_tuple(rest...); }, t);
}

tuple<> operator+(const tuple<>& a, const tuple<>& b) { return make_tuple(); }

template <typename T, typename... Rest>
tuple<T, Rest...> operator+(const tuple<T, Rest...>& a,
                            const tuple<T, Rest...>& b) {
  return tuple_cat(make_tuple(get<0>(a) + get<0>(b)), tail(a) + tail(b));
}
