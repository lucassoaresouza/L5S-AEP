#ifndef COLLIDER_H
#define COLLIDER_H

#include <iostream>
#include <vector>

#include "gameObject.hpp"

namespace Engine {
class Collider {
 private:
  static Collider* instance;
  std::vector<GameObject*> objects;

 public:
  static Collider& get_instance();
  std::vector<GameObject*> verify(GameObject* object);
  void add_object(GameObject* object);
  void remove_all_objects();
};
}  // namespace Engine

#endif