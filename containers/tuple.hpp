#pragma once

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
struct NthType {
  using Type = typename NthType<I - 1, Ts...>::Type;
};

template <typename T, typename... Ts>
struct NthType<0, T, Ts...> {
  using Type = T;
};

template <typename Seq, typename... Ts>
struct TupleImpl;

template <std::size_t... Is, typename... Ts>
struct TupleImpl<std::index_sequence<Is...>, Ts...> : TupleLeaf<Is, Ts>... {
  template <typename... Us>

  constexpr explicit TupleImpl(Us&&... us)
      : TupleLeaf<Is, Ts>(std::forward<Us>(us))... {}
};

template <typename... Ts>
struct Tuple : TupleImpl<std::index_sequence_for<Ts...>, Ts...> {
  using Base = TupleImpl<std::index_sequence_for<Ts...>, Ts...>;

  template <size_t I>
  using Nth_t = typename NthType<I, Ts...>::Type;

  template <size_t I>
  using Leaf_t = TupleLeaf<I, Nth_t<I>>;

  constexpr Tuple() = default;

  template <typename... Us>
    requires(sizeof...(Us) == sizeof...(Ts))
  constexpr explicit Tuple(Us&&... us)
      : Base(std::forward<Us>(us)...) {}

  template <size_t I>
  constexpr auto& get() {
    static_assert(I < sizeof...(Ts));
    return static_cast<Leaf_t<I>&>(*this).value;
  }

  template <size_t I>
  constexpr auto& get() const {
    static_assert(I < sizeof...(Ts));
    return static_cast<const Leaf_t<I>&>(*this).value;
  }
};
