DEBUG_CFLAGS = -g3 -Wextra -Werror -march=native -mtune=native -Wshadow 
CFLAGS = -03

timer:
	clang-format -i -style=file src/main.c src/get_input.c
	gcc -o bin/release/timer ${DEBUG_CFLAGS} -lm src/main.c src/get_input.c
