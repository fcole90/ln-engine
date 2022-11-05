#include "Core.h"
#include <iostream>


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

int LNCore::close() {
  SDL_DestroyWindow(LNCore::window);
  SDL_Quit();
  return 0;
}

SDL_Window * LNCore::getWindow() {
  return LNCore::window;
}