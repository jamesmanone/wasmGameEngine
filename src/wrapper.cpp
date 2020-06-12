#include "wrapper.h"
#include "renderer.h"

Wrapper* Wrapper::me = nullptr;

int Wrapper::w = 1280;
int Wrapper::h = 720;

Wrapper* Wrapper::get() {
  if(me == nullptr) me = new Wrapper();
  return me;
}

void Wrapper::setDimensions(int _w, int _h) {
  w = _w;
  h = _h;
}

void Wrapper::step() {
  renderer.randomFrame();
  renderer.print();
}


extern "C" {
  void step() {
    Wrapper::get()->step();
  }

  void setWH(int w, int h) {
    Wrapper::setDimensions(w, h);
  }

  void _free(void* p) { free(p); }
};


