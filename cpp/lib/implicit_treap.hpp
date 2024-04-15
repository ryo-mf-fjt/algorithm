#include <random>

#include "base.hpp"

template <int N>
class ImplicitTreap {
 public:
  int l[N];
  int r[N];
  int priority[N];
  int size[N];
  int new_i;

 public:
  int root;

 public:
  ImplicitTreap() { init(); }
  ImplicitTreap(int n) { init(n); }

  void init() {
    fill_n(l, N, -1);
    fill_n(r, N, -1);
    random_device seed_gen;
    mt19937 engine(seed_gen());
    rep(i, N) { priority[i] = engine(); }
    fill_n(size, N, 1);
    new_i = 0;
    root = -1;
  }
  void init(int n) {
    init();
    _init(0, n, root);
    new_i = n;
  }

  int insert(int i) {
    int a, b;
    split(root, i, a, b);
    merge(a, new_i, root);
    merge(root, b, root);
    return new_i++;
  }

  void erase(int i) {
    int a, b, c;
    split(root, i + 1, b, c);
    split(b, i, a, b);
    merge(a, c, root);
  }

  int get(int i) {
    int a, b, c;
    split(root, i + 1, b, c);
    split(b, i, a, b);
    merge(a, b, root);
    merge(root, c, root);
    return b;
  }

  vector<int> debug() { return _debug(root); }

  void print() {
    vector<string> lines = _print(root);
    for (string& line : lines) {
      cout << line << endl;
    }
  }

 private:
  void _init(int i, int j, int& t) {
    if (i == j) {
      t = -1;
      return;
    }
    t = max_element(priority + i, priority + j) - priority;
    _init(i, t, l[t]);
    _init(t + 1, j, r[t]);
    update_size(t);
  }

  vector<int> _debug(int t) {
    if (t == -1) {
      return {};
    }
    vector<int> a = _debug(l[t]);
    vector<int> b = _debug(r[t]);
    vector<int> c;
    copy(a.begin(), a.end(), back_inserter(c));
    c.push_back(t);
    copy(b.begin(), b.end(), back_inserter(c));
    return c;
  }

  vector<string> _print(int t) {
    if (t == -1) {
      return {};
    }
    vector<string> a = _print(l[t]);
    vector<string> b = _print(r[t]);
    int an = a.size();
    int bn = b.size();
    int max_a = 0;
    for (string& v : a) {
      max_a = max(int(v.size()), max_a);
    }
    int cn = max(an, bn) + 1;
    vector<string> c(cn);
    c[0] = string(max_a, ' ') + to_string(t);
    rep(i, cn - 1) {
      if (i < an) {
        c[i + 1] += a[i];
      }
      if (i < bn) {
        c[i + 1] += string(c[0].size() - c[i + 1].size(), ' ');
        c[i + 1] += b[i];
      }
    }
    return c;
  }

 private:
  int implicit_key(int t) { return l[t] != -1 ? size[l[t]] : 0; }

 protected:
  void update_size(int t) {
    size[t] = 1;
    if (l[t] != -1) {
      size[t] += size[l[t]];
    }
    if (r[t] != -1) {
      size[t] += size[r[t]];
    }
  }

 protected:
  // i より小と i 以上に分ける
  void split(int t, int i, int& a, int& b) {
    if (t == -1) {
      a = b = -1;
      return;
    }
    int key = implicit_key(t);
    if (key < i) {
      split(r[t], i - key - 1, r[t], b);
      update_size(t);
      a = t;
    } else {
      split(l[t], i, a, l[t]);
      update_size(t);
      b = t;
    }
  }

  void merge(int a, int b, int& t) {
    if (a == -1) {
      t = b;
      return;
    }
    if (b == -1) {
      t = a;
      return;
    }
    if (priority[a] > priority[b]) {
      merge(r[a], b, r[a]);
      update_size(a);
      t = a;
    } else {
      merge(a, l[b], l[b]);
      update_size(b);
      t = b;
    }
  }
};
