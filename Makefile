timer:main.o
	gcc -o bin/timer obj/main.o
main.o:
	clang-format -i -style=file src/main.c
	gcc -c -Wall src/main.c -o obj/main.o

