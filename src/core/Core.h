#ifndef LNCORE_H
#define LNCORE_H

#include "../components/BaseComponents.h"
#include "../graphics/Canvas2D.h"
#include "../input/InputHandler.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

class LNCore {
private:
  // Env
  bool isLoop{true};

  // Window
  SDL_Window *window{nullptr};
  std::string window_name;
  int width;
  int height;

  // Canvas
  LNCanvas2D canvas{nullptr};

  // Input
  InputHandler inputHandler;

  // Object List
  std::vector<BaseComponent *> objectList;

public:
  LNCore(std::string window_name, int width, int height);

  int init();
  int loop();
  int close();

  void addObject(BaseComponent *obj) { objectList.push_back(obj); }

  // Getters
  int getWindowHeight() { return height; }
  int getWindowWidth() { return width; }
  LNCanvas2D *getCanvas() { return &canvas; }

  // Input
  auto *getKeyPressed() { return inputHandler.getKeyPressed(); }
  auto *getSpecialEvents() { return inputHandler.getSpecialEvents(); }
};

#endif