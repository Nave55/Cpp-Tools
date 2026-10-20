#include <cstdint>
#include <cstdio>
#include <cstdlib>

struct Tracker {
  uint32_t total_allocated = 0;
  uint32_t total_freed = 0;

  void CurrentUsage() const {
    std::printf("Memory Usage:\n  Allocated: %d bytes\n  Freed:     %d bytes\n", total_allocated,
                total_freed);
  };

  template <typename T>
  auto alloc(T val) -> T* {
    total_allocated += sizeof(T);
    return new T(val);
  }

  template <typename T>
  auto dealloc(T* memory) -> void {
    total_freed += sizeof(T);
    delete memory;
  }

  auto malloc(size_t size) -> void* {
    total_allocated += size;
    return ::malloc(size);
  }

  template <typename T>
  auto free(T* memory) -> void {
    total_freed += sizeof(T);
    ::free(memory);
  }
};
