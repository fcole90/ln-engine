#ifndef LNCORE_H
#define LNCORE_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../components/BaseComponents.h"
#include "../graphics/Canvas2D.h"
#include "../input/InputHandler.h"

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
  std::vector<std::shared_ptr<BaseComponent>> objectList;

 public:
  LNCore(std::string window_name, int width, int height);

  int init();
  int loop();
  int close();

  void mainLoop();

  void addObject(std::shared_ptr<BaseComponent> obj) { objectList.push_back(obj); }

  // Rendering
  void render(BaseComponent *obj){};
  void render(GraphicComponent2D *obj) { obj->render(); };

  // Getters
  int getWindowHeight() { return height; }
  int getWindowWidth() { return width; }
  LNCanvas2D *getCanvas() { return &canvas; }

  // Input
  auto *getKeyPressed() { return inputHandler.getKeyPressed(); }
  auto *getSpecialEvents() { return inputHandler.getSpecialEvents(); }
};

#endif