#include <iostream>

#define rep(i, n) for (int i = 0; i < (n); ++i)

using ll = long long;

using ld = long double;

template <typename T>
void debug(T v) {
  std::cout << v << std::endl;
}

template <typename It>
void debug(It x, int n) {
  rep(i, n) {
    if (i != n - 1) {
      std::cout << x[i] << ' ' << std::flush;
    } else {
      std::cout << x[i] << std::endl;
    }
  }
}

template <typename It>
void debug(It x, int n, int m) {
  rep(i, n) { debug(x[i], m); }
}

template <typename T>
void debug(std::string label, T v) {
  std::cout << label << ": " << std::flush;
  debug(v);
}

template <typename It>
void debug(std::string label, It x, int n) {
  std::cout << label << ": " << std::flush;
  debug(x, n);
}

template <typename It>
void debug(std::string label, It x, int n, int m) {
  std::cout << label << ": " << std::endl;
  debug(x, n, m);
}
