#include "browser.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

static inline void check_is_dir_opened(DIR* d) {
    if(!d) {
        fatal_error("Cannot open directory.", 1);
    }
}

DirectoryStructure get_execution_structure() {
    DirectoryStructure directory_structure;

    char* cwd = getcwd(directory_structure.path, sizeof(directory_structure.path));
    if(cwd == NULL) {
        fatal_error("getcwd() error.", 1);
    }

    DIR* d;
    struct dirent* dir;

    d = opendir(cwd);
    check_is_dir_opened(d);

    directory_structure.files_count = 0;
    while((dir = readdir(d)) != NULL) {
        directory_structure.files_count++;
    }
    closedir(d);

    directory_structure.files =
        (char**)
        smalloc(sizeof(char*) * directory_structure.files_count);

    d = opendir(cwd);
    check_is_dir_opened(d);

    for(unsigned int i = 0; (dir = readdir(d)) != NULL; i++) {
        directory_structure.files[i] = (char*)smalloc(sizeof(dir->d_name));
        strcpy(directory_structure.files[i], dir->d_name);
    }
    closedir(d);

    return directory_structure;
}

void free_directory_structure(DirectoryStructure* structure) {
    for(unsigned int i = 0; i < structure->files_count; i++) {
        free(structure->files[i]);
    }
    free(structure->files);
}
