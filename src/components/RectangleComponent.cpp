#include "./RectangleComponent.h"

#include <iostream>

void LNComponents::RectangleComponent::render() {
  SDL_Rect sdlRect;
  sdlRect.w = static_cast<int>(rect.size.x);
  sdlRect.h = static_cast<int>(rect.size.y);
  sdlRect.x = static_cast<int>(rect.position.x);
  sdlRect.y = static_cast<int>(rect.position.y);

  auto canvas2D = core->getCanvas();
  canvas2D->fillRect(&sdlRect, canvas2D->getColor(RectangleComponent::color));
}