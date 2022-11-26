#ifndef LNGAME_OBJECT_H
#define LNGAME_OBJECT_H

#include "../graphics/Geometry.h"
#include "./Core.h"
#include <array>

namespace LNObjects {

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

} // namespace LNObjects

#endif
