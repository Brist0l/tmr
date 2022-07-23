#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

void convert_time(int time, bool sec) {
  char suffix_mins[5] = "mins";
  char suffix_secs[5] = "secs";

  int mins = time / 60;
  int secs;

  if (sec == false)
    secs = 60 + (int)remainder(time, 60);
  else
    secs = time;

  if (mins <= 1) strcpy(suffix_mins, "min");
  if (secs <= 1) strcpy(suffix_secs, "sec");

  printf("\rTime Left: %d %s %d %s", mins, suffix_mins, secs, suffix_secs);
}

void send_notification(int time, bool sec) {
  char command[100];
  char suffix[5] = "secs";

  if (sec != true) {
    // grammar ftw
    strcpy(suffix, "mins");
    if (time == 60) strcpy(suffix, "min");
    time /= 60;
  }
  snprintf(command, 100, "notify-send -u low '%d %s over :)'\n", time, suffix);
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

  if (sec != true) time_x *= 60;
  printf("%d\n", time_x);

  for (int i = time_x; i > 0; i--) {
    convert_time(i, sec);
    fflush(stdout);
    sleep(1);
  }

  send_notification(time_x, sec);
}
