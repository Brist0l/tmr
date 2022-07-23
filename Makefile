CFLAGS = -g3 -Wextra -Werror -march=native -mtune=native -Wshadow 

timer:main.o
	gcc -o bin/timer obj/main.o
main.o:
	clang-format -i -style=file src/main.c
	gcc -c -Wall  src/main.c -o obj/main.o
clean:
	@echo "Cleaning...."
	rm -rf obj/
	rm -rf src/
debug:
	@echo "Debugging..."
	clang-format -i -style=file src/main.c
	gcc -c ${CFLAGS} src/main.c -o obj/main.o 
	gcc -o bin/timer -lm obj/main.o
