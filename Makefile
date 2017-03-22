CFLAGS = -Wall -g

all : ChainMain ReconstitueReseau

entree_sortie.o : entree_sortie.h entree_sortie.c
	gcc ${CFLAGS} -lm -c entree_sortie.c

Chaine.o : Chaine.c Chaine.h entree_sortie.h
	gcc ${CFLAGS} -lm -c Chaine.c

ChainMain.o : ChainMain.c entree_sortie.h Chaine.h
	gcc ${CFLAGS} -lm -c main.c

SVGwriter.o: SVGwriter.c SVGwriter.h
	gcc ${CFLAGS} -lm -c SVGwriter.c

Reseau.o : Reseau.h Reseau.c Chaine.h Chaine.o entree_sortie.o
	gcc ${CFLAGS} -lm -c Reseau.c

ReconstitueReseau.o : ReconstitueReseau.c entree_sortie.h Chaine.h Reseau.h
	gcc ${CFLAGS} -lm -c ReconstitueReseau.c

Hachage.o : Hachage.h Hachage.c
	gcc ${CFLAGS} -lm -c Hachage.c

ArbreQuat.o : ArbreQuat.h ArbreQuat.c
	gcc ${CFLAGS} -lm -c ArbreQuat.c


ChainMain : ChainMain.c Chaine.o entree_sortie.o SVGwriter.o
	gcc ${CFLAGS} -o ChainMain ChainMain.c Chaine.o entree_sortie.o SVGwriter.o -lm

ReconstitueReseau : ReconstitueReseau.c ReconstitueReseau.o entree_sortie.o Chaine.o Reseau.o SVGwriter.o Hachage.o ArbreQuat.o
	gcc ${CFLAGS} -o ReconstitueReseau ReconstitueReseau.c entree_sortie.o Reseau.o Chaine.o SVGwriter.o Hachage.o	ArbreQuat.o -lm


clean :
	rm -f *.o ChainMain ReconstitueReseau reseauSVG.html reseau.txt
