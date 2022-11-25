#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>

#include <SDL2/SDL.h>

#include "../core/Core.h"
#include "../drawing/Colors.h"

constexpr auto SCREEN_WIDTH = 640;
constexpr auto SCREEN_HEIGHT = 480;
// constexpr auto FRAME_LIMIT = 60;

class Rect : public GameObject {
private:
  int posX;
  int posY;
  int width;
  int height;
  LNCore *core;

public:
  Rect(LNCore *core, int posX, int posY, int width, int height)
      : posX(posX), posY(posY), width(width), height(height), core(core) {}

  void center() {
    posX = core->getWindowWidth() / 2;
    posY = core->getWindowHeight() / 2;
  }

  int onUpdate(int eps) override {
    auto rect = SDL_Rect();
    rect.w = width;
    rect.h = height;
    rect.x = posX;
    rect.y = posY;

    const auto speed = 1;

    auto keys = core->getKeyPressed();
    // SDL_Event event;
    if ((*keys)[SDLK_UP]) {
      posY -= speed;
    }

    if ((*keys)[SDLK_DOWN]) {
      posY += speed;
    }

    if ((*keys)[SDLK_LEFT]) {
      posX -= speed;
    }

    if ((*keys)[SDLK_RIGHT]) {
      posX += speed;
    }

    auto canvas2D = Rect::core->getCanvas();
    canvas2D->fillRect(&rect, canvas2D->getColor(Colors::Red));
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
  auto rect = Rect(core, 0, 0, 15, 15);
  rect.center();
  core->addObject(&rect);

  core->loop();
  return core->close();
}