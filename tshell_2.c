#include <stdio.h>
#include <stdlib.h>

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

size_t length(const char *str)
{
	const char *s;
	for(s=str; *s; ++s);
	return(s-str);
}



int main(){
	while(1){
		char * line = get_a_line();
		if(length(line) > 1) {
			system(line);
		}
		else{
			exit(0);
		}
	}
	return 0;
}
