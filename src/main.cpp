#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "core/Core.h"
#include "drawing/Canvas2D.h"
#include "drawing/Colors.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAME_LIMIT 60

int main(int argc, char* args[]) {
  auto core = new LNCore("LN Engine Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  core->init();
  auto canvas2D = new LNCanvas2D(core->getWindow()); 

  // Create Player
  auto rect = SDL_Rect();
  rect.w = 32;
  rect.h = 32;
  rect.x = SCREEN_WIDTH / 2;
  rect.y = SCREEN_HEIGHT / 2;
  int speed = 3;

  SDL_Event event;

  // Time variables
  Uint32 delta = 0;
  Uint32 last_update = 0;
  Uint32 current_update = 0;

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
          const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
          if (keyboard_state_array[SDL_SCANCODE_UP]) {
            rect.y -= speed;
          }
          
          if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
            rect.y += speed;
          }
          
          if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
            rect.x -= speed;
          }
          
          if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
            rect.x += speed;
          }
          break;
      }
    }

    // Game update
    canvas2D->fillRect(NULL, canvas2D->getColor(Colors::White));
    canvas2D->fillRect(&rect, canvas2D->getColor(Colors::Red));
    canvas2D->update();

    // Frame limiter
    SDL_Delay(1000 / FRAME_LIMIT - (SDL_GetTicks() - current_update));
  }

  return core->close();
}