#ifndef LNRECTANGLE_COMPONENT_H
#define LNRECTANGLE_COMPONENT_H

#include <iostream>

#include "../core/Core.h"
#include "../graphics/Geometry.h"
#include "./BaseComponents.h"

namespace LNComponents {

class RectangleComponent : public GraphicComponent2D {
 private:
  LNCore *core;
  Geometry::Rectangle rect;
  std::array<Uint8, 4> color;

 public:
  RectangleComponent(LNCore *core, float x, float y, float w, float h, std::array<Uint8, 4> color)
    : core(core), rect(x, y, w, h), color(color){};

  void render() override;

  bool isCollisionAABB(std::shared_ptr<RectangleComponent> component);

  // Getters
  auto getCore() { return &(*core); }
  auto getRect() { return &rect; }
};

}  // namespace LNComponents

#endif