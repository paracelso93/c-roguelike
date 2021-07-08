#include "engine.h"

void font_set(const char* file_path) {
    TCOD_Error err = TCOD_console_set_custom_font(file_path, TCOD_FONT_LAYOUT_ASCII_INCOL, 16, 16);
    if (err != TCOD_E_OK) {
        fprintf(stderr, "Error: %s\n", TCOD_get_error());
        exit(EXIT_FAILURE);
    }
}

Engine* engine_create(u16 width, u16 height, const char* title) {
    Engine* engine = (Engine*) malloc(sizeof(Engine));
    CHECK_ALLOCATION(engine, "engine");
    engine->width = width;
    engine->height = height;
    engine->fullscreen = false;

    engine->player = (Entity*) malloc(sizeof(Entity));
    CHECK_ALLOCATION(engine->player, "player");

    engine->player->x = 25;
    engine->player->y = 20;
    engine->player->ch = '@';
    engine->player->color.r = 255;
    engine->player->color.g = 255;
    engine->player->color.b = 255;

    for (size_t i = 0; i < MAX_ENTITIES; i++) {
        engine->entities[i] = NULL;
    }

    engine->entities[0] = engine->player;

    engine->map_width = width;
    engine->map_height = height - 5;

    engine->map = game_map_create(engine->map_width, engine->map_height, engine->player);

    TCOD_Error err = TCOD_console_init_root(engine->width, engine->height, title, engine->fullscreen, TCOD_RENDERER_SDL2);
    if (err != TCOD_E_OK) {
        fprintf(stderr, "Error: %s", TCOD_get_error());
        free(engine->player);
        free(engine);
        exit(EXIT_FAILURE);
    }

    engine->console = TCOD_console_new(engine->width, engine->height);
    if (!engine->console) {
        fprintf(stderr, "Error: %s", TCOD_get_error());
        free(engine->player);
        free(engine);
        exit(EXIT_FAILURE);
    }

    engine_compute_fov(engine);

    return engine;
}

void engine_destroy(Engine* engine) {
    TCOD_console_delete(engine->console);
    game_map_destroy(engine->map);
    for (size_t i = 0; i < MAX_ENTITIES; i++) {
        if (engine->entities[i]) {
            free(engine->entities[i]);
        }
    }
    free(engine);
    TCOD_quit();
}

void engine_render(Engine* engine) {
    TCOD_console_clear(engine->console);
    game_map_render(engine->console, engine->map);
    entity_render(engine->console, engine->player);

    TCOD_console_blit(engine->console, 0, 0, 0, 0, NULL, 0, 0, 1.0, 1.0);
    TCOD_console_flush();
}

void engine_update(Engine* engine) {

}

void engine_handle_events(Engine* engine) {
    SDL_Event event;
    SDL_PollEvent(&event);

    Action a = input_handlers_keyboard(&event);
    if (a.action_type == AT_NONE) return;
    if (a.action_type == AT_MOVE) {
        MoveAction *ma = (MoveAction*) a.data;
        entity_move(engine->player, engine->map, ma->dx, ma->dy);
        engine_compute_fov(engine);
		input_handlers_action_free(&a);
    } else if (a.action_type == AT_EXIT) {
        input_handlers_action_free(&a);
        exit(EXIT_SUCCESS);
    }

}


void engine_compute_fov(Engine* engine) {
    TCOD_map_compute_fov(engine->map->tcod_map, engine->player->x, engine->player->y, 8, true, FOV_SHADOW);
    for (size_t i = 0; i < engine->map->width; i++) {
        for (size_t j = 0; j < engine->map->height; j++) {
            if (TCOD_map_is_in_fov(engine->map->tcod_map, i, j)) {
                engine->map->explored[i][j] = true;
            }
        }
    }
}