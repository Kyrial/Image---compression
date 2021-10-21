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

//initialiser la seed avant
int genereMsg( int nTaille){
      
      int alea = rand()%nTaille;
      //printf("pseudo aléatoire %i  \n",alea);
      return alea;
}

void seuil(int nTaille,OCTET* ImgIn, OCTET* ImgOut, int S){
 for (int i=0; i < nTaille; i++)
     {
       //printf("img : %i \n", ImgIn[i]);
       if (ImgIn[i] == 0)
        ImgOut[i]=0; 
      else {
        ImgOut[i]=255;
        //printf("MIAOU");
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

void insertion(int nTaille,OCTET* ImgIn,OCTET* imgOut, int plan, int seed){
  srand(seed);
  copyTabpgm(nTaille,ImgIn,ImgOut);
  int binaire = (int)pow(2,plan);
  for (int i=0; i < (nTaille); i++){
    ImgOut[i] = ImgIn[i] | binaire;
    ImgOut[i] = ImgIn[i] & genereMsg(1)*(int)pow(2,plan);
    
  

   // printf(" test " BYTE_TO_BINARY_PATTERN "  et valeur original: " BYTE_TO_BINARY_PATTERN "\n" , BYTE_TO_BINARY(planBinaire[i]), BYTE_TO_BINARY(ImgIn[i]) );
  }
}


int main(int argc, char* argv[])
{
 
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, Seed;
 
  if (argc != 3) 
     {
       printf("Usage: ImageIn.pgm seed_Du_Message \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   //sscanf (argv[2],"%s",cNomImgEcrite);
   sscanf (argv[3],"%d",&Seed);

   OCTET *ImgIn, *planbinaire, *imgSeuil;
    
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
	allocation_tableau(planbinaire, OCTET, nTaille);
  allocation_tableau(imgSeuil, OCTET, nTaille);




























  planBinaire( nTaille, ImgIn, planbinaire, 7);
  seuil( nTaille, planbinaire,  imgSeuil, 0);
  char planBinaireMSB[250]= "planBinaireMSB.pgm";
  ecrire_image_pgm(planBinaireMSB, imgSeuil, nH, nW);

  planBinaire( nTaille, ImgIn, planbinaire, 0);
  seuil( nTaille, planbinaire,  imgSeuil, 0);
  char planBinaireLSB[250]= "planBinaireLSB.pgm";
  ecrire_image_pgm(planBinaireLSB, imgSeuil, nH, nW);

   return 1;
}
