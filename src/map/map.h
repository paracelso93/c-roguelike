#ifndef CRL_MAP_MAP_H
#define CRL_MAP_MAP_H

#include "../defines.h"

typedef struct {
    Color fg, bg;
    u8 ch;
} Texture;

static const Texture TX_SHROUD = { .fg = (Color) { 255, 255, 255 }, .bg = (Color) { 0, 0, 0 }, .ch = ' ' };

typedef struct {
    bool walkable, transparent;
    Texture dark;
    Texture light;
} Tile;

static const Tile T_FLOOR = { .walkable = true,
                              .transparent = true,
                              .dark = { .fg = (Color) { 255, 255, 255 }, .bg = (Color) { 50, 50, 150 }, .ch = ' ' },
                              .light = { .fg = (Color) { 255, 255, 255 }, .bg = (Color) { 200, 180, 50 }, .ch = ' ' } 
                            };
static const Tile T_WALL =  {
                              .walkable = false, 
                              .transparent = false, 
                              .dark = { .fg = (Color) { 255, 255, 255 }, .bg = (Color) { 0, 0, 100 }, .ch = ' '},
                              .light = { .fg = (Color) { 255, 255, 255 }, .bg = (Color) { 130, 110, 50 }, .ch = ' '}
                            };

typedef struct {
    u32 x1, y1, x2, y2;
} RectangularRoom;

/*
    rooms.c
*/

RectangularRoom *rectangular_room_create(u32 x, u32 y, u32 width, u32 height);
void             rectangular_room_destroy(RectangularRoom* room);
Vector2i         rectangular_room_center(RectangularRoom* room);
bool             rectangular_room_intersects(RectangularRoom* r1, RectangularRoom* r2);

typedef struct {
    u32 width, height;
    bool **explored;

    TCOD_Map* tcod_map;
    Tile **tiles;
} GameMap;


/*
    proc_gen.c
*/

#define PG_ROOM_MAX_SIZE 10
#define PG_ROOM_MIN_SIZE 6
#define PG_MAX_ROOMS     30

struct Entity_t;

void     proc_gen_generate_dungeon(GameMap* map, struct Entity_t* player);
void     proc_gen_tunnel_between_rooms(GameMap* map, Vector2i c1, Vector2i c2);

/*
    game_map.c
*/

GameMap* game_map_create(u32 width, u32 height, struct Entity_t* player);
void     game_map_destroy(GameMap* map);
void     game_map_render(TCOD_Console* console, GameMap* map);
bool     game_map_in_bounds(GameMap* map, i32 x, i32 y);
bool     game_map_blocks(GameMap* map, i32 x, i32 y);

void     game_map_dig_rectangular_room(GameMap* map, RectangularRoom* room);


#endif // CRL_MAP_MAP_H