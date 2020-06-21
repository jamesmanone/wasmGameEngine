#ifndef RENDERER_H
#define RENDERER_H
#include <cstdint>
#include <memory>
#include "color.h"
#include "util.h"
#include "v2d.h"
#include "util.h"
#include "path.h"

typedef v2d<int> vec;


class Renderer {
public:
  Renderer(int w, int h);
  ~Renderer();

  void clearScreen(Color &c);
  void randomFrame();
  void geometryTestFrame();

  void print();
  void setPixel(vec p, Color &c);
  void drawLine(vec p1, vec p2, Color &c);
  void drawRect(vec orig, vec size, Color &c);
  void drawRect(vec orig, vec size, int t, Color &c);
  void fillRect(vec orig, vec size, Color &c);
  void drawCircle(vec cvec, int r, Color &c);
  void fillCircle(vec cvec, int r, Color &c);
  void drawPath(vec orig, Path<int> &p, Color &c);


  static uint32_t getRand();
private:

  int w;
  int h;
  int lock{0};
  std::unique_ptr<uint32_t[]> frameBuffer;
  std::unique_ptr<uint32_t[]> frame;
  Path<int> test;


};


#endif