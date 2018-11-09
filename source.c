#include "prototype.h"


void unPixel(int x, int y,Uint32 couleur){

  if(x>=0 && x<1600 && y>=0 && y<900) //remplacer le nombres par des constantes.
                                     *((Uint32*)(ecran->pixels) + x + y * ecran->w) = couleur;
}

void echangerEntiers(int* x, int* y)
{
  int t = *x;
  *x = *y;
  *y = t;
}

void ligne(int x1, int y1, int x2, int y2, Uint32 coul){
  int d, dx, dy, aincr, bincr, xincr, yincr, x, y;

  if (abs(x2 - x1) < abs(y2 - y1)) {
    /* parcours par l'axe vertical */

    if (y1 > y2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    xincr = x2 > x1 ? 1 : -1;
    dy = y2 - y1;
    dx = abs(x2 - x1);
    d = 2 * dx - dy;
    aincr = 2 * (dx - dy);
    bincr = 2 * dx;
    x = x1;
    y = y1;

    unPixel(x, y, coul);

    for (y = y1+1; y <= y2; ++y) {
      if (d >= 0) {
	x += xincr;
	d += aincr;
      } else
	d += bincr;

      unPixel(x, y, coul);
    }

  } else {
    /* parcours par l'axe horizontal */

    if (x1 > x2) {
      echangerEntiers(&x1, &x2);
      echangerEntiers(&y1, &y2);
    }

    yincr = y2 > y1 ? 1 : -1;
    dx = x2 - x1;
    dy = abs(y2 - y1);
    d = 2 * dy - dx;
    aincr = 2 * (dy - dx);
    bincr = 2 * dy;
    x = x1;
    y = y1;

    unPixel(x, y, coul);

    for (x = x1+1; x <= x2; ++x) {
      if (d >= 0) {
	y += yincr;
	d += aincr;
      } else
	d += bincr;

      unPixel(x, y, coul);
    }
  }
}

void tracerCercle(int cx, int cy, int rayon,Uint32 couleur){

  int d, y, x;

  d = 3 - (2 * rayon);
  x = 0;
  y = rayon;

  while (y >= x) {
                  unPixel(cx + x, cy + y, couleur);
                  unPixel(cx + y, cy + x, couleur);
                  unPixel(cx - x, cy + y, couleur);
                  unPixel(cx - y, cy + x, couleur);
                  unPixel(cx + x, cy - y, couleur);
                  unPixel(cx + y, cy - x, couleur);
                  unPixel(cx - x, cy - y, couleur);
                  unPixel(cx - y, cy - x, couleur);
                  if (d < 0)
                            d = d + (4 * x) + 6;
                  else {
                        d = d + 4 * (x - y) + 10;
                        y--;
                       }
                  x++;
                 }
  SDL_Flip(ecran);
}


SDL_Surface* surfaceEcrite(int racine){

   SDL_Surface *surface=NULL;  // surface à écrire.
   TTF_Font *police=NULL;      // police de l'écriture.
   SDL_Color couleurNoire={0,0,0},couleurBlanche={255,255,255};
   char chaine[4];

   police=TTF_OpenFont("arial.ttf",35); // taille de l'écriture.
   sprintf(chaine,"%d",racine);         // pour ecrire dans une chaine de caractère.
   surface=TTF_RenderText_Shaded(police,chaine,couleurNoire,couleurBlanche); // pour écrire dans la surface avec les caractéristiques ci-dessus.
   TTF_CloseFont(police);

   return surface;
}


ARBRE newMaillon(int racine,int x,int y,int hauteur){

  ARBRE p=(ARBRE)(malloc(sizeof(NOEUD)));

  if(!p){
         printf("Erreur d'allocation de mémoire!");
         exit(EXIT_FAILURE);
        }
  else{
       p->racine=racine;
       p->x=x;
       p->y=y;
       p->hauteur=hauteur;
       p->sag=NULL;
       p->sad=NULL;
       return p;
      }
}


void afficherNoeud(NOEUD N){

   tracerCercle(N.x,N.y,30,SDL_MapRGB(ecran->format,0,0,0));

   SDL_Surface *surface=NULL;
   surface=surfaceEcrite(N.racine);

   SDL_Rect position;
   if(N.racine/10){
                   position.x=N.x-20;
                   position.y=N.y-20;
                  }
   else{
        position.x=N.x-10;
        position.y=N.y-20;
       }
   SDL_BlitSurface(surface,NULL,ecran,&position);
   SDL_Flip(ecran);

   SDL_FreeSurface(surface);
}

void afficherArbre(ARBRE A){

 if(A){
        afficherNoeud(*A);

        if(A->sag){

                   ligne(A->x-25,A->y+15,A->sag->x+25,A->sag->y-15,SDL_MapRGB(ecran->format,0,0,0));

                   afficherArbre(A->sag);

                  }

        if(A->sad){

                   ligne(A->x+25,A->y+15,A->sad->x-25,A->sad->y-15,SDL_MapRGB(ecran->format,0,0,0));

                   afficherArbre(A->sad);

                  }

       }

}


ARBRE detruireArbre(ARBRE A){
 if(!A)
       return NULL;
 else{
      A->sag=detruireArbre(A->sag);
      A->sad=detruireArbre(A->sad);
      free(A);
      A=NULL;
      return A;
     }
}



void majHauteur(NOEUD* A){
        int hd,hg;
     if(A==NULL)
        exit(-1);
     else
        if(A->sad==NULL)
           hd=0;
        else
            hd=A->sad->hauteur;
        if(A->sag==NULL)
            hg=0;
        else
            hg=A->sag->hauteur;
     A->hauteur=hg>hd?hg:hd + 1;
}

int desequilibre(ARBRE A){
        int hd,hg;
     if(A==NULL)
              return 0;
     else
        if(A->sad==NULL)
           hd=0;
        else
            hd=A->sad->hauteur;
        if(A->sag==NULL)
            hg=0;
        else
            hg=A->sag->hauteur;
    return (hg-hd);

}


void majPositionsDescendreGauche(ARBRE A,ARBRE pere,char direction){

 if(A){
       majPositionsDescendreGauche(A->sag,A,'g');
       majPositionsDescendreGauche(A->sad,A,'d');
       if(direction=='g'){
                          A->x -= (pere->x - A->x)/2;
                          A->y +=160;
                         }
       if(direction=='d'){
                          A->x -= (A->x - pere->x)/2;
                          A->y +=160;
                         }
      }
}

void majPositionsMonterGauche(ARBRE A,ARBRE pere,char direction){

 if(A){
       majPositionsMonterGauche(A->sag,A,'g');
       majPositionsMonterGauche(A->sad,A,'d');
       if(direction=='g'){
                          A->x -= pere->x - A->x;
                          A->y -= 160;
                         }
       if(direction=='d'){
                          A->x -=(A->x - pere->x);
                          A->y -=160;
                         }
      }
}

void  majpositionsGauche(ARBRE A,ARBRE pere,char direction){

  if(A){
        if(direction=='g')
                           A->x = pere->x-360/(2*(A->hauteur));
        if(direction=='d')
                           A->x = pere->x+360/(2*(A->hauteur));
         majpositionsGauche(A->sag,A,'g');
         majpositionsGauche(A->sad,A,'d');
       }
}

void majPositionsDescendreDroite(ARBRE A,ARBRE pere,char direction){

 if(A){
       majPositionsDescendreGauche(A->sag,A,'g');
       majPositionsDescendreGauche(A->sad,A,'d');
       if(direction=='g'){
                          A->x += (pere->x - A->x)/2;
                          A->y +=160;
                         }
       if(direction=='d'){
                          A->x += (A->x - pere->x)/2;
                          A->y +=160;
                         }
      }
}

void majPositionsMonterDroite(ARBRE A,ARBRE pere,char direction){

 if(A){
       majPositionsMonterGauche(A->sag,A,'g');
       majPositionsMonterGauche(A->sad,A,'d');
       if(direction=='g'){
                          A->x += pere->x - A->x;
                          A->y -= 160;
                         }
       if(direction=='d'){
                          A->x +=(A->x - pere->x);
                          A->y -=160;
                         }

      }

}

void majpositionsDroite(ARBRE A,ARBRE pere,char direction){

  if(A){

        if(direction=='g')

                           A->x = pere->x-360/(2*(A->hauteur));

        if(direction=='d')

                           A->x = pere->x+360/(2*(A->hauteur));
         majpositionsGauche(A->sag,A,'g');

         majpositionsGauche(A->sad,A,'d');

       }
}

void RGauche(ARBRE *A){

 if((*A)->sad==NULL)
                   exit(-1);
 SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
 afficherArbre(lakheu);
 SDL_Delay(3000);

 ARBRE B;
 B=(*A)->sad;
 (*A)->sad=B->sag;
 B->sag=(*A);

 majPositionsDescendreGauche((*A)->sag,(*A),'g');
 majPositionsMonterGauche(B->sad,B,'d');
 int diffOrdonneeAetB=(B->y) - ((*A)->y),diffAbscisseAetB=(B->x) - ((*A)->x);
 ((*A)->y) += diffOrdonneeAetB;
 ((*A)->x) -= diffAbscisseAetB;
 (B->y) -= diffOrdonneeAetB;
 (B->x) -= diffAbscisseAetB;

 majpositionsGauche((*A)->sad,(*A),'d');

 majHauteur(*A);
 majHauteur(B);

 if((*A)==lakheu)
               lakheu=B;
 (*A)=B;
}


void RDroite(ARBRE *A){

 if((*A)->sag==NULL)
                    exit(-1);

 SDL_FillRect(ecran,NULL,SDL_MapRGB(ecran->format,255,255,255));
 afficherArbre(lakheu);
 SDL_Delay(3000);

 ARBRE B;
 B=(*A)->sag;
 (*A)->sag=B->sad;
 B->sad=(*A);

 majPositionsDescendreDroite((*A)->sad,(*A),'d');
 majPositionsMonterDroite(B->sag,B,'g');
 int diffOrdonneeAetB=B->y - (*A)->y,diffAbscisseAetB=(*A)->x - B->x;
 ((*A)->y) += diffOrdonneeAetB;
 ((*A)->x) += diffAbscisseAetB;
 (B->y) -= diffOrdonneeAetB;
 (B->x) += diffAbscisseAetB;

 majpositionsDroite((*A)->sag,(*A),'g');

 majHauteur(*A);
 majHauteur(B);

 if((*A)==lakheu)
               lakheu=B;
 (*A)=B;
}


void RGDroite(ARBRE* A){

 if((*A)->sag==NULL)
                    exit(-1);

 RGauche(&((*A)->sag));
 RDroite(A);
}


void RDGauche(ARBRE* A){

 if((*A)->sad==NULL)
                    exit(-1);
 RDroite(&((*A)->sag));
 RGauche(A);

}


void reequilibrage(ARBRE* A){

 int d;
 d=desequilibre(*A);
 if(d==2)
         if(desequilibre((*A)->sag)==-1)
                                        RGDroite(A);
         else
             RDroite(A);

 else
     if(d==-2)
              if(desequilibre((*A)->sad)==+1)
                                             RDGauche(A);
              else
                  RGauche(A);
}


int ajouterNoeud(int racine,ARBRE* A,ARBRE pere,char direction,int hauteur){
 int ok;
  if(!(*A)){
            if(hauteur==1)
                          lakheu=*A=newMaillon(racine,750,50,1); // remplacer les constntes.
            else
                if(hauteur==2)
                              if(direction=='g')
                                                *A=newMaillon(racine,pere->x-360,pere->y+160,1);
                              else
                                  *A=newMaillon(racine,pere->x+360,pere->y+160,1);
               else
                   if(direction=='g')
                                     *A=newMaillon(racine,pere->x-360/(2*(hauteur-2)),pere->y+160,1);
                   else
                       *A=newMaillon(racine,pere->x+360/(2*(hauteur-2)),pere->y+160,1);
            return 1;
           }
  else
       if(racine==(*A)->racine)
                               return 0;
       else
           if(racine<(*A)->racine)
                                  ok=ajouterNoeud(racine,&((*A)->sag),*A,'g',++hauteur);
           else
               ok=ajouterNoeud(racine,&((*A)->sad),*A,'d',++hauteur);
  if(ok){
         majHauteur(*A);
         reequilibrage(A);
         }
  return ok;
}

ARBRE supNeudMax(ARBRE *A,ARBRE r){
 ARBRE q;
 if(!(r->sad)){
               (*A)->racine=r->racine;
               q=r;
               majPositionsMonterDroite(r->sag,r,'g');
               r=r->sag;
               free(q);
              }
 else
     r->sad=supNeudMax(A,r->sad);
 return r;
}

ARBRE supprimer(ARBRE A,int racine){
 ARBRE q;
 if(!A)
       return A;
 else
     if(racine==A->racine)
                     if(!(A->sad)){
                                   q=A;
                                   majPositionsMonterDroite(A->sag,A,'g');
                                   A=A->sag;
                                   free(q);
                                  }
                     else
                         if(!(A->sag)){
                                       q=A;
                                       majPositionsMonterGauche(A->sad,A,'d');
                                       A=A->sad;
                                       free(q);
                                      }
                        else
                            A->sag=supNeudMax(&A,A->sag);
     else
         if(racine<A->racine)
                            A->sag=supprimer(A->sag,racine);
         else
             A->sad=supprimer(A->sad,racine);
 return A;


}

int supprimerARBRE(ARBRE* A,int x,int y){

  int ok;
  if(!(*A))
           return 0;
  else
      if(x<((*A)->x)-30)
                        ok=supprimerARBRE(&((*A)->sag),x,y);
      else
          if(x>((*A)->x)+30)
                            ok=supprimerARBRE(&((*A)->sad),x,y);
          else
               if( ((*A)->y-30)<=y && y<=(*A)->y+30 ){
                                                      lakheu=*A=supprimer(*A,(*A)->racine);
                                                      ok=1;
                                                     }
   if(ok && (*A)){
                  majHauteur(*A);
                  reequilibrage(A);
                 }
   return ok;
}



