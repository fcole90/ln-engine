#ifndef LNBASE_COMPONENT_H
#define LNBASE_COMPONENT_H

#include "../graphics/Renderable2D.h"

/**
 * Interface for all components.
 */
class BaseComponent {
private:
 public:
  virtual ~BaseComponent() = default;
  virtual int onUpdate(int eps) = 0;
};

/**
 * Interface for all components rendering 2D graphics.
 */
class GraphicComponent2D : public BaseComponent, public Renderable2D {};

#endif
