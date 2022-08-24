VERSION = 0.1 (in development)
EXECUTABLE = fimg

LIBS = ncurses

CFLAGS = -pedantic -Wall -O2 -march=native -pipe
LDFLAGS = ${LIBS:%=-l%}
CC = cc
