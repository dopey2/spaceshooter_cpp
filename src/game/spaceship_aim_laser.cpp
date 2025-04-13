#include "../engine/__engine.h"
#include "math.cpp"

#define spaceship_w 60

class SpaceshipAimLaser : public WorldObject {
private:
    float target_x = 0;
    uint8_t render_count = 0;

public:
    float getTargetX() { return this->target_x; }

    void update(float *spaceship_y) {
        float xdiff = this->target_x;
        float ydiff = -*spaceship_y;
        auto [length, degree] = Math::cartesianToPolar(xdiff, ydiff);

        if (MouseAndKeyboard::isKeyDown(SDLK_LEFT)) {
            if (degree < (270 - 20)) {
                return;
            }
            target_x -= 3;
        } else if (MouseAndKeyboard::isKeyDown(SDLK_RIGHT)) {
            if (degree > (270 + 20)) {
                return;
            }
            target_x += 3;
        }
    }

    /**
     * Custom rendering function
     */
  void render(SDL_Renderer *renderer, float parent_x, float parent_y) {
        if (this->render_count > 4) {
          SDL_SetRenderDrawColor(renderer, 200, 50, 50, 200);
        } else if (this->render_count > 2) {
          SDL_SetRenderDrawColor(renderer, 50, 50, 200, 200);
        } else {
          SDL_SetRenderDrawColor(renderer, 50, 200, 50, 200);
        }

        SDL_RenderLine(
          renderer,
          parent_x + spaceship_w / 2,
          parent_y,
          parent_x + spaceship_w / 2 + this->target_x,
          0
        );

        this->render_count++;
        this->render_count = this->render_count % 6;
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }
};