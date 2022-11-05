#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "core/Core.h"
#include "drawing/Canvas2D.h"
#include "drawing/Colors.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480


int main(int argc, char* args[]) {
  auto core = new LNCore("LN Engine Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  core->init();
  
  auto canvas2D = new LNCanvas2D(core->getWindow()); 

  // Game Loop
  SDL_Event event;
  bool closed = false;
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

  return core->close();
}