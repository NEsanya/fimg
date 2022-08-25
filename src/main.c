#include "window.h"
#include "browser.h"

#include <stdlib.h>
#include <ncurses.h>

int main() {
    init_window();

    char* path = get_execution_path();
    DirectoryStructure structure = get_directory_structure(path);
    free(path);

    for(int i = 0; i < structure.file_count; i++) {
        printw("%s\n", structure.files[i].name);
    }

    start_keyboard_loop();

    free_directory_structure(&structure);
    return 0;
}
