#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

void convert_time(time_t time, bool is_sec);
void send_notification(int time, bool sec);

void convert_time(time_t time, bool is_sec){
      int mins = time/60;
      int secs;
      char suffix_minsx[5];
      char suffix_secsx[5];

      strcpy(suffix_minsx, "mins");
      strcpy(suffix_secsx, "secs");

      if(is_sec == false)
            secs = time - mins*60;
      else
            secs = time;

      if (mins <= 1) 
	      strcpy(suffix_minsx, "min");
      if (secs <= 1) 
	      strcpy(suffix_secsx, "sec");

      printf("\rTime Left: %d %s %d %s", mins, suffix_minsx, secs, suffix_secsx);
}

void send_notification(int time, bool is_sec) {
      char command[50];
      char suffix[10];

      if (is_sec == true) {
            strcpy(suffix, "secs");
      } else {
            strcpy(suffix, "mins");
            if (time == 60) 
		    strcpy(suffix, "min");
            time /= 60;
      }
      snprintf(command, 50, "notify-send -u low '%d %s over'\n", time, suffix);
      system(command);
}

int main(int argc, char* argv[]) {
      	bool is_sec = false;
      	int arg_num = 1;
	int c;
	
	if(getopt(argc,argv,"s")=='s')
                	is_sec = true;
                
                //        fprintf(stderr, "Usage: ./timer (time)\n-s\tseconds\n");
                 //       exit(EXIT_FAILURE);

      	if(argc == 3) // if -s flag is also included
	      	arg_num += 1;

      	time_t time_x = atoi(argv[arg_num]);  // converting the str {time} into int
      	
	if(is_sec == false)
		time_x *= 60;
      
	// makes the program sleep for the given amount of time
      	for(time_t i = time_x; i > 0; i--) {
            convert_time(i, is_sec);
            fflush(stdout);
            sleep(1);
      }
	printf("\n");
      	send_notification(time_x, is_sec);
}
