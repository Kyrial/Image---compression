// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"
/**
comp= 0 pour rouge, 1 pour vert, 2 pour bleu;
**/
void getComposante(int nTaille,OCTET* ImgIn, OCTET* ImgComp, int comp){
      for (int i=0; i < (nTaille); i++)
       ImgComp[i]= ImgIn[(i*3)+comp];
}
void getComposanteDiv2(int nH,int nW,OCTET* ImgIn, OCTET* ImgComp, int comp){
      
      
  for (int i = 0; i < (nH)/2; i+=1)
    for (int j = 0; j < (nW)/2; j+=1)
            {
             int  i6 = i*6;
             int  j6=j*6;
             
             //  ImgComp[(i * (nW/2) + j)] = ImgIn[i6 * nW + j6 + comp];
              ImgComp[(i * (nW/2) + j)] = (int)ceil((ImgIn[i6 * nW + j6 + comp]+ImgIn[(i6+3) * nW + j6 + comp]+ImgIn[(i6+3) * nW + j6+3 + comp]+ImgIn[(i6) * nW + j6+3 + comp])/4);
            }
      
      
      
 /*     for (int i = 0; i < (nH)/2-1; i+=2)
          for (int j = 0; j < (nW)/2-1; j+=2)
            {
       ImgComp[(int)floor((i * nW + j))]=ceil((ImgIn[(i * nW)*3 + j*3 + comp]+ImgIn[((i+1) * nW)*3 + j*3 + comp]+ImgIn[(i+1) * nW*3 + j*3+3 + comp]+ImgIn[i * nW*3 + j*3+3 + comp])/4);
     }*/
}
void copyComp(int nTaille3,OCTET* ImgOut, OCTET* ImgIn, int comp){
      for (int i=0; i < nTaille3; i+=3)
       ImgOut[i+comp]= ImgIn[i+comp];
}

void copyComp2(int nH,int nW,OCTET* ImgOut, OCTET* ImgIn, int comp){
      for (int i = 0; i < (nH); i+=1)
          for (int j = 0; j < (nW); j+=1)        
            ImgOut[(i * nW*3) + j*3+comp]=ImgIn[(i * nW*3) + j*3+comp];

}

void reverseComposante(int nTaille,OCTET* ImgOut, OCTET* ImgComp, int comp){
      for (int i=0; i < ceil(nTaille); i++)
       ImgOut[i*3+comp]= ImgComp[i];
}

void reverseComposanteDiv2(int nH,int nW,OCTET* ImgOut, OCTET* ImgComp, int comp){
     for (int i = 0; i < (nH); i+=1)
          for (int j = 0; j < (nW); j+=1)
            {
           //   printf("%i \n", ImgIn[i6 * nW + j6 + comp]);
       ImgOut[(i * nW*3) + j*3+comp]=ImgComp[(int)floor(((i/2) * (nW/2) + j/2))];
            }
}


int main(int argc, char* argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  
  if (argc != 2) 
     {
       printf("Usage: ImageIn.ppm  \n"); 
       exit (1) ;
     }
   
   sscanf (argv[1],"%s",cNomImgLue) ;
  // sscanf (argv[2],"%s",cNomImgEcrite);
  // sscanf (argv[3],"%d",&S);

   OCTET *ImgIn, *ImgOut, *ImgTempR, *ImgTempB, *ImgTempG;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   int nHdiv2 = nH/2;
   int nWdiv2 = nW/2;
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	 allocation_tableau(ImgTempR, OCTET, ceil(nTaille/4.0f));
   allocation_tableau(ImgTempB, OCTET, ceil(nTaille/4.0f));
	 allocation_tableau(ImgTempG, OCTET, nTaille);


  getComposanteDiv2( nH, nW, ImgIn, ImgTempR, 0);
    getComposante( nTaille, ImgIn, ImgTempG, 1);
  getComposanteDiv2( nH, nW, ImgIn, ImgTempB, 2);

  char nomOut1_r[250]= "1_out_1_rouge.pgm";
 ecrire_image_pgm(nomOut1_r, ImgTempR, nH/2, nW/2);
   char nomOut1_b[250]= "1_out_1_bleu.pgm";
 ecrire_image_pgm(nomOut1_b, ImgTempB, nH/2, nW/2);
  char nomOut1_g[250]= "1_out_1_vert.pgm";
 ecrire_image_pgm(nomOut1_g, ImgTempG, nH, nW);

  reverseComposanteDiv2( nH, nW, ImgOut,  ImgTempR, 0);
  reverseComposanteDiv2( nH, nW, ImgOut,  ImgTempB, 2);
 // reverseComposante( nTaille, ImgOut,  ImgIn, 1);
  copyComp2( nH, nW, ImgOut, ImgIn,1);

  char nomOut1[250]= "1_out_1.ppm";
  ecrire_image_ppm(nomOut1, ImgOut,  nH, nW);
  free(ImgIn);
  return 1;
}
