#include "Canvas2D.h"


LNCanvas2D::LNCanvas2D(SDL_Window *window)
{
  LNCanvas2D::window = window;
  LNCanvas2D::surface = SDL_GetWindowSurface(window);
}

LNCanvas2D::~LNCanvas2D() {}

SDL_Surface * LNCanvas2D::getSurface()
{
  return LNCanvas2D::surface;
}

Uint32 LNCanvas2D::getColor(const Uint8 color[3]) {
  return SDL_MapRGB(LNCanvas2D::surface->format, color[0], color[1], color[2]);
}

int LNCanvas2D::fillRect(const SDL_Rect *rect, Uint32 color) {
  return SDL_FillRect(LNCanvas2D::surface, rect, color);
}

int LNCanvas2D::update() {
  return SDL_UpdateWindowSurface(window);
}