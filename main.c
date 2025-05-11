#define _XOPEN_SOURCE

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <pthread.h>
#include <termios.h>

#include "headers/args.h"
#include "headers/log.h"
#include "headers/proc.h"

#define PROGRESSBAR 15
#define NOTOPENTIME 5

time_t global_time;
char log_name[10];
static struct termios oldt;
bool _pause = false;

void non_canonical_term();
void *thread_takeinput(void* arg);
void *thread_func(void* arg);
void exit_handler(int sig);
void constrtotm(const char *str_time,struct tm *tm);
double convert_to_sec(struct tm *tm);
void convert_time(time_t time,bool first);
void send_notification(time_t time, bool sec);


void non_canonical_term(){ 
	static struct termios newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    	tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    	newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    	newt.c_lflag &= ~(ICANON);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    	tcsetattr( STDIN_FILENO, TCSANOW, &newt);
}

void *thread_takeinput(void* arg){
    /*I choose ' ' to end input. Notice that EOF is also turned off
    in the non-canonical mode*/
	char c;	
	while (true){
//		printf("_pause's value: %s\n", _pause ? "true":"false");
		c = getchar();
    		if((c == ' ') && _pause == false)
			_pause = true;
		else
			_pause = false;
	}
	
	return NULL;
}
void *thread_func(void* arg){
	static int counter = 0;
	if(counter == NOTOPENTIME){
		focus();
		counter = 0;
	}
	else
		counter++;

	return NULL;
}

void exit_handler(int sig){
//      	send_notification(time_x, is_sec);
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
	bool focus_mode = false;
	bool notopen = false;
     	char str_time[9];
	
	struct t_thing args = sendargs(argc,argv);
	
 	time_t time_x = atoi(args.sliced_args[0]);  // converting the str {time} into int
	is_sec = pyboolconverter(args.sliced_args[1]);
	strcpy(str_time,args.sliced_args[2]);	
	strcpy(log_name,args.sliced_args[3]);
	show_logs = pyboolconverter(args.sliced_args[4]); // if show log then don't start the tmr
	reverse_countdown = pyboolconverter(args.sliced_args[5]);
	focus_mode = pyboolconverter(args.sliced_args[6]);
	notopen = pyboolconverter(args.sliced_args[7]);


	if(show_logs == true){
		show_log();
		exit(0);
	}

	if(focus_mode == true)
		focus();

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

	non_canonical_term();

	pthread_t thread;
	pthread_t thread2;

	pthread_create(&thread2, NULL, thread_takeinput, NULL);

	// makes the program sleep for the given amount of time
      	for(time_t i = time_x; i > 0; i--){
		if(notopen == true)
			pthread_create(&thread, NULL, thread_func, NULL);
		
            	convert_time(i,first);
		first = false;
            	fflush(stdout);

		if(_pause == false){
          		sleep(1);
			global_time = time_x - i + 1;
		}
		else{
			while(_pause == true);
		//	_pause = false;
		}
		if(i == 1)
			pthread_cancel(thread2);
		if(notopen == true)
			pthread_join(thread,NULL);
      	}
    	tcsetattr( STDIN_FILENO, TCSANOW, &oldt); //return terminal to the old setting
	printf("\n");
	exit_handler(0);
	pthread_exit(NULL);
}
