#include "keyboard_input.h"
#include "game_object.h"
#include "fsm.h"

void KeyboardInput::get_input() {
    const bool *key_states = SDL_GetKeyboardState(NULL);

    if (key_states[SDL_SCANCODE_D]) {
        next_action_type = ActionType::MoveRight;
    }

    if (key_states[SDL_SCANCODE_A]) {
        next_action_type = ActionType::MoveLeft;
    }

    if (key_states[SDL_SCANCODE_W]) {
        next_action_type = ActionType::Forward;
    }
}

void KeyboardInput::handle_input(World& world, GameObject& obj) {
    Action* action = obj.fsm->current_state->input(world, obj, next_action_type);

    // consume the action
    next_action_type = ActionType::None;
    if (action != nullptr) {
        action->perform(world, obj);
        delete action;
    }
}

void KeyboardInput::collect_discrete_event(SDL_Event* event) {
    
}
