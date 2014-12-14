#ifndef red_pokazivac
#define red_pokazivac

#include <iostream>
using namespace std;

struct cetvorka {
	int ai, bi, ci, di;
};

struct tosoba {
	char ime[40];
	char prezime[40];
	int datumrod[3];
	char spol;
	int vrijeme_dolaska;
	int vrijeme_zavrsi;
	cetvorka ostalo;
};

struct tlista {
	tosoba elementi;
	tlista *sljedeci;	
};

struct tred {
	tlista *front, *rear;
};
tred *red = new tred;

void initQ (tred *red) { //inicijalizacija reda + liste
	tlista *lista = new tlista;
	lista->sljedeci = NULL;
	red->front = lista;
	red->rear = lista;
}

int isEmptyQ(tred *red) { //provjera je li red prazan
	if (red->rear == red->front)
		return 1;
	return 0;
}

tosoba frontQ (tred *red) { //vracanje vrijednosti sa pocetka reda
	if (isEmptyQ(red) == 0)
		return red->front->sljedeci->elementi;
}

int enQueue (tosoba elem, tred *red) { //postavljanje elementa na kraj reda
	tlista *novi = new tlista;
	novi->elementi = elem; //alociranje novog elementa
	novi->sljedeci = NULL;
	(red->rear)->sljedeci = novi; //povezivanje zadnjeg elementa u redu sa novim
	red->rear = novi; //novi elemt postaje zadnji u redu
	return 1;
}

int deQueue (tred *red) { //brisanje elementa sa pocetka reda
	if (isEmptyQ(red) == 1) //ako je red prazan nemas sta brisat
		return 0;
	tlista *prvi;
	prvi = red->front; //glava liste
	red->front = (red->front)->sljedeci; //nova glava liste postaje element na koji pokazuje glava
	delete prvi; //brise se stara glava liste
	return 1;
}

#endif
