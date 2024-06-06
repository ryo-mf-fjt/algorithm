import { St } from './st';

describe('St', () => {
  it('query', () => {
    const st = new St<number>(5, Math.min, Infinity);
    st.init_x([1, 2, 3, 2, 1]);
    expect(st.query(0, 5)).toBe(1);
    expect(st.query(2, 4)).toBe(2);
  });
});
