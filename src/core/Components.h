#ifndef LNCOMPONENTS_H
#define LNCOMPONENTS_H

#include "./GameObject.h"

namespace LNComponents {

class RectangleComponent : public GameObject {
protected:
  LNCore *core;
  Geometry::Rectangle rect;
  std::array<Uint8, 4> color;

public:
  RectangleComponent(LNCore *core, float x, float y, float w, float h,
                     std::array<Uint8, 4> color)
      : core(core), rect(x, y, w, h), color(color){};
};

} // namespace LNComponents

#endif