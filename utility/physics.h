#pragma once
#include "vec.h"

class Physics {
public:
    Physics()=default;
    Physics(Vec<float> position, Vec<float> velocity, Vec<float> acceleration);
    Physics(Vec<float> position, Vec<float> velocity, Vec<float> acceleration,
        float damping, float ship_acceleration, float max_speed);
    Physics(Vec<float> position, Vec<float> velocity, Vec<float> acceleration,
        float damping, float ship_acceleration, float max_speed,
        float turn_speed);
    
    Vec<float> position{0,0};
    Vec<float> velocity{0,0};
    Vec<float> acceleration{0,0};

    float damping{0.99f};
    float ship_acceleration{60.0f};
    float max_speed{30.0f};
    // TODO: https://lazyfoo.net/tutorials/SDL/15_rotation_and_flipping/index.php
    float turn_speed{20}; // degrees per second
    float turn_acceleration{100}; // degrees per second^2

    double angle{0}; // in degrees
    double angular_velocity{0};
    double angular_acceleration{0};
};
