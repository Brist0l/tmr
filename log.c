#include<stdio.h>
#include<string.h>
#include<sqlite3.h>
#include<time.h>

void make_db(char *activity,time_t time){
	sqlite3* db;
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
