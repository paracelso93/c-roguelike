#include <stdio.h>
#include "engine.h"

int main(void) {
    
    font_set("/Users/edoardobiasio/dev/crl/assets/terminal.png");
    Engine* engine = engine_create(80, 50, "C Roguelike");

    while (!TCOD_console_is_window_closed()) {
        engine_handle_events(engine);
        engine_update(engine);
        engine_render(engine);
    }

    engine_destroy(engine);

    return 0;
}