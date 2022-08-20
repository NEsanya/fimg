VERSION = 1.0
EXECUTABLE = fimg

LIBS =

CFLAGS = -pedantic -Wall -O2 -pipe
LDFLAGS = ${LIBS:%=-l%}
CC = cc
