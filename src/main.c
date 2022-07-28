#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "get_input.h"

void convert_time(int time, bool sec);
void send_notification(int time, bool sec);

const char suffix_mins[5] = "mins";
const char suffix_secs[5] = "secs";

void convert_time(int time, bool sec) {
  int mins = time / 60;
  int secs;
  char suffix_minsx[5];
  char suffix_secsx[5];

  strcpy(suffix_minsx, suffix_mins);
  strcpy(suffix_secsx, suffix_secs);

  if (sec == false)
    secs = 60 + (int)remainder(time, 60);
  else
    secs = time;

  if (mins <= 1) strcpy(suffix_minsx, "min");
  if (secs <= 1) strcpy(suffix_secsx, "sec");

  printf("\rTime Left: %d %s %d %s", mins, suffix_minsx, secs, suffix_secsx);
}

void send_notification(int time, bool sec) {
  char command[50];
  char suffix[10];

  if (sec == true) {
    strcpy(suffix, suffix_secs);
  } else {
    strcpy(suffix, suffix_mins);
    if (time == 60) strcpy(suffix, "min");
    time /= 60;
  }
  snprintf(command, 50, "notify-send -u low '%d %s over :)'\n", time, suffix);
  system(command);
}

int main(int argc, char *argv[]) {
  int c;
  bool sec = false;
  int arg_num = 1;

  while ((c = getopt(argc, argv, "s")) != -1) {
    switch (c) {
      case 's':
	// The time inputted will be treated in secs instead of mins
	sec = true;
	break;

      default:
	fprintf(stderr, "Usage: timer (time)\n-s:seconds\n");
	exit(EXIT_FAILURE);
    }
  }

  /***for (int i = 0; i < argc; i++) {
    printf("Num:%d Args:%s\n", i, argv[i]);
  }
  for debugging purposes
  ***/

  // If -s flag is used the {time} shifts it's place from 1 to 2
  if (argc == 3) arg_num += 1;
  int time_x = atoi(argv[arg_num]);  // converting the str {time} into int

  if (sec != true) time_x *= 60;

  // makes the program sleep for the given amount of time
  for (int i = time_x; i > 0; i--) {
    convert_time(i, sec);
    fflush(stdout);
    sleep(1);
  }

  send_notification(time_x, sec);
}
