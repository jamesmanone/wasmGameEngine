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
  Wrapper();
  static Wrapper *me;
  Renderer renderer;
  static int w;
  static int h;
  double lastT;
  bool geo{false};
};

#endif