#include <iostream>

#define rep(i, n) for (int i = 0; i < (n); ++i)

template <typename First>
void debug(First x, int n) {
  rep(i, n) {
    if (i != n - 1) {
      std::cout << x[i] << ' ' << std::flush;
    } else {
      std::cout << x[i] << std::endl;
    }
  }
}

template <typename First>
void debug2(First x, int n, int m) {
  rep(i, n) { debug(x[i], m); }
}
