#include "util.h"

namespace Javascript {

  void print(const char *s) {
    int length = strlen(s);
      char* o;
      o = (char*)malloc(length+1);
      memcpy(o, s, length);
      *(o+length) = '\0';
      println((uint32_t)o);
  }

}

namespace util {

  int abs(int n) {
    int const mask = n >> 31;
    return (n + mask) ^ mask;
  }

}