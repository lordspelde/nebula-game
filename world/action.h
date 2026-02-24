#pragma once

class World;
class GameObject;

enum class ActionType {
    None,
    Jump,
    MoveLeft,
    MoveRight,
};

class Action {
public:
    virtual ~Action()=default;
    virtual void perform(World& world, GameObject& obj) = 0;
};

class Jump : public Action {
    void perform(World&, GameObject& obj) override;
};

class MoveRight : public Action {
    void perform(World& world, GameObject& obj) override;
};

class MoveLeft : public Action {
    void perform(World& world, GameObject& obj) override;
};