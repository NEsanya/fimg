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

#define STR_EQUAL(a, b) strcmp(a, b) == 0

static unsigned int
get_directory_count(char path[PATH_MAX]) {
    DIR* dir_p = opendir(path);
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

DirectoryStructure get_execution_structure() {
    DirectoryStructure directory_structure;

    char* cwd = getcwd(directory_structure.path, sizeof(directory_structure.path));
    if(cwd == NULL) {
        fatal_error("getcwd() error.", 1);
    }

    directory_structure.file_count = get_directory_count(cwd);
    directory_structure.files = smalloc(sizeof(FileInfo) * directory_structure.file_count);

    write_directory_files(&directory_structure);

    return directory_structure;
}

void free_directory_structure(DirectoryStructure* structure) {
   free(structure->files);
}
