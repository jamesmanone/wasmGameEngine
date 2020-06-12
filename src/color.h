#ifndef COLOR_H
#define COLOR_H
#include <cstdint>


class Color {
public:
  Color();
  Color(uint8_t r, uint8_t g, uint8_t b) : color(r|(g<<8)|(b<<16)|0xFF00000000) { }
  Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a) : color(r|(g<<8)|(b<<16)|(a<<24)) { }
  Color(uint32_t c) : color(c) { }

  void r(uint8_t r) { color = (color & 0xFFFFFF00) | r; }
  void g(uint8_t g) { color = (color & 0xFFFF00FF) | (g<<8); }
  void b(uint8_t b) { color = (color & 0xFF00FFFF) | (b<<16); }
  void a(uint8_t a) { color = (color & 0xFFFFFF) | (a<<24); }

  uint8_t r() { return color & 0xFF; }
  uint8_t g() { return color>>8&0xFF; }
  uint8_t b() { return color>>16&0xFF; }
  uint8_t a() { return color>>24; }

  uint32_t color;
};

#endif