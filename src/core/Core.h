#ifndef LNCORE_H
#define LNCORE_H

#include "../graphics/Canvas2D.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>
#include <vector>

class GameObject {
protected:
  GameObject() = default; // 0. Default constructor
public:
  virtual ~GameObject() = default;                   // 1. Destructor
  GameObject(const GameObject &other) = default;     // 2. Copy constructor
  GameObject(GameObject &&other) noexcept = default; // 3. Move constructor
  GameObject &
  operator=(const GameObject &other) = default;       // 4. Copy assignment
  GameObject &operator=(GameObject &&other) noexcept; // 5. Move assignment

  virtual int onUpdate(int eps) = 0;
};

class LNCore {
private:
  // Env
  bool isLoop{true};
  // InputHandler inputHandler;

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