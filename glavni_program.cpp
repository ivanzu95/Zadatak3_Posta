#include <iostream>
#include <ctime>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <unistd.h>
#include <iomanip>
#include "red_pokazivac.h"
//#include "red_polje.h"

using namespace std;

//funkcija za generiranje prezimena i imena
void gen_prez_ime (tosoba &osoba) {
	char velika [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char mala [] = "abcdefghijklmnopqrstuvwxyz";
	osoba.ime[0] = velika[rand() % (sizeof(velika)-1)];
	for (int i = 1; i < 7; i++) {
		osoba.ime[i] = mala[rand() % (sizeof(mala)-1)];
	}
	osoba.ime[7] = 0;
	
	osoba.prezime[0] = velika[rand() % (sizeof(velika)-1)];
	for (int i = 1; i < 7; i++) {
		osoba.prezime[i] = mala[rand() % (sizeof(mala)-1)];
	}
	osoba.prezime[7] = 0;
}

//funkcija za generiranje spola
char gen_spol () {
	char spol;
	char znakovi [] = "mz";
	spol = znakovi[rand() % (sizeof(znakovi)-1)];
	return spol;
}

//funkcija za generiranje datuma rodjenja
void gen_datum (tosoba &osoba) {
	osoba.datumrod[2] = rand() % 83 + 1914;
	osoba.datumrod[1] = rand () % 12 + 1;
	if (osoba.datumrod[1] == 2)
		osoba.datumrod[0] = rand () % 29 + 1;
	else {
		if (osoba.datumrod[1] % 2 == 0 && osoba.datumrod[1] < 8)
			osoba.datumrod[0] = rand () % 30 + 1;
		if (osoba.datumrod[1] % 2 == 0 && osoba.datumrod[1] >= 8)
			osoba.datumrod[0] = rand () % 31 + 1;
		if (osoba.datumrod[1] % 2 != 0 && osoba.datumrod[1] < 8)
			osoba.datumrod[0] = rand () % 31 + 1;
		if (osoba.datumrod[1] % 2 != 0 && osoba.datumrod[1] > 8)
			osoba.datumrod[0] = rand () % 30 + 1;
	}
	if (osoba.ostalo.ci == 4)
		osoba.datumrod[2] = rand() % 55 + 1914;
	if(osoba.ostalo.ci == 3)
		osoba.datumrod[2] = rand() % 84 + 1914;
}

const char separator    = ' ';
template<typename T> void printElement(T t, const int& width)
{
    cout << left << setw(width) << setfill(separator) << t;
}

//funkcija koja prikazuje trnutno stanje reda u cekanju (tabelarno)
void stanje_reda(tred *red) {
    const int nameWidth     = 17;
    const int numWidth      = 4;
	int brojac = 0;
	tosoba osoba;
	tred *pom_red = new tred;
	initQ(pom_red);
	if (isEmptyQ(red)) {
		cout << "Red je prazan" << endl;
		return;	
	}
	cout << endl << endl;
	cout << left << setw(numWidth) << setfill(separator) << "Br.";
	cout << left << setw(nameWidth) << setfill(separator) << "Ime_Prez";
	cout << left << setw(10) << setfill(separator) << "Dat_rodj";
	printElement("Sp",4);
	cout << left << setw(nameWidth) << setfill(separator) << "Prioritet";
	cout << left << setw(10) << setfill(separator) << "Usluga";
	cout << left << setw(10) << setfill(separator) << "Vrijeme_dolaska";
	cout << endl;
	cout << left << setw(numWidth) << setfill(separator) << "---";
	cout << left << setw(nameWidth) << setfill(separator) << "--------";
	cout << left << setw(10) << setfill(separator) << "--------";
	printElement("--",4);
	cout << left << setw(nameWidth) << setfill(separator) << "---------";
	cout << left << setw(10) << setfill(separator) << "------";
	cout << left << setw(10) << setfill(separator) << "----------------";
	cout << endl;
	while(!isEmptyQ(red)) {
		osoba = frontQ(red);
		printElement(++brojac, numWidth);
		char prezime[40] ="";
		strcat(prezime,osoba.prezime);
		strcat(prezime, "_");
		strcat(prezime,osoba.ime);
		char datum[40] = "";
		char buffer[40];
		strcat(datum,itoa(osoba.datumrod[0],buffer,10));
		strcat(datum,".");
		strcat(datum,itoa(osoba.datumrod[1],buffer,10));
		strcat(datum,".");
		strcat(datum,itoa(osoba.datumrod[2],buffer,10));
		cout << left << setw(nameWidth) << setfill(separator) << prezime;
		cout << left << setw(12) << setfill(separator) << datum;
		printElement(osoba.spol,2);
		if (osoba.ostalo.ci == 1)
			cout << left << setw(nameWidth) << setfill(separator) << "1(VIP klijent)";
		if(osoba.ostalo.ci == 2)
			cout << left << setw(nameWidth) << setfill(separator) << "2(invalid)";
		if(osoba.ostalo.ci == 3)
			cout << left << setw(nameWidth) << setfill(separator) << "3(trudnica)";
		if(osoba.ostalo.ci == 4)
			cout << left << setw(nameWidth) << setfill(separator) << "4(umirovljenik)";
		if(osoba.ostalo.ci == 5)
			cout << left << setw(nameWidth) << setfill(separator) << "5(ostali)";
		if(osoba.ostalo.di == 1)
			cout << left << setw(nameWidth) << setfill(separator) << "Posiljka";
		if(osoba.ostalo.di == 2)
			cout << left << setw(nameWidth) << setfill(separator) << "Placanje racuna";
		if(osoba.ostalo.di == 3)
			cout << left << setw(nameWidth) << setfill(separator) << "Uplata lutrije";
		if(osoba.ostalo.di == 4)
			cout << left << setw(nameWidth) << setfill(separator) << "Western Union";
		if(osoba.ostalo.di == 5)
			cout << left << setw(nameWidth) << setfill(separator) << "EvoTV";
		char vrijeme1[40] = "";
		strcat(vrijeme1,itoa((osoba.vrijeme_dolaska/3600) % 24+ 0,buffer,10));
		strcat(vrijeme1,":");
		strcat(vrijeme1,itoa((osoba.vrijeme_dolaska / 60) % 60,buffer,10));
		cout << left << setw(7) << setfill(separator) << vrijeme1;
		cout << left << setw(nameWidth) << setfill(separator) << (osoba.ostalo.bi);
		cout << endl;
		enQueue(osoba,pom_red);
		deQueue(red);
		/*if (brojac % 15 == 0){
			cout << "ENTER ZA NASTAVAK ISPISA (ispisuje se po 15 klijenata)" << endl;
			getch();
			system("cls");
		}*/
	}
	
	cout << "ENTER ZA NASTAVAK" << endl;
	getch();
	system("cls");
	cout << "Ukupan broj osoba u redu: " << brojac << endl;
	while(!isEmptyQ(pom_red)) {
		osoba = frontQ(pom_red);
		enQueue(osoba,red);
		deQueue(pom_red);
	}
	delete pom_red;
}

//funkcija za ispis podataka samo jednog klijenta banke
void isklijent (tosoba &osoba) {
	cout << "---------------------------------------------" << endl;
	cout << "Prezime i ime: " << osoba.prezime << " " << osoba.ime << endl;
	cout << "Datum rodjenja: " << osoba.datumrod[0] << "." << osoba.datumrod[1] << "." << osoba.datumrod[2] << endl;
	cout << "Spol klijenta: " << osoba.spol << endl;
	cout << "Prioritet klijenta: ";
	if (osoba.ostalo.ci == 1)
		cout << "1 (VIP klijent)" << endl;
	if(osoba.ostalo.ci == 2)
		cout << "2 (invalid)" << endl;
	if(osoba.ostalo.ci == 3)
		cout << "3 (trudnica)" << endl;
	if(osoba.ostalo.ci == 4)
		cout << "4 (umirovljenik)" << endl;
	if(osoba.ostalo.ci == 5)
		cout << "5 (ostali klijent)" << endl;
	cout << "Potrebna usluga: ";
	if(osoba.ostalo.di == 1)
		cout << "Predaja/Preuzimanje posiljke" << endl;
	if(osoba.ostalo.di == 2)
		cout << "Placanje racuna" << endl;
	if(osoba.ostalo.di == 3)
		cout << "Uplata lutrije" << endl;
	if(osoba.ostalo.di == 4)
		cout << "Western Union" << endl;
	if(osoba.ostalo.di == 5)
		cout << "EvoTV" << endl;
	cout << "Vrijeme dolaska: " << (osoba.vrijeme_dolaska/3600) % 24 + 0 << ":" << (osoba.vrijeme_dolaska / 60) % 60 << endl;
	cout << "Trajanje usluge: " << (osoba.ostalo.bi) << "s " << endl;
	return;
}

//generairanje cetvorki, tj.podataka koji se odnose na klijente poste
void zadatak1 (cetvorka *polje, int n) {
	for (int i = 0; i < n; i++) {
		polje[i].ai = rand() % 500 + 10;
		polje[i].bi = rand() % 800 + 80;
		polje[i].ci = 1 + rand() % 5;
		polje[i].di = 1 + rand() % 5;
	}
}

//generiranje klijenata poste + paralelna simulacija
void zadatak2 (cetvorka *polje, int n, tred *red) {
	system("cls");
	int osobe_ul= 0, osobe_iz = 0, vrijeme2 = 0, vrijeme = 0, zavrseno = 0;
	
	tred *pom_red1 = new tred;
	tred *pom_red2 = new tred;
	initQ(pom_red1);
	initQ(pom_red2);
	tosoba osoba;
	tosoba osoba_salter,osoba_celo;
	
	for (int i = 0; i < n; i++) {
		osoba.ostalo.ai = polje[i].ai;
		osoba.ostalo.bi = polje[i].bi;
		osoba.ostalo.ci = polje[i].ci;
		osoba.ostalo.di = polje[i].di;
		gen_prez_ime(osoba);
		gen_datum(osoba);
		if(polje[i].ci == 3)
			osoba.spol = 'z';
		else
			osoba.spol = gen_spol();
		vrijeme += polje[i].ai; //vrijeme dolaska u postu
		osoba.vrijeme_dolaska = vrijeme;
		//zavrseno = vrijeme + osoba.ostalo.bi;
		//osoba.vrijeme_zavrsi = zavrseno;
		
		//pokazuje koja osoba ulazi trenutno u postu
		cout << "ULAZI OSOBA " << ++osobe_ul << endl;
		isklijent(osoba);
		cout << endl;
		
		if (i == 0)	//korekcija vremena zavrsetka usluge za prvog klijenta
			vrijeme2 += (polje[i].ai + polje[i].bi);
			
		if(i >= 0 && i < 2) { //ako su usle 2 osobe za redom, ne treba paziti na prioritet
			enQueue(osoba,red);
		}
			
		if (i >= 2) { //pazi na prioritet ako je osoba usla u red
			osoba_salter = frontQ(red);
			deQueue(red);
			//vrijeme2 = osoba_salter.vrijeme_zavrsi;
			
			if (osoba.vrijeme_dolaska >= vrijeme2){ //ukoliko je osoba na salteru zavrsila sa uslugom koju treba, vadi je van, a na salter postavljaj sljedeceg u redu
				//pokazuje koja osoba trenutno izlazi iz poste
				cout << "IZLAZI OSOBA " << ++osobe_iz << endl;
				isklijent(osoba_salter);
				cout << "Vrijeme zavrsetka usluge: " << (vrijeme2/3600)%24+0 << ":" << (vrijeme2/60) % 60 << endl;
				cout << endl << endl;
				osoba_salter=frontQ(red);
				vrijeme2 += osoba_salter.ostalo.bi;
				if(!isEmptyQ(red))
					deQueue(red);
			}
			
			//korekcija reda ukoliko je u postu usla osoba sa vecim prioritetom
			while (!isEmptyQ(red)) {
				osoba_celo = frontQ(red);
				if(osoba_celo.ostalo.ci <= osoba.ostalo.ci)
					enQueue(osoba_celo,pom_red1);
				else
					enQueue(osoba_celo,pom_red2);
				deQueue(red);
			}
		
			tosoba pom = osoba_salter;
			enQueue(osoba_salter,red); //osoba na salteru ostaje u redu (ona je dio reda)
			while (!isEmptyQ(pom_red1)) { //osobe veceg ili jednkog prioriteta od osoba koje je trenutno dosla
				pom = frontQ(pom_red1);
				enQueue(pom,red);
				deQueue(pom_red1);
			}
			enQueue(osoba,red); //osoba koja je trenutno dosla dolazi na svoju poziciju u red
			while (!isEmptyQ(pom_red2)) { //osobe koje su manjeg prioriteta od osobe koja je trenutno dosla
				pom = frontQ(pom_red2);
				enQueue(pom,red);
				deQueue(pom_red2);
			}
			
		}
		//sleep(1);
	}
	
	//ispis osoba mlađih od 40 godina sa hor.znakom jarac (potrebno je unijeti veci broj korisnika da bi se ispunio uvjet)
	int br_jrc = 0;
	system("cls");
	cout << "Ispis osoba starijih od 40 godina sa hor.znakom jarac" << endl;
	cout << "-----------------------------------------------------" << endl;
	while (!isEmptyQ(red)) {
		osoba = frontQ(red);
		enQueue(osoba,pom_red1);
		if (osoba.datumrod[2] >= 1974 && 
			(osoba.datumrod[1] == 12 && (osoba.datumrod[0]>=20 && osoba.datumrod[0]<=31) || 
			(osoba.datumrod[1] == 1 && osoba.datumrod[0]>=1 && osoba.datumrod[0]<=20)) && 
			 osoba.ostalo.di == 3) {
				isklijent(osoba);
				br_jrc++;
			}
		deQueue(red);
	}
	cout << "Ukupan broj osoba mladjih od 40 godina(jarac) i  cekaju na uplatu: " << br_jrc << endl;
	
	//osiguranje da je novonastali red nepromijenjen
	while (!isEmptyQ(pom_red1)) {
		osoba = frontQ(pom_red1);
		enQueue(osoba,red);
		deQueue(pom_red1);
	}
	
	delete pom_red1;
	delete pom_red2;
}

//izlaze sve trudnice + EvoTV usluga
void zadatak3(tred *red) {
	int br_osoba = 0;
	tred *pom_red = new tred;
	initQ(pom_red);
	tosoba osoba;
	while(!isEmptyQ(red)) {
		osoba = frontQ(red);
		if(osoba.ostalo.ci == 3 && osoba.ostalo.di == 5) {
			cout << endl;
			cout << "Izasla je osoba " << ++br_osoba << ":" << endl;
			isklijent(osoba);
			deQueue(red);
		}
		else {
			enQueue(osoba,pom_red);
			deQueue(red);
		}
	}
	
	//red nakon izlaska trudnica ostao nepromijenjen
	while (!isEmptyQ(pom_red)) {
		osoba = frontQ(pom_red);
		enQueue(osoba,red);
		deQueue(pom_red);
	}
	
	delete pom_red;
}

//rekurzijom raspodijeli glavni red n 5 usluznih i 1 brzi
void rek_svi(tred *red, tred *red2, tred *red3, tred *red4, tred *red5) {
	tosoba osoba;
	if (isEmptyQ(red))
		return;
	osoba = frontQ(red);
	deQueue(red);
	rek_svi(red,red2,red3,red4,red5);
	if (osoba.ostalo.di == 5) {
		enQueue(osoba,red5);
	}
	if(osoba.ostalo.di == 4) {
		enQueue(osoba,red4);
	}
	if(osoba.ostalo.di == 3) {
		enQueue(osoba,red3);
	}
	if(osoba.ostalo.di == 2) {
		enQueue(osoba,red2);
	}
	if(osoba.ostalo.di == 1) {
		enQueue(osoba,red);
	}
}

//rekurzijom korigiraj da red bude neporimijenjen
void rek_red(tred *red) {
	tosoba osoba;
	if (isEmptyQ(red))
		return;
	osoba = frontQ(red);
	deQueue(red);
	rek_red(red);
	enQueue(osoba,red);
}

void rek_brzi(tred *red, tred *brzi) {
	static int br = 0;
	if (br = 2)
		br = 0;
	if (isEmptyQ(red))
		return;
	tosoba osoba = frontQ(red);
	deQueue(red);
	rek_brzi(red,brzi);
	if (osoba.ostalo.ci == 4)
		enQueue(osoba,brzi);
	else {
		if (br < 2) {
			enQueue(osoba,brzi);
			br++;
		}
		else {
			enQueue(osoba,red);
	}
	}
}

//od glavnoga reda napravi 5 usluznih i jedan brzi
void zadatak4(tred *red) {
	tred *red2 = new tred;
	tred *red3 = new tred;
	tred *red4 = new tred;
	tred *red5 = new tred;
	tred *brzi = new tred;
	initQ(red2);
	initQ(red3);
	initQ(red4);
	initQ(red5);
	initQ(red5);
	initQ(brzi);
	
	rek_svi(red,red2,red3,red4,red5);
	rek_brzi(red5,brzi);
	rek_brzi(red4,brzi);
	rek_brzi(red3,brzi);
	rek_brzi(red2,brzi);
	rek_brzi(red,brzi);
	
	cout << "Stanje reda 1 (glavni red) " << endl;
	stanje_reda(red);
	cout << "Stanje reda 2 " << endl;
	stanje_reda(red2);
	cout << "Stanje reda 3 " << endl;
	stanje_reda(red3);
	cout << "Stanje reda 4 " << endl;
	stanje_reda(red4);
	cout << "Stanje reda 5 " << endl;
	stanje_reda(red5);
	cout << "Stanje brzog reda " << endl;
	stanje_reda(brzi);
}

//main
int main() {
	cetvorka *polje;
	initQ(red);
	srand(time(0));
	int n;
	int izbor;
	do {
		system("cls");
		cout << "***********************************IZBORNIK***********************************" << endl;
		cout << "1. Generiranje N cetvorki" << endl;
		cout << "2. Dodavanje zapisa o klijentima u red (+ paralelna simulacija)" << endl;
		cout << "3. Stanje reda" << endl;
		cout << "4. Izlazak svih trudnica iz reda sa EvoTV uslugom" << endl;
		cout << "5. Brza linija (umirovljenici + 2 osobe sa cela svakog reda)" << endl;
		cout << "9. Izlaz iz programa" << endl;
		cout << "******************************************************************************" << endl;
		cout << "Unesite mogucnost: ";
		cin >> izbor;
		switch(izbor) {
			case 1:
				cout << "Koliko klijenata zelite dodati u simulaciju: ";
				cin >> n;
				polje = new cetvorka[n];
				zadatak1(polje, n);
				cout << "Cetvorke uspjesno generirane. ENTER - nastavak!!!" << endl;
				getch();
				break;
			
			case 2:
				zadatak2(polje,n,red);
				cout << "ENTER ZA NASTAVAK" << endl;
				getch();
				break;
			
			case 3:
				stanje_reda(red);
				cout << "ENTER ZA NASTAVAK" << endl;
				getch();
				break;
				
			case 4:
				zadatak3(red);
				getch();
				system("cls");
				stanje_reda(red);
				cout << "ENTER ZA NASTAVAK" << endl;
				getch();
				break;
				
			case 5:
				zadatak4(red);
				getch();
				break;
				
		}
	} while (izbor != 9);
	
	return 0;
}
