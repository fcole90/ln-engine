#ifndef LNGAME_OBJECT_H
#define LNGAME_OBJECT_H

class GameObject {
public:
  virtual ~GameObject() = default;
  virtual int onUpdate(int eps) = 0;
};

#endif
