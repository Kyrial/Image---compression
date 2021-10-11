// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include <math.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
  char cNomImg1[250], cNomImg2[250];
  int couleur1[] = {242, 0, 25};
  int couleur2[] = {1, 137, 159};
  int nH, nW, nTaille;
  
  if (argc != 3) 
    {
      printf("Usage: ImageIn1.pgm ImageIn2.pgm\n"); 
      exit (1) ;
    }
   
  sscanf (argv[1],"%s",cNomImg1) ;
  sscanf (argv[2],"%s",cNomImg2);

  OCTET *Img1, *Img2;
   
  lire_nb_lignes_colonnes_image_pgm(cNomImg1, &nH, &nW);
  nTaille = nH * nW;

  allocation_tableau(Img1, OCTET, nTaille);
  lire_image_pgm(cNomImg1, Img1, nH * nW);
  allocation_tableau(Img2, OCTET, nTaille);
  lire_image_pgm(cNomImg2, Img2, nH * nW);
	
  float grandtotal = 0;
  int v1, v2;
  for (int i=0; i < nTaille; i++)
  {
    v1 = Img1[i];
    v2 = Img2[i];
    grandtotal += ((v1-v2)*(v1-v2));
  }
  grandtotal /= (float)(nTaille);

  //printf("%f\n", grandtotal);
  float result = 10 * log10((256*256)/((float)(grandtotal)));
  printf("%f\n", result);

  free(Img1);
  free(Img2);
  return 1;
}