/*
 ===================================================================================================
 Name        : Battleship Project
 Group		 : 24
 Author      : Cirilli Davide
 Description : Progetto d'esame per "Laboratorio di Informatica".
 	 	 	   Gioco della Battaglia Navale su console testuale, con regole e dinamiche modificate e migliorate.
 Note		 : Per quanto riguarda il modulo help è necessario copiare e incollare il file "Regole.txt" nel percorso "C:\Battleship".
 	 	 	   Suddetto percorso verrà generato automaticamente alla prima esecuzione del codice
 ===================================================================================================
*/

#include "Global\global.h"
#include "Giocatore\giocatore.h"
#include "Menu\menu.h"
#include "New Game\newGame.h"
#include "Load\load.h"
#include "Help\help.h"
#include "Play\play.h"

/**
 * main()
 *
 * DESCRIZIONE
 * Funzione main del programma, si occupa di visualizzare il menu principale, eseguire l'opzione scelta ed eventualmente di visualizzare il vincitore
 *
 * INPUT
 *
 * OUTPUT
 *
 * LAVORO
 * Scelta – opzione scelta nel menu principale – numerico – 1<=intero<=4
 * Rip – indica se devo ristampare il menu (dopo help) – booleano – FALSO=non ripetere, VERO=ripeti
 * P – giocatori che giocheranno la partita – array monodimensionale di giocatori statico
 * Esci – indica se è stata scelta l’opzione “esci” – booleano – FALSO=non esci, VERO=esci
 * Vincitore – indica il giocatore che ha vinto la partita (-1 se partita non completa) – numerico – intero
 * Nome – nome del giocatore che ha vinto la partita - stringa
 */

int main() {
	int scelta, rip, esci, vincitore=-1;
	stringa nome;
	giocatore p[2];
	system("title Battleship Project"); //modificareTitolo()
	system("mkdir C:\\BattleShip\\Salvataggi"); // creareCartella()
	nome=inizializzareStringa(LUNGHEZZANOME);
	inizializzareNome(&p[0]);
	inizializzareNome(&p[1]);
	esci=FALSO;
	do{
		rip=FALSO;
		scelta=stampareMenuPrincipale();
		if(scelta==1){
			inserimentoDati(p);  //inserimento da console da parte dell'utente
		}
		if(scelta==2){
			aperturaFileSalvataggio(p);  //trovo e apro il file di salvataggio da cui recuperare i dati
		}
		if(scelta==3){
			stampareHelp();
			rip=VERO;
		}
		if(scelta==4){
			esci=VERO;
		}
		if(leggereTurno(p[0])==-1 || rip==VERO){  //devo ripetere il menu (causa errori apertura file o help)
			printf("Premere un qualsiasi tasto per tornare al menu...");
			fflush(stdin);
			getchar();
		}
	}while(leggereTurno(p[0])==-1 || rip==VERO);  //finchè non ci sono più errori
	//sono sicuro di avere tutti i dati necessari alla partita
	if(esci==FALSO){
		vincitore=gioca(p);
	}
	if(vincitore!=-1){
		system("cls");
		leggereNome(p[vincitore], nome);
		printf("Ha vinto ");
		if(vincitore==0){
			printf(RED);
		}else{
			printf(BLUE);
		}
		printf("%s!!!\n", nome);
		printf(RESET);
		system("pause");
	}
	deinizializzareNome(&p[0]);
	deinizializzareNome(&p[1]);
}
