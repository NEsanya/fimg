#include "window.h"
#include "utils.h"
#include "keyboard.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct LayoutInfo {
    KeyboardLayout* layout;
    uint32_t size;
} LayoutInfo;

typedef struct Window {
    bool loop;
    WindowMode mode;
    LayoutInfo layout_info;
    WINDOW* curses_window;
} Window;

static Window* window = NULL;

inline static void check_window_initialised() {
    #ifdef DEBUG
        if(window == NULL) {
            fatal_error("Window is not initialised", -1);
        }
    #endif
}

static void set_layout_info() {
    if(window->layout_info.layout != NULL) {
        free(window->layout_info.layout);
    }

    LayoutInfo layout_info;
    get_keyboard_layout(&layout_info.size, NULL);

    layout_info.layout = (KeyboardLayout*)smalloc(sizeof(KeyboardLayout) * layout_info.size);
    get_keyboard_layout(&layout_info.size, layout_info.layout);

    window->layout_info = layout_info;
}

void init_window() {
    if(window != NULL) {
        fatal_error("Window is already initialised.", -1);
    }
    window = (Window*)smalloc(sizeof(Window));
    window->loop = true;
    window->mode = NAVIGATION_MODE;
    window->curses_window = initscr();
    set_layout_info();

    nodelay(window->curses_window, TRUE);
    keypad(window->curses_window, TRUE);
    halfdelay(5);
    noecho();

    while(window->loop) {
        int ch = getch();

        for(uint32_t i = 0; i < window->layout_info.size; i++) {
            if(window->layout_info.layout[i].key == ch) {
                window->layout_info.layout[i].action();
                break;
            }
        }

        refresh();
    }
}

void close_window() {
    check_window_initialised();

    window->loop = false;
    endwin();
}

void free_window() {
    check_window_initialised();
    free(window->layout_info.layout);
    free(window);
}

void change_window_mode(WindowMode mode) {
    check_window_initialised();

    window->mode = mode;
    set_layout_info();
}

WindowMode get_window_mode() {
    check_window_initialised();
    return window->mode;
}
