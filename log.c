#include<stdio.h>
#include<string.h>
#include<sqlite3.h>
#include<time.h>

char clm_names[50][50];
char clm_vals[50][50];
int je1 = 0;
int j2 = 0;

void make_db(char *activity,time_t time){
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc = sqlite3_open("log.db",&db);

	char update[1024];
	//write a sql command to insert a proccess , if it exists then update the process's time
	sprintf(update,"INSERT INTO tmrlog (process_name, time) VALUES ('%s',%d) ON CONFLICT(process_name) DO UPDATE SET time = time + excluded.time;",activity,time);
	char sql[100] = "CREATE TABLE if not exists tmrlog(process_name TEXT PRIMARY KEY,time BIGINT);";
	strcat(sql,update);
	rc = sqlite3_exec(db,sql, 0, 0, &zErrMsg);
	if( rc != SQLITE_OK ){
      		fprintf(stderr, "SQL error: %s\n", zErrMsg);
      		sqlite3_free(zErrMsg);
	}
	sqlite3_close(db);
}

int rowHandler(void *ptr, int columnCount, char **dataPtr, char **columnNamePtr){
	if(ptr != NULL)
		printf("whot %s\n", (char*)ptr);
	for(int i=0 ; i<columnCount; i++)
		if(i == 1) // number
			strcpy(clm_vals[je1++],dataPtr[i]);
		else //process_names
		     	strcpy(clm_names[j2++],dataPtr[i]);
	return 0;
}

void show_log(){
	sqlite3 *db;
	char *zErrMsg = 0;

	int result = sqlite3_open("log.db",&db);
	
	result = sqlite3_exec(db,"select * from tmrlog;",rowHandler,0,&zErrMsg);
	if(result != SQLITE_OK){
		fprintf(stderr,"SQL error(show): %s\n",zErrMsg);
		sqlite3_free(zErrMsg);
	}
	printf("  Process\tTime Spent\n\n");
	for(int x = 0; x<je1 ;x++)
		printf("  %6s\t%6s\n",clm_names[x],clm_vals[x]);
	sqlite3_close(db);
}
