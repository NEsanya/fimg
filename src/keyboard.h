#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "window.h"

#include <stdint.h>
#include <ncurses.h>

typedef struct KeyboardLayout {
    int key;
    void (*action)(void);
} KeyboardLayout;

static const KeyboardLayout navigation_layout[] = {
    {.key=KEY_F(2), .action=close_window},
};

static void escape_command_layout();

static const KeyboardLayout command_layout[] = {
    {.key=27, .action=escape_command_layout}
};

void get_keyboard_layout(uint32_t* count, KeyboardLayout* layout);

#endif // KEYBOARD_H
