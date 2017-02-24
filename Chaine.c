#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "entree_sortie.h"
#include "Chaine.h"
#include "SVGwriter.h"

#define TAILLE 100

/*retourne un CellPoint*/

CellPoint* creer_CellPoint (double x, double y, CellPoint* suiv)
{
	CellPoint* cellP;
	cellP = (CellPoint*)malloc(sizeof(CellPoint));
	
	if (!cellP){
		printf("Erreur : creer_CellPoint\n");
		return NULL;
	}
	
	cellP->x = x;
	cellP->y = y;
	cellP->suiv = suiv;
	
	return cellP;
}

/*retourne un CellChaine*/
CellChaine* creer_CellChaine (int numero, CellPoint* points, CellChaine* suiv)
{
	CellChaine* cellC;
	cellC = (CellChaine*)malloc(sizeof(CellChaine));
	
	if (!cellC){
		printf("Erreur : creer_CellChaine\n");
		return NULL;
	}
	
	cellC->numero = numero;
	cellC->points = points;
	cellC->suiv = suiv;
	
	return cellC;
}

/*retourne un Chaines*/
Chaines* creer_Chaines (int gamma, int nbChaines, CellChaine* chaines)
{
	Chaines* chain;
	chain = (Chaines*)malloc(sizeof(Chaines));
	
	if (!chain){
		printf("Erreur : creer_Chaines\n");
		return NULL;
	}
	
	chain->gamma = gamma;
	chain->nbChaines = nbChaines;
	chain->chaines = chaines;
	
	return chain;
}


/*affiche une Chaines*/
void afficher_Chaines (Chaines* C)
{
	if (!C){
		printf("Erreur afficher_Chaines\n");
		exit(1);
	}
	
	CellChaine* cellC = C->chaines;
	CellPoint* cellP;
	printf ("gamma : %d\nnbChaines : %d\n", C->gamma, C->nbChaines);
	
	while (cellC){
		printf("\tNumero Chaine: %d\n", cellC->numero);
		cellP = cellC->points;
		
		while (cellP){
			printf("\t\t(%.2f , %.2f)\n", cellP->x, cellP->y);
			cellP = cellP->suiv;
		}
		cellC = cellC->suiv;
		printf("\n");	
	}
	printf("\n");
}


/*retourne une Chaines a partir du fichier f*/
Chaines* lectureChaine(FILE *f){

	CellPoint * cellP;
	CellPoint * listePoints = NULL;
	
	CellChaine * cellC;
	CellChaine * chaines = NULL;
	
	int nbChaines, gamma, numero, nbPoints;
	float x, y;
	int i, j;
	
	char tmp[128];

	//revoir les if si besoin
	GetChaine(f, 128, tmp);
	if (strcmp (tmp, "NbChain:") == 0);
	nbChaines = GetEntier(f);
	
	GetChaine(f, 128, tmp);
	if (strcmp (tmp, "Gamma:") == 0);
	gamma = GetEntier(f);
	
	for(i=0; i<nbChaines; i++){
		numero = GetEntier(f);
		nbPoints = GetEntier(f);
		
		for(j=0; j<nbPoints; j++){
			x = GetReel(f);
			y = GetReel(f);
			cellP = creer_CellPoint(x,y,listePoints);
			listePoints = cellP;
		}
		
		cellC = creer_CellChaine(numero, listePoints, chaines);
		chaines = cellC;
		listePoints = NULL;
	}
	
	return creer_Chaines(gamma, nbChaines, chaines);	
}

/*retourne le nombre de points dans une liste de cellPoint*/
int nbPoints (CellChaine* c)
{
	int cpt = 0;
	CellPoint* cellP = c->points;
	
	while (cellP){
		cpt++;
		cellP = cellP->suiv;
	}
	//printf("nbPoints : %d\n", cpt);
	return cpt;
}


/*ecrit la chaine C dans le fichier f*/
void ecrireChaineTxt(Chaines *C, FILE *f){
	
	if (!f){
		printf("Erreur ecrireChaineTxt");
		exit(1);
	}
	
	fprintf(f, "NbChain: %d\n", C->nbChaines);
	fprintf(f, "Gamma: %d\n\n", C->gamma);

	CellChaine * cellC = C->chaines;
	
	while (cellC){
		fprintf(f, "%d %d", cellC->numero, nbPoints(cellC));
		CellPoint * cellP = cellC->points;
		while(cellP){
			fprintf(f, "%.2f %.2f ", cellP->x, cellP->y);
			cellP = cellP->suiv;
		}
	fprintf(f, "\n");
	cellC = cellC->suiv;
	}		
}

void min_max (Chaines* C, double* minX, double* maxX, double* minY, double* maxY){

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

void afficheChaineSVG(Chaines *C, char* nomInstance){
	
	SVGwriter* new = (SVGwriter *) malloc (sizeof(SVGwriter));
	double minX, maxX, minY, maxY;

	min_max (C, &minX, &maxX, &minY, &maxY);
	
	SVGinit(new, nomInstance, maxX-minX, maxY-minY);
	SVGlineRandColor(new);

	CellChaine* currCC = C->chaines;
	CellPoint* currCP; 
	while(currCC){
		currCP = currCC->points;
		if(currCP){
			SVGpoint(new, currCP->x - minX, currCP->y - minY);
			while(currCP->suiv){
				SVGpoint(new, currCP->suiv->x - minX, currCP->suiv->y - minY);
				SVGline(new, currCP->x - minX, currCP->y - minY, currCP->suiv->x - minX, currCP->suiv->y - minY);
				currCP = currCP->suiv;
			}
		}
		currCC = currCC->suiv;
	}
	SVGfinalize(new);
}


/*retourne la longueur de la liste chainee de CellChaine c*/
double longueurChaine (CellChaine* c)
{
	CellPoint* p = c->points;
	CellPoint* p_suiv;
	double longueur = 0.0;
	
	while (p->suiv){
		p_suiv = p->suiv;
		//ajout sqrt !
		longueur += sqrt ( (p_suiv->x - p->x)*(p_suiv->x - p->x) + (p_suiv->y - p->y)*(p_suiv->y - p->y) );
		p = p_suiv;
	}
	
	return longueur;
}


/*retourne la longueur totale des chaines*/
double longueurTotale(Chaines *C){
	
	CellChaine* cellC = C->chaines;
	double longueur_totale = 0.0;
	
	while(cellC){
		longueur_totale += longueurChaine(cellC);
		cellC = cellC->suiv;
	}
	
	return longueur_totale;
}


int comptePointsTotal(Chaines *C){

	int cpt = 0;
	CellChaine* cellC = C->chaines;
	
	while (cellC){
		cpt += nbPoints(cellC);
		cellC = cellC->suiv;
	}
	
	return cpt;
}
