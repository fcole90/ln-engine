#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

#include "drawing/Canvas2D.h"
#include "drawing/Colors.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main(int argc, char* args[]) {
  SDL_Window* window = nullptr;
  LNCanvas2D* canvas2D = nullptr;
  SDL_Event event;
  bool closed = false;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Could not initialize SDL2: " << SDL_GetError() << std::endl;
    return 1;
  }

  window = SDL_CreateWindow(
    "hello_sdl2",
    SDL_WINDOWPOS_UNDEFINED, 
    SDL_WINDOWPOS_UNDEFINED,
    SCREEN_WIDTH, 
    SCREEN_HEIGHT,
    SDL_WINDOW_SHOWN
	);
  if (!window) {
    std::cerr << "Could not create SDL Window: " << SDL_GetError() << std::endl;
    return 1;
  }

  canvas2D = new LNCanvas2D(window); 

  // Game Loop
  while (!closed) {
    // Events management
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          closed = true;
          break;
      }
    }
    
    // Game update
    canvas2D->fillRect(NULL, canvas2D->getColor(Colors::White));
    canvas2D->update();
  }
  
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}