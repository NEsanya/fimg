#include "window.h"
#include "utils.h"
#include "keyboard.h"

#include <ncurses.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>

typedef struct Window {
    bool loop;
    WindowMode mode;
} Window;

static Window window;

static void* keyboard_parse_loop(void* data) {
    int ch;
    while(window.loop) {
        ch = getch();
        parse_key(ch);
    }

    return NULL;
}

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
}

void start_keyboard_loop() {
    pthread_t pthread_id;
    pthread_create(&pthread_id, NULL, keyboard_parse_loop, NULL);
    pthread_join(pthread_id, NULL);
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
