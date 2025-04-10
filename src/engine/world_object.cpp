#include "world_object.h"
#include <SDL3/SDL.h>
#include "application.h"

WorldObject::WorldObject() { this->m_application = Application::getInstance(); }

WorldObject::~WorldObject() {}

void WorldObject::load(SDL_Renderer *renderer) {}
void WorldObject::unload() {}
void WorldObject::render(SDL_Renderer *renderer) {};
void WorldObject::onUpdate(Uint64 delta) {};