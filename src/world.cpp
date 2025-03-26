#pragma once

#include <vector>
#include "world_object.cpp"

class World {
  public:
    std::vector<WorldObject*> objects;

    World() {}

    void addObject(WorldObject* object) {
      this->objects.push_back(object);
    };
};