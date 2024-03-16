#include <algorithm>
#include <vector>

using namespace std;

#define rep(i, n) for (int i = 0; i < (n); ++i)

using ll = long long;

using ld = long double;

template <typename T>
void debug(T v) {
  cout << v << endl;
}

template <typename It>
void debug(It x, int n) {
  rep(i, n) {
    if (i != n - 1) {
      cout << x[i] << ' ' << flush;
    } else {
      cout << x[i] << endl;
    }
  }
}

template <typename It>
void debug(It x, int n, int m) {
  rep(i, n) { debug(x[i], m); }
}

template <typename T>
void debug2(string label, T v) {
  cout << label << ": " << flush;
  debug(v);
}

template <typename It>
void debug2(string label, It x, int n) {
  cout << label << ": " << flush;
  debug(x, n);
}

template <typename It>
void debug2(string label, It x, int n, int m) {
  cout << label << ": " << endl;
  debug(x, n, m);
}
