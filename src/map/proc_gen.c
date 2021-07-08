#include "map.h"
#include "../entity.h"

void proc_gen_generate_dungeon(GameMap* map, struct Entity_t* player) {
	RectangularRoom *rooms[PG_MAX_ROOMS] = {NULL};
    TCOD_random_t random = TCOD_random_get_instance();
    for (size_t i = 0; i < PG_MAX_ROOMS; i++) {
        i32 room_width =  TCOD_random_get_int(random, PG_ROOM_MIN_SIZE, PG_ROOM_MAX_SIZE); 
        i32 room_height = TCOD_random_get_int(random, PG_ROOM_MIN_SIZE, PG_ROOM_MAX_SIZE); 

        i32 x = TCOD_random_get_int(random, 0, map->width - room_width - 1);
        i32 y = TCOD_random_get_int(random, 0, map->height - room_height - 1);

        RectangularRoom* new_room = rectangular_room_create(x, y, room_width, room_height);

        bool intersects = false;
        for (size_t j = 0; j < i; j++) {
            if (rooms[j]) {
                intersects = rectangular_room_intersects(rooms[j], new_room);
                if (intersects) break; 
            }
        }
        
        if (intersects) {
            rectangular_room_destroy(new_room);
            continue;
        }

        game_map_dig_rectangular_room(map, new_room);
        
        size_t rooms_size = 0;
        for (size_t j = 0; j < i; j++) {
            if (rooms[j]) rooms_size++;
        }

        if (rooms_size == 0) {
            player->x = rectangular_room_center(new_room).x;
            player->y = rectangular_room_center(new_room).y;
        } else {
            RectangularRoom* old_room;
            for (i32 j = i; j >= 0; j--) {
                if (rooms[j]) {
                    old_room = rooms[j];
                }
            }
            proc_gen_tunnel_between_rooms(map, rectangular_room_center(new_room), rectangular_room_center(old_room));
        }

        rooms[i] = new_room;
    }

    for (size_t i = 0; i < PG_MAX_ROOMS; i++) {
        if (rooms[i]) {
            rectangular_room_destroy(rooms[i]);
        }
    }
}

void proc_gen_tunnel_between_rooms(GameMap* map, Vector2i c1, Vector2i c2) {
    
    i32 x1 = c1.x, y1 = c1.y, x2 = c2.x, y2 = c2.y;
    i32 corner_x = 0, corner_y = 0;

    TCOD_random_t random = TCOD_random_get_instance();
    if (TCOD_random_get_float(random, 0.0f, 1.0f) < 0.5f) {
        corner_x = x2;
        corner_y = y1;
    } else {
        corner_x = x1;
        corner_y = y2;
    }

    for (size_t i = MIN(x1, corner_x); i <= MAX(x1, corner_x); i++) {
        for (size_t j = MIN(y1, corner_y); j <= MAX(y1, corner_y); j++) {
            map->tiles[i][j] = T_FLOOR;
        }
    }

    for (size_t i = MIN(corner_x, x2); i <= MAX(corner_x, x2); i++) {
        for (size_t j = MIN(corner_y, y2); j <= MAX(corner_y, y2); j++) {
            map->tiles[i][j] = T_FLOOR;
        }
    }
}
