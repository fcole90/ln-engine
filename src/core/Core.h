#ifndef LNCORE_H
#define LNCORE_H

#include "../drawing/Canvas2D.h"
#include "./GameObject.h"
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
  std::map<int, bool> keyPressed;

  // Object List
  std::vector<GameObject *> objectList;

public:
  LNCore(std::string window_name, int width, int height);

  int init();
  int handleInput();
  int loop();
  int close();

  void addObject(GameObject *obj) { LNCore::objectList.push_back(obj); }

  // Getters
  int getWindowHeight() { return LNCore::height; }
  int getWindowWidth() { return LNCore::width; }
  LNCanvas2D *getCanvas() { return &(LNCore::canvas); }
  std::map<int, bool> *getKeyPressed() { return &(LNCore::keyPressed); }
};

#endif