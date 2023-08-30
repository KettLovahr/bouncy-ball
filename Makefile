OBJS="main.c"
OUT="raylib"
CC=gcc
LIBS="-lraylib"

build:
	${CC} -o ${OUT} ${OBJS} ${LIBS}

run:
	make build
	./${OUT}
