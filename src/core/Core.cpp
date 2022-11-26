#include "Core.h"

#include <iostream>

#include "../graphics/Colors.h"
#include <SDL2/SDL_events.h>
#include <iostream>

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

int LNCore::handleInput() {
  // Events management
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      LNCore::isLoop = false;
      break;

    case SDL_KEYDOWN:
      LNCore::keyPressed[event.key.keysym.sym] = true;
      break;
    case SDL_KEYUP:
      LNCore::keyPressed[event.key.keysym.sym] = false;
      break;
    }
  }

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

    LNCore::handleInput();

    // Report update
    constexpr auto ms_to_sec = 1000;
    std::cout << "FPS: " << 1.0 / delta * ms_to_sec << std::endl;

    // Game update
    canvas2D.fillRect(nullptr, canvas2D.getColor(Colors::White));

    // Update objects
    for (auto gameObject : objectList) {
      constexpr auto tmp_eps = 1;
      gameObject->onUpdate(tmp_eps);
    }

    // canvas2D->fillRect(&rect, canvas2D->getColor(Colors::Red));
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
