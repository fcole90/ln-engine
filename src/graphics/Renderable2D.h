#ifndef RENDERABLE_H
#define RENDERABLE_H

class Renderable2D {
 public:
  virtual ~Renderable2D() = default;
  virtual void render() = 0;
};

#endif