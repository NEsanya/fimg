#ifndef BROWSER_H
#define BROWSER_H

#include <limits.h>

typedef struct DirectoryStructure {
    char path[PATH_MAX];
    char** files;
    unsigned int files_count;
} DirectoryStructure;

DirectoryStructure get_execution_structure();

void free_directory_structure(DirectoryStructure* structure);

#endif // BROWSER_H
