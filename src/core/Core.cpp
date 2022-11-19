#include "Core.h"

#include <iostream>
#include <utility>

#include "../drawing/Colors.h"

LNCore::LNCore(std::string window_name, int width, int height)
    : isLoop(true),
      window(nullptr),
      window_name(std::move(window_name)),
      width(width),
      height(height) {}

int LNCore::init() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
    return 1;
  }

  LNCore::window = SDL_CreateWindow(
    LNCore::window_name.c_str(),
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED,
    LNCore::width, 
    LNCore::height,
    SDL_WINDOW_SHOWN
	);
  if (!LNCore::window) {
    std::cerr << "Could not create SDL Window: " << SDL_GetError() << std::endl;
    return 1;
  }

  LNCore::canvas = new LNCanvas2D(LNCore::window);

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
        
        // case SDL_KEYDOWN:
        //   // Handle input
        //   switch( event.key.keysym.sym ){
        //     case SDLK_UP:
        //       rect.y -= speed;
        //       break;

        //     case SDLK_DOWN:
        //       rect.y += speed;
        //       break;

        //     case SDLK_LEFT:
        //       rect.x -= speed;
        //       break;

        //     case SDLK_RIGHT:
        //       rect.x += speed;
        //       break;
        //   }
      }
    }
  
  return 0;
}


int LNCore::loop() {
  auto canvas2D = LNCore::canvas;
  auto objectList = LNCore::objectList;

  // Create Player
  // auto rect = SDL_Rect();
  // rect.w = 32;
  // rect.h = 32;
  // rect.x = LNCore::width / 2;
  // rect.y = LNCore::height / 2;
  // int speed = 3;

  

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
    std::cout << "FPS: " << 1.0 / delta * 1000 << std::endl;

    

    // Game update
    canvas2D->fillRect(nullptr, canvas2D->getColor(Colors::White));

    // Update objects
    for(auto gameObject : objectList) {
      gameObject->onUpdate(5);
    }

    // canvas2D->fillRect(&rect, canvas2D->getColor(Colors::Red));
    canvas2D->update();

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
