#include "map.h"

RectangularRoom *rectangular_room_create(u32 x, u32 y, u32 width, u32 height) {
    RectangularRoom* room = (RectangularRoom*) malloc(sizeof(RectangularRoom));
    CHECK_ALLOCATION(room, "rectangular room");

    room->x1 = x;
    room->x2 = width + x;
    room->y1 = y;
    room->y2 = height + y;

    return room;
}

void rectangular_room_destroy(RectangularRoom* room) {
    free(room);
}

Vector2i rectangular_room_center(RectangularRoom* room) {
    Vector2i center;
    center.x = (room->x1 + room->x2) / 2;
    center.y = (room->y1 + room->y2) / 2;
    return center;
}

bool rectangular_room_intersects(RectangularRoom* r1, RectangularRoom* r2) {
    return (r1->x1 <= r2->x2 && r1->x2 >= r2->x1 && r1->y1 <= r2->y2 && r1->y2 >= r2->y1);
}