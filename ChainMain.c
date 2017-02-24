#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "entree_sortie.h"
#include "Chaine.h"

int main(){
	FILE* f = fopen("00014_burma.cha", "r");
	
	Chaines* C = lectureChaine(f);
	
	fclose(f);
	
	/*afficher_Chaines(C);

	
	FILE* f2 = fopen("test.txt", "w");
	ecrireChaineTxt(C, f2);
	printf("fin ecriture Chaines\n");
	fclose(f2);

	//printf("longueur chaine %f\n", longueurChaine (C->chaines));
	printf("longueur Chaines %f\n", longueurTotale(C));
	printf("Points total de C : %d\n", comptePointsTotal(C));
	*/

	afficheChaineSVG(C, "test");
	printf("fin afficheChaineSVG\n");

	return 0;
}
