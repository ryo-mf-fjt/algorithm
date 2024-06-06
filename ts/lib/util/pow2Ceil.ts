export const pow2Ceil = (n: number, _n = 1): number => {
  return n <= _n ? _n : pow2Ceil(n, _n * 2);
};
