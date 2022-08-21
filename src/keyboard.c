#include "keyboard.h"
#include "utils.h"

enum KEYS {
    NULL_KEY = 0,
    ESCAPE = 27
};

typedef struct Hotkey {
    int key;
    void (*action)();
} Hotkey;

#define NULL_HOTKEY { .key=NULL_KEY, .action=NULL }

const Hotkey navigaton_hotkeys[] = {
    { .key=ESCAPE, .action=close_window },
    NULL_HOTKEY
};
const Hotkey command_hotkeys[] = {
    NULL_HOTKEY
};

static bool parse_hotkeys(int key) {
    const Hotkey* hotkeys;
    switch(get_window_mode()) {
        case NAVIGATION_MODE:
            hotkeys = navigaton_hotkeys;
            break;
        case COMMAND_MODE:
            hotkeys = command_hotkeys;
            break;
        default:
            fatal_error("Hotkeys not found", -1);
    }

    bool is_hotkey = false;
    for(uint32_t i = 0; hotkeys[i].key != NULL_KEY; i++) {
        if(key == hotkeys[i].key)  {
            hotkeys[i].action();
            is_hotkey = true;
            break;
        }
    }

    return is_hotkey;
}

void parse_key(int key) {
    if(key == -1) {
        return;
    }

    if(!parse_hotkeys(key)) {
        printw("%d\n", key);
    }

    refresh();
}
