#include <iostream>
#include <string>

#include <SDL2/SDL.h>

#include "core/Core.h"
#include "./drawing/Colors.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAME_LIMIT 60

class Rect: public GameObject {
  private:
    int posX;
    int posY; 
    int width;
    int height;
    LNCore * core;

  public:
    Rect(LNCore * core, int posX, int posY, int width, int height) {
      Rect::core = core;
      Rect::posX = posX;
      Rect::posY = posY;
      Rect::width = width;
      Rect::height = height;
    }

    ~Rect();

    int onUpdate(int eps) {
      auto rect = SDL_Rect();
      rect.w = 32;
      rect.h = 32;
      rect.x = core->getWindowWidth() / 2;
      rect.y = core->getWindowHeight() / 2;

      auto canvas2D = Rect::core->getCanvas();
      canvas2D->fillRect(&rect, canvas2D->getColor(Colors::Red));
      std::cout << "Rect update: " << eps << std::endl;


      // // Handle input
      // switch( event.key.keysym.sym ){
      //   case SDLK_UP:
      //     rect.y -= speed;
      //     break;

      //   case SDLK_DOWN:
      //     rect.y += speed;
      //     break;

      //   case SDLK_LEFT:
      //     rect.x -= speed;
      //     break;

      //   case SDLK_RIGHT:
      //     rect.x += speed;
      //     break;
      // }

      return 0;
    }
};

int main(int argc, char* args[]) {
  
  auto core = new LNCore("LN Engine Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  auto rect = new Rect(core, 0, 0, 0, 0);
  core->init();
  rect->onUpdate(500);
  core->addObject((GameObject *) rect);
  core->loop();
  return core->close();
}