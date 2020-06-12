#include "renderer.h"

uint32_t Renderer::nLehmer = 0;

Renderer::Renderer(int w, int h) :
  w(w), h(h), frameBuffer(new uint32_t[w*h]) { }

void Renderer::clearScreen(Color c) {
  int l = w*h;
  for(int i = 0; i < l; ++i) frameBuffer[i] = c.color;
}

uint32_t Renderer::getRand() {
  // nLehmer += 0xE120FC15;
  // uint64_t tmp{nLehmer + 0x4A39b70D};
  // uint32_t m1 = (tmp>>32)^tmp;
  // tmp = (uint64_t)m1 * 0x12FAD5C9;
  // uint32_t m2 = (tmp>>32)^tmp;
  // return m2;
  return ((rand()&0xFFFF)<<16)|(rand()&0xFFFF);
}

void Renderer::randomFrame() {
  int l = w*h;
  for(int i = 0; i < l; ++i) frameBuffer[i] = getRand()|0xFF000000;
}



extern "C" {
  void test(int w, int h) {
    Renderer renderer(w, h);

    while(1) {
      renderer.randomFrame();
      renderer.print();
    }
  }
}