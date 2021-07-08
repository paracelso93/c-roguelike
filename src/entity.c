#include "entity.h"

void entity_render(TCOD_Console* console, Entity* entity) {
    TCOD_console_set_default_foreground(console, color_to_tcod(&entity->color));
    TCOD_console_put_char(console, entity->x, entity->y, entity->ch, TCOD_BKGND_NONE);
}

void entity_move(Entity* entity, GameMap* map, i32 dx, i32 dy) {
    if ((!game_map_blocks(map, entity->x + dx, entity->y + dy)) && game_map_in_bounds(map, entity->x + dx, entity->y + dy)) {
        entity->x += dx;
        entity->y += dy;
    }
}