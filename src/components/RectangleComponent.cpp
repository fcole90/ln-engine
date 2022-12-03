#include "./RectangleComponent.h"

#include <iostream>

void LNComponents::RectangleComponent::render() {
  SDL_Rect sdlRect;
  sdlRect.w = rect.size.x;
  sdlRect.h = rect.size.y;
  sdlRect.x = rect.position.x;
  sdlRect.y = rect.position.y;

  auto canvas2D = core->getCanvas();
  canvas2D->fillRect(&sdlRect, canvas2D->getColor(RectangleComponent::color));
}