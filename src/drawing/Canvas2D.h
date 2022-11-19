#ifndef LNCANVAS_H
#define LNCANVAS_H
#include <SDL2/SDL.h>

class LNCanvas2D {
private:
  SDL_Surface *surface;
  SDL_Window *window;

public:
  LNCanvas2D(SDL_Window *window);
  ~LNCanvas2D();
  SDL_Surface *getSurface();
  Uint32 getColor(const Uint8 color[3]);
  int fillRect(const SDL_Rect *rect, Uint32 color);
  int update();
};

#endif