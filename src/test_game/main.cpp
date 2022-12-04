#include <SDL2/SDL_keycode.h>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <ostream>
#include <utility>

#include "../components/RectangleComponent.h"
#include "../core/Core.h"
#include "../graphics/Colors.h"

constexpr auto PI = 3.1416;

constexpr auto SCREEN_WIDTH = 1280;
constexpr auto SCREEN_HEIGHT = 720;
constexpr auto RECT_SIZE = 15;
constexpr auto PADDLE_HEIGHT = 5 * RECT_SIZE;
constexpr auto DIST_FROM_BORDER = 5;

constexpr auto LEFT_PLAYER = 0;
constexpr auto RIGHT_PLAYER = 1;

class Paddle : public LNComponents::RectangleComponent {
 private:
  int side{0};

 public:
  Paddle(LNCore *core, float x, float y, float w, float h, std::array<Uint8, 4> color, int mode)
    : RectangleComponent::RectangleComponent(core, x, y, w, h, color), side(mode){};

  int onUpdate(int eps) override {
    const float speed = 1.0;
    auto rect = getRect();

    auto UP = side == RIGHT_PLAYER ? SDLK_UP : SDLK_w;
    auto DOWN = side == RIGHT_PLAYER ? SDLK_DOWN : SDLK_s;

    auto keys = getCore()->getKeyPressed();
    // SDL_Event event;
    if ((*keys)[UP] && rect->position.y >= 0) {
      rect->position.y -= speed * static_cast<float>(eps);
    }

    if ((*keys)[DOWN] && rect->position.y + rect->size.y <= SCREEN_HEIGHT) {
      rect->position.y += speed * static_cast<float>(eps);
    }

    return 0;
  }
};

class Ball : public LNComponents::RectangleComponent {
  using RectangleComponent::RectangleComponent;

 private:
  float angle{-PI / 12};
  float speed{0.15};

 public:
  void reflectAngleX() { angle = atan2(sin(angle), -cos(angle)); }
  void reflectAngleY() { angle = atan2(-sin(angle), cos(angle)); }

  void center() {
    auto rect = getRect();
    rect->position.x = SCREEN_WIDTH / 2 + rect->size.x / 2;
    rect->position.y = SCREEN_HEIGHT / 2 + rect->size.y / 2;
  }

  void reset() {
    center();
    auto innerAngle = rand() % 2 < 1 ? -PI / 12.0 : PI / 12.0;
    angle = rand() % 2 < 1 ? innerAngle : innerAngle + PI;
    speed = speed < 1.0f ? speed * 1.05f : speed;
  }

  int onUpdate(int eps) override {
    auto ballRect = getRect();

    if (ballRect->position.y <= 0 || ballRect->position.y + ballRect->size.y >= SCREEN_HEIGHT) {
      reflectAngleY();
    }

    for (auto gameComponent : *getCore()->getObjectList()) {
      auto paddle = std::dynamic_pointer_cast<Paddle>(gameComponent);
      if (paddle) {
        if (isCollisionAABB(paddle)) {
          reflectAngleX();
        }
      }
    }
    auto x_component = cos(angle);
    auto y_component = sin(angle);

    ballRect->position.x += speed * eps * x_component;
    ballRect->position.y += speed * eps * y_component;

    return 0;
  };
};

class Scene : public BaseComponent {
  LNCore *core;
  std::shared_ptr<Paddle> leftPaddle;
  std::shared_ptr<Paddle> rightPaddle;
  std::shared_ptr<Ball> ball;

  int leftScore{0};
  int rightScore{0};

 public:
  Scene(LNCore *core) : core(core) {
    leftPaddle = std::make_shared<Paddle>(
      core, DIST_FROM_BORDER, SCREEN_HEIGHT / 2, RECT_SIZE, PADDLE_HEIGHT, Colors::Gray, LEFT_PLAYER
    );
    rightPaddle = std::make_shared<Paddle>(
      core,
      SCREEN_WIDTH - DIST_FROM_BORDER - RECT_SIZE,
      SCREEN_HEIGHT / 2,
      RECT_SIZE,
      PADDLE_HEIGHT,
      Colors::Gray,
      RIGHT_PLAYER
    );
    ball = std::make_shared<Ball>(core, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, RECT_SIZE, RECT_SIZE, Colors::Red);

    core->addObject(leftPaddle);
    core->addObject(rightPaddle);
    core->addObject(ball);
  };

  int onUpdate(int eps) override {
    // Scored left
    if (ball->getRect()->position.x < -DIST_FROM_BORDER) {
      rightScore += 1;
      std::cout << "Score: " << leftScore << " - " << rightScore << std::endl;
      ball->reset();
    }

    // Scored right
    if (ball->getRect()->position.x > DIST_FROM_BORDER + SCREEN_WIDTH) {
      leftScore += 1;
      std::cout << "Score: " << leftScore << " - " << rightScore << std::endl;
      ball->reset();
    }

    return 0;
  }
};

int main(int argc, char *args[]) {
  auto core = new LNCore("LN Engine Test", SCREEN_WIDTH, SCREEN_HEIGHT);
  core->init();
  core->addObject(std::make_shared<Scene>(core));
  std::cout << "Starting..." << std::endl;
  core->loop();
  std::cout << "Closing..." << std::endl;
  return core->close();
}