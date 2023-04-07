#include "menu.h"

/**
 * stampaLogo()
 *
 * DESCRIZIONE
 * Si occupa di stampare a video il logo della battaglia navale
 *
 * INPUT
 *
 * OUTPUT
 *
 * LAVORO
 *
 */

void stampaLogo(){
	printf(RED);
	centra("    ____   ___   ______ ______ ___    ______ __     ____ ___         _   __ ___  _    __ ___     __     ______\n");
	centra("   / __ ) /   | /_  __//_  __//   |  / ____// /    /  _//   |       / | / //   || |  / //   |   / /    / ____/\n");
	centra("  / __  |/ /| |  / /    / /  / /| | / / __ / /     / / / /| |      /  |/ // /| || | / // /| |  / /    / __/   \n");
	printf(BLUE);
	centra(" / /_/ // ___ | / /    / /  / ___ |/ /_/ // /___ _/ / / ___ |     / /|  // ___ || |/ // ___ | / /___ / /___   \n");
	centra("/_____//_/  |_|/_/    /_/  /_/  |_|\\____//_____//___//_/  |_|    /_/ |_//_/  |_||___//_/  |_|/_____//_____/   \n");
	printf(RESET);
	printf("\n");
}

/**
 * stampareMenuPrincipale()
 *
 * DESCRIZIONE
 * Stampa a video il menu principale interattivo e ritorna la scelta dell'utente
 *
 * INPUT
 *
 * OUTPUT
 * Scelta – indica l’opzione che è stata scelta nel menu – numerico – 1<=intero<=4
 *
 * LAVORO
 * Rip – indica se devo ristampare il menu – booleano – FALSO=non ristampare, VERO=ristampa
 * Tasto – serve a contenere il valore del tasto premuto - carattere
 */

int stampareMenuPrincipale(){
	int scelta, rip;
	char tasto;
	scelta=1;
	rip=VERO;
	do{
		system("cls");  //pulisco console
		stampaLogo();
		if(scelta==1){
			printf(YELLOW);
			centra(">New Game<\0");
			printf(RESET);
		}else{
			centra("New Game\0");
		}
		printf("\n");

		if(scelta==2){
			printf(YELLOW);
			centra(">Load<\0");
			printf(RESET);
		}else{
			centra("Load\0");
		}
		printf("\n");

		if(scelta==3){
			printf(YELLOW);
			centra(">Help<\0");
			printf(RESET);
		}else{
			centra("Help\0");
		}
		printf("\n");

		if(scelta==4){
			printf(YELLOW);
			centra(">Exit<\0");
			printf(RESET);
		}else{
			centra("Exit\0");
		}
		printf("\n");

		do{  //aspetto un input adatto a muovere il cursore
			tasto=getch();
			tasto=toUpperCase(tasto);
			fflush(stdin);
		}while(tasto!=T_SU && tasto!=T_GIU && tasto!=INVIO && tasto!='W' && tasto!='S');

		if(tasto==T_SU || tasto=='W'){
			scelta--;
			if(scelta<1){
				scelta=4;
			}
		}

		if(tasto==T_GIU || tasto=='S'){
			scelta++;
			if(scelta>4){
				scelta=1;
			}
		}

		if(tasto==INVIO){
			rip=FALSO;
		}

	}while(rip==VERO);
	return scelta;
}

/**
 * Centra()
 *
 * DESCRIZIONE
 * Data una stringa la stampa a video al centro della console
 *
 * INPUT
 * Str – stringa da stampare al centro della console - stringa
 *
 * OUTPUT
 *
 * LAVORO
 * Len – indica la lunghezza di str – numerico – intero>=0
 * I – indice per contare gli spazi stampati – numerico – intero>0
 *
 */

void centra(stringa str){
	int len;
	len=leggereDimensioneStringa(str);
	stampaCaratteri(' ', (LUNGHEZZARIGA-len)/2);
	printf("%s", str);
}
