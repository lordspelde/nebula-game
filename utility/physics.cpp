#include "physics.h"

Physics::Physics(Vec<float> position, Vec<float> velocity, Vec<float> acceleration)
    : position{position}, velocity{velocity}, acceleration{acceleration}{}

Physics::Physics(Vec<float> position, Vec<float> velocity, Vec<float> acceleration, float damping, float ship_acceleration, float max_speed)
    : position{position}, velocity{velocity}, acceleration{acceleration}, damping{damping}, ship_acceleration{ship_acceleration}, max_speed{max_speed}{}
