// test_couleur.cpp : Seuille une image couleur 

#include <stdio.h>
#include "image_ppm.h"


int min(int a, int b){
  return a>b?b:a;
}

int max(int a, int b){
  return a>b?a:b;
}
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

printf(" %f ",result );
} 

/**
comp= 0 pour rouge, 1 pour vert, 2 pour bleu;
**/
void conversion(int nTaille3, OCTET* imgIn,OCTET* imgycrcb){
  for (int i=0; i < (nTaille3); i+=3){
    imgycrcb[i]= (int)max(0,min(255,(0.299*imgIn[i]+ 0.587*imgIn[i+1]+0.114*imgIn[i+2])));
    imgycrcb[i+2]=(int)max(0,min(255,(-0.1687*imgIn[i]- 0.3313*imgIn[i+1]+0.5*imgIn[i+2]+128)));
    imgycrcb[i+1]=(int)max(0,min(255,(0.5*imgIn[i]-0.4187*imgIn[i+1]-0.0813*imgIn[i+2]+128)));
  }
}


//reverseY(int nTaille3, OCTET* imgOut,OCTET* imgycrcb))

void reverseconversion(int nTaille3, OCTET* imgOut,OCTET* imgycrcb){
  for (int i=0; i < (nTaille3); i+=3){
    imgOut[i]=max(0,min(255,(int)(imgycrcb[i]+1.402*((float)(imgycrcb[i+1]-128)))));
    imgOut[i+1]=max(0,min(255,(int)(imgycrcb[i]-0.34414*((float)(imgycrcb[i+2]-128))- 0.71414*((float)(imgycrcb[i+1]-128)))));
    imgOut[i+2]=max(0,min(255,(int)(imgycrcb[i]+1.772*((float)(imgycrcb[i+2]-128)))));

  }
}


void copyTabpgm(int nTaille,OCTET* ImgIn, OCTET* ImgOut){
      for (int i=0; i < (nTaille); i++)
       ImgOut[i]= ImgIn[i];
}


void recomposition( int nH, int nW, OCTET* ImgIn, OCTET* ImgOut, int rec){
	if(rec < 1)
		return;
	else{
	
		int HF_Q=4;
		int MF_Q=2;
		
		float HF_q = max(1,(HF_Q/pow(2,rec-1)));
		float MF_q = max(1,(MF_Q/pow(2,rec-1)));
		
		OCTET *Temp;
		allocation_tableau(Temp, OCTET, nH*nW);
		copyTabpgm(nH*nW, ImgIn,  Temp);

		//image supposé carré
		int tailleCase = nH / pow(2,rec);
	//	printf("reconposition taille = %i ,,,,%i, %i\n", tailleCase,nH, nW);
		for(int i = 0; i<(int)(tailleCase); i+=1){
			for(int j = 0; j<(int)(tailleCase); j+=1){
				int n1 = Temp[i * nW + j];
				int n2 = Temp[i * nW + j+tailleCase];
				int n3 = Temp[(i+tailleCase) * nW + j];		
				int n4 = Temp[(i+tailleCase) * nW + j+tailleCase];
				
				//printf("n  = %i,  %i,,  %i,  %i,, \n",
			//			n1, n2, n3, n4)
			//	;
				
				/*printf("case  = %i,  %i,,  %i,  %i,,  %i,  %i,,  %i,  %i  \n",
					   	i,j,
      					i,j+ tailleCase,
						(tailleCase+i), j,
						(tailleCase+i), j+tailleCase)
				;*/
				
				
				
				
				
				float A = n1*4;
				float B = (n2-128)*MF_q*2;
				float C = (n3-128)*MF_q*2;
				float D = (n4-128)*HF_q*2;
			
			//	printf("     = %f,  %f,,  %f,  %f,,  \n",A, B, C, D);
				
				
				ImgOut[i*2 * nW +j*2] = 			(int)min(255,max(0,		(A + B + C + D)/4		));
				ImgOut[i*2 * nW + (j*2) + 1] = 		(int)min(255,max(0,		(A + B - C - D)/4		));
				ImgOut[( 1 + i*2) * nW + j*2] = 	(int)min(255,max(0,		(A - B + C - D)/4		));
       			ImgOut[(1 + i*2) * nW + (j*2)+ 1] = (int)min(255,max(0,		(A - B - C + D)/4		));
				
		/*						printf("     = %i,  %i,,  %i,  %i,,  \n",
					(int)min(255,max(0,		(A + B + C + D)/4		)),
				(int)min(255,max(0,		(A + B - C - D)/4		)),
					(int)min(255,max(0,		(A - B + C - D)/4		)),
       	 		(int)min(255,max(0,		(A - B - C + D)/4		)))
				;*/
				
				/*printf("     = %f,  %f,,  %f,  %f,,  \n",
					(A + B + C + D)/4,
				(A + B - C - D)/4		,
				(A - B + C - D)/4		,
       	 			(A - B - C + D)/4		)
													;
				*/
				
		/*		printf("case  = %i,  %i,,  %i,  %i,,  %i,  %i,,  %i,  %i  \n",
					   	i*2,j*2,
      					i*2,j*2 + 1,
						(1+i*2), j*2,
						(1+i*2), j*2+1)
				;*/

		  }
	}

	copyTabpgm(nH*nW, ImgOut,  Temp);
	recomposition(  nH, nW,Temp, ImgOut, --rec);


  }
}





void decomposition( int nH,int nW,OCTET* ImgIn, OCTET* ImgOut, int rec, int maxrec){
if(rec > maxrec)
    return;
  else{

    int HF_Q=4;
    int MF_Q=2;
	  
	  
		float HF_q = max(1,(HF_Q/pow(2,rec-1)));
		float MF_q = max(1,(MF_Q/pow(2,rec-1)));
	

      OCTET *Temp;
      allocation_tableau(Temp, OCTET, nH*nW);
      copyTabpgm(nH*nW, ImgIn,  Temp);


    //image supposé carré
    int tailleCase = nH / pow(2,rec);
   // printf("taille = %i ,,,,%i, %i\n", tailleCase,nH, nW);


    for(int i = 0; i<(int)(nH/pow(2,rec-1))-1; i+=2){
      for(int j = 0; j<(int)(nW/pow(2,rec-1))-1; j+=2){
        int p1 = Temp[i * nW + j];
        int p2 = Temp[i * nW + j+1];
        int p3 = Temp[(i+1) * nW + j];
        int p4 = Temp[(i+1) * nW + j+1];

        int BF = (p1 + p2 + p3 + p4) / 4;
        int MF_vert = ((p1 + p2 - p3 - p4) / 2)/max(1,MF_q)+128;
        int MF_hor = ((p1 - p2 + p3 - p4) / 2)/max(1,MF_q)+128;
        int HF = (p1 - p2 - p3 + p4)/ max(1,HF_q)+128;
        
        ImgOut[(int)i/2 * nW +(int)j/2] = (int)min(255,max(0,BF));
        ImgOut[(int)i/2 * nW + ((int)j/2 + tailleCase)] = (int)min(255,max(0,MF_vert));
        ImgOut[(tailleCase + (int)i/2) * nW +(int)j/2] = (int)min(255,max(0,MF_hor));
       ImgOut[(tailleCase + (int)i/2) * nW + ((int)j/2 + tailleCase)] = (int)min(255,max(0,HF));

    /*  printf("case  = %i,  %i,,  %i,  %i,,  %i,  %i,,  %i,  %i  \n",(int)i/2,(int)j/2,
      (int)i/2, ((int)j/2 + tailleCase),
      (tailleCase + (int)i/2), (int)j/2,
      (tailleCase + (int)i/2),
       ((int)j/2 + tailleCase));*/
     //   x++;
        
        }
     //   y+1;
     //   x=0;
      }

  copyTabpgm(nH*nW, ImgOut,  Temp);

  decomposition(  nH, nW,Temp, ImgOut, ++rec,  maxrec);


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


   OCTET *ImgIn, *ImgOut,*imgycrcb, *ImgTempY, *ImgTempcr, *ImgTempcb, *reconstituer, *finale;
   
   lire_nb_lignes_colonnes_image_ppm(cNomImgLue, &nH, &nW);
   nTaille = nH * nW;
   int nHdiv2 = nH/2;
   int nWdiv2 = nW/2;
   int nTaille3 = nTaille * 3;
   allocation_tableau(ImgIn, OCTET, nTaille3);
   lire_image_ppm(cNomImgLue, ImgIn, nH * nW);
   allocation_tableau(ImgOut, OCTET, nTaille3);
	 allocation_tableau(ImgTempcb, OCTET, nTaille);
   allocation_tableau(ImgTempcr, OCTET, nTaille);
   allocation_tableau(ImgTempY, OCTET, nTaille);
	//	 allocation_tableau(ImgTempcb, OCTET, ceil(nTaille/4.0f));
   //allocation_tableau(ImgTempcr, OCTET, ceil(nTaille/4.0f));
	 
	
	allocation_tableau(finale, OCTET, nTaille*3);
	allocation_tableau(reconstituer, OCTET, nTaille*3);
	allocation_tableau(imgycrcb, OCTET, nTaille*3);
  
	
	int profondeur = 5;
	
 // for( profondeur=1; profondeur<6;profondeur++ ){
  
	bool convers = true;
	
	if(convers){
		//convertie en YCrCb
	  	conversion( nTaille3,  ImgIn, imgycrcb);

	  //Recupère les composante Y, Cr, Cb
	  getComposante( nTaille, imgycrcb, ImgTempY, 0);
	  getComposante( nTaille, imgycrcb, ImgTempcr, 1);
	  getComposante( nTaille, imgycrcb, ImgTempcb, 2);
	}
	else{
	  getComposante( nTaille, ImgIn, ImgTempY, 0);
	  getComposante( nTaille, ImgIn, ImgTempcr, 1);
	  getComposante( nTaille, ImgIn, ImgTempcb, 2);
	}
	
  //char nomOut1_g[250]= "2_out_1_Y.pgm";
  //ecrire_image_pgm(nomOut1_g, ImgTempY, nH, nW);
	
	//split l'image par composante
	
	
	
  decomposition(nH, nW, ImgTempY,  ImgTempY,  1,  profondeur);
  decomposition(nH, nW, ImgTempcr,  ImgTempcr,  1,  profondeur);
  decomposition(nH, nW, ImgTempcb,  ImgTempcb,  1,  profondeur);

	
	
	
	//stock les composante dans imgycrcb
  reverseComposante( nTaille, imgycrcb,  ImgTempY, 0);
  reverseComposante( nTaille, imgycrcb,  ImgTempcr, 1);
  reverseComposante( nTaille, imgycrcb,  ImgTempcb, 2);

	
	
	

 // }


  char nomOutycrcb[250]= "2_out_2ycrcb.ppm";
  ecrire_image_ppm(nomOutycrcb, imgycrcb,  nH, nW);

	if(convers){
	//ycrcb -> RGB
		reverseconversion( nTaille3, ImgOut, imgycrcb);
	}
	else{
		copyComp(nTaille3, ImgOut,  imgycrcb, 0);
		copyComp(nTaille3, ImgOut,  imgycrcb, 1);
		copyComp(nTaille3, ImgOut,  imgycrcb, 2);
	}
	
/*
  getComposante( nTaille, ImgOut, ImgTempY, 0);
  getComposante( nTaille, ImgOut, ImgTempcr, 1);
  getComposante( nTaille, ImgOut, ImgTempcb, 2);
      
  char nomOut1_r[250]= "2_out_1_cr.pgm";
 ecrire_image_pgm(nomOut1_r, ImgTempcr, nH, nW);
   char nomOut1_b[250]= "2_out_1_cb.pgm";
 ecrire_image_pgm(nomOut1_b, ImgTempcb, nH, nW);
  char nomOut1_g[250]= "2_out_1_Y.pgm";
 ecrire_image_pgm(nomOut1_g, ImgTempY, nH, nW);
*/

 //char nomOut11[250]= "2_out_1.pgm";
  //ecrire_image_pgm(nomOut11, ImgOut,  nH, nW);
  //free(ImgIn);
  char nomOut1[250]= "5__2_out_2.ppm";
  ecrire_image_ppm(nomOut1, ImgOut,  nH, nW);
 // free(ImgIn);
  free(ImgTempcb);free(ImgTempcr);free(ImgTempY);
   allocation_tableau(ImgTempcb, OCTET, nTaille);
   allocation_tableau(ImgTempcr, OCTET, nTaille);
   allocation_tableau(ImgTempY, OCTET, nTaille);
	if(convers){
		//convertie en YCrCb
	  	conversion( nTaille3,  ImgIn, imgycrcb);

	  //Recupère les composante Y, Cr, Cb
	  getComposante( nTaille, imgycrcb, ImgTempY, 0);
	  getComposante( nTaille, imgycrcb, ImgTempcr, 1);
	  getComposante( nTaille, imgycrcb, ImgTempcb, 2);
	}
	else{
	  getComposante( nTaille, ImgIn, ImgTempY, 0);
	  getComposante( nTaille, ImgIn, ImgTempcr, 1);
	  getComposante( nTaille, ImgIn, ImgTempcb, 2);
	}
	
  decomposition(nH, nW, ImgTempY,  ImgTempY,  1,  profondeur);
  decomposition(nH, nW, ImgTempcr,  ImgTempcr,  1,  profondeur);
  decomposition(nH, nW, ImgTempcb,  ImgTempcb,  1,  profondeur);
	OCTET * test;
	allocation_tableau(test, OCTET, nTaille);
	
  recomposition(nH, nW, ImgTempY,  test,    profondeur);
  recomposition(nH, nW, ImgTempY,  ImgTempY,    profondeur);
  recomposition(nH, nW, ImgTempcr,  ImgTempcr,  profondeur);
  recomposition(nH, nW, ImgTempcb,  ImgTempcb,  profondeur);
	
//char nomOutfinal2[250]= "test.pgm";
 // ecrire_image_pgm(nomOutfinal2, test,  nH, nW);
	
  reverseComposante( nTaille, reconstituer,  ImgTempcr, 1);
  reverseComposante( nTaille, reconstituer,  ImgTempcb, 2);
    reverseComposante( nTaille, reconstituer,  ImgTempY, 0);


  if(convers){
	reverseconversion( nTaille3, finale, reconstituer);
	}
  else{
		copyComp(nTaille3, finale,  reconstituer, 0);
		copyComp(nTaille3, finale,  reconstituer, 1);
		copyComp(nTaille3, finale,  reconstituer, 2);
	}
  char nomOutfinal[250]= "reconstituer.ppm";
  ecrire_image_ppm(nomOutfinal, finale,  nH, nW);
  char nomOut11[250]= "testreconversion.pgm";
  ecrire_image_pgm(nomOut11, ImgTempY, nH, nW);

		printf("%i", profondeur);
		PSNR( nTaille,ImgIn, finale);
	  printf("\n");
//  }

  return 1;
}









