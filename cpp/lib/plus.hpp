#include <tuple>

#include "base.hpp"

template <typename T, typename U>
pair<T, U> operator+(const pair<T, U>& a, const pair<T, U>& b) {
  return make_pair(a.first + b.first, a.second + b.second);
}

template <typename T, typename U>
pair<T, U> operator-(const pair<T, U>& a, const pair<T, U>& b) {
  return make_pair(a.first - b.first, a.second - b.second);
}

tuple<> operator+(const tuple<>&, const tuple<>&) { return make_tuple(); }

template <typename T, typename... Rest>
tuple<T, Rest...> operator+(const tuple<T, Rest...>& a,
                            const tuple<T, Rest...>& b) {
  return tuple_cat(make_tuple(get<0>(a) + get<0>(b)), tail(a) + tail(b));
}
