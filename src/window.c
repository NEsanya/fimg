#include "window.h"
#include "utils.h"
#include "keyboard.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Window {
    bool loop;
    WindowMode mode;
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

void init_window() {
    if(window != NULL) {
        fatal_error("Window is already initialised.", -1);
    }
    window = (Window*)smalloc(sizeof(Window));
    window->loop = true;
    window->mode = NAVIGATION_MODE;

    window->curses_window = initscr();
    nodelay(window->curses_window, TRUE);
    keypad(window->curses_window, TRUE);
    halfdelay(5);
    noecho();

    while(window->loop) {
        int ch = getch();

        uint32_t size;
        get_keyboard_layout(&size, NULL);

        KeyboardLayout* layout = (KeyboardLayout*)smalloc(sizeof(KeyboardLayout) * size);
        get_keyboard_layout(&size, layout);

        for(uint32_t i = 0; i < size; i++) {
            if(layout[i].key == ch) {
                layout[i].action();
                break;
            }
        }

        refresh();
        free(layout);
    }
}

void close_window() {
    check_window_initialised();

    window->loop = false;
    endwin();
}

void free_window() {
    check_window_initialised();
    free(window);
}

void change_window_mode(WindowMode mode) {
    check_window_initialised();
    window->mode = mode;
}

WindowMode get_window_mode() {
    check_window_initialised();
    return window->mode;
}
