#pragma once

#include "player.h"
#include "world.h"
#include "camera.h"

class Game {
public:
    Game(std::string title, int width, int height);
    void input();
    void update();
    void render();

private:
    Player* player;
    World world;
    Graphics graphics;
    Camera camera;

    // timing
    float dt, lag;
    Uint64 performance_frequency, prev_counter;

};
