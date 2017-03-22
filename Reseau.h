#ifndef __RESEAU_H__
#define __RESEAU_H__

#include "Chaine.h"

typedef struct noeud Noeud;

/* Liste chainee de noeuds (pour la liste des noeuds du reseau ET les listes des voisins de chaque noeud) */
typedef struct cellnoeud {
    Noeud *nd;               /* Pointeur vers le noeud stock\'e */
    struct cellnoeud *suiv;         /* Cellule suivante dans la liste */
} CellNoeud;

/* Noeud du reseau */
struct noeud{
   int num;                        /* Numero du noeud */
   double x, y;                    /* Coordonnees du noeud*/
   CellNoeud *voisins;             /* Liste des voisins du noeud */
};

/* Liste chainee de commodites */
typedef struct cellCommodite {
    Noeud *extrA, *extrB;       /* Noeuds aux extremites de la commodite */
    struct cellCommodite *suiv;     /* Cellule suivante dans la liste */
} CellCommodite;

/* Un reseau */
typedef struct {
    int nbNoeuds;                   /* Nombre de noeuds du reseau */
    int gamma;                      /* Nombre maximal de fibres par cable */
    CellNoeud *noeuds;              /* Liste des noeuds du reseau */
    CellCommodite *commodites;      /* Liste des commodites a relier */
} Reseau;

Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y);
Reseau* reconstitueReseauListe(Chaines *C);
void ecrireReseauTxt(Reseau *R, FILE *f);
int nbLiaison(Reseau *R);
int nbCommodite(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);

Noeud * creer_noeud(int num, double x, double y);
CellNoeud * creer_CellNoeud(Noeud * n);
CellCommodite * creer_commodite(Noeud * a, Noeud * b);
Reseau * creer_reseau_vide();
void ajouter_voisins(Noeud * n, CellNoeud * voisin);
void afficher_noeud(Noeud * n, int afficheVoisins);
void afficher_reseau(Reseau * R);
void reseau_min_max (Reseau* R, double* xmin, double* ymin, double* xmax, double* ymax);

void liberer_un_noeud(Noeud * n);
void liberer_liste_noeud(CellNoeud * ln);
void liberer_liste_commodites( CellCommodite * cm);
void liberer_reseau(Reseau * r);

#endif
