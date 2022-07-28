CFLAGS = -g3 -Wextra -Werror -march=native -mtune=native -Wshadow 

timer:main.o
	gcc -o bin/release/timer -lm obj/release/main.o
main.o:
	clang-format -i -style=file src/main.c
	gcc -c -O3 src/main.c -o obj/release/main.o
clean:
	@echo "Cleaning...."
	rm -rf obj/
	rm -rf src/
debug:
	@echo "Debugging..."
	clang-format -i -style=file src/main.c
	gcc  ${CFLAGS} src/main.c src/get_input.c -o bin/debug/timer -lm
