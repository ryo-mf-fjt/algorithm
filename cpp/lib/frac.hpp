#include "base.hpp"
#include "gcd.hpp"

template <typename T = ll>
class Frac {
 public:
  // "a / b" を表す
  T a, b;

 public:
  inline Frac(const T &a = 0, const T &b = 1) : a(a), b(b) {}

  inline Frac operator+(const Frac &x) const {
    Frac t = *this;
    t += x;
    return t;
  }
  inline Frac operator-(const Frac &x) const {
    Frac t = *this;
    t -= x;
    return t;
  }
  inline Frac operator*(const Frac &x) const {
    Frac t = *this;
    t *= x;
    return t;
  }
  inline Frac operator/(const Frac &x) const {
    Frac t = *this;
    t /= x;
    return t;
  }

  inline Frac &operator+=(const Frac &x) {
    this->a = this->a * x.b + x.a * this->b;
    this->b *= x.b;
    return this->reduce();
  }
  inline Frac &operator-=(const Frac &x) {
    this->a = this->a * x.b - x.a * this->b;
    this->b *= x.b;
    return this->reduce();
  }
  inline Frac &operator*=(const Frac &x) {
    this->a *= x.a;
    this->b *= x.b;
    return this->reduce();
  }
  inline Frac &operator/=(const Frac &x) {
    this->a *= x.b;
    this->b *= x.a;
    return this->reduce();
  }

 private:
  inline Frac &reduce() {
    if (a == 0) {
      b = 1;
      return *this;
    }
    if (b < 0) {
      a *= -1;
      b *= -1;
    }
    T g = gcd(abs(a), b);
    a /= g;
    b /= g;
    return *this;
  }
};

template <typename T>
inline bool operator==(const Frac<T> &x, const Frac<T> &y) {
  return x.a == y.a && x.b == y.b;
}

template <typename T>
inline bool operator<=(const Frac<T> &x, const Frac<T> &y) {
  return x.a * y.b <= y.a * x.b;
}

template <typename T>
inline bool operator<(const Frac<T> &x, const Frac<T> &y) {
  return x.a * y.b <= y.a * x.b;
}

template <typename T>
inline bool operator>=(const Frac<T> &x, const Frac<T> &y) {
  return y <= x;
}

template <typename T>
inline bool operator>(const Frac<T> &x, const Frac<T> &y) {
  return y < x;
}

template <typename T>
ostream &operator<<(ostream &stream, const Frac<T> &x) {
  return stream << x.a << " / " << x.b;
};