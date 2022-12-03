#ifndef LNINPUT_H
#define LNINPUT_H

#include <SDL2/SDL.h>

#include <map>
#include <string>

namespace LNInput {
constexpr auto QUIT_EVENT = "QUIT_EVENT";
}

class InputHandler {
 private:
  std::map<int, bool> keyPressed;
  std::map<std::string, bool> specialEvents;

 public:
  std::map<int, bool> *getKeyPressed() { return &keyPressed; }
  std::map<std::string, bool> *getSpecialEvents() { return &specialEvents; }

  void handleInput() {
    specialEvents.clear();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          specialEvents[LNInput::QUIT_EVENT] = true;
          break;

        case SDL_KEYDOWN:
          keyPressed[event.key.keysym.sym] = true;
          break;
        case SDL_KEYUP:
          keyPressed[event.key.keysym.sym] = false;
          break;
      }
    }
  }
};

#endif