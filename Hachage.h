#ifndef __HACHAGE_H__
#define __HACHAGE_H__

#include "Reseau.h"

typedef struct _hachage{
	int nb_elem;
	int taille;
	CellNoeud ** tab;
}tab_hach;


tab_hach * creer_tab_hach(int taille);

double fonction_clef(double x, double y);

int fonction_hachage(double clef, int taille);

Noeud* rechercheCreeNoeudHachage(Reseau *R, tab_hach* H, double x, double y);

Reseau* recreeReseauHachage(Chaines *C);

void libere_tab_hach(tab_hach * H);

#endif
