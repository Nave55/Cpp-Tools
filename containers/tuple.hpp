#pragma once

#include <cstddef>
#include <utility>

template <std::size_t I, typename T>
struct TupleLeaf {
  T value;

  constexpr TupleLeaf() = default;

  template <typename U>
  constexpr explicit TupleLeaf(U&& v)
      : value(std::forward<U>(v)) {}
};

template <std::size_t I, typename T, typename... Ts>
struct NthType : NthType<I - 1, Ts...> {};

template <typename T, typename... Ts>
struct NthType<0, T, Ts...> {
  using type = T;
};

template <typename Seq, typename... Ts>
struct TupleTmpl;

template <std::size_t... Is, typename... Ts>
struct TupleTmpl<std::index_sequence<Is...>, Ts...> : TupleLeaf<Is, Ts>... {
  constexpr TupleTmpl() = default;

  template <typename... Us>
  constexpr explicit TupleTmpl(Us&&... us)
      : TupleLeaf<Is, Ts>(std::forward<Us>(us))... {}
};

template <typename... Ts>
struct Tuple : TupleTmpl<std::index_sequence_for<Ts...>, Ts...> {
  using base = TupleTmpl<std::index_sequence_for<Ts...>, Ts...>;

  constexpr Tuple() = default;

  template <typename... Us>
  constexpr explicit Tuple(Us&&... us)
      : base(std::forward<Us>(us)...) {}

  template <size_t I>
  constexpr auto& get() {
    using T = typename NthType<I, Ts...>::type;
    return static_cast<TupleLeaf<I, T>&>(*this).value;
  }

  template <size_t I>
  constexpr auto& get() const {
    using T = typename NthType<I, Ts...>::type;
    return static_cast<const TupleLeaf<I, T>&>(*this).value;
  }
};
