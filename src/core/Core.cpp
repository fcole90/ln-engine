#include <iostream>

#include "Core.h"
#include "../drawing/Canvas2D.h"
#include "../drawing/Colors.h"


LNCore::LNCore(std::string window_name, int width, int height) {
  LNCore::window = nullptr;
  LNCore::window_name = window_name;
  LNCore::width = width;
  LNCore::height = height;
}

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

  return 0;
}


int LNCore::loop() {
  auto canvas2D = new LNCanvas2D(LNCore::getWindow()); 

  // Create Player
  auto rect = SDL_Rect();
  rect.w = 32;
  rect.h = 32;
  rect.x = LNCore::width / 2;
  rect.y = LNCore::height / 2;
  int speed = 3;

  SDL_Event event;

  // Time variables
  Uint32 delta = 0;
  Uint32 last_update = 0;
  Uint32 current_update = 1;

  // Game Loop
  bool closed = false;
  while (!closed) {
    // Keep track of time
    last_update = current_update;
    current_update = SDL_GetTicks();
    delta = current_update - last_update;

    // Report update
    std::cout << "FPS: " << 1.0 / delta * 1000 << std::endl;

    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          closed = true;
          break;
        
        case SDL_KEYDOWN:
          // Handle input
          switch( event.key.keysym.sym ){
            case SDLK_UP:
              rect.y -= speed;
              break;

            case SDLK_DOWN:
              rect.y += speed;
              break;

            case SDLK_LEFT:
              rect.x -= speed;
              break;

            case SDLK_RIGHT:
              rect.x += speed;
              break;
          }
      }
    }

    // Game update
    canvas2D->fillRect(NULL, canvas2D->getColor(Colors::White));
    canvas2D->fillRect(&rect, canvas2D->getColor(Colors::Red));
    canvas2D->update();

    // Frame limiter
    // SDL_Delay(1000.0 / FRAME_LIMIT - (SDL_GetTicks() - current_update));
  }
};


int LNCore::close() {
  SDL_DestroyWindow(LNCore::window);
  SDL_Quit();
  return 0;
}


SDL_Window * LNCore::getWindow() {
  return LNCore::window;
}