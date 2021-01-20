#ifndef _FUNCTION_SUPP_
#define  _FUNCTION_SUPP_
int min(int a, int b){
  if(a<=b)
    return a;
  else
    return b;
}

int find(char*codon, char*seq){ // codon ! ATG(start); TAG,TGA,TAA(stop)

	unsigned char found = 0; // boolean
	unsigned long long pos; // position codon
	
	for(pos = 0; !found && pos < strlen(seq) - 3; pos++) // -3 to stop before the last 3
		found = !strncmp(codon, seq + pos, 3); // compare 3 by 3
	
	if(found) // if codon exist
	
		return pos; // found
	
	return -1; // not found		
}

int find_stop(char*seq){
	
	int stop1, stop2, stop3;
	stop1 = find("TAG", seq); // position TAG
	stop2 = find("TGA", seq); // position TGA
	stop3 = find("TAA", seq); // position TAA

	if(stop1 < 0){ // return (-1)
		if(stop2 < 0){ // return -1
			return stop3;
		}else{
			if(stop3 < 0)
				return stop2;
			else 
				return min(stop2, stop3);
		}	
	
	} 
	
	else{
		if(stop2 < 0){
			if(stop3 < 0)
				return stop1;
			else 
				return min(stop1, stop3);
			}
		else{
			if(stop3 < 0)
				return min(stop1, stop2);
			else{
				int min123 = min(stop1, stop2);
				return min(min123, stop3);
			}	
		}			
	}
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

#endif
