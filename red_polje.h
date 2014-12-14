#ifndef red_polje
#define red_polje

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

struct tred {
	tosoba elementi[10000];
	int front, rear;	
};
tred *red = new tred;

int AddOne(int n) { //dodatna funkcija za rad sa pokazivacima front i rear
	return ((n+1)%10000);	
}

void initQ (tred *red) { //inicijalizacija reda
	red->front = 0;
	red->rear = 0;
}

int isEmptyQ (tred *red) { //provjera je li red prazan
	if (red->rear == red->front)
		return 1;
	return 0;
}

tosoba frontQ (tred *red) {
	if (isEmptyQ(red) == 0)
		return red->elementi[red->front];	
}

int enQueue (tosoba elem, tred *red) {
	if (AddOne(red->rear) == red->front)
		return 0; //ako je red pun ne postavljaj novi element
	red->elementi[red->rear] = elem;
	red->rear = AddOne(red->rear);
	return 1;
}

int deQueue (tred *red) {
	if (isEmptyQ(red) == 1)
		return 0;
	red->front = AddOne(red->front);
	return 1;
}

#endif
