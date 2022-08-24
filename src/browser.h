#ifndef BROWSER_H
#define BROWSER_H

#include <limits.h>

typedef struct FileInfo {
    unsigned char type;
    char name[NAME_MAX + 1];
} FileInfo;

typedef struct DirectoryStructure {
    char path[PATH_MAX];
    unsigned int file_count;
    FileInfo* files;
} DirectoryStructure;

DirectoryStructure get_execution_structure();

void free_directory_structure(DirectoryStructure* structure);

#endif // BROWSER_H
