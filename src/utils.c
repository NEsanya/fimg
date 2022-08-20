#include "utils.h"

#include <stdio.h>
#include <errno.h>

void fatal_error(char* message, int code) {
   fprintf(stderr, "FATAL: %s (code: %d)\n", message, code);
   exit(code);
}

void* smalloc(size_t bytes) {
    void* pointer = malloc(bytes);
    if(pointer == NULL) {
        fatal_error("Malloc out of memmory", ENOMEM);
    }

    return pointer;
}
