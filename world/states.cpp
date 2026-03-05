#include "states.h"

#include "action.h"
#include "world.h"

// Helper functions
bool on_platform(const World& world, const GameObject& obj) {
    constexpr float epsilon = 1e-4;
    Vec<float> left_foot{obj.physics.position.x + epsilon, obj.physics.position.y - epsilon};
    Vec<float> right_foot{obj.physics.position.x + obj.size.x - epsilon, obj.physics.position.y - epsilon};

    return world.collides(left_foot) || world.collides(right_foot);
}

// Standing
void Idle::on_enter(World&, GameObject& object) {
    object.color = {0, 0, 255, 255};
    object.physics.acceleration = {0, 0};
}

Action* Idle::input(World& world, GameObject& obj, ActionType action_type) {
    if (action_type == ActionType::Forward) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveForward();
    } else if (action_type == ActionType::MoveRight) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveRight();
    } else if (action_type == ActionType::MoveLeft) {
        obj.fsm->transition(Transition::Move, world, obj);
        return new MoveLeft();
    }

    return nullptr;
}

// Flying
void Flying::on_enter(World&, GameObject& obj) {
    obj.color = {255, 0, 0, 255};
}

Action* Flying::input(World& world, GameObject& obj, ActionType action_type) {
    if (action_type == ActionType::None) {
        obj.fsm->transition(Transition::Stop, world, obj);
    }

    return nullptr;
}
