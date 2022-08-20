include config.mk

SRC = $(wildcard src/*.c)
HDR = $(wildcard src/*.h)

OBJ_DIR = obj
OBJ = ${SRC:src/%.c=${OBJ_DIR}/%.o}

all: options ${EXECUTABLE}

${OBJ_DIR}:
	@mkdir ${OBJ_DIR}
	@echo Object directory "${OBJ_DIR}" created

config.h: config.def.h
	@cp $< $@
	@echo Default config copied to $@

${OBJ_DIR}/%.o: src/%.c ${HDR} config.h ${OBJ_DIR}
	${CC} ${CFLAGS} -c $< -o $@

${EXECUTABLE}: ${OBJ}
	${CC} ${LDFLAGS} $^ -o $@

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
