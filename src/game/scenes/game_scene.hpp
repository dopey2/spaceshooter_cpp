#pragma once

#include "../world_objects/asteroids/asteroids_view.hpp"
#include "../world_objects/spaceship/missiles_view.hpp"
#include "../world_objects/spaceship/spaceship_view.hpp"
#include "engine/__engine.h"
#include "engine/logger.h"
#include "engine/mouse_keyboard.h"
#include <string>

class GameScene : public Scene {
  private:
    bool is_game_over = false;
    SpaceshipView* spaceship_view = nullptr;
    AsteroidsView* asteroids_view = nullptr;
    MissilesView* missiles_view = nullptr;

  public:
    GameScene() {
        auto* background = new Sprite(AssetsLoaders::getAsset("img/bg.bmp"));
        this->addObject(background);

        background->m_width = this->application->getWidthF();
        background->m_height = this->application->getHeightF();

        this->spaceship_view = new SpaceshipView();
        this->addObject(this->spaceship_view);

        this->asteroids_view = new AsteroidsView();
        this->addObject(this->asteroids_view);

        this->missiles_view = new MissilesView();
        this->addObject(this->missiles_view);
    }

    void setGameOver() {
        this->is_game_over = true;
        this->spaceship_view->setGameOver(true);
        this->application->scene_manager->setActiveScene("menu");
    }

    void onActive() override {
        this->is_game_over = false;
        this->spaceship_view->init();
        this->asteroids_view->init();
        this->missiles_view->init();
    }

    void onUpdate(Uint64 delta) override {
        if (this->is_game_over) {
            return;
        }

        this->asteroids_view->update(delta, this->missiles_view);
        this->missiles_view->update(delta, this->spaceship_view);

        if (this->asteroids_view->isCollidingWithSpaceship(this->spaceship_view)) {
            this->setGameOver();
        }
    }
};