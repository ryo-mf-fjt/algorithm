#include "base.hpp"
#include "pow.hpp"

ll reg_mod(ll x, ll mod) {
  return x >= 0 ? x % mod : (-((-x) % mod) + mod) % mod;
}

template <ll mod>
class Mod {
 public:
  ll val;

 public:
  inline Mod() : val(0) {}
  inline Mod(ll val) : val(reg_mod(val, mod)) {}

  inline Mod operator+(const Mod &x) const {
    Mod t = *this;
    t += x;
    return t;
  }
  inline Mod operator-(const Mod &x) const {
    Mod t = *this;
    t -= x;
    return t;
  }
  inline Mod operator*(const Mod &x) const {
    Mod t = *this;
    t *= x;
    return t;
  }
  // mod は素数
  inline Mod operator/(const Mod &x) const {
    Mod t = *this;
    t /= x;
    return t;
  }
  inline Mod operator-() const { return Mod() - *this; }

  inline Mod &operator+=(const Mod &x) {
    this->val += x.val;
    if (this->val >= mod) {
      this->val -= mod;
    }
    return *this;
  }
  inline Mod &operator-=(const Mod &x) {
    this->val += mod - x.val;
    if (this->val >= mod) {
      this->val -= mod;
    }
    return *this;
  }
  inline Mod &operator*=(const Mod &x) {
    this->val *= x.val;
    this->val %= mod;
    return *this;
  }
  // mod は素数
  inline Mod &operator/=(const Mod &x) { return *this *= b_pow(x, mod - 2); }
};

template <ll mod>
inline bool operator==(const Mod<mod> &x, const Mod<mod> &y) {
  return x.val == y.val;
}

template <ll mod>
inline bool operator!=(const Mod<mod> &x, const Mod<mod> &y) {
  return x.val != y.val;
}

template <ll mod>
ostream &operator<<(ostream &stream, const Mod<mod> &x) {
  return stream << x.val;
};
