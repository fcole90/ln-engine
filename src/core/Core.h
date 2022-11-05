#ifndef LNCORE_H
#define LNCORE_H
#include <string>
#include <SDL2/SDL.h>

class LNCore
{
private:
  SDL_Window *window;
  std::string window_name;
  int width;
  int height;
public:
  LNCore(std::string window_name, int width, int height);
  SDL_Window * getWindow();
  ~LNCore();
  int init();
  int close();
};

#endif