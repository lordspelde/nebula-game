#pragma once

#include "fsm.h"

class World;

class Standing : public State {
    void on_enter(World&, GameObject&) override;
    Action* input(World&, GameObject&, ActionType) override;
};

class InAir : public State {
    void on_enter(World&, GameObject&) override;
    void update(World&, GameObject&, double dt) override;

    static constexpr double cooldown = 0.1;
    double elapsed = 0;
};

class Running : public State {
    void on_enter(World&, GameObject&) override;
    Action* input(World&, GameObject&, ActionType) override;
};