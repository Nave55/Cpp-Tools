#pragma once

#include <concepts>

namespace Concept {
template <typename T>
concept Numeric = (std::integral<T> && !std::same_as<T, bool> && !std::same_as<T, char> &&
                   !std::same_as<T, signed char> && !std::same_as<T, unsigned char>) ||
                  std::floating_point<T>;
}
