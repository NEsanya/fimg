#include "keyboard.h"

#include <string.h>

static void escape_command_layout() {
    change_window_mode(NAVIGATION_MODE);
}

static inline void set_layout(KeyboardLayout* layout, const KeyboardLayout* from, uint32_t size) {
    if(layout != NULL) {
        memcpy(layout, from, sizeof(KeyboardLayout) * size);
    }
}

void get_keyboard_layout(uint32_t* count, KeyboardLayout* layout) {
    switch(get_window_mode()) {
        case NAVIGATION_MODE:
            *count = sizeof(navigation_layout) / sizeof(KeyboardLayout);
            set_layout(layout, navigation_layout, *count);
            break;
        case COMMAND_MODE:
            *count = sizeof(command_layout) / sizeof(KeyboardLayout);
            set_layout(layout, command_layout, *count);
            break;
    }
}
