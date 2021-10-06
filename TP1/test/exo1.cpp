// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"

int SommeC1R=0;
int SommeC1G=0;
int SommeC1B=0;
int NbeC1 =0;
int SommeC2R=0;
int SommeC2G=0;
int SommeC2B=0;
int NbeC2 =0;

int C1R = 1;
int C1G = 1;
int C1B = 1;

int C2R = 150;
int C2G = 150;
int C2B = 150;


float k_mean(int CR, int CG, int CB, int pixel, OCTET *ImgIn)
{

  float dist = sqrt(pow(ImgIn[pixel] - CR, 2) +
                    pow(ImgIn[pixel] - CG, 2) +
                    pow(ImgIn[pixel] - CB, 2));
  return dist;
}

void resetMoyenneC(){
 SommeC1R=0;
SommeC1G=0;
SommeC1B=0;
 NbeC1 =0;
SommeC2R=0;
SommeC2G=0;
SommeC2B=0;
 NbeC2 =0;
}




void parcoursMoyenneK_mean(int nTaille, OCTET *ImgIn, OCTET *ImgOut){

int moyenneC1R = SommeC1R/NbeC1;
int moyenneC1G= SommeC1G/NbeC1;
int moyenneC1B= SommeC1B/NbeC1;

int moyenneC2R= SommeC2R/NbeC2;
int moyenneC2G= SommeC2G/NbeC2;
int moyenneC2B= SommeC2B/NbeC1;  

for (int i = 0; i < (nTaille*3); i += 3)
  {
    int nR = ImgIn[i];
    int nG = ImgIn[i + 1];
    int nB = ImgIn[i + 2];

    if(nR == C1R && nG == C1G && nB == C1B){
      ImgOut[i] = moyenneC1R;
      ImgOut[i+1] = moyenneC1G;
      ImgOut[i+2] = moyenneC1B;
    } 
    else{
      ImgOut[i] = moyenneC2R;
      ImgOut[i+1] = moyenneC2G;
      ImgOut[i+2] = moyenneC2B;
    }
  }
 
}



void parcoursK_mean(int nTaille, OCTET *ImgIn, OCTET *ImgTemp)
{
  
 for (int i = 0; i < (nTaille*3); i += 3)
  {
   
    float valC1 = k_mean(C1R,C1G,C1B,i,ImgIn);
    float valC2 = k_mean(C2R,C2G,C2B,i,ImgIn);
   
    if(valC2 > valC1){
      ImgTemp[i] = C1R;
      ImgTemp[i+1] = C1G;
      ImgTemp[i+2] = C1B;
     NbeC1++;
      SommeC1R +=  ImgIn[i] ;
      SommeC1G +=  ImgIn[i+1] ;
      SommeC1B += ImgIn[i+2] ;
      
    }
   
    else{
      ImgTemp[i] = C2R;
      ImgTemp[i+1] = C2G;
      ImgTemp[i+2] = C2B;
      NbeC2++;
      SommeC2R +=  ImgIn[i] ;
      SommeC2G +=  ImgIn[i+1];
      SommeC2B+=  ImgIn[i+2] ;
      
    }    
  }
}

void convergence(int nTaille, OCTET *ImgIn, OCTET *ImgTemp){

int moyenneC1R = 0;
int moyenneC1G= 0;
int moyenneC1B= 0;

int moyenneC2R= 0;
int moyenneC2G= 0;
int moyenneC2B= 0;
 int moyenneC1R_Last = 0;
 int moyenneC1G_Last= 0;
 int moyenneC1B_Last= 0;

int  moyenneC2R_Last= 0;
int  moyenneC2G_Last= 0;
int  moyenneC2B_Last= 0;

int i=0;

do{
  printf("aa %i et %i\n ",C1R, C2R);
  resetMoyenneC();

parcoursK_mean(nTaille, ImgIn, ImgTemp);

parcoursMoyenneK_mean( nTaille, ImgTemp, ImgTemp);

  moyenneC1R_Last = moyenneC1R;
  moyenneC1G_Last= moyenneC1G;
  moyenneC1B_Last=moyenneC1B;

  moyenneC2R_Last= moyenneC2R;
  moyenneC2G_Last= moyenneC2G;
  moyenneC2B_Last= moyenneC2B;

 moyenneC1R = SommeC1R/NbeC1;
 moyenneC1G= SommeC1G/NbeC1;
 moyenneC1B= SommeC1B/NbeC1;

 moyenneC2R= SommeC2R/NbeC2;
 moyenneC2G= SommeC2G/NbeC2;
 moyenneC2B= SommeC2B/NbeC1;


 C1R = moyenneC1R;
 C1G = moyenneC1G;
 C1B = moyenneC1B;

 C2R = moyenneC2R;
 C2G = moyenneC2G;
 C2B = moyenneC2B;
}
//while(i++<1);
//while(C1R !=C2R &&C1G !=C2G &&C1B !=C2B);
while(moyenneC1R != moyenneC1R_Last && moyenneC1G != moyenneC1G_Last && moyenneC1B != moyenneC1B_Last &&
 moyenneC2R != moyenneC2R_Last && moyenneC2G != moyenneC2G_Last && moyenneC2B != moyenneC2B_Last);

printf("\n\n bb  %i et %i\n ",C1R, C2R);
printf("  %i et %i\n ",C1G, C2G);
printf("  %i et %i\n ",C1B, C2B);
}


int main(int argc, char *argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  if (argc != 3)
  {
    printf("Usage: ImageIn.ppm ImageOut.ppm Seuil \n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
 // sscanf(argv[3], "%d", &S);

  OCTET *ImgIn, *ImgOut, *ImgTemp;
  ;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  int nTaille3 = nTaille * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille3);
  allocation_tableau(ImgTemp, OCTET, nTaille3);
//  int indexPixelC1 = rand() % nTaille;
 // int indexPixelC2 = rand() % nTaille;

parcoursK_mean(nTaille, ImgIn, ImgTemp);

ecrire_image_ppm(cNomImgEcrite, ImgTemp, nH, nW);

 parcoursMoyenneK_mean(nTaille, ImgTemp, ImgOut);
 char nomOut[250]= "3_out_2.ppm";
  ecrire_image_ppm(nomOut, ImgOut, nH, nW);

convergence(nTaille, ImgIn, ImgTemp);
char nomOut2[250]= "3_out_3.ppm";
  ecrire_image_ppm(nomOut2, ImgTemp, nH, nW);


  free(ImgIn);
  return 1;
}
