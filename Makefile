CFILES="main.c"
OUT="bouncy-ball"
CC=gcc
LIBS="-lraylib"

build:
	${CC} -o ${OUT} ${CFILES} ${LIBS}

run: build
	./${OUT}
