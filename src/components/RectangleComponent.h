#ifndef LNRECTANGLE_COMPONENT_H
#define LNRECTANGLE_COMPONENT_H

#include "../core/Core.h"
#include "../graphics/Geometry.h"
#include "./BaseComponents.h"
#include <iostream>

namespace LNComponents {

class RectangleComponent : public GraphicComponent2D {
private:
  LNCore *core;
  Geometry::Rectangle rect;
  std::array<Uint8, 4> color;

public:
  RectangleComponent(LNCore *core, float x, float y, float w, float h,
                     std::array<Uint8, 4> color)
      : core(core), rect(x, y, w, h), color(color){};

  void render() override;

  auto getCore() { return &(*core); }
  auto getRect() { return &rect; }
};

} // namespace LNComponents

#endif