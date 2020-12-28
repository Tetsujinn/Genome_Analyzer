#include<unistd.h>
#include<string.h>

#include"load.h"
#include"detection.h"
#include"rdtsc.h"

//Genere la mapping des codons start et stop d'une sequence ADN
gene_map mapping(char *seq){

  //Alloue la memoire pour la map des genes
  gene_map gm=malloc(sizeof(struct gene_map_s));
  //Initialise le compteur de gene a 0
  gm->gene_counter = 0;

  //Variable pour enregistrer la pos d'un codon start
  //Seulement si y en a un de trouver
  int start_pos = 0;
  //Variable pour enregistrer la pos d'un codon stop
  //Seulement si y en a un de trouver
  int stop_pos = 0;

  //Variable pour check si on trouve notre motif
  int check=-1;

  //Chercher les zones codantes / mapper la sequence
  do{
    //Cherche le motif "ATG" dans la sequence à partir de la position du dernier codon stop trouvé
    //stop_pos: 0 à l'init
    check=find("ATG",seq+stop_pos);
    //Si on a trouvé le motif
    if(check!=-1){
      //On enregistre sa position dans la sequence
      start_pos=stop_pos+check-3;
      /*printf("start_pos : %d "
               "-> codon : %c%c%c\n",start_pos,seq[start_pos],seq[start_pos+1],seq[start_pos+2]);
      */

      //Cherche le premier codon stop à partir de la position du dernier codon start trouvé
      check=find_stop(seq+start_pos);
      //Si on a trouvé un stop
      if(check!=-1){
        //On enregistre sa position dans la sequence
        stop_pos=start_pos+check-3;
        /*printf("stop_pos : %d "
                 "-> codon : %c%c%c\n",stop_pos,seq[stop_pos],seq[stop_pos+1],seq[stop_pos+2]);
        */

        //On enregistre les positions trouvé dans notre structure, map
        gm->gene_start[gm->gene_counter]=start_pos;
        gm->gene_end[gm->gene_counter]=stop_pos+2;
        gm->gene_counter++;
        //printf("ADD !\n");
      }
    }
  //Tant que l'on trouve un codon start et stop
  }while(check!=-1);

  return gm;
}


//Transnforme l'ADN en ARN messager, seulement pour les genes de la séquence
char **generate_ARN(gene_map gm,char* seq){

  //Alloue de la memoire pour stocker les ARN dans un tableau
  char** ARN_m = (char **)malloc(gm->gene_counter*sizeof(char*));
  //Pour chaque ligne on alloue l'espace nécessaire pour stocker le gene en ARN
  for(int i=0; i < gm->gene_counter; i++)
    ARN_m[i] = (char *)malloc(gm->gene_end[i] - gm->gene_start[i] + 1 *sizeof(char));


  int pos=0;
  int pos_arn=0;
  //Pour chaque gene trouvé
  for(int i=0; i < gm->gene_counter; i++){
    //Init la pos au debut du gene
    pos=gm->gene_start[i];

    pos_arn=0;

    //On parcours le gene caractére par caractére pour l'afficher sous forme ADN
    while(pos<=gm->gene_end[i]){
      //Si on croise le caractère T on le remplace par U
      if(seq[pos]=='T')
        ARN_m[i][pos_arn]='U';
      else
        ARN_m[i][pos_arn]=(char)seq[pos];

      pos++;
      pos_arn++;
    }
  }

  return ARN_m;
}


void generate_prot(char *arn, char **codons){
  int i=0;
  int pos=0;
  char prot[3];
  //Nombre proteines
  int nb_prot=strlen(arn)/3;
  int short_names[nb_prot];
  int symbols[nb_prot];

  printf("ARN_m : ");
  
  //Parcours chaque codons de la sequence ARN
  for(pos=0; pos<nb_prot; pos++){
  	//Recupere le codon dans prot
    prot[0]=arn[pos*3];
    prot[1]=arn[pos*3+1];
    prot[2]=arn[pos*3+2];

    //Compare a tout les codons possible
    //pour trouver a quelle proteine il correspond
    i=0;
    while(strcmp(codons[i],prot) && i<192){
      i+=3;
    }
    //Une fois trouver on enregistre la position du short name
    short_names[pos]=i+1;
    //Une fois trouver on enregistre la position du symbol
    symbols[pos]=i+2;
    printf("%s ",prot);
  }
  //Affichage en parcourant chaque proteine obtenu
  printf("\n(Short name) Protein : ");
  for(pos=0; pos<nb_prot; pos++)
    printf("%s ",codons[short_names[pos]]);
  printf("\n(Symbol) Protein : ");
  for(pos=0; pos<nb_prot; pos++)
    printf("%s ",codons[symbols[pos]]);
  printf("\n");

}


//
int main(int argc, char **argv){
  //Check arg
  if(argc<2)
    return printf("Usage: %s [file]\n",argv[0]);

//Charge les codons en mémoire
char* codons[192]={"AAA","Lys","K",
		    		 "AAC","Asn","N",
		    		 "AAG","Lys","K",
		     		 "AAU","Asn","N",
					 "ACA","Thr","T",
					 "ACC","Thr","T",
					 "ACG","Thr","T",
					 "ACU","Thr","T",
					 "AGA","Arg","R",
					 "AGC","Ser","S",
					 "AGG","Arg","R",
					 "AGU","Ser","S",
					 "AUA","Ile","I",
					 "AUC","Ile","I",
					 "AUG","Met","M",
					 "AUU","Ile","I",
					 "CAA","Gln","Q",
					 "CAC","His","H",
					 "CAG","Gln","Q",
					 "CAU","His","H",
					 "CCA","Pro","P",
					 "CCC","Pro","P",
					 "CCG","Pro","P",
					 "CCU","Pro","P",
					 "CGA","Arg","R",
					 "CGC","Arg","R",
					 "CGG","Arg","R",
					 "CGU","Arg","R",
					 "CUA","Leu","L",
					 "CUC","Leu","L",
					 "CUG","Leu","L",
					 "CUU","Leu","L",
					 "GAA","Glu","E",
					 "GAC","Asp","D",
					 "GAG","Glu","E",
					 "GAU","Asp","D",
					 "GCA","Ala","A",
					 "GCC","Ala","A",
					 "GCG","Ala","A",
					 "GCU","Ala","A",
					 "GGA","Gly","G",
					 "GGC","Gly","G",
					 "GGG","Gly","G",
					 "GGU","Gly","G",
					 "GUA","Val","V",
					 "GUC","Val","V",
					 "GUG","Val","V",
					 "GUU","Val","V",
					 "UAA","Stp","O",
					 "UAC","Tyr","Y",
					 "UAG","Stp","O",
					 "UAU","Tyr","Y",
					 "UCA","Ser","S",
					 "UCC","Ser","S",
					 "UCG","Ser","S",
					 "UCU","Ser","S",
					 "UGA","Stp","O",
					 "UGC","Cys","C",
					 "UGG","Trp","W",
					 "UGU","Cys","C",
					 "UUA","Leu","L",
					 "UUC","Phe","F",
					 "UUG","Leu","L",
					 "UUU","Phe","F"};


  printf("*** CHARGE LA SEQUENCE ***\n\n");
  //Charge la sequence
  char *seq=load_data(argv[1]);


/// MAPPING
  
  //
  double before=rdtsc();

  printf("*** MAPPING EN COURS ***\n\n");
  //Map la sequence avec la structure
  gene_map gm=mapping(seq);  
  
  //
  double after=rdtsc();
  printf("%lf cycles to find all genes\n\n",after-before);


/// GENERE ET AFFICHE TOUT LES GENES SOUS FORME D'ARN MESSAGER

  //
  before=rdtsc();

  printf("*** GENERATION DE L'ARN MESSAGER POUR CHAQUE GENE ***\n\n");
  //Genere l'ARN_m pour chaque gene de la sequence
  char** ARN_m=generate_ARN(gm,seq);

  //
  after=rdtsc();

  //
  int pos=0;
  //Pour chaque gene trouvé
  for(int i=0; i < gm->gene_counter; i++){
    printf("(ADN)Gene %d : ",i+1);

    //Initialise la pos au debut du gene
    pos=gm->gene_start[i];

    //On parcours le gene caractére par caractére pour les afficher
    while(pos<=gm->gene_end[i]){
      printf("%c", seq[pos]);
      pos++;
    }
    printf("\n");

    printf("(ARN)Gene %d : ",i+1); 
    printf("%s",ARN_m[i]);  
    printf("\n\n");
  }

  printf("%lf cycles to generate mARN for all genes\n\n",after-before);


/// GENERE ET AFFICHE LES PROTEINES SELON L'ARN
  //
  before=rdtsc();

  printf("*** GENERATION DES PROTEINES ***\n\n");
  //Genere l'ARN_m pour chaque gene de la sequence
  for(int i=0; i < gm->gene_counter; i++){
    generate_prot(ARN_m[i], codons);
    printf("\n");
  }

  //
  after=rdtsc();
  printf("%lf cycles to generate protein for all genes\n\n",after-before);


///Detect mutation







///Hamming
///To compare 2 sequences :
///		Compress them
///		res = seq1 XOR seq2
///		popcount(res)



  //Libère la mémoire des genes en ARN
  free(ARN_m);
  //Libère la mémoire du mapping
  free(gm);
  //Libère la mémoire de la séquence
  release_data(seq);

  return 0;
}
