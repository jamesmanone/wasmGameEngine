#ifndef UTIL_H
#define UTIL_H
#include <cstdint>
#include <string>

extern "C" {
  extern void println(uint32_t pointer);
};

namespace Javascript {
  void print(const char *s);
  extern "C" {
    extern double now(void);
    extern void drawScreen(uint32_t pointer, int width);
  }
}

namespace util {
  int abs(int);
}

#endif