#ifndef CRL_INPUT_HANDLERS_H
#define CRL_INPUT_HANDLERS_H

#include "defines.h"

enum ActionType {
    AT_MOVE,
    AT_EXIT,
    AT_NONE,
    AT_NUMBER
};

typedef struct {
    i32 dx, dy;
} MoveAction;

typedef struct {

} ExitAction;

typedef struct {
    u8 action_type;
    void* data;
} Action;

void input_handlers_action_free(Action* action);
Action input_handlers_keyboard(SDL_Event *event);

#endif