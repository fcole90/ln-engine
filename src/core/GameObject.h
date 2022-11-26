#ifndef LNGAME_OBJECT_H
#define LNGAME_OBJECT_H

class GameObject {
protected:
  // GameObject() = default; // 0. Default constructor
public:
  // virtual ~GameObject() = default;                   // 1. Destructor
  // GameObject(const GameObject &other) = default;     // 2. Copy constructor
  // GameObject(GameObject &&other) noexcept = default; // 3. Move constructor
  // GameObject &
  // operator=(const GameObject &other) = default;       // 4. Copy assignment
  // GameObject &operator=(GameObject &&other) noexcept; // 5. Move assignment

  virtual int onUpdate(int eps) = 0;
};

#endif
