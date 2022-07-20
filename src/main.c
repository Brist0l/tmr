#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int c;
  bool sec = false;

  while ((c = getopt(argc, argv, "s")) != -1) {
    switch (c) {
      case 's':
	sec = true;
	break;

      default:
	fprintf(stderr, "Usage: timer (time)\n-s:seconds\n");
	exit(EXIT_FAILURE);
      case -1:
	break;
    }
  }
  for (int i = 0; i < argc; i++) {
    printf("Args:%s\n", argv[i++]);
  }
  int time_x = atoi(argv[1]);

  if (sec == true) time_x *= 60;

  printf("%d\n", time_x);
  sleep(time_x);
}
