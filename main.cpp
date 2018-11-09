#include <stdio.h>
#include <stdlib.h>

#include "constantes.h"
#include "hanoi.h"
#include "hanoi.c"

int main(int argc,char* argv[]){
 //int n;
 SDL_Surface *ecran=NULL;
 PILE P1,P2,P3;

 //n=saisie();
 creerFenetre(&ecran);
 creer_3_poteaux(ecran,&P1,&P2,&P3);
 creerDisques(ecran,4,&P1);
 hanoi(ecran,4,&P1,&P2,&P3);

 SDL_Flip(ecran);
 pause();
 SDL_Quit();
return EXIT_SUCCESS;
}
