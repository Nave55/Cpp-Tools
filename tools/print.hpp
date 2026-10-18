#pragma once

#include <span>
#include "../containers/pair.hpp"
#include "../containers/str.hpp"
#include "../containers/string.hpp"

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
