#include "renderer.h"
#include <cmath>
#include <string>
#include "path.h"



Renderer::Renderer(int w, int h) :
  w(w), h(h), frameBuffer(new uint32_t[w*h]), frame(new uint32_t[w*h]) {
    test.push(vec(0, -12));
    test.push(vec(10, 10));
    test.push(vec(10, 12));
    test.push(vec(8, 12));
    test.push(vec(8, 10));
    test.push(vec(5, 5));
    test.push(vec(-5, 5));
    test.push(vec(-8, 10));
    test.push(vec(-8, 12));
    test.push(vec(-10, 12));
    test.push(vec(-10, 10));
  }

  void Renderer::print() {
    memcpy(frame.get(), frameBuffer.get(), w*h*4);
    Javascript::drawScreen((uint32_t)frame.get(), w); 
  }

void Renderer::clearScreen(Color &c) {
  int l = w*h;
  for(int i = 0; i < l; ++i) frameBuffer[i] = c.color;
}

uint32_t Renderer::getRand() {
  return ((rand()&0xFFFF)<<16)|(rand()&0xFFFF);
}

void Renderer::randomFrame() {
  int l = w*h;
  // for(int i = 0; i < l; ++i) frameBuffer[i] = getRand()|0xFF000000;
  for(int y = 0; y < h; ++y) for(int x = 0; x < w; ++x) {
    Color c(getRand()|0xFF000000);
    setPixel(vec(x, y), c);
  }
}

void Renderer::setPixel(vec p, Color &c) {
  if(p.x() >= w || p.y() >= h || p.y() < 0 || p.x() < 0) return;
  frameBuffer[(p.y() * w) + p.x()] = c.color;
}

void Renderer::drawLine(vec p0, vec p1, Color &c) {
  int x0 = p0.x(), x1 = p1.x(), y0 = p0.y(), y1 = p1.y();
   const bool steep = util::abs(y1-y0) > util::abs(x1-x0);
  if(steep) {
    std::swap(x0, y0);
    std::swap(x1, y1);
  }
  if(x0 > x1) {
    std::swap(x0, x1);
    std::swap(y0, y1);
  }

  const int dx{x1-x0}, dy{util::abs(y1-y0)}, ystep = y0 < y1 ? 1 : -1;
  float e{dx/2.0f};

  while(x0 <= x1) {
    if(steep) setPixel(vec(y0, x0), c);
    else setPixel(vec(x0, y0), c);

    e -= dy;
    if(e < 0) {
      y0 += ystep;
      e += dx;
    }
    ++x0;
  }
}

void Renderer::drawRect(vec orig, vec size, Color &c) {
  const int xMax = orig.x()+size.x()>this->w ? this->w : orig.x()+size.x(),
            yMax = orig.y()+size.y()>this->h ? this->h : orig.y()+size.y();

  // Top and bottom
  for(int i = orig.x(); i <= xMax; ++i){
    setPixel(vec(i, orig.y()), c);
    setPixel(vec(i, yMax), c);
  } 
  // Left and right
  for(int i = orig.y(); i <= yMax; ++i) {
    setPixel(vec(orig.x(), i), c);
    setPixel(vec(xMax, i), c);
  }
}

void Renderer::drawRect(vec orig, vec size, int t, Color &c) {
  if(t==0) return;
  while(t-- != 0) {
    drawRect(orig++, size, c);
    size -= 2;
  }
}

void Renderer::fillRect(vec orig, vec size, Color &c) {
  const int xMax = orig.x()+size.x()>this->w ? this->w : orig.x()+size.x(),
            yMax = orig.y()+size.y()>this->h ? this->h : orig.y()+size.y();

  while(orig.y() <= yMax) {
    for(int i = orig.x(); i <= xMax; ++i) setPixel(vec(i, orig.y()), c);
    orig.y(orig.y()+1);
  }
}

void Renderer::drawCircle(vec cvec, int r, Color &c) {
  int d{3 - (2 * r)}, x{0}, y{r};

  while(x <= y) {
    if(d <= 0) d += (4 * x) + 6;
    else {
      d += (4 * x) - (4 * y) + 10;
      --y;
    }
    ++x;

    setPixel(cvec + vec(x, y), c);
    setPixel(cvec + vec(x, -y), c);
    setPixel(cvec + vec(-x, -y), c);
    setPixel(cvec + vec(-x, y), c);
    setPixel(cvec + vec(y, x), c);
    setPixel(cvec + vec(y, -x), c);
    setPixel(cvec + vec(-y, -x), c);
    setPixel(cvec + vec(-y, x), c);
  }
}

void Renderer::fillCircle(vec cvec, int r, Color &c) {
  for(float dy = 1; dy <= r; ++dy) {
    const float dx = floor(sqrt((2.0f * r * dy) - (dy * dy)));
    drawLine(cvec + vec((int)-dx, (int)dy-r), cvec + vec((int)dx, (int)dy-r), c);
    drawLine(cvec + vec(-dx, -dy+r), cvec + vec(dx, -dy+r), c);
  }
}

void Renderer::drawPath(vec orig, Path<int> &p, Color &c) {
  int points = p.size();
  for(int i = 1; i < points; ++i) drawLine(p[i-1] + orig, p[i] + orig, c);
  drawLine(p[0] + orig, p[points-1] + orig, c);
}

void Renderer::geometryTestFrame() {
  Color fill(0x10, 0x10, 0x10),
        blank(0, 0, 0),
        c1(0x80, 0x00, 0xFF),
        c2(0xFF, 0x00, 0x80),
        c3(0xFF, 0x6A, 0x00),
        c4(0x00, 0xCF, 0x15),
        c5(0x00, 0xCF, 0xC8),
        white(0xFF, 0xFF, 0xFF);

  clearScreen(blank);



  fillRect(vec((int)w*0.05, (int)h*0.05), vec((int)w*0.9, (int)h*0.9), fill);


  drawLine(vec(0, 0), vec(w, h), c1);
  drawLine(vec(0, h), vec(w, 0), c1);
  drawLine(vec(w/2, 0), vec(w/2, h), c1);

  drawRect(vec((int)w*0.3, (int)h*0.3), vec((int)w*0.4, (int)h*0.4), 4, c2);

  int yl{static_cast<int>(h*0.7)}, yh{static_cast<int>(h*0.3)},
      xl{static_cast<int>(w*0.3)}, xr{static_cast<int>(w*0.7)},
      r{static_cast<int>(h*0.05)};

  fillCircle(vec(xl, yl), r, c3);
  fillCircle(vec(xr, yl), r, c3);
  drawCircle(vec(xl, yh), r, c4);
  drawCircle(vec(xr, yh), r, c4);

  drawCircle(vec(0, h/2), h/2, c5);
  drawCircle(vec(0, h/2), h/2 -1, c5);
  drawCircle(vec(w, h/2), h/2, c5);
  drawCircle(vec(w, h/2), h/2 -1, c5);

  drawPath(vec(w/2, (h/4)*3), test, white);
}


// extern "C" {
//   void test(int w, int h) {
//     Renderer renderer(w, h);
//     double lastT = Javascript::now();
//     bool geo = 0;

//     while(1) {
//       double deltaT = Javascript::now() - lastT;
//       if(deltaT > 3.0f) {
//         geo = !geo;
//         lastT += deltaT;
//       }

//       if(!geo) renderer.randomFrame();
//       else renderer.geometryTestFrame();
//       renderer.print();
//     }
//   }
// }