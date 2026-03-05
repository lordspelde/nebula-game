#include "action.h"

#include "world.h"
#include "game_object.h"

void MoveForward::perform(World&, GameObject& obj) {
     obj.physics.acceleration.y = obj.physics.ship_acceleration;
}

void MoveRight::perform(World&, GameObject& obj) {
     // obj.physics.acceleration.x = obj.physics.ship_acceleration;
     obj.physics.angular_acceleration = obj.physics.turn_speed;
}

void MoveLeft::perform(World&, GameObject& obj) {
     // obj.physics.acceleration.x = -obj.physics.ship_acceleration;
     obj.physics.angular_acceleration = -obj.physics.turn_speed;
}
