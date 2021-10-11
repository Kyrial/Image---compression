#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[]){
    char cNomImgLue[250];
    int nH, nW, nTaille, currentPix;
    int troisChan[256][3];

    if(argc != 2){
        printf("Usage : ImageIn.ppm \n");
        exit(1);
    }

    sscanf (argv[1],"%s",cNomImgLue);

    OCTET *ImgIn;

    lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille*3);
    lire_image_ppm(cNomImgLue, ImgIn, nH * nW);

    for(int i=0; i < 256; i++){
        for(int ii=0; ii < 3; ii++){
            troisChan[i][ii] = 0;
        }
    }

    for (int i = 0; i < 3*nTaille; i+=3){
        currentPix = ImgIn[i];
        troisChan[currentPix][0]++;
        currentPix = ImgIn[i+1];
        troisChan[currentPix][1]++;
        currentPix = ImgIn[i+2];
        troisChan[currentPix][2]++;
    }

    printf("# Niveau R G B\n");
    for(int i=0; i < 256; i++){
        printf("%d %d %d %d\n", i, troisChan[i][0], troisChan[i][1], troisChan[i][2]);
    }

    return 1;
}