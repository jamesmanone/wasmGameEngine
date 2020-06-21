#include "wrapper.h"
#include "renderer.h"
#include <string>

Wrapper* Wrapper::me = nullptr;
int Wrapper::w = 0;
int Wrapper::h = 0;


Wrapper::Wrapper() : renderer(w, h) {
  Javascript::print("Wrapper created!");
  if(w == 0 || h == 0) Javascript::print("no HxW");
  lastT = Javascript::now();
}

Wrapper* Wrapper::get() {
  if(me == nullptr) me = new Wrapper();
  return me;
}

void Wrapper::setDimensions(int _w, int _h) {
  w = _w;
  h = _h;
}

void Wrapper::step() {
  double deltaT = Javascript::now() - lastT;
  if(deltaT >= 3000.0f) {
    double fps = frames/(deltaT/1000);
    lastT += deltaT;
    geo = !geo;
    frames = 0;
    Javascript::print((std::to_string(fps) + " fps").c_str());
  }
  ++frames;
  if(geo) renderer.geometryTestFrame();
  else renderer.randomFrame();
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

  void go() {
    while(1) Wrapper::get()->step();
  }
};


