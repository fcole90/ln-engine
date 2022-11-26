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
// constexpr auto FRAME_LIMIT = 60;

class MyRect : public LNComponents::RectangleComponent {
  using RectangleComponent::RectangleComponent;

public:
  void center() {
    rect.position.x = core->getWindowWidth() / 2;
    rect.position.y = core->getWindowHeight() / 2;
  }

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
  auto rectComponent = MyRect(core, 0, 0, 15, 15, Colors::Red);
  rectComponent.center();
  core->addObject(&rectComponent);

  core->loop();
  return core->close();
}