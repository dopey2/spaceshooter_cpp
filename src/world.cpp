#include <vector>
#include "world_object.cpp";

class World {
  public:
    std::vector<WorldObject*> objects;

    static World* _instance;

    World();

    // For the singleton: disable constructor by reference
    World(World const&) = delete;
    // For the singleton: disable assignment operator
    void operator=(World const&)  = delete;

    static World* getInstance() {
      if(World::_instance == nullptr) {
        World::_instance = new World();
      }
      return World::_instance;
    }

    void addObject(WorldObject* object) {
      this->objects.push_back(object);
    };
};

World* World::_instance = nullptr;