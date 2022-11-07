#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "core/Core.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAME_LIMIT 60

int main(int argc, char* args[]) {
  auto core = new LNCore("LN Engine Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  core->init();
  core->loop();
  return core->close();
}