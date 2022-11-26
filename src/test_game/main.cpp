#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "../core/Core.h"
#include "../core/GameObject.h"
#include "../graphics/Colors.h"

constexpr auto SCREEN_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 480;
// constexpr auto FRAME_LIMIT = 60;

class MyRect : public LNObjects::RectangleComponent {

public:
  MyRect(LNCore *core, float x, float y, float w, float h,
         std::array<Uint8, 4> color)
      : RectangleComponent(core, x, y, w, h, color){};

  void center() {
    rect.position.x = core->getWindowWidth() / 2;
    rect.position.y = core->getWindowHeight() / 2;
  }

  void render() {}

  int onUpdate(int eps) override {
    auto sdlRect = SDL_Rect();
    sdlRect.w = rect.size.x;
    sdlRect.h = rect.size.y;
    sdlRect.x = rect.position.x;
    sdlRect.y = rect.position.y;

    const auto speed = 1.0;

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

    auto canvas2D = core->getCanvas();
    canvas2D->fillRect(&sdlRect, canvas2D->getColor(Colors::Red));
    std::cout << "keys: ";
    if (keys->size() == 0) {
      std::cout << "[empty]" << std::endl;
    } else {
      for (auto key : *keys) {
        std::cout << key.first << ": " << key.second << ", ";
      }
      std::cout << std::endl;
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