DEBUG_CFLAGS = -g3 -Wpedantic -Wextra -Werror -march=native -mtune=native -Wshadow 
CFLAGS = -O3 -march=native -mtune=native
FILES = main.c args.c log.c proc.c

timer:
	gcc -o timer ${CFLAGS} -lm -l sqlite3 ${FILES}

debug:
	gcc -o timer_debug ${DEBUG_CFLAGS} -lm -l sqlite3 ${FILES}
