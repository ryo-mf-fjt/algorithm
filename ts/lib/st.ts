import { pow2Ceil } from './util/pow2Ceil';

export class St<T> {
  N: number;
  st!: T[];

  constructor(
    n: number,
    public comp: (a: T, b: T) => T,
    public bottom: T,
    v?: T,
  ) {
    this.N = pow2Ceil(n);
    if (v == null) {
      this.init();
    } else {
      this.init_v(v);
    }
  }

  init(): void {
    this.st = Array(2 * this.N - 1).fill(this.bottom);
  }
  init_v(v: T): void {
    this.init_x(Array(this.N).fill(v));
  }
  init_x(x: T[], k = 0, l = 0, r = this.N): T {
    if (r - l == 1) {
      return (this.st[k] = x[l] ?? this.bottom);
    }
    return (this.st[k] = this.comp(
      this.init_x(x, k * 2 + 1, l, (l + r) >> 1),
      this.init_x(x, k * 2 + 2, (l + r) >> 1, r),
    ));
  }

  get(i: number): T {
    return this.st[i + this.N - 1];
  }

  set(i: number, x: T): void {
    let k = i + this.N - 1;
    this.st[k] = x;
    while (k > 0) {
      k = (k - 1) >> 1;
      this.st[k] = this.comp(this.st[k * 2 + 1], this.st[k * 2 + 2]);
    }
  }

  query(a: number, b: number, k = 0, l = 0, r = this.N): T {
    if (b <= l || r <= a) {
      return this.bottom;
    }
    if (a <= l && r <= b) {
      return this.st[k];
    }
    return this.comp(
      this.query(a, b, k * 2 + 1, l, (l + r) >> 1),
      this.query(a, b, k * 2 + 2, (l + r) >> 1, r),
    );
  }

  debug(n: number): T[] {
    return this.st.slice(this.N - 1, this.N - 1 + n);
  }
}
