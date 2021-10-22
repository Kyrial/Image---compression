// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')


int genereKeyXOR( int nTaille){
      
      int alea = rand()%nTaille;
      //printf("pseudo aléatoire %i  \n",alea);
      return alea;
}

void chiffrementSymetrique(int nTaille,OCTET* ImgIn, OCTET* ImgOut){
  //copyTabpgm( nTaille, ImgIn, ImgOut)

  for (int i=0; i < (nTaille); i++){
    int alea = genereKeyXOR(nTaille);
    ImgOut[i]= ImgIn[i] ^ alea;
  }
}



//initialiser la seed avant
int genereMsg( int nTaille){
      
      int alea = rand()%nTaille;
   //   printf("pseudo aléatoire %i  \n",alea);
      return alea;
}

void seuil(int nTaille,OCTET* ImgIn, OCTET* ImgOut, int S){
 for (int i=0; i < nTaille; i++)
     {
       if (ImgIn[i] == 0)
        ImgOut[i]=0; 
      else {
        ImgOut[i]=255;
      }
     }
}

void copyTabpgm(int nTaille,OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}


void planBinaire(int nTaille,OCTET* ImgIn,OCTET* planBinaire, int plan){
  int binaire = (int)pow(2,plan);
  for (int i=0; i < (nTaille); i++){
    planBinaire[i] = ImgIn[i] & binaire;
   // printf(" test " BYTE_TO_BINARY_PATTERN "  et valeur original: " BYTE_TO_BINARY_PATTERN "\n" , BYTE_TO_BINARY(planBinaire[i]), BYTE_TO_BINARY(ImgIn[i]) );
  }
}

void insertion(int nTaille,OCTET* ImgIn,OCTET* ImgOut, int plan, int seed){
  srand(seed);
  copyTabpgm(nTaille,ImgIn,ImgOut);
  int otherPlan = 0;
  for(int j=0; j<8;j++)
		if(j!=plan)
			otherPlan+=	(int)pow(2,j);
	
  int binaire = (int)pow(2,plan);
  for (int i=0; i < (nTaille); i++){	  
//printf("plan binaire : " BYTE_TO_BINARY_PATTERN "\n" , BYTE_TO_BINARY(binaire));
 //   printf("val filtre : " BYTE_TO_BINARY_PATTERN "\n" , BYTE_TO_BINARY(ImgIn[i] | binaire));
    ImgOut[i] = ImgIn[i] | binaire;
		int msg = (genereMsg(2)*(int)pow(2,plan)+otherPlan);
    ImgOut[i] = ImgOut[i] & msg; 
//    printf("val filtre : " BYTE_TO_BINARY_PATTERN " \n resultat " BYTE_TO_BINARY_PATTERN "  et valeur original: " BYTE_TO_BINARY_PATTERN "\n\n" ,BYTE_TO_BINARY(msg), BYTE_TO_BINARY(ImgOut[i]), BYTE_TO_BINARY(ImgIn[i]) );
  }
}
void insertionWithoutFirstLine(int nH, int nW,OCTET* ImgIn,OCTET* ImgOut, int plan, int seed){
  srand(seed);
  copyTabpgm(nH*nW,ImgIn,ImgOut);
  int otherPlan = 0;
  for(int j=0; j<8;j++)
		if(j!=plan)
			otherPlan+=	(int)pow(2,j);
	
  int binaire = (int)pow(2,plan);
	for (int i=1; i < nH; i++)
    for (int j=1; j < nW; j++){

    ImgOut[i*nW + j] = ImgIn[i*nW + j] | binaire;
		int msg = (genereMsg(2)*(int)pow(2,plan)+otherPlan);
    ImgOut[i*nW + j] = ImgOut[i*nW + j] & msg; 
    }
}

int main(int argc, char* argv[])
{
 
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, Seed,plan;
 
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm seed_Du_Message \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   //sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[2],"%d",&Seed);
	// sscanf (argv[3],"%d",&plan);
   OCTET *ImgIn, *ImgOut, *ImgChiffre, *ImgDechiffre ;
    
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(ImgOut, OCTET, nTaille);
  allocation_tableau(ImgChiffre, OCTET, nTaille);  allocation_tableau(ImgDechiffre, OCTET, nTaille);

	
  plan = 7;
	

	srand(Seed);
  	chiffrementSymetrique(nTaille, ImgIn, ImgChiffre);
	//insert msg secret sauf i =0 et j=0
	insertionWithoutFirstLine(nH, nW, ImgChiffre, ImgOut,  plan, Seed);	
	char msgIncrusterChiffre[250]= "imgChiffreWithMarque.pgm";
 	ecrire_image_pgm(msgIncrusterChiffre, ImgOut, nH, nW);

  
  
  srand(Seed);
	chiffrementSymetrique(nTaille, ImgOut, ImgDechiffre);
	char msgIncrusterDehiffre[250]= "imgDechiffreWithMarque.pgm";
 	ecrire_image_pgm(msgIncrusterDehiffre, ImgDechiffre, nH, nW);
	
	
	
	
	
	/*
	if(plan<8 && plan>=0){
	insertion( nTaille, ImgIn, ImgOut,  plan, Seed);

	char msgIncruster[250]= "msgIncrusterMSB.pgm";
 	ecrire_image_pgm(msgIncruster, ImgOut, nH, nW);
	}
	else{
		printf("attention, plan binaire incorrecte\n"); 
	}*/







/*
  planBinaire( nTaille, ImgIn, planbinaire, 7);
  seuil( nTaille, planbinaire,  imgSeuil, 0);
  char planBinaireMSB[250]= "planBinaireMSB.pgm";
  ecrire_image_pgm(planBinaireMSB, imgSeuil, nH, nW);

  planBinaire( nTaille, ImgIn, planbinaire, 0);
  seuil( nTaille, planbinaire,  imgSeuil, 0);
  char planBinaireLSB[250]= "planBinaireLSB.pgm";
  ecrire_image_pgm(planBinaireLSB, imgSeuil, nH, nW);
*/
   return 1;
}
