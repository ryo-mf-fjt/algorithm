pub fn read<T: std::str::FromStr>(v: &mut T) {
    let mut s = String::new();
    let _ = std::io::stdin().read_line(&mut s);
    *v = s.trim_end().parse().ok().unwrap();
}

pub fn read_2<T: std::str::FromStr, U: std::str::FromStr>(a: &mut T, b: &mut U) {
    let mut s = String::new();
    let _ = std::io::stdin().read_line(&mut s);
    s.trim_end().split(' ').enumerate().for_each(|(i, v)| {
        if i == 0 {
            *a = v.parse().ok().unwrap();
        } else {
            *b = v.parse().ok().unwrap();
        }
    })
}

pub fn read_3<T: std::str::FromStr, U: std::str::FromStr, V: std::str::FromStr>(
    a: &mut T,
    b: &mut U,
    c: &mut V,
) {
    let mut s = String::new();
    let _ = std::io::stdin().read_line(&mut s);
    s.trim_end().split(' ').enumerate().for_each(|(i, v)| {
        if i == 0 {
            *a = v.parse().ok().unwrap();
        } else if i == 1 {
            *b = v.parse().ok().unwrap();
        } else {
            *c = v.parse().ok().unwrap();
        }
    })
}

pub fn read_4<
    T: std::str::FromStr,
    U: std::str::FromStr,
    V: std::str::FromStr,
    W: std::str::FromStr,
>(
    a: &mut T,
    b: &mut U,
    c: &mut V,
    d: &mut W,
) {
    let mut s = String::new();
    let _ = std::io::stdin().read_line(&mut s);
    s.trim_end().split(' ').enumerate().for_each(|(i, v)| {
        if i == 0 {
            *a = v.parse().ok().unwrap();
        } else if i == 1 {
            *b = v.parse().ok().unwrap();
        } else if i == 2 {
            *c = v.parse().ok().unwrap();
        } else {
            *d = v.parse().ok().unwrap();
        }
    })
}

pub fn read_arr<T: std::str::FromStr>(arr: &mut [T]) {
    let mut s = String::new();
    let _ = std::io::stdin().read_line(&mut s);
    s.trim_end()
        .split(' ')
        .enumerate()
        .for_each(|(i, v)| arr[i] = v.parse().ok().unwrap())
}

fn main() {
    let mut n: i32 = 0;
    read(&mut n);
    println!("{}", n);
}
