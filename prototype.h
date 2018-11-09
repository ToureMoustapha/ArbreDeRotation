#ifndef HANOI_H_INCLUDED
#define HANOI_H_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


typedef struct noeud{
        int racine;
        int x,y,hauteur;  
        struct noeud *sag,*sad;
        }NOEUD,*ARBRE;

SDL_Surface *ecran=NULL;
ARBRE lakheu=NULL; 

void unPixel(int,int,Uint32);
void echangerEntiers(int*,int*);
void ligne(int,int,int,int,Uint32);
void tracerCercle(int,int,int,Uint32);
SDL_Surface* surfaceEcrite(int);
ARBRE newMaillon(int,int,int,int);
void afficherNoeud(NOEUD);
void afficherArbre(ARBRE);
ARBRE detruireArbre(ARBRE);
void majHauteur(NOEUD*);
int desequilibre(ARBRE);
void majPositionsDescendreGauche(ARBRE,ARBRE,char);
void majPositionsMonterGauche(ARBRE,ARBRE,char);
void  majpositionsGauche(ARBRE,ARBRE,char);
void majPositionsDescendreDroite(ARBRE,ARBRE,char);
void majPositionsMonterDroite(ARBRE,ARBRE,char);
void majpositionsDroite(ARBRE,ARBRE,char);
void RGauche(ARBRE*);
void RDroite(ARBRE*);
void RGDroite(ARBRE*);
void RDGauche(ARBRE*);
void reequilibrage(ARBRE*);
int ajouterNoeud(int,ARBRE*,ARBRE,char,int);
ARBRE supNeudMax(ARBRE*,ARBRE);
ARBRE supprimer(ARBRE,int);
int supprimerARBRE(ARBRE*,int,int);

#endif // HANOI_H_INCLUDED
