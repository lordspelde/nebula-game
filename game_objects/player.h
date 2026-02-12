#pragma once

#include <utility>
#include <SDL3/SDL.h>
#include "graphics.h"
#include  "vec.h"

class Player {
public:
    Player(const Vec<float>& position, const Vec<float>& size);
    void handle_input();
    void update();
    std::pair<Vec<float>, Color> get_sprite() const;

// private:
    SDL_FRect bounding_box;
    Vec<float> size, position, velocity, acceleration;

};