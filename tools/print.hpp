#pragma once

#include <array>
#include <iostream>
#include <span>
#include "../containers/pair.hpp"
#include "../containers/str.hpp"
#include "../containers/string.hpp"

// Overload << for printing arrays
template <typename T, size_t N>
std::ostream& operator<<(std::ostream& os, const std::array<T, N>& arr) {
  os << "[";
  for (size_t i{0}; i < arr.size(); ++i) {
    os << arr[i];
    if (i < arr.size() - 1) {
      os << ",";
    }
  }
  os << "]\n";
  return os;
}

// Overload << for printing pairs
template <typename T, typename S>
std::ostream& operator<<(std::ostream& os, const Pair<T, S>& pair) {
  os << "[" << pair.x << ", " << pair.y << "]\n";
  return os;
}

template <typename T, std::size_t N>
auto printCArr(const T (&arr)[N]) -> void {
  for (size_t i{0}; i < N; ++i) {
    if (i == 0) {
      std::cout << "[" << arr[i] << ", ";
    } else if (i > 0 && i < N - 1) {
      std::cout << arr[i] << ", ";
    } else {
      std::cout << arr[i] << "]\n";
    }
  }
}

inline void printValue(int v) noexcept {
  printf("%d", v);
}

inline void printValue(size_t v) noexcept {
  printf("%zu", v);
}

inline void printValue(float v) noexcept {
  printf("%f", v);
}

inline void printValue(double v) noexcept {
  printf("%f", v);
}

inline void printValue(const char* s) noexcept {
  printf("%s", s);
}

inline void printValue(char c) noexcept {
  printf("%c", c);
}

inline void printValue(String s) noexcept {
  s.print();
}

template <size_t N>
inline void printValue(Str<N> s) noexcept {
  s.print();
}

// print for spans
template <typename T, typename PrintFn>
void spanPrint(std::span<T> sli, PrintFn printFn) noexcept {
  size_t len = sli.size();
  if (sli.size() == 0) {
    std::printf("[]\n");
    return;
  }
  for (size_t i = 0; i < len; i++) {
    if (i == 0) {
      std::printf("[");
      printFn(sli[i]);
    } else if (i < len - 1) {
      std::printf(", ");
      printFn(sli[i]);
    } else {
      std::printf(", ");
      printFn(sli[i]);
      std::printf("]\n");
    }

    if (len == 1) std::printf("]\n");
  }
}
