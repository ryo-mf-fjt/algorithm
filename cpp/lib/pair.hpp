#include "base.hpp"

template <typename P, typename Q, typename S, typename T>
auto operator+(const pair<P, Q>& a, const pair<S, T>& b) {
  return make_pair(a.first + b.first, a.second + b.second);
}

template <typename P, typename Q, typename S, typename T>
auto operator-(const pair<P, Q>& a, const pair<S, T>& b) {
  return make_pair(a.first - b.first, a.second - b.second);
}

template <typename P, typename Q, typename S, typename T>
auto operator*(const pair<P, Q>& a, const pair<S, T>& b) {
  return make_pair(a.first * b.first, a.second * b.second);
}

template <typename P, typename Q, typename S, typename T>
pair<P, Q>& operator+=(pair<P, Q>& a, const pair<S, T>& b) {
  a.first += b.first;
  a.second += b.second;
  return a;
}

template <typename P, typename Q, typename S, typename T>
pair<P, Q>& operator-=(pair<P, Q>& a, const pair<S, T>& b) {
  a.first -= b.first;
  a.second -= b.second;
  return a;
}

template <typename P, typename Q, typename S, typename T>
pair<P, Q>& operator*=(pair<P, Q>& a, const pair<S, T>& b) {
  a.first *= b.first;
  a.second *= b.second;
  return a;
}
