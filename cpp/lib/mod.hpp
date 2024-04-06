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

  inline Mod operator+(const Mod &x) const { return Mod(this->val + x.val); }
  inline Mod operator-(const Mod &x) const {
    return Mod(this->val - x.val + mod);
  }
  inline Mod operator*(const Mod &x) const { return Mod(this->val * x.val); }
  // mod は素数
  inline Mod operator/(const Mod &x) const { return *this * b_pow(x, mod - 2); }

  inline Mod &operator+=(const Mod &x) {
    this->val = (this->val + x.val) % mod;
    return *this;
  }
  inline Mod &operator-=(const Mod &x) {
    this->val = (this->val - x.val + mod) % mod;
    return *this;
  }
  inline Mod &operator*=(const Mod &x) {
    this->val = (this->val * x.val) % mod;
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
ostream &operator<<(ostream &stream, const Mod<mod> &x) {
  return stream << x.val;
};
