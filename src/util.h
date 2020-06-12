#ifndef UTIL_H
#define UTIL_H
#include <cstdint>
#include <string>

extern "C" {
  extern void drawScreen(uint32_t pointer, int width);
  extern void println(uint32_t pointer);
};

namespace Javascript {
  void print(const char *s);
}

#endif