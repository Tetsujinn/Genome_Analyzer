#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
void main(int argc, char **argv)
{
	if(argc != 2)
    		printf("Usage: %s file\n",argv[0]);
	
	FILE * fp;
	FILE * fd_descr;
	FILE * fd_seq;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
 
	fp = fopen(argv[1], "r");
	
	fd_descr=fopen("description.txt","w");
	
	if (fp == NULL)
		exit(EXIT_FAILURE);
	
	if (fd_descr == NULL)
		exit(EXIT_FAILURE);	
	
	fd_seq = NULL;
	
	int pos;
	char *file_name = NULL; 

	
	while ((read = getline(&line, &len, fp)) != -1) {
		/* Delete trailing newline */
		if (line[read - 1] == '\n')
			line[read - 1] = 0;
		/* Handle comment lines*/
		if (line[0] == '>') {

				fputs(line+1,fd_descr);
				fputc('\n',fd_descr);
				if(fd_seq){
					fclose(fd_seq);
					free(file_name);
				}
				pos = 0;
				while(line[pos] != ' ')
					pos++;
				file_name = strndup(line+1,pos-1);
				
				fd_seq = fopen(file_name,"w");	
			        if(!fd_seq)
					printf("Error: can't open files sequence");
		} else {
			/* Print everything else */
				fputs(line,fd_seq);	
		}
	}
	printf("\n");
 
	fclose(fp);
	fclose(fd_descr);
	if (line)
		free(line);
	exit(EXIT_SUCCESS);
}
