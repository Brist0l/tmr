#define _XOPEN_SOURCE

#include<stdio.h> 
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include"headers/args.h"

void constrtotm(const char *str_time,struct tm *tm){
	struct tm *tmp;

	memset(tm,0,sizeof(tm));		
	time_t curr_time = time(NULL);
	tmp = localtime(&curr_time);
	*tm = *tmp;	
	strptime(str_time,"%H:%M:%S",tm);// converts the string into struct tm
}

struct tm *getcurtime(struct tm *tm){
//	struct t_thing args = sendargs(argc,argv);
	bool is_sec = false;
        char buf[255];
	char time[255];
	FILE *cmd = popen("date +%H:%M:%S","r");

      	//time_t time_x = atoi(args.sliced_args[0]);  // converting the str {time} into int
	//is_sec = pyboolconverter(args.sliced_args[1]);

	while(fgets(time, sizeof(time), cmd) != NULL);
	
	constrtotm(time,tm);

	return tm; 
//      strftime(buf, sizeof(buf), "%H:%M:%S", &tm);
		
//	if(is_sec == true)
//		printf("%d\n",tm.tm_sec + time_x);
//	else 
//		printf("%d\n",tm.tm_min + time_x);

}
