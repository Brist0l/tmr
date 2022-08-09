DEBUG_CFLAGS = -g3 -Wextra -Werror -march=native -mtune=native -Wshadow 
CFLAGS = -O3

timer:
	gcc -o timer ${CFLAGS} -lm src/main.c
