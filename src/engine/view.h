#include <vector>
#include "world_object.h"

class View : public WorldObject {
public:
   WorldObject* parent = nullptr;
   std::vector<WorldObject*> children;

    View();
    ~View();
    void load(SDL_Renderer *renderer);
    virtual void render(SDL_Renderer *renderer, float parent_x, float parent_y);
    void addObject(WorldObject* object);
};