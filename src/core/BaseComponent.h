#ifndef LNBASE_COMPONENT_H
#define LNBASE_COMPONENT_H

class BaseComponent {
public:
  virtual ~BaseComponent() = default;
  virtual int onUpdate(int eps) = 0;
};

#endif
