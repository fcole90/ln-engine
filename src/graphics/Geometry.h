#ifndef LNGEOMETRY_H
#define LNGEOMETRY_H

namespace Geometry {

class Point {
 public:
  float x;
  float y;
  Point(float x, float y) : x(x), y(y){};
};

class Rectangle {
 public:
  Point position;
  Point size;
  Rectangle(float x, float y, float w, float h) : position(x, y), size(w, h){};
};

}  // namespace Geometry

#endif
