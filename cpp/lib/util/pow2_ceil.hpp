constexpr int pow2_ceil(int n, int _n = 1) {
  return n <= _n ? _n : pow2_ceil(n, _n * 2);
}
