#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Read from command line and returns char pointer to string command*/
char * get_a_line(void)
{
	char * line = malloc(100), * linep = line;
	size_t lenmax = 100, len = lenmax;
	int c;
	
	if(line == NULL)
		return NULL;

	while(1){
		c = fgetc(stdin);
		if(c == EOF)
			break;

		if(--len == 0) {
			len = lenmax;
			char * linen = realloc(linep, lenmax *= 2);

			if(linen == NULL) {
				free(linep);
				return NULL;
			}
			line = linen + (line - linep);
			linep = linen;
		}
		
		if((*line++ = c) == '\n')
			break;
	}
	*line = '\0';
	return linep;
}

/* Read from a char pointer and returns its length as a size_t (unsigned int)*/
size_t length(const char *str)
{
	const char *s;
	for(s=str; *s; ++s);
	return(s-str);
}

/* My implementation of system() library function using fork()*/
int my_system(const char *command)
{
	#ifdef FORK
		pid_t childPid, wPid;
		int status;
		switch(childPid = fork()){
			/* Error */
			case -1:
				status = -1; 
				printf("Error in creating child process");
				break;
			/* Successful */
			case 0:
				if(execl("/bin/sh", "sh", "-c", command, (char *) NULL) == -1){
					printf("Error in exec");
				}
				exit(0);
			default:
				waitpid(childPid, &status, 0);
		}
	#elif VFORK
		pid_t childPid, wPid;
		int status;
		switch(childPid = fork()){
			/* Error */
			case -1:
				status = -1; 
				printf("Error in creating child process");
				break;
			/* Successful */
			case 0:
				if(execl("/bin/sh", "sh", "-c", command, (char *) NULL) == -1){
					printf("Error in exec");
				}
				exit(0);
			default:
				waitpid(childPid, &status, 0);
		}
	#elif CLONE
		system(command);
	#elif PIPE
		system(command);
	#else
		system(command);
	#endif
		return 0;
	}
int main(){
	printf("Enter your command: ");
	while(1){
		char * line = get_a_line();
		if(length(line) > 1) {
			struct timespec start, stop;
			clock_gettime(CLOCK_REALTIME, &start);
			my_system(line);
			clock_gettime(CLOCK_REALTIME, &stop);
			double time = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / 1E9;
			printf("Execution of this command took %lf seconds", time);
			
		}
		else{
			exit(0);
		}
	}
	return 0;
}
