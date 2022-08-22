#include "window.h"
#include "utils.h"
#include "keyboard.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Window {
    bool loop;
    WindowMode mode;
} Window;

static Window window;

void init_window() {
    window.loop = true;
    window.mode = NAVIGATION_MODE;

    initscr();
    raw();
    nodelay(stdscr, TRUE);
    keypad(stdscr, TRUE);
    halfdelay(5);
    set_escdelay(0);
    noecho();

    int ch;
    while(window.loop) {
        ch = getch();
        parse_key(ch);
    }
}

void close_window() {
    window.loop = false;
    endwin();
}

void change_window_mode(WindowMode mode) {
    window.mode = mode;
}

WindowMode get_window_mode() {
    return window.mode;
}
