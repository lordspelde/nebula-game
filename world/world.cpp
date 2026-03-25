#include "world.h"

#include <SDL3/SDL_rect.h>
#include <algorithm>

#include "physics.h"
#include "fsm.h"
#include "states.h"
#include "keyboard_input.h"

World::World(int width, int height): tilemap{width, height} {}

void World::add_platform(float x, float y, float width, float height) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            tilemap(x+j, y+i) = Tile{};
        }
    }
}

bool World::collides(const Vec<float>& position) const {
    int x = std::floor(position.x);
    int y = std::floor(position.y);

    return tilemap(x, y).blocking;
}

GameObject* World::create_player() {
    // Create
    Transitions transitions = {
        {{StateType::Idle, Transition::Move}, StateType::Moving},
        {{StateType::Moving, Transition::Stop}, StateType::Idle},
    };

    States states = {
        {StateType::Idle, new Idle()},
        {StateType::Moving, new Flying()},
    };

    FSM* fsm = new FSM{transitions, states, StateType::Idle};
    KeyboardInput* input = new KeyboardInput();

    player = std::make_unique<GameObject>(
            // Vec<float>{10, 5},
            Vec<int>{1, 1},
            *this,
            fsm,
            input,
            Color(255, 0, 0, 255)
        );

    return player.get();
}

void World::update(float dt) {
    // currently only updating player
    auto position = player->physics.position;
    auto velocity = player->physics.velocity;
    auto acceleration = player->physics.acceleration;

    velocity += 0.5f * acceleration * dt;
    position += velocity * dt;
    velocity += 0.5f * acceleration * dt;
    velocity.x *= player->physics.damping;

    // probably inefficient as hell, but i'm not too keen to redo the actual motion formula at this time
    float magnitude = std::clamp(length(velocity), 0.0f, player->physics.max_speed);
    velocity = player->physics.direction * magnitude;

    // velocity.x = std::clamp(velocity.x, -player->physics.max_speed, player->physics.max_speed);
    // velocity.y = std::clamp(velocity.y, -player->physics.max_speed, player->physics.max_speed);

    // check for x collisions
    // Check for collisions with the world - x direction
    Vec<float> future_position{position.x, player->physics.position.y};
    Vec<float> future_velocity{velocity.x, 0};
    move_to(future_position, player->size, future_velocity);

    // y direction attempt after (maybe) moving in x
    future_velocity.y = velocity.y;
    future_position.y = position.y;
    move_to(future_position, player->size, future_velocity);

    // update player
    player->physics.position = future_position;
    player->physics.velocity = future_velocity;
}

void World::move_to(Vec<float>& position, const Vec<int>& size, Vec<float>& velocity) {
    // test sides first. if both collide move backward
    // bottom side
    if (collides(position) && collides({position.x + size.x, position.y})) {
        position.y = std::ceil(position.y);
        velocity.y = 0;
    }
    // top side
    else if (collides({position.x, position.y + size.y}) && collides({position.x + size.x, position.y + size.y})) {
        position.y = std::floor(position.y);
        velocity.y = 0;
    }
    // left side
    if (collides(position) && collides({position.x, position.y + size.y})) {
        position.x = std::ceil(position.x);
        velocity.x = 0;
    }
    // right side
    else if (collides({position.x + size.x, position.y}) && collides({position.x + size.x, position.y + size.y})) {
        position.x = std::floor(position.x);
        velocity.x = 0;
    }
    // test corners next, move back in smaller axis
    if (collides(position)) {
        float dx = std::ceil(position.x) - position.x;
        float dy = std::ceil(position.y) - position.y;
        if (dx > dy) {
            position.y = std::ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::ceil(position.x);
            velocity.x = 0;
        }
    }
    else if (collides({position.x, position.y + size.y})) {
        float dx = std::ceil(position.x) - position.x;
        float dy = position.y - std::floor(position.y);
        if (dx > dy) {
            position.y = std::floor(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::ceil(position.x);
            velocity.x = 0;
        }
    }
    else if (collides({position.x + size.x, position.y})) {
        float dx = position.x - std::floor(position.x);
        float dy = std::ceil(position.y) - position.y;
        if (dx > dy) {
            position.y = std::ceil(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::floor(position.x);
            velocity.x = 0;
        }
    }
    else if (collides({position.x + size.x, position.y + size.y})) {
        float dx = position.x - std::floor(position.x);
        float dy = position.y - std::floor(position.y);
        if (dx > dy) {
            position.y = std::floor(position.y);
            velocity.y = 0;
        }
        else {
            position.x = std::floor(position.x);
            velocity.x = 0;
        }
    }
}
