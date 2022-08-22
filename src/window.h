#ifndef WINDOW_H
#define WINDOW_H

typedef enum WindowMode {
    NAVIGATION_MODE,
    COMMAND_MODE
} WindowMode;

void init_window();
void close_window();

void change_window_mode(WindowMode mode);
WindowMode get_window_mode();

#endif // WINDOW_H
