#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include "functions.h"

#define MAX_GENES 100000



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
int cond = -1;

   
do{
   
   cond = find("ATG", initial_start + get_SeqGenome("LC547526.1")) + initial_start;
   
   if(cond != -1){
	gene_start = cond -3;
   			printf("gene_start : %d\n", gene_start);
   			
   	gene_stop1 = find("TGA", get_SeqGenome("LC547526.1") + gene_start) + gene_start;

   	gene_stop2 = find("TAG", get_SeqGenome("LC547526.1") + gene_start) + gene_start;

   	gene_stop3 = find("TAA", get_SeqGenome("LC547526.1") + gene_start) + gene_start;

	if(gene_stop1 < 0){
		if(gene_stop2){
			cond = gene_stop3;
				printf("gene_stop : %d\n", cond);
		}else{
			if(gene_stop3<0){
				cond = gene_stop2;
					printf("gene_stop : %d\n", cond);
			}else{
				cond = min(gene_stop2, gene_stop3);
					printf("gene_stop : %d\n", cond);
			}
		}

	}else{
		if(gene_stop2 <0){
			if(gene_stop3 <0){
				cond = gene_stop1;
				printf("gene_stop : %d\n", cond);	
			}else{
				cond = min(gene_stop1, gene_stop3);
						printf("gene_stop : %d\n", cond);
			}
		}else{
			if(gene_stop3 < 0){
				
				cond = min(gene_stop1, gene_stop2);
					printf("gene_stop : %d\n", cond);
			}else{
				int mini=min(gene_stop1,gene_stop2);
        			cond = min(mini,gene_stop3);
					printf("gene_stop : %d\n", cond);
			}
		}
		
	}
	if(cond != -1){
	
	
   		//gene_map.gene_start_in[gene_map.genes_counter] = gene_start;
    		//gene_map.gene_stop_in[gene_map.genes_counter] = cond - 3;
		//gene_map.genes_counter++;
		initial_start += gene_stop + 3; 
	}	
	}
	
}while(cond != -1);

//printf("%lln, %lln, %lld", gene_map.gene_start_in, gene_map.gene_stop_in, gene_map.genes_counter++);
}	
	

 
 
