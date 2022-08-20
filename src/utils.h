#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

void fatal_error(char* message, int code);

void* smalloc(size_t bytes);

#endif // UTILS_H
