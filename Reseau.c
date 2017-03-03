#include <stdio.h>
#include <stdlib.h>

#include "Reseau.h"
#include "Chaine.h"


Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y){
	if(R){
		CellNoeud *curr = R->noeuds;
		while(curr){
			if(curr->nd->x == x && curr->nd->y == y)
				return curr->nd;
			curr = curr->suiv;
		}
	}

	CellNoeud *new = (CellNoeud*)malloc(sizeof(CellNoeud));
	
	new->nd = (Noeud*)malloc(sizeof(Noeud));
	new->nd->num = R->noeuds->nd->num + 1;
	new->nd->x = x;
	new->nd->y = y;
	new->nd->voisins = NULL;
	
	new->suiv = R->noeuds;
	
	R->noeuds = new;
	R->nbNoeuds ++;

	return new->nd;
}


Reseau* reconstitueReseauListe(Chaines *C){
	Reseau* R = (Reseau*)malloc(sizeof(Reseau));

	R->gamma = C->gamma;
	R->nbNoeuds = 0;
	R->noeuds = NULL;
	R->commodites = NULL;

	CellChaine* currCC = C->chaines;
	CellPoint* currCP;

	CellCommodite* newCom;

	Noeud* n1;
	Noeud* n2;

	while (currCC){
		printf("While 1\n");
		if (currCC->points)
			currCP = currCC->points;

		if (!currCP)
			continue;

		n1 = rechercheCreeNoeudListe(R, currCP->x, currCP->y);
		printf("test\n");
		while(currCP && currCP->suiv){
			printf("While 2\n");
			n2 = rechercheCreeNoeudListe(R, currCP->suiv->x, currCP->suiv->y);
			newCom = (CellCommodite*)malloc(sizeof(CellCommodite));
			newCom->extrA = n1;
			newCom->extrB = n2;
			newCom->suiv = R->commodites;

			R->commodites = newCom;

			currCP = currCP->suiv;
		}
		currCC = currCC->suiv;
	}

	return R;
}

/*
void ecrireReseauTxt(Reseau *R, FILE *f);
int nbLiaison(Reseau *R);
int nbCommodite(Reseau *R);
void afficheReseauSVG(Reseau *R, char* nomInstance);
*/