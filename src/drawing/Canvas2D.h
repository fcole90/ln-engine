#ifndef LNCANVAS_H
#define LNCANVAS_H
#include <SDL2/SDL.h>
#include <array>

class LNCanvas2D {
private:
  SDL_Surface *surface;
  SDL_Window *window;

public:
  LNCanvas2D(SDL_Window *window);
  ~LNCanvas2D() = default;
  SDL_Surface *getSurface();
  Uint32 getColor(std::array<Uint8, 4> color);
  int fillRect(const SDL_Rect *rect, Uint32 color);
  int update();
};

#endif