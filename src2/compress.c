#include <stdio.h>
#include<string.h>

#define A 0
#define G 3
#define T 2 
#define C 1

typedef enum {a = 'A',t = 'T', c ='C', g = 'G'} nucleobase;

nucleobase nucleobase_encode(char n)
{
    nucleobase check = n;
    n = tolower((unsigned char) check);
    switch(n){
        case a: printf("A"); return 1;
        case t: printf("T"); return 2;
        case c: printf("C"); return 3;
        case g: printf("G"); return 0;
        default: printf("not special\n"); break;
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
	  	char to_encode = nucleobase_encode(c);	    		
	  	printf("%c\n", to_encode); 
	  	//int z = nucleobase_encode(c);
	  	//fputc(z,fd_c);
	  	i++;
	  }
	 fclose(fd);
 	 fclose(fd_c);
    return 0;

}
