#include "window.h"
#include "browser.h"

#include <ncurses.h>

int main() {
    init_window();

    DirectoryStructure structure = get_execution_structure();
    for(int i = 0; i < structure.file_count; i++) {
        printw("%s\n", structure.files[i].name);
    }

    start_keyboard_loop();

    free_directory_structure(&structure);
    return 0;
}
