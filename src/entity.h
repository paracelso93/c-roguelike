#ifndef CRL_ENTITY_H
#define CRL_ENTITY_H

#include "defines.h"
#include "map/map.h"

typedef struct Entity_t {
    u32 x, y;
    u8 ch;
    Color color;
} Entity;

void entity_render(TCOD_Console* console, Entity* entity);
void entity_move(Entity* entity, GameMap* map, i32 dx, i32 dy);

#endif // CRL_ENTITY_H