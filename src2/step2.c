#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#define MAX_GENES 100000

int min(int x, int y, int z){
	if(x<y && x<z)
		return x;
	else if(y<x && y<z)	
		return y;
	else if(z<x && z<y)
		return z;		
}	

int find(char*codon, char*seq){

	unsigned char found = 0;
	unsigned long long pos;
	
	for(pos = 0; !found && pos < strlen(seq) - 3; pos++)
		found = !strncmp(codon, seq + pos, 3);
	
	if(found)
	
		return pos;
	
	return -1;		
}

struct stat st;

char *get_SeqGenome(char *fp){

	FILE * file;
	file = fopen(fp, "r");

	 stat(fp, &st);
	 int size = st.st_size;	



	 char *Sequence_ = malloc(sizeof(char) * size);
	   unsigned i=0;
	   while ( ! feof( file ) && (i<size) ) {
		int theCurrentChar;        
		theCurrentChar = fgetc( file );
		 Sequence_[i] = theCurrentChar;

		 i++;
	    }	

	   fclose(file); 
	return Sequence_;
}


struct gene_map_s {

   //
   unsigned long long genes_counter;

   //Gene start position (ATG)
   unsigned long long gene_start_in[MAX_GENES];

   //Gene stop position (TAA, TAG, TGA)
   unsigned long long gene_stop_in[MAX_GENES];

};




int main(){
 		
int gene_start, gene_stop;
int gene_stop1, gene_stop2, gene_stop3;

int initial_start = 0;
struct gene_map_s gene_map;

unsigned int cond = 1;

   
do{
   
   gene_start = find("ATG", initial_start + get_SeqGenome("LC565412.1")) + initial_start;
         printf("gene_start : %d\n",gene_start);
   gene_stop1 = find("TGA", get_SeqGenome("LC565412.1") + gene_start) + gene_start;
      	 printf("gene_stop1 : %d\n",gene_stop1);
   gene_stop2 = find("TAG", get_SeqGenome("LC565412.1") + gene_start) + gene_start;
         printf("gene_stop2 : %d\n",gene_stop2);
   gene_stop3 = find("TAA", get_SeqGenome("LC565412.1") + gene_start) + gene_start;
 	 printf("gene_stop3 : %d\n",gene_stop3);
   gene_stop = min(gene_stop1, gene_stop2, gene_stop3);
         printf("gene_stop : %d\n",gene_stop);
       
       printf("-----------------"); 
  	
  	if (gene_stop && gene_start)
  	{
  	        gene_map.gene_start_in[gene_map.genes_counter] = gene_start;
    		gene_map.gene_stop_in[gene_map.genes_counter] = gene_stop;
		gene_map.genes_counter++;

  	}else cond = (gene_stop || gene_start);
	
}while(cond >0);
//printf("%lln, %lln, %lld", gene_map.gene_start_in, gene_map.gene_stop_in, gene_map.genes_counter++);
}	
	

 
 
