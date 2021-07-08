#include "input_handlers.h"

void input_handlers_action_free(Action* action) {
    switch (action->action_type) {
        case AT_EXIT: free((ExitAction*) action->data); break;
        case AT_MOVE: free((MoveAction*) action->data); break;
        default: fprintf(stderr, "Error: unable to free action, unrecognised action type %hu.\n", (u16) action->action_type);
    }
}

Action input_handlers_keyboard(SDL_Event *event) {
	
	Action none = { .action_type = AT_NONE, .data = NULL };
    switch (event->type) {
        case SDL_QUIT: {
            ExitAction* action = (ExitAction*) malloc(sizeof(ExitAction));
            CHECK_ALLOCATION(action, "exit action");

            Action a = { .action_type = AT_EXIT, .data = action };
            return a;
        } break;
        case SDL_KEYDOWN: {
            
			i32 dx = 0, dy = 0;
            switch (event->key.keysym.sym) {
                case SDLK_LEFT:  dx = -1; break;
                case SDLK_RIGHT: dx = 1;  break;
                case SDLK_UP:    dy = -1; break;
                case SDLK_DOWN:  dy = 1;  break;
                case SDLK_ESCAPE: {
                    ExitAction* action = (ExitAction*) malloc(sizeof(ExitAction));
                    CHECK_ALLOCATION(action, "exit action");

                    Action a = { .action_type = AT_EXIT, .data = action };
                    return a; 
                } break;
                default: {
					return none;
                } break;
            }
			
			MoveAction* action = (MoveAction*) malloc(sizeof(MoveAction));
			CHECK_ALLOCATION(action, "move action");

			action->dx = dx;
			action->dy = dy;

            Action a = { .action_type = AT_MOVE, .data = (void*) action };
            return a;
        }
    }
    return none;
}
