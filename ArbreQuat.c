#include <stdio.h>
#include <stdlib.h>

#include "ArbreQuat.h"



void chaineCoordMinMax (Chaines* C, double* minX, double* maxX, double* minY, double* maxY){
	CellChaine* cellC = C->chaines;
	CellPoint* cellP ;

	*minX = cellC->points->x;
	*maxX = cellC->points->x;
	*minY = cellC->points->y;
	*maxY = cellC->points->y;
	//cellC = cellC->suiv;
	while (cellC){
		cellP = cellC->points;
		while (cellP){
			if (cellP->x > *maxX) {
				*maxX = cellP->x;
			}
			if (cellP->x < *minX) {
				*minX = cellP->x;
			}
			if (cellP->y > *maxY) {
				*maxY = cellP->y;
			}
			if (cellP->y < *minY) {
				*minY = cellP->y;
			}
			cellP = cellP->suiv;
		}
		cellC = cellC->suiv;
	}
}

ArbreQuat* creerArbreQuat (double xc, double yc, double coteX, double coteY){
	ArbreQuat* new = (ArbreQuat*) malloc(sizeof (ArbreQuat));
	new->coteX = coteX;
	new->coteY = coteY;
	new->xc = xc;
	new->yc = yc;
	new->so = NULL;
	new->se = NULL;
	new->no = NULL;
	new->ne = NULL;
	new->noeud = NULL;

	return new;
}


ArbreQuat* insererNoeudArbre (Noeud* n, ArbreQuat* a, ArbreQuat* parent){
	//arbre vide
	if (a == NULL){
		//det la position du point par rapport au parent
		//noeud au Nord Ouest
		if (parent->xc < n->x && parent->yc > n->x){
			parent->no = a;
			a = creerArbreQuat (parent->coteX/4, (parent->coteY*3)/4, parent->coteX/2, parent->coteY/2);
		}
		//noeud au Nord Est
		if (parent->xc > n->x && parent->yc > n->x){
			parent->ne = a;
			a = creerArbreQuat ((parent->coteX*3)/4, (parent->coteY*3)/4, parent->coteX/2, parent->coteY/2);
		}
		//noeud au Sud Ouest
		if (parent->xc < n->x && parent->yc < n->x){
			parent->so = a;
			a = creerArbreQuat (parent->coteX/4, parent->coteY/4, parent->coteX/2, parent->coteY/2);
		}
		//noeud au Sud Est
		if (parent->xc > n->x && parent->yc < n->x){
			parent->se = a;
			a = creerArbreQuat ((parent->coteX*3)/4, parent->coteY/4, parent->coteX/2, parent->coteY/2);
		}
		a->noeud  = n;
		return a;
	}
	//feuille
	if (a->noeud != NULL){
		//noeud que l'on veut insererNoeudArbre
		//noeud au Nord Ouest
		if (a->xc < n->x && a->yc > n->y)
			insererNoeudArbre(n, a->no, a);
		//noeud au Nord Est
		if (a->xc > n->x && a->yc > n->y)
			insererNoeudArbre(n, a->ne, a);
		//noeud au Sud Ouest
		if (a->xc < n->x && a->yc < n->y)
			insererNoeudArbre(n, a->so, a);
		//noeud au Sud Est
		if (a->xc > n->x && a->yc < n->y)
			insererNoeudArbre(n, a->se, a);

		//noeud de la feuille
		//noeud au Nord Ouest
		if (a->xc < a->noeud->x && a->yc > a->noeud->y)
			insererNoeudArbre(a->noeud, a->no, a);
		//noeud au Nord Est
		if (a->xc > a->noeud->x && a->yc > a->noeud->y)
			insererNoeudArbre(a->noeud, a->ne, a);
		//noeud au Sud Ouest
		if (a->xc < a->noeud->x && a->yc < a->noeud->y)
			insererNoeudArbre(a->noeud, a->so, a);
		//noeud au Sud Est
		if (a->xc > a->noeud->x && a->yc < a->noeud->y)
			insererNoeudArbre(a->noeud, a->se, a);

		a->noeud = NULL;
		return a;
	}
	//cellule interne
	if (a->noeud == NULL && a != NULL){
		//noeud au Nord Ouest
		if (a->xc < n->x && a->yc > n->y){
			return insererNoeudArbre(n, a->no, a);
		}
		//noeud au Nord Est
		if (a->xc > n->x && a->yc > n->y){
			return insererNoeudArbre(n, a->ne, a);
		}
		//noeud au Sud Ouest
		if (a->xc < n->x && a->yc < n->y){
			return insererNoeudArbre(n, a->so, a);
		}
		//noeud au Sud Est
		if (a->xc > n->x && a->yc < n->y){
			return insererNoeudArbre(n, a->se, a);
		}
	}
	return a;
}

Noeud* chercherNoeudArbre(CellPoint* pt, Reseau* R, ArbreQuat** aptr, ArbreQuat* parent){

	//arbre Vide;
	if (*aptr == NULL) {
		R->nbNoeuds ++;
		Noeud* newNoeud = creer_noeud(R->nbNoeuds, pt->x, pt->y);
		CellNoeud* newCellNoeud = creer_CellNoeud(newNoeud);
		newCellNoeud->suiv = R->noeuds;
		R->noeuds = newCellNoeud;
		insererNoeudArbre (newNoeud, *aptr, parent);
		return newNoeud;
	}
	//feuille
	if ((*aptr)->noeud != NULL) {
		if ((*aptr)->noeud->x == pt->x && (*aptr)->noeud->y == pt->y){
			return (*aptr)->noeud;
		}else{
			R->nbNoeuds ++;
			Noeud* newNoeud = creer_noeud(R->nbNoeuds, pt->x, pt->y);
			CellNoeud* newCellNoeud = creer_CellNoeud(newNoeud);
			newCellNoeud->suiv = R->noeuds;
			R->noeuds = newCellNoeud;
			insererNoeudArbre (newNoeud, *aptr, parent);
			return newNoeud;
		}
	}
	//cellulle interne
	if(*aptr != NULL && (*aptr)->noeud == NULL){
		//noeud au Nord Ouest
		if ((*aptr)->xc < pt->x && (*aptr)->yc > pt->y){
			return chercherNoeudArbre(pt, R, &(*aptr)->no, *aptr);
		}
		//noeud au Nord Est
		if ((*aptr)->xc > pt->x && (*aptr)->yc > pt->y){
			return chercherNoeudArbre(pt, R, &(*aptr)->ne, *aptr);
		}
		//noeud au Sud Ouest
		if ((*aptr)->xc < pt->x && (*aptr)->yc < pt->y){
			return chercherNoeudArbre(pt, R, &(*aptr)->so, *aptr);
		}
		//noeud au Sud Est
		if ((*aptr)->xc > pt->x && (*aptr)->yc < pt->y){
			return chercherNoeudArbre(pt, R, &(*aptr)->se, *aptr);
		}
	}
}

Reseau* recreeReseauArbre (Chaines* C){
	Reseau* res = creer_reseau_vide();
	res->gamma = C->gamma;

	double minX, minY, maxX, maxY;
	chaineCoordMinMax(C, &minX, &maxX, &minY, &maxY);
	double xc, yc, coteX, coteY;
	coteX = maxX - minX;
	coteY = maxY - minY;
	xc = coteX/2;
	yc = coteY/2;
	ArbreQuat* abr = creerArbreQuat(xc, yc, coteX, coteY);

	CellPoint * p;
	Noeud * noeud1, * noeud2;
	CellNoeud * cell1, * cell2;
	Noeud * exA;
	Noeud * exB;
	CellCommodite * com;
	CellChaine * cell = C->chaines;

	while (cell){
		p = cell->points;
		noeud1 = chercherNoeudArbre(p, res, &abr, NULL);
		exA = noeud1;
		cell1 = creer_CellNoeud(noeud1);
		p=p->suiv;
		while (p){
			noeud2 = chercherNoeudArbre(p, res, &abr, NULL);
			ajouter_voisins(noeud1, cell1);
			cell2 = creer_CellNoeud(noeud2);
			ajouter_voisins(noeud1, cell2);
			noeud1 = noeud2;
			p = p->suiv;
		}

		exB = noeud1;
		com = creer_commodite(exA, exB);
		com->suiv = res->commodites;
		res->commodites = com;
		cell = cell->suiv;
	}
	return res;
}
