#include <stdio.h>
#include <stdlib.h>

#include "Reseau.h"
#include "Chaine.h"

#define TAILLE 100

/*
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

	R->gamma = C-> gamma;
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
*/

Noeud * creer_noeud (int num, double x, double y)
{
	Noeud *nd = (Noeud *)malloc(sizeof(Noeud));
	
	if(nd == NULL){
		printf("Erreur malloc : creer_noeud\n");
		return NULL;
	}
	
	nd->x = x;
	nd->y = y;
	nd->num = num;
	nd->voisins = NULL;
	
	return nd;
}

CellNoeud * creer_CellNoeud(Noeud * n)
{
	CellNoeud * cn = (CellNoeud *)malloc(sizeof(CellNoeud));
	
	if(cn == NULL){
		printf("Erreur malloc : creer_CellNoeud\n");
		return NULL;
	}
	
	cn->nd = n;
	cn->suiv = NULL;
	
	return cn;
}

CellCommodite * creer_commodite(Noeud * a, Noeud * b)
{
	CellCommodite * com = (CellCommodite *)malloc(sizeof(CellCommodite));
	
	if(com == NULL){
		printf("Erreur malloc\n");
		return NULL;
	}
	
	com->extrA = a;
	com->extrB = b;
	com->suiv = NULL;
	
	return com;
}

Reseau * creer_reseau_vide()
{
	Reseau * R = (Reseau *)malloc(sizeof(Reseau));
	if(R==NULL){
		printf("probleme d'allocation memoire\n");
		return NULL;
	}
	
	R->gamma = 0;
	R->nbNoeuds = 0;
	R->noeuds = NULL;
	R->commodites = NULL;
	return R;
}

void ajouter_voisins(Noeud * n, CellNoeud * voisin)
{
	
	CellNoeud * tmp = n->voisins;
	
	while(tmp){
		if((tmp->nd->x==voisin->nd->x)&&(tmp->nd->y==voisin->nd->y)){
			return;
		}
		
		tmp = tmp->suiv;
	}
	
	voisin -> suiv = n->voisins;
	n->voisins = voisin;
	
}

void afficher_noeud(Noeud * n, int afficheVoisins)
{
	if(n==NULL){
		printf("noeud non initialise\n");
		return;
	}
	
	printf("numero : %d\n", n->num);
	printf("(%.2f, %.2f)\n", n->x, n->y);
	if(afficheVoisins){
		if(n->voisins==NULL){
			printf("Pas de voisins\n\n");
		}
		else{
			printf("Voisins :\n");
			CellNoeud * c = n->voisins;
			while(c){
				printf("(%.2f, %.2f)\n", c->nd->x, c->nd->y);
				c = c->suiv;
			}
			printf("Fin des voisins\n \n");
		}
	}
	
}
//affichage du reseau R
void afficher_reseau(Reseau * R)
{
	if(R==NULL){
		printf("reseau non initialise\n");
		return;
	}
	
	printf("NbNoeuds : %d\n", R->nbNoeuds);
	printf("Gamma : %d\n", R->gamma);
	
	printf("liste de noeuds :\n");
	CellNoeud * liste = R->noeuds;
	while(liste){
		afficher_noeud(liste->nd, 1);
		liste = liste -> suiv;
	}
	printf("Fin des noeuds\n\n");
	
	
	printf("Liste des commodites : \n");
	CellCommodite * com = R -> commodites;
	while(com){
		printf("Commodite entre : \n");
		afficher_noeud(com->extrA, 0);
		printf("et \n");
		afficher_noeud(com->extrB, 0);
		printf("\n");
		com = com -> suiv;
	}
	printf("Fin des Commodites \n \n");
	
	printf("FIN DU RESEAU \n \n");
	
}


Noeud* rechercheCreeNoeudListe(Reseau *R, double x, double y)
{
	if(R==NULL){
		printf("reseau non initialise\n");
		return NULL;
	}
	
	CellNoeud * c = R->noeuds;
	while(c){
		if((c->nd->x==x)&&(c->nd->y==y)){
			return c->nd;
		}
		
		c = c ->suiv;
	}

	CellNoeud * n = creer_CellNoeud (creer_noeud((R->nbNoeuds)+1, x, y));
	
	n->suiv = R->noeuds;
	R->noeuds = n;
	
	R->nbNoeuds++;
	
	return n->nd;
	
}

Reseau* reconstitueReseauListe(Chaines *C)
{
	if(C==NULL){
		printf("Erreur\n");
		return NULL;
	}

	Reseau * R = creer_reseau_vide();
	R -> gamma = C -> gamma;
	
	CellPoint * p;
	Noeud * noeud1, * noeud2;
	
	CellNoeud * cell1, * cell2;
	Noeud * exA;
	Noeud * exB;
	CellCommodite * com;
	CellChaine * cell = C->chaines;
	while(cell){
		
		p = cell -> points;
		
		noeud1 = rechercheCreeNoeudListe(R, p->x, p->y);
		exA = noeud1;
		
		cell1 = creer_CellNoeud(noeud1);
		
		p = p -> suiv;
		
		while(p){
			
			
			noeud2 = rechercheCreeNoeudListe(R, p->x, p->y);
			
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

void ecrireReseauTxt(Reseau *R, FILE *f)
{
	if(f==NULL){
		printf("Erreur\n");
		return;
	}
	
	if(R==NULL){
		printf("Erreur\n");
		return;
	}
	
	fprintf(f, "NbNoeuds: %d\n", R->nbNoeuds);
	fprintf(f, "NbLiaison: %d\n", nbLiaison(R));
	fprintf(f, "NbCommodite: %d\n", nbCommodite(R));
	fprintf(f, "Gamma: %d\n\n", R->gamma);
	
	int i;
	CellNoeud * tmp = R->noeuds;
	
	for(i=0; i<(R->nbNoeuds); i++){
		fprintf(f, "v %d %.6f %.6f\n", tmp->nd->num, tmp->nd->x, tmp->nd->y);
		tmp = tmp -> suiv;
	}
	
	fprintf(f, "\n");
	
	CellNoeud * vois;
	tmp = R->noeuds;
	
	while(tmp){
		vois = tmp->nd->voisins;
		while(vois){
			if( (tmp->nd->num) < (vois->nd->num)){
				fprintf(f, "l %d %d\n", tmp->nd->num, vois->nd->num);
			}
			vois = vois -> suiv;
		}
		
		tmp = tmp -> suiv;
	}
	
	fprintf(f, "\n");
	
	CellCommodite * com = R->commodites;
	
	while(com){
		fprintf(f, "k %d %d\n", com->extrA->num, com->extrB->num);
		com = com -> suiv;
	}
	
	return;
}

int nbCommodite(Reseau *R)
{
	int nb=0;
	CellCommodite * c = R->commodites;
	
	while(c){
		nb++;
		c = c -> suiv;
	}
	
	return nb;
}

int nbLiaison(Reseau *R)
{
	int nb=0;
	CellNoeud * tmp = R->noeuds;
	CellNoeud * vois;
	
	while(tmp){
		vois = tmp -> nd -> voisins;
		
		while(vois){
			nb++;
			vois = vois -> suiv;
		}
		
		tmp = tmp -> suiv;
	}

	return nb/2;
}

void reseau_min_max (Reseau* R, double* xmin, double* ymin, double* xmax, double* ymax)
{
	if(R==NULL){
		printf("Erreur\n");
		return;
	}
	
	CellNoeud * tmp = R -> noeuds;
	
	if(tmp){
		*xmax = tmp -> nd -> x;
		*xmin = tmp -> nd -> x;
		*ymax = tmp -> nd -> y;
		*ymin = tmp -> nd -> y;
		tmp = tmp -> suiv;
	}
	
	while(tmp){
		
		if((tmp -> nd -> x) > (*xmax)){
			*xmax = tmp -> nd -> x;
		}
		
		if ((tmp -> nd -> x) < (*xmin)){
			*xmin = tmp -> nd -> x;
		}
		
		if ((tmp -> nd -> y) > (*ymax)){
			*ymax = tmp -> nd -> y;
		}
		
		if ((tmp -> nd -> y) < (*ymin)){
			*ymin = tmp -> nd -> y;
		}
		
		tmp = tmp -> suiv;
	}
}

void afficheReseauSVG(Reseau *R, char* nomInstance)
{
	
	if(R==NULL){
		printf("la structure Chaines* n'est pas alloue\n");
		return;
	}
	
	double xmax, xmin, ymax, ymin;
	reseau_min_max(R, &xmin, &ymin, &xmax, &ymax);
	SVGwriter svg;
	SVGinit(&svg, nomInstance, TAILLE, TAILLE);
	SVGpointColor(&svg, "Orange");
	SVGlineColor(&svg, "RoyalBlue");
	
	CellNoeud * nd_courant = R -> noeuds;
	CellNoeud * voisins;
	
	while(nd_courant){
		SVGpoint(&svg, TAILLE*((nd_courant->nd->x - xmin)/(xmax-xmin)),
			 TAILLE*((nd_courant->nd->y - ymin)/(ymax - ymin)));
		
		voisins = nd_courant -> nd -> voisins;
		
		while(voisins){
			if((nd_courant->nd->num)<(voisins->nd->num)){
				SVGline(&svg, TAILLE*((nd_courant->nd->x - xmin)/(xmax-xmin)),
					TAILLE*((nd_courant->nd->y - ymin)/(ymax - ymin)),
					TAILLE*((voisins->nd->x - xmin)/(xmax-xmin)),
					TAILLE*((voisins->nd->y - ymin)/(ymax - ymin)));
			}
			voisins = voisins -> suiv;
		}
		
		nd_courant = nd_courant -> suiv;
	}
	
	SVGfinalize(&svg);
}

//fonctions pour les free