#ifndef CRL_ENGINE_H
#define CRL_ENGINE_H

#include "entity.h"
#include "input_handlers.h"
#include "map/map.h"

#include <stdlib.h>

typedef struct {
    u16 width, height;
    u16 map_width, map_height;

    TCOD_Console* console;

    bool fullscreen;
    Entity* player;
    Entity* entities[MAX_ENTITIES];
    GameMap* map;
} Engine;


void     font_set(const char* file_path);
Engine*  engine_create(u16 width, u16 height, const char* title);
void     engine_destroy(Engine* engine);
void     engine_render(Engine* engine);
void     engine_update(Engine* engine);
void     engine_handle_events(Engine* engine);
void     engine_compute_fov(Engine* engine);

#endif