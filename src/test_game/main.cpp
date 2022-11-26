#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "../components/RectangleComponent.h"
#include "../core/Core.h"
#include "../graphics/Colors.h"

constexpr auto SCREEN_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 480;
constexpr auto RECT_SIZE = 15;
constexpr auto DIST_FROM_BORDER = 5;

class ConcreteRect : public LNComponents::RectangleComponent {
  using RectangleComponent::RectangleComponent;

  int onUpdate(int eps) override { return 0; };
};

class ControlledRect : public LNComponents::RectangleComponent {
  using RectangleComponent::RectangleComponent;

public:
  int onUpdate(int eps) override {
    const auto speed = 0.1;

    auto keys = core->getKeyPressed();
    // SDL_Event event;
    if ((*keys)[SDLK_UP]) {
      rect.position.y -= speed;
    }

    if ((*keys)[SDLK_DOWN]) {
      rect.position.y += speed;
    }

    if ((*keys)[SDLK_LEFT]) {
      rect.position.x -= speed;
    }

    if ((*keys)[SDLK_RIGHT]) {
      rect.position.x += speed;
    }

    return 0;
  }
};

int main(int argc, char *args[]) {

  auto core = new LNCore("LN Engine Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  core->init();
  auto rectComponent = ControlledRect(core, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2,
                                      RECT_SIZE, RECT_SIZE, Colors::Red);
  auto otherRect1 = ConcreteRect(core, DIST_FROM_BORDER, SCREEN_HEIGHT / 2,
                                 RECT_SIZE, RECT_SIZE, Colors::Gray);
  auto otherRect2 =
      ConcreteRect(core, SCREEN_WIDTH - DIST_FROM_BORDER - RECT_SIZE,
                   SCREEN_HEIGHT / 2, RECT_SIZE, RECT_SIZE, Colors::Gray);
  core->addObject(&rectComponent);
  core->addObject(&otherRect1);
  core->addObject(&otherRect2);

  core->loop();
  return core->close();
}