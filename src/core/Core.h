#ifndef LNCORE_H
#define LNCORE_H

#include <map>
#include <string>
#include <vector>
#include <SDL2/SDL.h>
#include "../drawing/Canvas2D.h"


class GameObject {
  public:
    virtual int onUpdate(int eps) = 0;
};

class LNCore
{
private:
  // Env
 bool isLoop{true};

 // Window
 SDL_Window *window{nullptr};
 std::string window_name;
 int width;
 int height;

 // Canvas
 LNCanvas2D *canvas{};

 // Input
 std::map<int, bool> keyPressed;

 // Object List
 std::vector<GameObject *> objectList;

public:
  LNCore(std::string window_name, int width, int height);
  ~LNCore();

  int init();
  int handleInput();
  int loop();
  int close();

  void addObject(GameObject * obj) { LNCore::objectList.push_back(obj); }

  // Getters
  int getWindowHeight(){ return LNCore::height; }
  int getWindowWidth(){ return LNCore::width; }
  LNCanvas2D * getCanvas(){ return LNCore::canvas; }
};

#endif