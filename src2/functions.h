int min(int a, int b){
  if(a<=b)
    return a;
  else
    return b;
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
