#include "browser.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>

#define STR_EQUAL(a, b) strcmp(a, b) == 0
#define SIZE_OF_PATH sizeof(char) * PATH_MAX

static inline void check_is_dir_opened(DIR* d) {
    if(!d) {
        fatal_error("Cannot open directory.", 1);
    }
}

static unsigned int
get_directory_count(char path[PATH_MAX]) {
    DIR* dir_p = opendir(path);
    check_is_dir_opened(dir_p);
    struct dirent* dirent_p;

    unsigned int count = 0;
    while((dirent_p = readdir(dir_p)) != NULL) {
        if(STR_EQUAL(dirent_p->d_name, ".")) {
           continue;
        }

        count++;
    }

    closedir(dir_p);
    return count;
}

static void write_directory_files(DirectoryStructure* structure) {
    DIR* dir_p = opendir(structure->path);
    check_is_dir_opened(dir_p);
    struct dirent* dirent_p;

    for(int i = 0; (dirent_p = readdir(dir_p)) != NULL; i++) {
        if(STR_EQUAL(dirent_p->d_name, ".")) {
            i--;
            continue;
        }

        structure->files[i].type = dirent_p->d_type;
        strcpy(structure->files[i].name, dirent_p->d_name);
    }

    closedir(dir_p);
}

char* get_execution_path() {
    char* path = smalloc(SIZE_OF_PATH);
    char* cwd = getcwd(path, SIZE_OF_PATH);
    if(cwd == NULL) {
        fatal_error("getcwd() error.", 1);
    }

    return path;
}

DirectoryStructure get_directory_structure(char* path) {
    DirectoryStructure directory_structure;

    strcpy(directory_structure.path, path);
    directory_structure.file_count = get_directory_count(directory_structure.path);
    directory_structure.files = smalloc(sizeof(FileInfo) * directory_structure.file_count);

    write_directory_files(&directory_structure);

    return directory_structure;
}

void free_directory_structure(DirectoryStructure* structure) {
   free(structure->files);
}
