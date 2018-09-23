#include <stdio.h>
#include <stdlib.h>

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
	pid_t childPid;
	int status;
	switch(childPid = fork()){
		/* Error */
		case -1:
			status = -1; 
			perror("Error in creating child process");
			break;
		/* Successful */
		case 0:
			execve("/bin/sh", "sh", "-c", command, (char *) NULL);
		default:
			waitpid(childPid, &status, 0);
			
	}
	return 0;
}
int main(){
	while(1){
		char * line = get_a_line();
		if(length(line) > 1) {
			my_system(line);
		}
		else{
			exit(0);
		}
	}
	return 0;
}
