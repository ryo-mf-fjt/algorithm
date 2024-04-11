#include <tuple>

#include "base.hpp"

template <typename T, typename... Rest>
tuple<Rest...> tail(tuple<T, Rest...>);

template <typename Op>
tuple<> tuple_op(tuple<>, tuple<>, Op);

template <typename FirstA, typename... RestA, typename B, typename Op>
auto tuple_op(tuple<FirstA, RestA...> a, B b, Op op) {
  return tuple_cat(make_tuple(op(get<0>(a), get<0>(b))),
                   tuple_op(tail(a), tail(b), op));
};

template <typename A, typename B, typename Op>
using tuple_op_t =
    decltype(tuple_op(declval<A>(), declval<B>(), declval<Op>()));

template <typename Op, typename Seq>
struct tuple_seq_op {
  template <typename A, typename B>
  void operator()(A&, B&) {}

  template <typename A, typename B, typename R>
  void operator()(A&, B&, R&) {}
};

template <typename Op, size_t seq_first, size_t... seq_rest>
struct tuple_seq_op<Op, index_sequence<seq_first, seq_rest...>> {
  template <typename A, typename B>
  void operator()(A& a, B& b) {
    Op()(get<seq_first>(a), get<seq_first>(b));
    tuple_seq_op<Op, index_sequence<seq_rest...>>()(a, b);
  }

  template <typename A, typename B, typename R>
  void operator()(A& a, B& b, R& r) {
    get<seq_first>(r) = Op()(get<seq_first>(a), get<seq_first>(b));
    tuple_seq_op<Op, index_sequence<seq_rest...>>()(a, b, r);
  }
};

template <typename... As, typename B>
auto operator+(const tuple<As...>& a, const B& b) {
  tuple_op_t<tuple<As...>, B, plus<>> r;
  tuple_seq_op<plus<>, index_sequence_for<As...>>()(a, b, r);
  return r;
}

template <typename... As, typename B>
auto operator-(const tuple<As...>& a, const B& b) {
  tuple_op_t<tuple<As...>, B, plus<>> r;
  tuple_seq_op<minus<>, index_sequence_for<As...>>()(a, b, r);
  return r;
}

template <typename... As, typename... Bs>
auto operator*(const tuple<As...>& a, const tuple<Bs...>& b) {
  tuple_op_t<tuple<As...>, tuple<Bs...>, plus<>> r;
  tuple_seq_op<multiplies<>, index_sequence_for<As...>>()(a, b, r);
  return r;
}

struct plus_eq {
  template <typename A, typename B>
  A& operator()(A& a, const B& b) {
    return a += b;
  };
};

template <typename... As, typename... Bs>
tuple<As...>& operator+=(tuple<As...>& a, const tuple<Bs...>& b) {
  tuple_seq_op<plus_eq, index_sequence_for<As...>>()(a, b);
  return a;
}

struct minus_eq {
  template <typename A, typename B>
  A& operator()(A& a, const B& b) {
    return a -= b;
  };
};

template <typename... As, typename... Bs>
tuple<As...>& operator-=(tuple<As...>& a, const tuple<Bs...>& b) {
  tuple_seq_op<minus_eq, index_sequence_for<As...>>()(a, b);
  return a;
}

struct multiplies_eq {
  template <typename A, typename B>
  A& operator()(A& a, const B& b) {
    return a *= b;
  };
};

template <typename... As, typename... Bs>
tuple<As...>& operator*=(tuple<As...>& a, const tuple<Bs...>& b) {
  tuple_seq_op<multiplies_eq, index_sequence_for<As...>>()(a, b);
  return a;
}
