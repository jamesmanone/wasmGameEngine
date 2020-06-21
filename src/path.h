#ifndef PATH_H
#define PATH_H
#include "v2d.h"

template<class T>
class Path {
public:
  Path<T>() { vectors = (v2d<T>*)malloc(sizeof(v2d<T>) * 10); };
  ~Path<T>() { free(vectors); }

  v2d<T> &operator[](int i) { return *(vectors+i); }

  int size() const { return _size; }
  void push(v2d<T> v) {
    if(_size >= maxSize) expand();
    *(vectors+_size++) = v;
  }

private:
  v2d<T> *vectors{nullptr};
  int _size{0};
  int maxSize{10};

  void expand() {
    auto temp = vectors;
    // maxSize *= 3;
    vectors = (v2d<T>*)malloc(sizeof(v2d<T>)*maxSize*3);
    memcpy(vectors, temp, sizeof(v2d<T>)*maxSize);
    maxSize *= 3;
  }
};

#endif