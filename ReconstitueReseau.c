#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Reseau.h"
#include "Chaine.h"


int main (int argc, char* argv[]){

	if(argc != 3){
		printf("Erreur format main\n");
		return 1;
	}

	char* nomfichier = strdup(argv[1]);
	int num_methode = atoi (argv[2]);

	printf("lecture\n");
	FILE* f = fopen(nomfichier, "r");

	printf("lectureChaine\n");
	Chaines* C = lectureChaine(f);

	fclose(f);

	printf("reconstitueReseauListe\n");
	Reseau* R = reconstitueReseauListe(C);
	printf("fin : reconstitueReseauListe\n");

	return 0;
}