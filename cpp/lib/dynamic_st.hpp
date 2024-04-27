#include <functional>
#include <random>

#include "base.hpp"

template <typename T, int N>
class DynamicSt {
 public:
  using Comp = function<T(const T&, const T&)>;

 public:
  int l[N];
  int r[N];
  int priority[N];
  int size[N];
  int new_i;

 public:
  int root;

 public:
  const T bottom;
  const Comp comp;

 public:
  T val[N];
  T acc[N];

 public:
  DynamicSt(const T& bottom, const Comp& comp) : bottom(bottom), comp(comp) {
    init();
  }
  DynamicSt(const T& bottom, const Comp& comp, int n)
      : bottom(bottom), comp(comp) {
    init(n);
  }
  DynamicSt(const T& bottom, const Comp& comp, int n, const T& v)
      : bottom(bottom), comp(comp) {
    init(n, v);
  }

  void init() {
    fill_n(l, N, -1);
    fill_n(r, N, -1);
    random_device seed_gen;
    mt19937 engine(seed_gen());
    rep(i, N) { priority[i] = engine(); }
    fill_n(size, N, 1);
    new_i = 0;
    root = -1;
    fill_n(val, N, bottom);
    fill_n(acc, N, bottom);
  }
  void init(int n) {
    init();
    _init(0, n, root);
    new_i = n;
  }
  void init(int n, const T& v) {
    init();
    fill_n(val, n, v);
    fill_n(acc, n, v);
    _init(0, n, root);
    new_i = n;
  }
  template <typename It>
  void init(It first, It last) {
    init();
    int n = last - first;
    copy_n(first, n, val);
    copy_n(first, n, acc);
    _init(0, n, root);
    new_i = n;
  }

  int insert(int i, const T& v) {
    val[new_i] = v;
    acc[new_i] = v;
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

  T get(int i) {
    int a, b, c;
    split(root, i + 1, b, c);
    split(b, i, a, b);
    merge(a, b, root);
    merge(root, c, root);
    return val[b];
  }

  void set(int i, const T& x) {
    int a, b, c;
    split(root, i + 1, b, c);
    split(b, i, a, b);
    val[b] = acc[b] = x;
    merge(a, b, root);
    merge(root, c, root);
  }

  T query(int a, int b) {
    int x, y, z;
    split(root, b, y, z);
    split(y, a, x, y);
    T r = y != -1 ? acc[y] : bottom;
    merge(x, y, root);
    merge(root, z, root);
    return r;
  }

  vector<int> debug() { return _debug(root); }

 private:
  void _init(int i, int j, int& t) {
    if (i == j) {
      t = -1;
      return;
    }
    t = max_element(priority + i, priority + j) - priority;
    _init(i, t, l[t]);
    _init(t + 1, j, r[t]);
    update(t);
  }

  vector<int> _debug(int t) {
    if (t == -1) {
      return {};
    }
    vector<int> a = _debug(l[t]);
    vector<int> b = _debug(r[t]);
    vector<int> c;
    copy(a.begin(), a.end(), back_inserter(c));
    c.push_back(val[t]);
    copy(b.begin(), b.end(), back_inserter(c));
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

  void update(int t) {
    update_size(t);
    acc[t] = comp(l[t] != -1 ? acc[l[t]] : bottom,
                  comp(val[t], r[t] != -1 ? acc[r[t]] : bottom));
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
      update(t);
      a = t;
    } else {
      split(l[t], i, a, l[t]);
      update(t);
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
      update(a);
      t = a;
    } else {
      merge(a, l[b], l[b]);
      update(b);
      t = b;
    }
  }
};
