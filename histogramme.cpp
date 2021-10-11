#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]){
    char cNomImgLue[250];
    int nH, nW, nTaille, currentGris;
    int nivGris[256];

    if(argc != 2){
        printf("Usage : ImageIn.pgm \n");
        exit(1);
    }

    sscanf (argv[1],"%s",cNomImgLue);

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);

    for(int i=0; i < 256; i++){
        nivGris[i] = 0;
    }

    for (int i=0; i < nH; i++){
        for (int ii=0; ii < nW; ii++){
            currentGris = ImgIn[i*nW + ii];
            nivGris[currentGris]++;
        }
    }

    printf("# Niveau Nombre\n");
    for(int i=0; i < 256; i++){
        printf("%d %d\n", i, nivGris[i]);
    }

    return 1;
}