#ifndef CRL_DEFINES_H
#define CRL_DEFINES_H

#include <stdint.h>
#include <libtcod/libtcod.h>
#include <SDL2/SDL.h>

typedef int8_t   i8;
typedef int16_t  i16;
typedef int32_t  i32;
typedef int64_t  i64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float    f32;
typedef double   f64;

typedef uint8_t  b8;

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef struct {
    u8 r, g, b;
} Color;

static TCOD_color_t color_to_tcod(const Color* color) {
    return TCOD_color_RGB(color->r, color->g, color->b);
}

typedef struct {
    i32 x, y;
} Vector2i;

#define ASSERT(x, str) if (!x) { \
    fprintf(stderr, "Assertion Failed at line %d in file %s: %s.\n", __LINE__, __FILE__, str); \
    exit(EXIT_FAILURE); \
}

#define MAX_ENTITIES 2000

#define CHECK_ALLOCATION(data, name) if (!data) { \
    fprintf(stderr, "Error: Unable to allocate %s at line %d in file %s.\n", name, __LINE__, __FILE__); \
    exit(EXIT_FAILURE); \
}

#endif