CFLAGS = -Wall -g

all : ChainMain ReconstitueReseau

entree_sortie.o : entree_sortie.h entree_sortie.c
	gcc ${CFLAGS} -c entree_sortie.c

Chaine.o : Chaine.c Chaine.h entree_sortie.h
	gcc ${CFLAGS} -c Chaine.c

ChainMain.o : ChainMain.c entree_sortie.h Chaine.h
	gcc ${CFLAGS} -c main.c

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc ${CFLAGS} -c SVGwriter.c

Reseau.o : Reseau.h Reseau.c Chaine.h Chaine.o entree_sortie.o
	gcc ${CFLAGS} -c Reseau.c

ReconstitueReseau.o : ReconstitueReseau.c entree_sortie.h Chaine.h Reseau.h
	gcc ${CFLAGS} -c ReconstitueReseau.c




ChainMain : ChainMain.c Chaine.o entree_sortie.o entree_sortie.h Chaine.h SVGwriter.o SVGwriter.h
	gcc ${CFLAGS} -lm -o ChainMain ChainMain.c Chaine.o entree_sortie.o SVGwriter.o

ReconstitueReseau : ReconstitueReseau.c ReconstitueReseau.o entree_sortie.o Chaine.o Reseau.o SVGwriter.o
	gcc ${CFLAGS} -lm -o ReconstitueReseau ReconstitueReseau.c entree_sortie.o Reseau.o Chaine.o SVGwriter.o


clean :
	rm -f *.o ChainMain ReconstitueReseau
