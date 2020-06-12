#ifndef RENDERER_H
#define RENDERER_H
#include <cstdint>
#include <memory>
#include "color.h"
#include "util.h"


class Renderer {
public:
  Renderer(int w, int h);
  ~Renderer();

  void clearScreen(Color c);
  void randomFrame();
  void print() { drawScreen((uint32_t)frameBuffer.get(), w); }


  static uint32_t getRand();
private:

  int w;
  int h;
  std::unique_ptr<uint32_t[]> frameBuffer;
  static uint32_t nLehmer;

};


#endif