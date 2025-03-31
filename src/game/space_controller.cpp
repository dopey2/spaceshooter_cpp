#include "../engine/application.h"
#include "spaceship.cpp"
#include "asteroid.cpp"


class SpaceController {
private:
    Application* m_application = nullptr;
    Spaceship* m_spaceship = nullptr;
    std::vector<Asteroid*> asteroids_list;


    Uint64 lastSpawnTimeAsteroid = -1000;
    Uint64 spawnInterval = 2000;

public:
        SpaceController() {
            m_application = Application::getInstance();
            m_spaceship = new Spaceship();


            this->m_application->scene->addObject(this->m_spaceship);


            this->m_application->register_update_callback([=](Uint64 delta) -> void {
                this->onUpdate(delta);
            });
        }

        ~SpaceController() {
            m_application = nullptr;
            delete m_spaceship;
            m_spaceship = nullptr;
        }

        void onUpdate(Uint64 delta) {
            if (lastSpawnTimeAsteroid + spawnInterval < delta) {
                this->lastSpawnTimeAsteroid = delta;
                Asteroid* asteroid = new Asteroid();
                this->m_application->scene->addObject(asteroid);
                this->asteroids_list.push_back(asteroid);
            }

            for (auto asteroid : this->asteroids_list) {
                asteroid->updateAsteroidPosition();
            }
        }
};