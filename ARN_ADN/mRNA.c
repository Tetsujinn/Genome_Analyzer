#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>



#define ALIGN 64

char *Generating_mRNA(const char *fname){
  
   if(!fname)
    return printf("Error: null pointer!\n"),NULL;

  //Structure to store meta-info
  struct stat sb;

  //Load meta-info
  if(stat(fname,&sb)<0)
    return printf("Error: can't stat %s !\n",fname),NULL;

  //Open file data
  FILE *fd=fopen(fname,"r");

  //check pointer
  if(!fd)
    return printf("Error: can't open %s !\n",fname),NULL;

  //Allocate memory for store datas
  char *t= aligned_alloc(ALIGN,sb.st_size+1);

  //Check pointer
  if(!t)
    return printf("Error: can't allocate memory !\n"),NULL;

  //Load all datas
  unsigned long long n= fread(t,sizeof(char),sb.st_size,fd);

  //Close file data
  fclose(fd);

  //Check no missing data
  if(n != sb.st_size)
    return printf("Error: read size doesn't match !"),NULL;

  //Make sure data is zero terminated
  t[sb.st_size]=0;


  unsigned long long pos=0;
  unsigned long long t_len=strlen(t);
  
  FILE *fd_s=NULL;
  fd_s=fopen(fname,"w");
  fwrite(t,sizeof(char),t_len,fd_s); 
  
  for(pos=0;pos<t_len;pos++){
  if(t[pos]=='T')
  { 
    t[pos]='U';
     
  }
  
  }
  fwrite(t,sizeof(char),t_len,fd_s); 
     
  
   fclose(fd_s);
  
   return t;
}

static inline void release_data(char *t){
  //Check arg
  if(t)
    free(t);
}



  

int main(int argc, char **argv){

 char *data=Generating_mRNA(argv[1]);

 //Generating_mRNA(data);
 release_data(data);

return 0;

}
