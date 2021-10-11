// test_couleur.cpp : Seuille une image couleur

#include <stdio.h>
#include "image_ppm.h"
#include <iostream>
#include <math.h>

double EQM(int nTaille,OCTET *Original, OCTET *Alterer){
 double result = 0;
 for(int i=0; i<(nTaille*3); i++){
  result += pow(Original[i]-Alterer[i], 2)  ;
} 
result = result*(1/(double)nTaille);
return result;
} 
void PSNR(int nTaille,OCTET *Original, OCTET *Alterer){
double result = 10*log10((double)pow(255,2)/EQM( nTaille,Original, Alterer));

printf("PSNR =%f\n ",result );
} 






float k_mean(int* palette,int indexPalette, int pixel, OCTET *ImgIn)
{

  float dist = sqrt(pow(ImgIn[pixel] - palette[indexPalette], 2) +
                    pow(ImgIn[pixel+1] - palette[indexPalette+1], 2) +
                    pow(ImgIn[pixel+2] - palette[indexPalette+2], 2));
  return dist;
}


void remplirPalette(int* palette, int taillePalette){
 //srand (time(NULL));
 srand (10);
for(int i=0; i<(taillePalette*3);i+=3){
 
 palette[i] = rand()%256;
 palette[i+1] = rand()%256;
palette[i+2] = rand()%256;

//printf("%i, %i, %i \n", palette[i], palette[i+1], palette[i+2]);



}
/* palette[0] = 1;
 palette[1] = 1;
palette[2] = 1;
 palette[4] =150;
 palette[5] = 150;
palette[3] =150;*/
} 

void convertIndexToRGB(int nTaille, OCTET *ImgIndex, OCTET *ImgOut, int* palette){
for (int i = 0; i < (nTaille); i++){ 
  ImgOut[i*3]= palette[ImgIndex[i]*3];
   ImgOut[i*3+1]= palette[ImgIndex[i]*3+1];
    ImgOut[i*3+2]= palette[ImgIndex[i]*3+2]; 
} 
} 
void initTab(int* tab, int taille){
  for(int j = 0; j < taille; j ++){  
    tab[j] = 0;
 //   printf("%i, \n", tab[j]);
  } }



void parcoursMoyenneK_mean(int* paletteMoy, int* sommeC, int* nbC, int taillePalette){
  for(int j = 0; j < taillePalette; j ++){  
    // printf("%i\n",(int)nbC[j]);
  //   printf("%i, %i, \n", nbC[j], sommeC[j*3]);
    paletteMoy[j*3] = (int) ((int)sommeC[j*3]/std::max((int)nbC[j],1));
    paletteMoy[j*3+1] =(int)( (int)sommeC[j*3+1]/std::max((int)nbC[j],1));
    paletteMoy[j*3+2] =(int)((int)sommeC[j*3+2]/std::max((int)nbC[j],1));

  //  printf("%i, %i, %i \n", paletteMoy[j], paletteMoy[j+1], paletteMoy[j+2]);
}
}



void parcoursK_mean(int nTaille, OCTET *ImgIn, OCTET *ImgIndex, int* palette, int*  sommeC , int* nbC , int taillePalette)
{

 for (int i = 0; i < (nTaille); i++)
 {
   int indexMin = 0;
   int distMin = k_mean(palette,0,i*3,ImgIn);
   for(int j = 1; j < taillePalette; j++){
      int dist = k_mean(palette,j*3,i*3,ImgIn);
      if(dist < distMin){ 
      //  printf("%i avant %i\n", distC[j], distC[indexMin]);
        distMin = dist;
        indexMin = j;
      } 
    } 
    //printf("%i\n",indexMin);

      ImgIndex[i] = indexMin;
     nbC[indexMin]++;
  //   printf("\n  %i, %i,  \n", ImgIn[i*3], sommeC[indexMin*3]);
      sommeC[indexMin*3] =sommeC[indexMin*3] + ImgIn[i*3] ;
   //   printf("%i, %i, %i \n", ImgIn[i*3], sommeC[indexMin*3], nbC[indexMin]);

      sommeC[indexMin*3+1] += ImgIn[i*3+1] ;
      sommeC[indexMin*3+2] += ImgIn[i*3+2] ;
     // printf("%i, %i, %i \n", ImgIn[i*3], sommeC[indexMin*3], nbC[indexMin]);
  }
}


bool ifSamePalette(int* palette, int* palettemoy){
  for(int i =0; i<256*3; i++){
    if(pow(palette[i]- palettemoy[i],2)>4){
      printf("diff à %i \n", i);
    return false;
    }
  } 
  return true;
} 

void convergence(int nTaille, OCTET *ImgIn, OCTET *ImgIndex, int* palette, int *paletteMoy, int* sommeC, int* nbC, int taillePalette){
int i=0;
do{
  parcoursMoyenneK_mean(palette, sommeC, nbC, taillePalette);
  initTab(sommeC, 256*3);
  initTab(nbC, 256*3);

  parcoursK_mean(nTaille, ImgIn, ImgIndex, palette, sommeC, nbC, taillePalette);
  parcoursMoyenneK_mean(paletteMoy, sommeC, nbC, taillePalette);

  printf("%i \n", i++);
 // printf("%i %i,   ,%i %i,   ,%i %i \n" ,palette[0],paletteMoy[0], palette[1],paletteMoy[1], palette[2],paletteMoy[2]);
} while( !ifSamePalette(palette, paletteMoy));


}


int main(int argc, char *argv[])
{
  char cNomImgLue[250], cNomImgEcrite[250];
  int nH, nW, nTaille, nR, nG, nB, S;
  if (argc !=3)
  {
    printf("Usage: ImageIn.ppm img.ppm  \n");
    exit(1);
  }

  sscanf(argv[1], "%s", cNomImgLue);
  sscanf(argv[2], "%s", cNomImgEcrite);
 // sscanf(argv[3], "%d", &S);

  OCTET *ImgIn, *ImgOut, *ImgTemp, /*palette*/ *ImgIndex /*sommeC, *nbC paletteMoy*/ ;

  lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
  nTaille = nH * nW;

  int nTaille3 = nTaille * 3;
  allocation_tableau(ImgIn, OCTET, nTaille3);
  lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
  allocation_tableau(ImgOut, OCTET, nTaille3);
  allocation_tableau(ImgTemp, OCTET, nTaille3);
lire_image_ppm(cNomImgEcrite, ImgTemp, nH * nW);

int  taillePalette = 256;

 // allocation_tableau(palette, OCTET, taillePalette*3);
//allocation_tableau(paletteMoy, OCTET, taillePalette*3);

  allocation_tableau(ImgIndex, OCTET, nTaille);
 // allocation_tableau(sommeC, OCTET, taillePalette*3);  
 // allocation_tableau(nbC, OCTET, taillePalette);

int sommeC[256*3];   
initTab(sommeC, 256*3);
int paletteMoy[256*3];   
initTab(paletteMoy, 256*3);
int palette[256*3];   

initTab(palette, 256*3);
int nbC[256];  
initTab(nbC, 256);


//initTab(sommeC, taillePalette*3);
//initTab(nbC, taillePalette);

//  int indexPixelC1 = rand() % nTaille;
 // int indexPixelC2 = rand() % nTaille;

PSNR(nTaille3,ImgIn, ImgTemp);

  free(ImgIn);
  return 1;
}
