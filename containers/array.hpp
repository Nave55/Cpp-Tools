#pragma once

#include <algorithm>
#include <cstdio>
#include <optional>
#include <span>
#include <typeinfo>

template <typename T, size_t N>
struct Array {
  T arr[N] = {};

  constexpr explicit Array() = default;

  constexpr explicit Array(std::initializer_list<T> lst) {
    size_t count = (N < lst.size()) ? N : lst.size();
    auto it = lst.begin();
    for (size_t i = 0; i < count; ++i) {
      arr[i] = *it++;
    }
  }

  constexpr Array(const Array& other) {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = other.arr[i];
    }
  }

  constexpr Array(Array&& other) noexcept {
    for (size_t i = 0; i < N; ++i) {
      arr[i] = std::move(other.arr[i]);
    }
  }

  constexpr Array& operator=(const Array& other) {
    if (this != &other) {
      for (size_t i = 0; i < N; ++i) {
        arr[i] = other.arr[i];
      }
    }
    return *this;
  }

  constexpr Array& operator=(Array&& other) noexcept {
    if (this != &other) {
      for (size_t i = 0; i < N; ++i) {
        arr[i] = std::move(other.arr[i]);
      }
    }
    return *this;
  }

  constexpr ~Array() = default;

  constexpr bool operator==(const Array& other) const {
    for (size_t i = 0; i < N; ++i) {
      if (!(arr[i] == other.arr[i])) return false;
    }
    return true;
  }

  constexpr T& operator[](size_t i) noexcept {
    return arr[i];
  }

  constexpr const T& operator[](size_t i) const noexcept {
    return arr[i];
  }

  constexpr std::optional<T&> at(size_t i) noexcept {
    if (i >= N) return std::nullopt;
    return arr[i];
  }

  constexpr std::optional<const T&> at(size_t i) const noexcept {
    if (i >= N) return std::nullopt;
    return arr[i];
  }

  constexpr size_t size() const noexcept {
    return N;
  }

  constexpr T* begin() noexcept {
    return &arr[0];
  }

  constexpr const T* begin() const noexcept {
    return &arr[0];
  }

  constexpr std::span<T> slice(size_t start, size_t end) noexcept {
    if (start >= end) return {};
    size_t actual_end = std::min(N, end);
    return std::span<T>(begin() + start, begin() + actual_end);
  }

  constexpr std::span<const T> slice(size_t start, size_t end) const noexcept {
    if (start >= end) return {};
    size_t actual_end = std::min(N, end);
    return std::span<const T>(begin() + start, begin() + actual_end);
  }

  constexpr std::span<T> toSpan() noexcept {
    return std::span<T>(&arr[0], N);
  }

  constexpr std::span<const T> toSpan() const noexcept {
    return std::span<const T>(&arr[0], N);
  }

  const char* type() const noexcept {
    return typeid(T).name();
  }

  template <typename PrintFn>
  void print(PrintFn printFn) const noexcept {
    std::printf("[");
    for (size_t i = 0; i < N; ++i) {
      if (i > 0) std::printf(", ");
      printFn(arr[i]);
    }
    std::printf("]\n");
  }

  void printInfo() const noexcept {
    std::printf("length: ");
    std::printf("%zu", N);
    std::printf(", type: ");
    printf("%s", type());
    std::printf("\n");
  }

  constexpr T* end() noexcept {
    return &arr[N];
  }

  constexpr const T* end() const noexcept {
    return &arr[N];
  }

  constexpr T first() const noexcept {
    return arr[0];
  }

  constexpr T last() const noexcept {
    return arr[N - 1];
  }

  constexpr void clear() noexcept {
    for (auto& i : arr) i = T();
  }

  constexpr void fill(const T& val) noexcept {
    std::fill(begin(), end(), val);
  }

  constexpr void reverse() noexcept {
    for (size_t i = 0; i < N / 2; ++i) std::swap(arr[i], arr[N - 1 - i]);
  }

  constexpr void sort() noexcept {
    std::sort(begin(), end());
  }

  constexpr void sortDescending() noexcept {
    std::sort(begin(), end(), [](const T& a, const T& b) { return a > b; });
  }

  template <typename Fn>
  constexpr void sortCustom(Fn fn) noexcept {
    std::sort(begin(), end(), fn);
  }

  constexpr std::optional<int> linearSearch(T x) const noexcept {
    for (size_t i = 0; i < N; i++) {
      if (arr[i] == x) return static_cast<int>(i);
    }
    return std::nullopt;
  }

  constexpr std::optional<int> binarySearch(T x) const noexcept {
    int high = static_cast<int>(N) - 1;
    int low = 0;

    while (low <= high) {
      int mid = low + ((high - low) / 2);
      if (arr[mid] == x)
        return mid;
      else if (arr[mid] > x)
        high = mid - 1;
      else
        low = mid + 1;
    }

    return std::nullopt;
  }

  constexpr void orderedRemove(size_t ind) noexcept {
    if (ind >= N) return;
    for (size_t i = ind; i + 1 < N; ++i) {
      arr[i] = std::move(arr[i + 1]);
      arr[i + 1] = T();
    }
  }

  constexpr void unorderedRemove(size_t ind) noexcept {
    if (ind >= N) return;
    arr[ind] = std::move(arr[N - 1]);
    arr[N - 1] = T();
  }

  constexpr void deleteVal(T val) noexcept {
    for (int i = static_cast<int>(N) - 1; i >= 0; --i) {
      if (arr[i] == val) orderedRemove(static_cast<size_t>(i));
    }
  }

  constexpr void deleteValUnordered(T val) noexcept {
    for (int i = static_cast<int>(N) - 1; i >= 0; --i) {
      if (arr[i] == val) unorderedRemove(static_cast<size_t>(i));
    }
  }

  template <typename Fn>
  constexpr void mapIter(Fn fn) noexcept {
    for (size_t i = 0; i < N; ++i) fn(arr[i]);
  }

  template <typename Rtype>
    requires std::is_arithmetic_v<Rtype> && std::is_arithmetic_v<T>
  constexpr std::optional<Rtype> sum() const noexcept {
    if (N == 0) return std::nullopt;
    if (N == 1) return static_cast<Rtype>(arr[0]);
    Rtype ttl = 0;
    for (size_t i = 0; i < N; ++i) ttl += static_cast<Rtype>(arr[i]);
    return ttl;
  }

  template <typename Rtype>
    requires std::is_arithmetic_v<Rtype> && std::is_arithmetic_v<T>
  constexpr std::optional<Rtype> prod() const noexcept {
    if (N == 0) return std::nullopt;
    if (N == 1) return static_cast<Rtype>(arr[0]);
    Rtype ttl = 1;
    for (size_t i = 0; i < N; ++i) ttl *= static_cast<Rtype>(arr[i]);
    return ttl;
  }

  template <typename Rtype, typename Fn>
  constexpr std::optional<Rtype> foldl(size_t init, Fn fn) const noexcept {
    if (N == 0) return std::nullopt;
    Rtype ttl = static_cast<Rtype>(init);
    for (size_t i = 0; i < N; ++i) {
      fn(ttl, static_cast<Rtype>(arr[i]));
    }
    return ttl;
  }

  template <typename Rtype, typename Fn>
  constexpr std::optional<Rtype> reduce(Fn fn) const noexcept {
    if (N == 0) return std::nullopt;
    if (N == 1) return static_cast<Rtype>(arr[0]);
    Rtype ttl = static_cast<Rtype>(arr[0]);
    for (size_t i = 1; i < N; ++i) {
      fn(ttl, static_cast<Rtype>(arr[i]));
    }
    return ttl;
  }
};
