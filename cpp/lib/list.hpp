#include "base.hpp"

// N は追加の最大回数
template <int N>
class List {
 public:
  int prev[N];
  int next[N];
  int from;
  int to;
  int size;
  int new_i;

 public:
  List() { init(); }

  void init() {
    fill_n(prev, N, -1);
    fill_n(next, N, -1);
    from = -1;
    to = -1;
    size = 0;
    new_i = 0;
  }

  int push_front() {
    if (from != -1) {
      prev[from] = new_i;
    }
    next[new_i] = from;
    from = new_i;
    if (to == -1) {
      to = new_i;
    }
    ++size;
    return new_i++;
  }

  int push_back() {
    prev[new_i] = to;
    if (to != -1) {
      next[to] = new_i;
    }
    if (from == -1) {
      from = new_i;
    }
    to = new_i;
    ++size;
    return new_i++;
  }

  // i の前に追加
  int insert(int i) {
    int prev_i = prev[i];
    if (prev_i == -1) {
      return push_front();
    }
    prev[new_i] = prev_i;
    prev[i] = new_i;
    next[prev_i] = new_i;
    next[new_i] = i;
    ++size;
    return new_i++;
  }

  void pop_front() {
    int next_from = next[from];
    if (next_from != -1) {
      prev[next_from] = -1;
    }
    next[from] = -1;
    if (from == to) {
      to = -1;
    }
    from = next_from;
    --size;
  }

  void pop_back() {
    int prev_to = prev[to];
    prev[to] = -1;
    if (prev_to != -1) {
      next[prev_to] = -1;
    }
    if (from == to) {
      from = -1;
    }
    to = prev_to;
    --size;
  }

  void erase(int i) {
    int prev_i = prev[i];
    int next_i = next[i];
    if (prev_i == -1) {
      pop_front();
      return;
    }
    if (next_i == -1) {
      pop_back();
      return;
    }
    prev[i] = -1;
    prev[next_i] = prev_i;
    next[prev_i] = next_i;
    next[i] = -1;
    --size;
  }

  vector<int> debug() {
    vector<int> x;
    int cur = from;
    while (cur != -1) {
      x.push_back(cur);
      cur = next[cur];
    }
    return x;
  }
};
