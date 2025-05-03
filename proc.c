#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

char** str_split(char* a_str, const char a_delim){
	char** result    = 0;
    	size_t count     = 0;
 	char* tmp        = a_str;
   	char* last_comma = 0;
   	char delim[2];
   	delim[0] = a_delim;
   	delim[1] = 0;

    	while (*tmp){
        	if (a_delim == *tmp){
            		count++;
            		last_comma = tmp;
        	}
        tmp++;
    	}

    	count += last_comma < (a_str + strlen(a_str) - 1);
    	count++;
    	result = malloc(sizeof(char*) * count);

    	if (result){
        	size_t idx  = 0;
        	char* token = strtok(a_str, delim);

        	while (token){
        	    assert(idx < count);
        	    *(result + idx++) = strdup(token);
        	    token = strtok(0, delim);
        	}
        	assert(idx == count - 1);
        	*(result + idx) = 0;
    	}

    	return result;
}

void focus(){
	FILE *fp1;
	FILE *fp2;
  	char path[1024];
	char *ps = (char *)malloc(20000);
	char *focus = (char *)malloc(20000);
	char **tokens;

  	fp1 = popen("ps x", "r");
  	fp2 = fopen("focus.txt", "r");

  	while(fgets(path, sizeof(path), fp1) != NULL)
		strcat(ps,path);
  	while(fgets(path, sizeof(path), fp2) != NULL)
		strcat(focus,path);

	tokens = str_split(focus,'\n');

	for(int i = 0;*(tokens + i);i++){
		char *ff = strstr(ps,*(tokens+i));
		if(ff != NULL){
			char command[100] = "killall ";
			strcat(command,*(tokens+i));
			system(command);
		}
	}

	pclose(fp1);
  	pclose(fp2);
}
