#include "base.hpp"

template <typename T>
void debug(const T &v) {
  cout << v << endl;
}

template <typename T, typename... Rest>
void debug(const T &v, const Rest &...rest) {
  cout << v << ' ' << flush;
  debug(rest...);
}

template <typename It>
void debug(It first, It last) {
  debug(vector<typename iterator_traits<It>::value_type>(first, last));
}

template <typename... Args>
void debug_l(const char label[], Args... args) {
  cout << label << ": " << flush;
  debug(args...);
}

template <typename T>
ostream &operator<<(ostream &stream, const vector<T> &x) {
  for (auto it = x.begin(); it != x.end(); ++it) {
    if (it != x.begin()) {
      stream << ' ' << flush;
    }
    stream << *it << flush;
  }
  return stream;
};
