#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Reseau.h"
#include "Chaine.h"
#include "Hachage.h"
#include "ArbreQuat.h"

//menu
int main (int argc, char* argv[]){

	if(argc != 3){
		printf("Erreur format main\n");
		return 1;
	}

	char* nomfichier = strdup(argv[1]);
	int num_methode = atoi (argv[2]); //numero de la methode choisie


	FILE* f = fopen(nomfichier, "r");
	Chaines* C = lectureChaine(f);
	fclose(f);


	switch (num_methode){
			case 0:
				break;

			case 1:
				printf("Methode 1 : liste chainee\n");

				//printf("--------reconstitueReseauListe\n");
				Reseau* R = reconstitueReseauListe(C);
				//printf("--------fin : reconstitueReseauListe\n");
				//afficher_reseau(R);

				afficheReseauSVG(R, "reseauSVG");

				FILE* f2 = fopen("Reseau.txt", "w");
				ecrireReseauTxt(R, f2);
				fclose(f2);
				break;

			case 2:
				printf("Methode 2 : table de hachage\n");
				recreeReseauHachage(C);
				printf("reseau recree\n");
				break;

			case 3:
				printf("Methode 3 : Arbre\n");
				Reseau* R1 = recreeReseauArbre(C);
				afficheReseauSVG(R1, "reseauSVG");
				FILE* f3 = fopen("Reseau.txt", "w");
				ecrireReseauTxt(R1, f3);
				fclose(f3);
				break;

			default:
				printf("Choix de methode invalide\n");
				break;
	}

	return 0;
}
