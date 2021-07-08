#include "map.h"
#include "../entity.h"

GameMap* game_map_create(u32 width, u32 height, struct Entity_t* player) {
    GameMap* map = (GameMap*) malloc(sizeof(GameMap));
    CHECK_ALLOCATION(map, "game map");

    map->width = width;
    map->height = height;

    map->tiles = (Tile**) calloc(map->width, sizeof(Tile*));
    CHECK_ALLOCATION(map->tiles, "map tiles row");

    map->explored = (bool**) calloc(map->width, sizeof(bool*));
    CHECK_ALLOCATION(map->explored, "map explored row");

    map->tcod_map = TCOD_map_new(map->width, map->height);

    for (size_t i = 0; i < map->width; i++) {
        map->tiles[i] = (Tile*) calloc(map->height, sizeof(Tile));
        CHECK_ALLOCATION(map->tiles[i], "map tiles coloumn");

        map->explored[i] = (bool*) calloc(map->height, sizeof(bool));
        CHECK_ALLOCATION(map->explored[i], "map explored coloumn");

        for (size_t j = 0; j < map->height; j++) {
            map->tiles[i][j] = T_WALL;
        }
    }

    proc_gen_generate_dungeon(map, player);

    for (size_t i = 0; i < map->width; i++) {
        for (size_t j = 0; j < map->height; j++) {
            TCOD_map_set_properties(map->tcod_map, i, j, map->tiles[i][j].transparent, map->tiles[i][j].walkable);
        }
    }

    return map;
}

void game_map_destroy(GameMap* map) {
    for (size_t i = 0; i < map->width; i++) {
        free(map->tiles[i]);
        free(map->explored[i]);
    }
    free(map->tiles);
    free(map->explored);
    TCOD_map_delete(map->tcod_map);
    free(map);
}

void game_map_render(TCOD_Console* console, GameMap* map) {
    for (size_t i = 0; i < map->width; i++) {
        for (size_t j = 0; j < map->height; j++) {
            if (map->explored[i][j]) {
                if (TCOD_map_is_in_fov(map->tcod_map, i, j)) {
                    TCOD_console_put_char_ex(console, i, j, map->tiles[i][j].light.ch, color_to_tcod(&map->tiles[i][j].light.fg), color_to_tcod(&map->tiles[i][j].light.bg));
                } else {
                    TCOD_console_put_char_ex(console, i, j, map->tiles[i][j].dark.ch, color_to_tcod(&map->tiles[i][j].dark.fg), color_to_tcod(&map->tiles[i][j].dark.bg));
                }
            } else {
                if (TCOD_map_is_in_fov(map->tcod_map, i, j)) {
                    TCOD_console_put_char_ex(console, i, j, map->tiles[i][j].light.ch, color_to_tcod(&map->tiles[i][j].light.fg), color_to_tcod(&map->tiles[i][j].light.bg));
                    map->explored[i][j] = true;
                } else {
                    TCOD_console_put_char_ex(console, i, j, TX_SHROUD.ch, color_to_tcod(&TX_SHROUD.fg), color_to_tcod(&TX_SHROUD.bg));
                }
            }
        }
    }
}

bool game_map_in_bounds(GameMap* map, i32 x, i32 y) {
    return (x >= 0 && y >= 0 && x < map->width && y < map->height);
}

bool game_map_blocks(GameMap* map, i32 x, i32 y) {
    return !map->tiles[x][y].walkable;
}

void game_map_dig_rectangular_room(GameMap* map, RectangularRoom* room) {
    for (size_t i = room->x1 + 1; i < room->x2; i++) {
        for (size_t j = room->y1 + 1; j < room->y2; j++) {
            ASSERT(game_map_in_bounds(map, i, j), "rectangle to dig is in bounds");
            map->tiles[i][j] = T_FLOOR;
        }
    }
}