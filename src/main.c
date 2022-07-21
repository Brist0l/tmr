#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void send_notification(int time, bool sec) {
  char command[100];

  char suffix[7] = "mins";
  if (sec == true) strcpy(suffix, "secs");

  int j = snprintf(command, 100, "notify-send -u low '%d %s over :)'\n", time,
                   suffix);
  system(command);
}

int main(int argc, char *argv[]) {
  int c;
  bool sec = false;
  int arg_num = 1;

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

  /***for (int i = 0; i < argc; i++) {
    printf("Num:%d Args:%s\n", i, argv[i]);
  }
  for debugging purposes
  ***/

  if (argc == 3) arg_num += 1;
  int time_x = atoi(argv[arg_num]);

  send_notification(time_x, sec);
  if (sec != true) time_x *= 60;
  printf("%d\n", time_x);
  sleep(time_x);
}
