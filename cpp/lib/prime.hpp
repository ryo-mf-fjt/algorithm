#include <map>

#include "base.hpp"

// n >= 1
// [0, n] が素数かを返す
vector<bool> make_is_prime(int n) {
  vector<bool> is_prime(n + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;
  for (int i = 2; i <= n; ++i) {
    if (is_prime[i]) {
      for (int j = i * 2; j <= n; j += i) {
        is_prime[j] = false;
      }
    }
  }
  return is_prime;
}

// n >= 1
// n 以下の素数を列挙する
vector<int> make_primes(int n) {
  vector<bool> is_prime = make_is_prime(n);
  vector<int> primes;
  rep(i, n + 1) {
    if (is_prime[i]) {
      primes.push_back(i);
    }
  }
  return primes;
}

// v >= 2
template <typename T, typename M>
void _prime_factorization(T v, M& m) {
  for (int i = 2; i * i <= v; ++i) {
    if (v % i == 0) {
      ++m[i];
      _prime_factorization(v / i, m);
      return;
    }
  }
  ++m[v];
}
// v >= 1
template <typename T, typename M = map<T, int>>
M prime_factorization(T v) {
  if (v == 1) {
    return {};
  }
  M m;
  _prime_factorization(v, m);
  return m;
}
