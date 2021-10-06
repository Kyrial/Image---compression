// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"


int min(int a, int b){
  return a>b?b:a;
}

int max(int a, int b){
  return a>b?a:b;
}

/**
comp= 0 pour rouge, 1 pour vert, 2 pour bleu;
**/
void conversion(int nTaille3, OCTET* imgIn,OCTET* imgycrcb){
  for (int i=0; i < (nTaille3); i+=3){
    imgycrcb[i]= (int)max(0,min(255,(0.299*imgIn[i]+ 0.587*imgIn[i+1]+0.114*imgIn[i+2])));
    imgycrcb[i+2]=(int)max(0,min(255,(-0.1687*imgIn[i]- 0.3313*imgIn[i+1]+0.5*imgIn[i+2]+128)));
    imgycrcb[i+1]=(int)max(0,min(255,(0.5*imgIn[i]-0.4187*imgIn[i+1]-0.0813*imgIn[i+2]+128)));
 /*   imgycrcb[i]= (int)(0.299*imgIn[i]+ 0.587*imgIn[i+1]+0.114*imgIn[i+2]);
    imgycrcb[i+1]=(int)(-0.1687*imgIn[i]- 0.3313*imgIn[i+1]+0.5*imgIn[i+2]);
    imgycrcb[i+2]=(int)(0.5*imgIn[i]-0.4187*imgIn[i+1]-0.0813*imgIn[i+2]);*/
 // if( imgycrcb[i]>255 ||  imgycrcb[i+1]>255 ||  imgycrcb[i+2]>255)
 // if( imgycrcb[i]<0 ||  imgycrcb[i+1]<0 ||  imgycrcb[i+2]<0 || imgycrcb[i]>255 ||  imgycrcb[i+1]>255 ||  imgycrcb[i+2]>255)
//    printf("a   %i,    %i ,    %i \n",imgycrcb[i],imgycrcb[i+1],imgycrcb[i+2] );
  }
}


//reverseY(int nTaille3, OCTET* imgOut,OCTET* imgycrcb))

void reverseconversion(int nTaille3, OCTET* imgOut,OCTET* imgycrcb){
  for (int i=0; i < (nTaille3); i+=3){
 /*     imgOut[i]=(int)(imgycrcb[i]+((float)(imgycrcb[i+1])));
    imgOut[i+1]=(int)(imgycrcb[i]-0.34414*((float)(imgycrcb[i+2]-128))- 0.71414*((float)(imgycrcb[i+1]-128)));
    imgOut[i+2]=(int)(imgycrcb[i]+((float)(imgycrcb[i+2])));*/
    imgOut[i]=max(0,min(255,(int)(imgycrcb[i]+1.402*((float)(imgycrcb[i+1]-128)))));
    imgOut[i+1]=max(0,min(255,(int)(imgycrcb[i]-0.34414*((float)(imgycrcb[i+2]-128))- 0.71414*((float)(imgycrcb[i+1]-128)))));
    imgOut[i+2]=max(0,min(255,(int)(imgycrcb[i]+1.772*((float)(imgycrcb[i+2]-128)))));
 //  if( (int)(imgycrcb[i]+1.402*((float)(imgycrcb[i+1]-128)))>255 ||  (int)(imgycrcb[i]-0.34414*((float)(imgycrcb[i+2]-128))- 0.71414*((float)(imgycrcb[i+1]-128)))>255 ||  (int)(imgycrcb[i]+1.772*((float)(imgycrcb[i+2]-128)))>255 || imgOut[i]<0 ||  imgOut[i+1]<0 ||  imgOut[i+2]<0 )
 //   printf("b   %i,    %i ,    %i \n",imgOut[i],imgOut[i+1],imgOut[i+2] );
  }
}



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

   OCTET *ImgIn, *ImgOut,*imgycrcb, *ImgTempY, *ImgTempcr, *ImgTempcb;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   int nHdiv2 = nH/2;
   int nWdiv2 = nW/2;
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	 allocation_tableau(ImgTempcb, OCTET, ceil(nTaille/4.0f));
   allocation_tableau(ImgTempcr, OCTET, ceil(nTaille/4.0f));
	 allocation_tableau(ImgTempY, OCTET, nTaille);
	 allocation_tableau(imgycrcb, OCTET, nTaille3);

  conversion( nTaille3,  ImgIn, imgycrcb);
  getComposante( nTaille, imgycrcb, ImgTempY, 0);
  getComposanteDiv2( nH, nW, imgycrcb, ImgTempcr, 1);
  getComposanteDiv2( nH, nW, imgycrcb, ImgTempcb, 2);

  char nomOut1_r[250]= "2_out_1_cr.pgm";
 ecrire_image_pgm(nomOut1_r, ImgTempcr, nH/2, nW/2);
   char nomOut1_b[250]= "2_out_1_cb.pgm";
 ecrire_image_pgm(nomOut1_b, ImgTempcb, nH/2, nW/2);
  char nomOut1_g[250]= "2_out_1_Y.pgm";
 ecrire_image_pgm(nomOut1_g, ImgTempY, nH, nW);

  reverseComposanteDiv2( nH, nW, imgycrcb,  ImgTempcr, 1);
  reverseComposanteDiv2( nH, nW, imgycrcb,  ImgTempcb, 2);
  reverseComposante( nTaille, imgycrcb,  ImgTempY, 0);
 // copyComp2( nH, nW, ImgOut, ImgIn,1);

  reverseconversion( nTaille3, ImgOut, imgycrcb);
  char nomOut1[250]= "2_out_1.ppm";
  ecrire_image_ppm(nomOut1, ImgOut,  nH, nW);
  free(ImgIn);
  return 1;
}
