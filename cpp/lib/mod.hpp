#include "base.hpp"

template <ll mod>
class Mod {
 public:
  ll val;

 public:
  inline Mod(ll val = 0) : val(val % mod) {}

  inline Mod operator+(const Mod &x) const { return Mod(this->val + x.val); }
  inline Mod operator-(const Mod &x) const {
    return Mod(this->val - x.val + mod);
  }
  inline Mod operator*(const Mod &x) const { return Mod(this->val * x.val); }

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
};

template <ll mod>
ostream &operator<<(ostream &stream, const Mod<mod> &x) {
  return stream << x.val;
};
