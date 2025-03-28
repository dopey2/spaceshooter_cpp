#pragma once

// #include <iostream>
// #include <SDL3/SDL.h>
// #include "application.cpp"
// #include "world.cpp"
//
//
// class RendererMediator : AppUpdateObserver, AppLoadObserver {
//   private:
//     Application* m_app;
//     World* m_world;
//
//   public:
//     RendererMediator(Application* app, World* world) {
//         this->m_app = app;
//         this->m_world = world;
//
//         SDL_Renderer* renderer = SDL_CreateRenderer(this->m_app->_window, NULL);
//         if (renderer == nullptr) {
//           std::cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
//           SDL_DestroyWindow(this->m_app->_window);
//           SDL_Quit();
//         }
//
//         this->m_app->_renderer = renderer;
//
//         this->m_app->add_updateObserver(this);
//         this->m_app->add_onloadObserver(this);
//     }
//
//     void application_interface_onLoad() override {
//       this->loadAllObjects();
//     }
//
//     void application_interface_unload() override {
//       this->unloadAllObjects();
//     }
//
//     void application_interface_onUpdate() override {
//       this->renderAllObjects();
//     }
//
//     void loadAllObjects() {
//       for(WorldObject* object: this->m_world->objects) {
//         object->load(this->m_app->_renderer);
//       }
//     }
//
//     void unloadAllObjects() {
//         for(WorldObject* object: this->m_world->objects) {
//           object->unload();
//         }
//     }
//
//     void renderAllObjects() {
//       SDL_RenderClear(this->m_app->_renderer);
//
//       for(WorldObject* object: this->m_world->objects) {
//             object->render(this->m_app->_renderer);
//       }
//
//       SDL_RenderPresent(this->m_app->_renderer);
//     }
// };