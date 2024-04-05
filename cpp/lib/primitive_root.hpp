#include "base.hpp"
#include "pow.hpp"

template <int...>
struct seq {
  using type = seq;
};

// seq の結合
template <typename, typename>
struct seq_cat;
template <int... Is, int... Js>
struct seq_cat<seq<Is...>, seq<Js...>> : seq<Is..., Js...> {};

// 素因数分解
template <int n, int i = 2, typename = void>
struct prime_seq : prime_seq<n, i + 1> {};
template <>
struct prime_seq<1, 2, void> : seq<> {};
template <int n, int i>
struct prime_seq<n, i, enable_if_t<(i * i > n)>> : seq<n> {};
template <int n, int i>
struct prime_seq<n, i, enable_if_t<n % i == 0>>
    : seq_cat<seq<i>, typename prime_seq<n / i>::type> {};

// 原始根か判定する
template <int p, int x, typename MulPrimes>
struct is_primitive_root : true_type {};
template <int p, int x, int first, int... rest>
struct is_primitive_root<p, x, seq<first, rest...>> {
  static const bool value = const_pow_mod(x, (p - 1) / first, p) == 1
                                ? false
                                : is_primitive_root<p, x, seq<rest...>>::value;
};

// 原始根を計算する
template <int p, int i = 1,
          typename MulPrimes = typename prime_seq<p - 1>::type, typename = void>
struct primitive_root : primitive_root<p, i + 1, MulPrimes> {};
template <int p, int i, typename MulPrimes>
struct primitive_root<p, i, MulPrimes,
                      enable_if_t<is_primitive_root<p, i, MulPrimes>::value>> {
  static const int value = i;
};
