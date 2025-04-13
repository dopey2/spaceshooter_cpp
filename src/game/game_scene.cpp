#pragma once

#include "../engine/__engine.h"
#include "../engine/mouse_keyboard.h"
#include "spaceship_view.cpp"
#include "asteroids_view.cpp"
#include "missiles_view.cpp"


#define COLLISION_OFFSET 4

class GameScene : public Scene {
private:
    bool is_game_over = false;
    SpaceshipView* spaceship_view = nullptr;
    AsteroidsView* asteroids_view = nullptr;
    MissilesView* missiles_view = nullptr;

public:
    GameScene() {
        Sprite* background = new Sprite("../assets/img/bg.bmp");
        this->addObject(background);

        *background->m_width = this->application->getWidth();
        *background->m_height = this->application->getHeight();

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

        this->asteroids_view->update(delta);
        this->missiles_view->update(delta, this->spaceship_view);

        this->asteroids_view->isCollidingWithMissiles(this->missiles_view);
        if (this->asteroids_view->isCollidingWithSpaceship(this->spaceship_view)) {
            this->setGameOver();
        }
    }
};