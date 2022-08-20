include config.mk

SRC = $(wildcard src/*.c)
HDR = $(wildcard src/*.h)

OBJ_DIR = obj
OBJ = ${SRC:src/%.c=${OBJ_DIR}/%.o}

all: options ${OBJ_DIR}/ ${EXECUTABLE}

config.h: config.def.h
	@cp $< $@
	@echo Default config copied to $@

${OBJ_DIR}/%.o: src/%.c ${HDR} config.h
	${CC} ${CFLAGS} -c $< -o $@

${EXECUTABLE}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

${OBJ_DIR}/:
	@mkdir $@

options:
	@echo ------OPTIONS------
	@echo -e "VERSION    = ${VERSION}"
	@echo -e "EXECUTABLE = ${EXECUTABLE}"
	@echo -e "CFLAGS     = ${CFLAGS}"
	@echo -e "LDFLAGS    = ${LDFLAGS}"
	@echo -e "CC         = ${CC}"
	@echo -------------------

clean:
	@rm -rf ${OBJ_DIR} fimg
	@echo Cleaned!

.PHONY: all options clean
