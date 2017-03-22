#include <stdio.h>
#include <stdlib.h>

#include "entree_sortie.h"
#include "Chaine.h"
#include "ArbreQuat.h"

int main(){
	FILE* f = fopen("00014_burma.cha", "r");

	//printf("main : ouverture fichier\n\n");
	Chaines* C = lectureChaine(f);

	//printf("main : creation Chaines\n");
	fclose(f);

	//printf("main : fermeture fichier\n");

	//afficher_Chaines(C);

	FILE* f2 = fopen("Chaine.txt", "w");
	ecrireChaineTxt(C, f2);
	printf("fin ecriture Chaines\n");
	fclose(f2);

	afficheChaineSVG(C, "Chaine");

	printf("longueur chaine %f\n", longueurChaine (C->chaines));
	//printf("main : fin affichage\n");
	return 0;
}
