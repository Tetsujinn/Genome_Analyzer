#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include "functions.h"

#define MAX_GENES 1000



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
int initial_start = 0;

struct gene_map_s gene_map; // map to store 


int cond = -1; // bool

 char *seq = get_SeqGenome("LC547526.1");

 printf("gene_stop : %d\n", find_stop(get_SeqGenome("LC547526.1")));

//Example
/*
AAAGTATGCTGACTAUGAGGCTAGGAGACTAATGGGCAAGTTGACGTAUGCAGTAGTGTG
     .        .  . 
     5       14  I
*/
do{
   
   cond = find("ATG", initial_start + seq) + initial_start;
   
   if(cond != -1){
	
	gene_start = cond - 3;
   	printf("gene_start : %d\n", gene_start);
   	cond = find_stop(seq + gene_start);		
  	
  	if(cond != -1){
  		
  		gene_stop = gene_start + cond -3;
  		printf("gene_stop : %d\n", gene_stop);
   		
   		gene_map.gene_start_in[gene_map.genes_counter] = gene_start;
    		gene_map.gene_stop_in[gene_map.genes_counter] = cond - 3;
		gene_map.genes_counter++;
		
		initial_start += gene_stop + 3; 
	
	}
  	
	}
	
	
}while(cond != -1);

//printf("%lln, %lln, %lld", gene_map.gene_start_in, gene_map.gene_stop_in, gene_map.genes_counter++);

}
	

 
 
