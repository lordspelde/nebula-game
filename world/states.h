#pragma once

#include "fsm.h"

class World;

class Idle : public State {
    void on_enter(World&, GameObject&) override;
    Action* input(World&, GameObject&, ActionType) override;
};

class Flying : public State {
    void on_enter(World&, GameObject&) override;
    Action* input(World&, GameObject&, ActionType) override;
};