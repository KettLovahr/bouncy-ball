CFILES="main.c"
OUT="raylib"
CC=gcc
LIBS="-lraylib"

build:
	${CC} -o ${OUT} ${CFILES} ${LIBS}

run: build
	./${OUT}
