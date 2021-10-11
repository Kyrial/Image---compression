// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"


void copyTabpgm(int nTaille,OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}


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



void getProba(int nTaille, OCTET* ImgIn, float nivGris[]){
  for(int i=0; i < 256; i++){
    nivGris[i] = 0;
  }

    for (int j=0; j < nTaille; j++){
      int currentGris = ImgIn[j];
      nivGris[currentGris]++;
    }
    for (int j=0; j < 255; j++){
    
      nivGris[j]=nivGris[j]/(float)nTaille;
    }
  }

//entropie = -somme(p(i)*log2(p(i)))
//avec p(i) la proba du niveau de gris i 
void entropie(int nTaille, OCTET * ImgIn){
  float nivGris[255];
  getProba(nTaille, ImgIn, nivGris);
  float resultat=0;

  for(int i=0; i<255; i++){
    if(nivGris[i]!=0)
    resultat =resultat + (float)nivGris[i]*log2((float)nivGris[i]); 

  }
  printf("entropie = %f \n", -resultat);
}


int main(int argc, char* argv[])
{
 
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
 
  if (argc != 2) 
     {
       printf("Usage: ImageIn.pgm  \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
   //sscanf (argv[2],"%s",cNomImgEcrite);
   //sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgChiffre, *ImgDechiffre;
    
   lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;

  
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille);
  lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgChiffre, OCTET, nTaille);
	allocation_tableau(ImgDechiffre, OCTET, nTaille);

  int key = 1500;
  srand(key);

   chiffrementSymetrique(nTaille, ImgIn, ImgChiffre);


  char imgchiffre[250]= "imgchiffre1.pgm";
  ecrire_image_pgm(imgchiffre, ImgChiffre, nH, nW);

  srand(key);

  chiffrementSymetrique(nTaille, ImgChiffre, ImgDechiffre);
  
  char imgdechiffre[250]= "imgdechiffre1.pgm";
  ecrire_image_pgm(imgdechiffre, ImgDechiffre, nH, nW);



//####################
//ENTROPIE
  printf("image original:  \n");
  entropie( nTaille,  ImgIn);
  
  printf("\n image chiffrée:  \n");
  entropie( nTaille,  ImgChiffre);
  free(ImgIn);

   return 1;
}
