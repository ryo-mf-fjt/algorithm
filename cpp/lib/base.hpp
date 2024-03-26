#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)

using ll = long long;

using ld = long double;

template <typename T, typename... Rest>
tuple<Rest...> tail(const tuple<T, Rest...>& t) {
  return apply(
      [](const T&, const Rest&... rest) { return make_tuple(rest...); }, t);
}
