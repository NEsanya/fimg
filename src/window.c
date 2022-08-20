#include "window.h"
#include "utils.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Window {
    bool loop;
    WINDOW* curses_window;
} Window;

static Window* window = NULL;

inline static void check_window_initialised() {
    if(window == NULL) {
        fatal_error("Window is not initialised", -1);
    }
}

void init_window() {
    if(window != NULL) {
        fatal_error("Window is already initialised.", -1);
    }
    window = (Window*)smalloc(sizeof(Window));

    window->curses_window = initscr();
    nodelay(window->curses_window, TRUE);
    keypad(window->curses_window, TRUE);
    halfdelay(5);
    noecho();

    window->loop = true;
    while(window->loop) {
        int ch = getch();

        if(ch == KEY_F(2)) {
            close_window();
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
    free(window);
}
