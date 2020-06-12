#ifndef V2D_H
#define V2D_H

template<class T>
class v2d {
public:
  v2d<T>();
  v2d<T>(T x, T y) : x(x), y(y) { }
  v2d<T>(v2d<T> b) : x(b.x), y(b.y) { }
  ~v2d();

  T x() { return x; }
  void x(T _x) { x = _x; }
  T y() { return y; };
  void y(T _y) { y = _y; }

  T &operator[](int i) { return i = 0 ? x : y; }
private:
  T x{0};
  T y{0};
};

#endif