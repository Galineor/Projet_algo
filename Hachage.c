#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Hachage.h"
#include "Reseau.h"
#define TAILLE_HACH 50

tab_hach * creer_tab_hach (int taille)
{
	if(taille<=0){
		printf("Erreur\n");
		return NULL;
	}

	tab_hach * t = (tab_hach *)malloc(sizeof(tab_hach));
	if(t==NULL){
		printf("Erreur\n");
		return NULL;
	}

	t->nb_elem = 0;
	t-> taille = taille;

	t->tab = (CellNoeud **)malloc(taille*sizeof(CellNoeud *));
	if(t->tab==NULL){
		printf("Erreur\n");
		free(t);
		return NULL;
	}

	int i;
	for(i=0; i<taille; i++){
		t -> tab[i] = NULL;
	}

	return t;
}

double fonction_clef(double x, double y)
{
	return y + ((x + y)*(x + y + 1) /2);
}

int fonction_hachage(double clef, int taille)
{
	double A = sqrt(5) -1 / 2.0;
	A = clef * A;

	return floor( taille * (A - floor(A)));
}


Noeud* rechercheCreeNoeudHachage(Reseau *R, tab_hach* t, double x, double y)
{
	if(t==NULL){
		printf("Erreur\n");
		return NULL;
	}

	if(R==NULL){
		printf("Erreur\n");
		return NULL;
	}

	int indice = fonction_hachage( fonction_clef(x, y), t -> taille);

	CellNoeud * tmp = t -> tab[indice];

	while(tmp){
		if((tmp->nd->x==x)&&(tmp->nd->y==y)){
			return tmp->nd;
		}

		tmp = tmp -> suiv;
	}

	Noeud * n = creer_noeud(x ,y, ((R->nbNoeuds)+1) );

	CellNoeud * cn_hach = creer_CellNoeud(n);
	cn_hach -> suiv = t -> tab[indice];
	t -> tab[indice] = cn_hach;
	t -> nb_elem++;

	CellNoeud * cn_res = creer_CellNoeud(n);
	cn_res -> suiv = R -> noeuds;
	R -> noeuds = cn_res;
	R -> nbNoeuds++;

	return n;
}

Reseau* recreeReseauHachage(Chaines *C)
{
	if(C==NULL){
		printf("Erreur\n");
		return NULL;
	}

	Reseau * R = creer_reseau_vide();
	R -> gamma = C -> gamma;
	tab_hach * H = creer_tab_hach(TAILLE_HACH);
	CellPoint * p;
	Noeud * noeud1, * noeud2;
	CellNoeud * cell1, * cell2;
	Noeud * exA;
	Noeud * exB;
	CellCommodite * com;
	CellChaine * cell = C->chaines;

	while(cell){
		p = cell -> points;
		noeud1 = rechercheCreeNoeudHachage(R, H,  p->x, p->y);
		exA = noeud1;
		cell1 = creer_CellNoeud(noeud1);
		p = p -> suiv;

		while(p){
			noeud2 = rechercheCreeNoeudHachage(R, H, p->x, p->y);
			ajouter_voisins(noeud2, cell1);
			cell2 = creer_CellNoeud(noeud2);
			ajouter_voisins(noeud1, cell2);
			noeud1 = noeud2;
			cell1 = creer_CellNoeud(cell2 -> nd);
			p = p -> suiv;
		}
		exB = noeud1;
		com = creer_commodite(exA, exB);
		com -> suiv = R -> commodites;
		R -> commodites = com;
		cell = cell -> suiv;
	}
	return R;
}

//affichage
//free
