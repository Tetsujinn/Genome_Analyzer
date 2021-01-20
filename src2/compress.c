#include <stdio.h>
#include<string.h>

typedef enum {A = 'A',T = 'T', C ='C', G = 'G'} extrema;

extrema nucleobase_encode(char n)
{
    extrema check = n;
    n = tolower((unsigned char) check);
    switch(n){
        case A: printf("neg inf"); return 1;
        case T: printf("zero"); return 2;
        case C: printf("pos inf"); return 3;
        case G: printf("pos inf"); return 0;
        default: printf("not special"); break;
    }

}


int main(int argc, char ** argv){
if(argc != 2)
		printf("ERROR, %s fichier du genome\n", argv[0]);
		
	FILE *fd = fopen(argv[1], "r");
    	char *filename= strcat(argv[1],".compressed");
    	
    	FILE *fd_c = fopen(filename, "w");
    	
    	if(!fd)
    		return printf("ERROR, le fichier genome n'est pas ouvert\n");
	if(!fd)
    		return printf("ERROR, le fichier genome n'est pas compressé\n");
    	
    	unsigned char compress=0;
	  int i=0;
	  char c;
	  while((c=fgetc(fd))!=EOF){	    		
	  	printf("%d\n", nucleobase_encode('c')); 
	  	fputc(compress,fd_c);
	  }
	 fclose(fd);
 	 fclose(fd_c);
    return 0;

}
