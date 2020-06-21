#ifndef V2D_H
#define V2D_H

template<class T>
class v2d {
public:
  v2d<T>();
  v2d<T>(T x, T y) : _x(x), _y(y) { }
  v2d<T>(v2d<T> const &b) : _x(b.x()), _y(b.y()) { }
  ~v2d();


  T x() const { return _x; }
  void x(T x) { _x = x; }
  T y() const { return _y; }
  void y(T y) { _y = y; }

  v2d<T> &operator=(v2d<T> &b) { _x = b.x(); _y = b.y(); return *this; }
  T &operator[](int i) { return i = 0 ? _x : _y; }
  v2d<T> operator+(v2d<T> b) { return v2d<T>(_x+b.x(), _y+b.y()); }
  v2d<T> &operator++() { ++_x; ++_y; return *this; }
  v2d<T> operator++(int) { v2d<T> t(*this); ++_x; ++_y; return t; }
  v2d<T> &operator--() { --_x; --_y; return *this; }
  v2d<T> operator--(int) { v2d<T> t(*this); --_x; --_y; return t; }
  v2d<T> &operator-=(int v) { _x-=v; _y-=v; return *this; }

private:
  T _x{0};
  T _y{0};
};

#endif