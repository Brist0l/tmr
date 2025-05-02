#define _XOPEN_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>

#include "headers/args.h"
#include "headers/log.h"

#define PROGRESSBAR 15

time_t global_time;
char log_name[10];

void exit_handler(int sig);
void constrtotm(const char *str_time,struct tm *tm);
double convert_to_sec(struct tm *tm);
void convert_time(time_t time,bool first);
void send_notification(time_t time, bool sec);

void exit_handler(int sig){
	printf("The time elasped is:%d\n",global_time);
	make_db(log_name,global_time);
	exit(0);
}

void constrtotm(const char *str_time,struct tm *tm){
	struct tm *tmp;

	memset(tm,0,sizeof(tm));		
	time_t curr_time = time(NULL);
	tmp = localtime(&curr_time);
	*tm = *tmp;	
	strptime(str_time,"%H:%M:%S",tm);// converts the string into struct tm
}

double convert_to_sec(struct tm *tm){
	time_t tmp_current_time = time(NULL);
//	printf("Localy time: %s\n",asctime(localtime(&tmp_current_time)));
	time_t tmr_time = mktime(tm);
//	printf("Localy tmr time: %s\n",asctime(localtime(&tmr_time)));
	double diff = difftime(tmr_time,tmp_current_time);
	if(diff > 0)
		return diff;
	else
		fprintf(stderr,"Enter a time that is bigger than current time");
}

void convert_time(time_t time,bool first){
	static int time_till_update;
	if(first == true){
		float new_time = time; // convert to float
		time_till_update = ceil(new_time/PROGRESSBAR);
	}
	
	static short progress_bar_count = PROGRESSBAR;

      	int mins = time/60;
     	int secs= time - mins*60;

      	char suffix_minsx[5],suffix_secsx[5];
      
	strcpy(suffix_minsx, "mins");
      	strcpy(suffix_secsx, "secs");
      
      	if(mins <= 1) 
		strcpy(suffix_minsx, "min");
      	if(secs <= 1) 
	      	strcpy(suffix_secsx, "sec");

      	printf("\rTime Left: %d %s %d %s\r\t\t\t\t", mins, suffix_minsx, secs, suffix_secsx);

	static char str[PROGRESSBAR];
	if(time <= time_till_update)
		for(int i = 0;i <= progress_bar_count;i++)
			strcat(str,"-");

	if(time % time_till_update == 0){
		printf("[%s",str);
		printf("\r\t\t\t\t\t\t]");
		strcat(str,"-");
		progress_bar_count--;
	}
}

void send_notification(time_t time, bool is_sec) {
      char command[50];
      char suffix[10];

      if (is_sec == true)
            strcpy(suffix, "secs");
      else{
            strcpy(suffix, "mins");
            if (time == 60) 
		    strcpy(suffix, "min");
            time /= 60;
      }
      snprintf(command, 50, "notify-send -u low '%d %s over'\n", time, suffix);
      system(command);
}

int main(int argc, char* argv[]) {
	signal(SIGINT,exit_handler);

      	bool is_sec = false;
	bool is_clock = false;
	bool first = true;
	bool show_logs = false;
	bool reverse_countdown = false;
     	char str_time[9];
	
	struct t_thing args = sendargs(argc,argv);
	
 	time_t time_x = atoi(args.sliced_args[0]);  // converting the str {time} into int
	is_sec = pyboolconverter(args.sliced_args[1]);
	strcpy(str_time,args.sliced_args[2]);	
	strcpy(log_name,args.sliced_args[3]);
	show_logs = pyboolconverter(args.sliced_args[4]); // if show log then don't start the tmr
	reverse_countdown = pyboolconverter(args.sliced_args[5]);

	if(show_logs == true){
		show_log();
		exit(0);
	}

	//clock time
//	printf("ssrringy time:%s\n",str_time);
	if(strcmp(str_time,"None") != 0){
		struct tm time; 
		constrtotm(str_time,&time);
		time_x = convert_to_sec(&time);
		is_sec = true;	
		is_clock = true;
	}

	if(is_sec == false)
		time_x *= 60;
      
	// makes the program sleep for the given amount of time
      	for(time_t i = time_x; i > 0; i--){
            	convert_time(i,first);
		first = false;
            	fflush(stdout);
          	sleep(1);
		global_time = time_x - i + 1;
      }
	printf("\n");
      	send_notification(time_x, is_sec);
	exit_handler(0);
}
