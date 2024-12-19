DEBUG_CFLAGS = -g3 -Wpedantic -Wextra -Werror -march=native -mtune=native -Wshadow 
CFLAGS = -O3

timer:
	gcc -o timer ${CFLAGS} -lm src/main.c

debug:
	gcc -o timer_debug ${DEBUG_CFLAGS} -lm src/main.c
