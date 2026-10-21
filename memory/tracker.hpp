#include <cstdio>
#include <cstdlib>

struct Tracker {
  size_t ttl = 0;
  size_t freed = 0;

  template <typename T>
  auto alloc(T val) -> T* {
    ttl += sizeof(T);
    return new T(val);
  }

  template <typename T>
  auto dealloc(T* memory) -> void {
    freed += sizeof(T);
    delete memory;
  }

  auto malloc(size_t size) -> void* {
    ttl += size;
    return ::malloc(size);
  }

  template <typename T>
  auto free(T* memory) -> void {
    freed += sizeof(T);
    ::free(memory);
  }

  void memReport() const {
    std::printf("Memory Usage:\n");
    std::printf("  Allocated: %zu bytes\n", ttl);
    std::printf("  Freed:     %zu bytes\n", freed);
  };
};
