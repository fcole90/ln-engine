#include "Core.h"

#include <iostream>

#include "../graphics/Colors.h"
#include <SDL2/SDL_events.h>
#include <iostream>
#include <memory>

LNCore::LNCore(std::string window_name, int width, int height)
    : window_name(std::move(window_name)), width(width), height(height) {}

int LNCore::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
    return 1;
  }

  LNCore::window = SDL_CreateWindow(
      LNCore::window_name.c_str(), SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED, LNCore::width, LNCore::height, SDL_WINDOW_SHOWN);
  if (!LNCore::window) {
    std::cerr << "Could not create SDL Window: " << SDL_GetError() << std::endl;
    return 1;
  }

  LNCore::canvas = LNCanvas2D(LNCore::window);

  return 0;
}

int LNCore::loop() {
  auto canvas2D = LNCore::canvas;
  auto objectList = LNCore::objectList;

  // Time variables
  Uint32 delta = 0;
  Uint32 last_update = 0;
  Uint32 current_update = 1;

  // Game Loop
  while (LNCore::isLoop) {
    // Keep track of time
    last_update = current_update;
    current_update = SDL_GetTicks();
    delta = current_update - last_update;

    LNCore::inputHandler.handleInput();
    if ((*LNCore::getSpecialEvents())[LNInput::QUIT_EVENT]) {
      LNCore::isLoop = false;
    }

    // Report update
    constexpr auto ms_to_sec = 1000;
    std::cout << "FPS: " << 1.0 / delta * ms_to_sec << std::endl;

    // Game update
    canvas2D.fillRect(nullptr, canvas2D.getColor(Colors::White));

    // Update objects
    for (auto gameComponent : objectList) {
      constexpr auto tmp_eps = 1;
      gameComponent->onUpdate(tmp_eps);
    }

    // Render objects
    for (auto gameComponent : objectList) {
      auto graphicComponent =
          std::dynamic_pointer_cast<GraphicComponent2D>(gameComponent);
      if (graphicComponent) {
        graphicComponent->render();
      }
    }

    // Update canvas frame
    canvas2D.update();

    // Frame limiter
    // SDL_Delay(1000.0 / FRAME_LIMIT - (SDL_GetTicks() - current_update));
  }
  return 0;
};

int LNCore::close() {
  SDL_DestroyWindow(LNCore::window);
  SDL_Quit();
  return 0;
}
