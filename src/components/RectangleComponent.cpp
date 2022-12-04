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

bool LNComponents::RectangleComponent::isCollisionAABB(std::shared_ptr<RectangleComponent> component) {
    auto rectA = getRect();
    auto rectB = component->getRect();

    if(
      (
        (
          rectA->position.y + rectA->size.y >= rectB->position.y &&
          rectA->position.y <= rectB->position.y
        ) ||
        (
          rectB->position.y + rectB->size.y >= rectA->position.y &&
          rectB->position.y <= rectA->position.y
        )
      ) &&
      (
        (
          rectA->position.x + rectA->size.x >= rectB->position.x &&
          rectA->position.x <= rectB->position.x
        ) ||
        (
          rectB->position.x + rectB->size.x >= rectA->position.x &&
          rectB->position.x <= rectA->position.x
        )
      )
    ) {
      return true;
    }

    return false;
  }