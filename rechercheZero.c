// test_couleur.cpp : Seuille une image en niveau de gris
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include "image_ppm.h"

int main(int argc, char* argv[])
{
    char cNomImgLue[250], cNomImgEcrite[250];
    int nH, nW, nTaille, S;

    if (argc < 3)
    {
        printf("Usage: ImageIn.pgm ImageOut.pgm  \n");
        exit(1);
    }

    sscanf(argv[1], "%s", cNomImgLue);
    sscanf(argv[2], "%s", cNomImgEcrite);
    

    OCTET* ImgIn, * ImgOut;

    lire_nb_lignes_colonnes_image_pgm(cNomImgLue, &nH, &nW);
    nTaille = nH * nW;

    allocation_tableau(ImgIn, OCTET, nTaille);
    lire_image_pgm(cNomImgLue, ImgIn, nH * nW);
    allocation_tableau(ImgOut, OCTET, nTaille);



        //   for (int i=0; i < nTaille; i++)
        // {
        //  if ( ImgIn[i] < S) ImgOut[i]=0; else ImgOut[i]=255;
        //  }

        //Question 1

        for (int i = 0; i < nH-1; i++)
            for (int j = 0; j < nW-1; j++)
            {
               // if (ImgIn[i * nW + j] < S) ImgOut[i * nW + j] = 0; else ImgOut[i * nW + j] = 255;
                float Ai = ImgIn[(i + 1) * nW + j] - ImgIn[i * nW + j];
                float Aj = ImgIn[i * nW + j+1] - ImgIn[i * nW + j];
                if (Aj != 0) {
                    float phase = atan(abs(Ai) / abs(Aj));
                    ImgOut[i * nW + j] = int(sqrt(pow(Ai, 2) + pow(Aj, 2)) * phase);
                }
                else
                    ImgOut[i * nW + j] = int(sqrt(pow(Ai, 2) + pow(Aj, 2)));
                }
    

    ecrire_image_pgm(cNomImgEcrite, ImgOut, nH, nW);
    free(ImgIn);
    return 1;
}
