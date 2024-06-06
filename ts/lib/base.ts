import fs from 'fs';

export const rep = (n: number, callback: (i: number) => void) => {
  for (let i = 0; i < n; ++i) {
    callback(i);
  }
};

let inputs: string[] | undefined;
export const read = (): string => {
  if (inputs == null) {
    inputs = fs.readFileSync(process.stdin.fd, 'utf8').split(/\s/).reverse();
  }
  return inputs.pop()!;
};

export const readNumber = (): number => {
  return Number(read());
};

export const readBigInt = (): bigint => {
  return BigInt(read());
};
