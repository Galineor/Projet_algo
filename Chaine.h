#ifndef __CHAINE_H__
#define __CHAINE_H__
#include <stdio.h>
#include <math.h>
#include "SVGwriter.h"


/* Liste chainee de points */
typedef struct cellPoint{
  double x,y;                   /* Coordonnees du point */
  struct cellPoint *suiv;       /* Cellule suivante dans la liste */
} CellPoint;

/* Celllule d une liste (chainee) de chaines */
typedef struct cellChaine{
  int numero;                   /* Numero de la chaine */
  CellPoint *points;            /* Liste des points de la chaine */
  struct cellChaine *suiv;      /* Cellule suivante dans la liste */
} CellChaine;

/* L'ensemble des chaines */
typedef struct {
  int gamma;                    /* Nombre maximal de fibres par cable */
  int nbChaines;                /* Nombre de chaines */
  CellChaine *chaines;          /* La liste chainee des chaines */
} Chaines;

CellPoint* creer_CellPoint (double x, double y, CellPoint* suiv);

CellChaine* creer_CellChaine (int numero, CellPoint* points, CellChaine* suiv);

Chaines* creer_Chaines (int gamma, int nbChaines, CellChaine* chaines);

void afficher_Chaines (Chaines* C);

Chaines* lectureChaine(FILE *f);

int nbPoints (CellChaine* c);

void ecrireChaineTxt(Chaines *C, FILE *f);

void min_max (Chaines* C, double* minX, double* maxX, double* minY, double* maxY);

void afficheChaineSVG(Chaines *C, char* nomInstance);

double longueurChaine (CellChaine* c);

double longueurTotale(Chaines *C);

int comptePointsTotal(Chaines *C);

#endif
