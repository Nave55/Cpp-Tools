#pragma once

#include <cstdio>
#include <span>

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
