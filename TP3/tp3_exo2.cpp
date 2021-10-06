#include <stdio.h>
#include "image_ppm.h"

int min(int a, int b){
  return a>b?b:a;
}

int max(int a, int b){
  return a>b?a:b;
}


void getDifference(int nH, int nW, OCTET *ImgIn, OCTET *ImgOut){
    ImgOut[0] = ImgIn[0];
    for (int i=0; i < nH; i++){
        for (int j=0; j < nW; j++){
            if(i==0 && j==0)
                continue;
            if(j==0)
                ImgOut[i * nW + j] = min(255,max(0,(ImgIn[(i-1) * nW + j]  - ImgIn[i * nW + j])+128));
            else
                ImgOut[i * nW + j] = min(255,max(0,(ImgIn[i * nW + j-1]  - ImgIn[i * nW + j])+128));
        }
}
}

void retrouveImage(int nH, int nW, OCTET *ImgIn, OCTET *ImgOut){
    ImgOut[0] = ImgIn[0];
    for (int i=0; i < nH; i++){
        for (int j=0; j < nW; j++){
            if(i==0 && j==0)
                continue;
            if(j==0)
                ImgOut[i * nW + j] = min(255,max(0,(128- ImgIn[i * nW + j]) + ImgOut[(i-1) * nW + j]));
            else
                ImgOut[i * nW + j] = min(255,max(0,(128- ImgIn[i * nW + j]) + ImgOut[i * nW + j-1]));
        }
}
}





int main(int argc, char* argv[]){
    char cNomImgLue[250];
    int nH, nW, nTaille, currentGris;
    int nivGris[256];

    if(argc != 2){
        printf("Usage : ImageIn.pgm \n");
        exit(1);
    }

    sscanf (argv[1],"%s",cNomImgLue);

    OCTET *ImgIn, *ImgOut, *ImgOut2;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);
    allocation_tableau(ImgOut2, OCTET, nTaille);


    getDifference( nH, nW,  ImgIn,  ImgOut);


    char nomOut1[250]= "2_out_1.pgm";
    ecrire_image_pgm(nomOut1, ImgOut, nH, nW);

    char nomOut2[250]= "2_out_2.pgm";
    retrouveImage(nH, nW, ImgOut, ImgOut2);
    ecrire_image_pgm(nomOut2, ImgOut2, nH, nW);

    return 1;
}