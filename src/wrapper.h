#ifndef WRAPPER_H
#define WRAPPER_H
#include "renderer.h"
#include "util.h"

class Wrapper {
public:
  static Wrapper* get();
  void step();
  static void setDimensions(int w, int h);
private:
  Wrapper() : renderer(w, h) { Javascript::print("Wrapper created!"); }
  static Wrapper *me;
  Renderer renderer;
  static int w;
  static int h;
};

#endif