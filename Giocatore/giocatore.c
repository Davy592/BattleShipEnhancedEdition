#include "giocatore.h"
#include "..\Global\global.h"

//Funzioni d'accesso di giocatore

/**
 * leggereTurno()
 *
 * DESCRIZIONE
 * Restituisce i turni attualmente giocati di un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere il turno - giocatore
 *
 * OUTPUT
 * t - turno di p - numerico - intero>=0
 *
 * LAVORO
 *
 */

int leggereTurno(giocatore p){
	int t;
	t=p.turno;
	return t;
}

/**
 * leggereNome()
 *
 * DESCRIZIONE
 * Restituisce il nome di un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere il nome – giocatore
 * n – stringa in cui inserire il nome del giocatore letto - stringa
 *
 * OUTPUT
 * n - nome del giocatore letto - stringa
 *
 * LAVORO
 *
 */

void leggereNome(giocatore p, stringa n){
	copiareStringa(n, p.nome);
}

/**
 * leggereValoreAttacco()
 *
 * DESCRIZIONE
 * Restituisce il valore di una cella della tabella d'attacco di un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere un valore della tabella d'attacco – giocatore
 * y – colonna del valore da leggere – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 * x – riga del carattere da leggere – numerico – MIN_ROWS<=intero<=MAX_ROWS
 *
 * OUTPUT
 * c – valore letto dalla tabella d’attacco del giocatore – carattere
 *
 * LAVORO
 *
 */

char leggereValoreAttacco(giocatore p, char y, int x){
	char c;
	c=p.attacco[x-1][upperCaseToInt(y)-1];  //(-1) perche in C i vettori partono da 0.
	return c;
}

/**
 * leggereValoreDifesa()
 *
 * DESCRIZIONE
 * Restituisce il valore di una cella della tabella di difesa di un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere un valore della tabella di difesa – giocatore
 * y – colonna del valore da leggere – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 * x – riga del carattere da leggere – numerico – MIN_ROWS<=intero<=MAX_ROWS
 *
 * OUTPUT
 * c – valore letto dalla tabella di difesa del giocatore – carattere
 *
 * LAVORO
 *
 */

char leggereValoreDifesa(giocatore p, char y, int x){
	char c;
	c=p.difesa[x-1][upperCaseToInt(y)-1];  //(-1) perche in C i vettori partono da 0.
	return c;
}

/**
 * leggereValoreFlotta()
 *
 * DESCRIZIONE
 * Restituisce una nave appartenente alla flotta di un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere una nave della flotta - giocatore
 * x - posizione della nave da leggere - numerico – MIN_SHIP<=intero<=MAX_SHIP
 *
 * OUTPUT
 * n – x-esima nave della flotta di p – nave
 *
 * LAVORO
 *
 */

nave leggereValoreFlotta(giocatore p, int x){
	nave n;
	n=p.flotta[x-1];  //(-1) perche in C i vettori partono da 0.
	return n;
}

/**
 * leggereLargoRaggio()
 *
 * DESCRIZIONE
 * Restituisce il numero di colpi a largo raggio rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere il numero di colpi a largo raggio rimasti - giocatore
 *
 * OUTPUT
 * l - numero di colpi a largo raggio rimasti a p - numerico – MIN_LARGE<=intero<=MAX_LARGE
 *
 * LAVORO
 *
 */

int leggereLargoRaggio(giocatore p){
	int l;
	l=p.largoRaggio;
	return l;
}

/**
 * leggereBombardamento()
 *
 * DESCRIZIONE
 * Restituisce il numero di bombardamenti rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere il numero di bombardamenti rimasti - giocatore
 *
 * OUTPUT
 * b - numero di bombardamenti rimasti a p - numerico – MIN_BOMB<=intero<=MAX_BOMB
 *
 * LAVORO
 *
 */

int leggereBombardamento(giocatore p){
	int b;
	b=p.bombardamento;
	return b;
}

/**
 * leggereRadar()
 *
 * DESCRIZIONE
 * Restituisce il numero di utilizzi del radar rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui leggere il numero di radar rimasti - giocatore
 *
 * OUTPUT
 * r - numero di radar rimasti a p - numerico – MIN_RADAR<=intero<=MAX_RADAR
 *
 * LAVORO
 *
 */

int leggereRadar(giocatore p){
	int r;
	r=p.radar;
	return r;
}

/**
 * scrivereTurno()
 *
 * DESCRIZIONE
 * Modifica il numero di turni attualmente giocati da un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare il turno - giocatore
 * t - nuovo turno di p - numerico - intero>=0
 *
 * OUTPUT
 * p - giocatore con il campo turno modificato - giocatore
 *
 * LAVORO
 *
 */

void scrivereTurno(giocatore *p, int t){
	p->turno=t;
}

/**
 * incrementareTurno()
 *
 * DESCRIZIONE
 * Incrementa (di 1) il numero di turni attualmente giocati da un giocatore
 *
 * INPUT
 * p - giocatore di cui incrementare il turno - giocatore
 *
 * OUTPUT
 * p - giocatore con il campo turno incrementato - giocatore
 *
 * LAVORO
 *
 */

void incrementareTurno(giocatore *p){
	scrivereTurno(p, leggereTurno(*p)+1);
}

/**
 * decrementareTurno()
 *
 * DESCRIZIONE
 * Decrementa (di 1) il numero di turni attualemnte giocati da un giocatore
 *
 * INPUT
 * p - giocatore di cui decrementare il turno - giocatore
 *
 * OUTPUT
 * p - giocatore con il campo turno decrementato - giocatore
 *
 * LAVORO
 *
 */

void decrementareTurno(giocatore *p){
	scrivereTurno(p, leggereTurno(*p)-1);
}

/**
 * inizializzareNome()
 *
 * DESCRIZIONE
 * Inizializza la memoria del campo nome di un giocatore per contenere una stringa
 *
 * INPUT
 * p - giocatore di cui inizializzare la memoria del campo nome - giocatore
 *
 * OUTPUT
 * p - giocatore con la memoria del campo nome inizializzata - giocatore
 *
 * LAVORO
 *
 */

void inizializzareNome(giocatore *p){
	p->nome=inizializzareStringa(LUNGHEZZANOME);
}

/**
 * deinizializzareNome()
 *
 * DESCRIZIONE
 * Libera la memoria del campo nome di un giocatore
 *
 * INPUT
 * p - giocatore di cui liberare la memoria del campo nome - giocatore
 *
 * OUTPUT
 * p - giocatore con la memoria del campo nome liberata - giocatore
 *
 * LAVORO
 *
 */

void deinizializzareNome(giocatore *p){
	deinizializzareStringa(p->nome);
}

/**
 * scrivereNome()
 *
 * DESCRIZIONE
 * Modifica il nome di un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare il nome - giocatore
 * str - nuovo nome di p – stringa
 *
 * OUTPUT
 * p - giocatore con il campo nome modificato – giocatore
 *
 * LAVORO
 *
 */

void scrivereNome(giocatore *p, stringa str){
	copiareStringa(p->nome, str);
}

/**
 * scrivereValoreDifesa()
 *
 * DESCRIZIONE
 * Modifica il valore di una cella della tabella di difesa di un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare un valore nella tabella di difesa – giocatore
 * y - colonna del valore da scrivere – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 * x - riga del valore da scrivere – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * c – valore da scrivere nella tabella di difesa di p - carattere
 *
 * OUTPUT
 * p - giocatore con un valore della tabella di difesa modificato – giocatore
 *
 * LAVORO
 *
 */

void scrivereValoreDifesa(giocatore *p, char y, int x, char c){
	p->difesa[x-1][upperCaseToInt(y)-1]=c;  //(-1) perche in C i vettori partono da 0.
}

/**
 * scrivereValoreAttacco()
 *
 * DESCRIZIONE
 * Modifica il valore di una cella della tabella d'attacco di un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare un valore nella tabella d’attacco – giocatore
 * y - colonna del valore da scrivere – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 * x - riga del valore da scrivere – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * c – valore da scrivere nella tabella d’attacco di p - carattere
 *
 * OUTPUT
 * p - giocatore con un valore della tabella di attacco modificato – giocatore
 *
 * LAVORO
 *
 */

void scrivereValoreAttacco(giocatore *p, char y, int x, char c){
	p->attacco[x-1][upperCaseToInt(y)-1]=c;  //(-1) perche in C i vettori partono da 0.
}

/**
 * scrivereValoreFlotta()
 *
 * DESCRIZIONE
 * Modifica una nave appartenente alla flotta di un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare una nave della flotta - giocatore
 * x - posizione della nave da modificare - numerico – MIN_SHIP<=intero<=MAX_SHIP
 * pos – nuova coordinata iniziale della nave - coordinata
 * verso – nuovo verso della nave – booleano – FALSO=orizzontale, VERO=verticale
 * hp – nuovo numero di celle della nave non ancora colpite – numerico – 0<=intero<=5
 *
 * OUTPUT
 * p - giocatore con x-esima nave modificata – giocatore
 *
 * LAVORO
 *
 */

void scrivereValoreFlotta(giocatore *p, int x, coordinata pos, int verso, int hp){
	scriverePos(&(p->flotta[x-1]), pos);  //(-1) perche in C i vettori partono da 0.
	scrivereVerso(&(p->flotta[x-1]), verso);  //(-1) perche in C i vettori partono da 0.
	scrivereHp(&(p->flotta[x-1]), hp);  //(-1) perche in C i vettori partono da 0.
}

/**
 * scrivereLargoRaggio()
 *
 * DESCRIZIONE
 * Modifica il numero di colpi a largo raggio rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare i colpi a largo raggio rimanenti- giocatore
 * l - nuovi colpi a largoRaggio rimanenti di p - numerico – MIN_LARGE<=intero<=MAX_LARGE
 *
 * OUTPUT
 * p - giocatore con il campo largoRaggio modificato – giocatore
 *
 * LAVORO
 *
 */

void scrivereLargoRaggio(giocatore *p, int l){
	p->largoRaggio=l;
}

/**
 * decrementareLargoRaggio()
 *
 * DESCRIZIONE
 * Decrementa (di 1) il numero di colpi a largo raggio rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui decrementare i colpi a largo raggio rimanenti - giocatore
 *
 * OUTPUT
 * p - giocatore con il campo largoRaggio decrementato- giocatore
 *
 * LAVORO
 *
 */

void decrementareLargoRaggio(giocatore *p){
	scrivereLargoRaggio(p, leggereLargoRaggio(*p)-1);
}

/**
 * scrivereBombardamento()
 *
 * DESCRIZIONE
 * Modifica il numero di bombardamenti rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare i bombardamenti rimanenti- giocatore
 * b - nuovi bombardamenti rimanenti di p - numerico – MIN_BOMB<=intero<=MAX_BOMB
 *
 * OUTPUT
 * p - giocatore con il campo bombardamento modificato – giocatore
 *
 * LAVORO
 *
 */

void scrivereBombardamento(giocatore *p, int b){
	p->bombardamento=b;
}

/**
 * decrementareBombardamento()
 *
 * DESCRIZIONE
 * Decrementa (di 1) il numero di bombardamenti rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui decrementare i bombardamenti rimanenti - giocatore
 *
 * OUTPUT
 * p - giocatore con il campo bombardamento decrementato- giocatore
 *
 * LAVORO
 *
 */

void decrementareBombardamento(giocatore *p){
	scrivereBombardamento(p, leggereBombardamento(*p)-1);
}

/**
 * scrivereRadar()
 *
 * DESCRIZIONE
 * Modifica il numero di utilizzi del radar rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui modificare i radar rimanenti- giocatore
 * r - nuovo radar rimanenti di p - numerico – MIN_RADAR<=intero<=MAX_RADAR
 *
 * OUTPUT
 * p - giocatore con il campo radar modificato – giocatore
 *
 * LAVORO
 *
 */

void scrivereRadar(giocatore *p, int r){
	p->radar=r;
}

/**
 * decrementareRadar()
 *
 * DESCRIZIONE
 * Decrementa (di 1) il numero di utilizzi del radar rimasti a un giocatore
 *
 * INPUT
 * p - giocatore di cui decrementare i radar - giocatore
 *
 * OUTPUT
 * p - giocatore con il campo radar decrementato- giocatore
 *
 * LAVORO
 *
 */

void decrementareRadar(giocatore *p){
	scrivereRadar(p, leggereRadar(*p)-1);
}

/**
 * decrementareHp()
 *
 * DESCRIZIONE
 * Decrementa (di 1) il numero di hp rimasti a una nave di un giocatore
 *
 * INPUT
 * p - giocatore di cui decrementare il numero di celle non ancora colpite di una nave - giocatore
 * x - posizione della nave di cui decrementare il numero di celle non ancora colpite - numerico – MIN_SHIP<=intero<=MAX_SHIP
 *
 * OUTPUT
 * p - giocatore con il numero di celle non ancora colpite della x-esima nave decrementato – giocatore
 *
 * LAVORO
 *
 */

void decrementareHp(giocatore *p, int x){
	scrivereValoreFlotta(p, x, leggerePos(leggereValoreFlotta(*p, x)), leggereVerso(leggereValoreFlotta(*p, x)), leggereHp(leggereValoreFlotta(*p, x))-1);
}

//Fine funzioni d'accesso

/**
 * riempireDifesa()
 *
 * DESCRIZIONE
 * Si occupa di riempire la tabella di difesa di un giocatore inserendo in tutte le celle lo stesso carattere
 *
 *
 * INPUT
 * P – giocatore di cui riempire la tabella di difesa – giocatore
 * C – carattere con cui riempire la tabella di difesa - carattere
 *
 * OUTPUT
 * P – giocatore con tabella di difesa riempita - giocatore
 *
 * LAVORO
 * X – indice per scandire le righe della tabella di difesa – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * Y – indice per scandire le colonne della tabella di difesa – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 */

void riempireDifesa(giocatore *p, char c){
	int x;
	char y;
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		x=MIN_ROWS;
		while(x<=MAX_ROWS){
			scrivereValoreDifesa(p, y, x, c);
			x++;
		}
		y=successivo(y);
	}
}

/**
 * riempireAttacco()
 * DESCRIZIONE
 * Si occupa di riempire la tabella di difesa di un giocatore inserendo in tutte le celle lo stesso carattere C ricevuto come parametro
 *
 * INPUT
 * P – giocatore di cui riempire la tabella d’attacco – giocatore
 * C – carattere con cui riempire la tabella d’attacco - carattere
 *
 * OUTPUT
 * P – giocatore con tabella d’attacco riempita - giocatore
 *
 * LAVORO
 * X – indice per scandire le righe della tabella d’attacco – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * Y – indice per scandire le colonne della tabella d’attacco – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN *
 */

void riempireAttacco(giocatore *p, char c){
	int x;
	char y;
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		x=MIN_ROWS;
		while(x<=MAX_ROWS){
			scrivereValoreAttacco(p, y, x, c);
			x++;
		}
		y=successivo(y);
	}
}

/**
 * stampaDifesa()
 *
 * DESCRIZIONE
 * Stampa a video la tabella di difesa di un giocatore
 *
 * INPUT
 * P – giocatore di cui stampare a video la tabella di difesa – giocatore
 *
 * OUTPUT
 *
 * LAVORO
 * X – numero di riga da stampare – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * Y – carattere di colonna da stampare – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 */

void stampaDifesa(giocatore p){
	int x;
	char y, c;
	printf("     ");
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	printf("\n\n");
	x=MIN_ROWS;
	while(x<=MAX_ROWS){
		if(x<10){
			printf(" ");
		}
		printf("%d   ", x);
		y=MIN_COLUMN;
		while(y<=MAX_COLUMN){
			c=leggereValoreDifesa(p, y, x);
			if(c=='~'){
				printf(CYAN);
			}
			if(c=='*'){
				printf(GREEN);
			}
			if(c=='!'){
				printf(YELLOW);
			}
			if(c=='X'){
				printf(ORANGE);
			}
			if(c=='#'){
				printf(RED);
			}
			printf("%c "RESET, c);
			y=successivo(y);
		}
		printf("  %d\n", x);
		x++;
	}
	printf("\n");
	printf("     ");
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	printf("\n");
}

/**
 * stampaAttacco()
 *
 * DESCRIZIONE
 * Stampa a video la tabella d'attacco di un giocatore
 *
 * INPUT
 * P – giocatore di cui stampare a video la tabella di attacco – giocatore
 *
 * OUTPUT
 *
 * LAVORO
 * X – numero di riga da stampare – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * Y – carattere di colonna da stampare – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 */

void stampaAttacco(giocatore p){
	int x;
	char y, c;
	printf("     ");
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	printf("\n\n");
	x=MIN_ROWS;
	while(x<=MAX_ROWS){
		if(x<10){
			printf(" ");
		}
		printf("%d   ", x);
		y=MIN_COLUMN;
		while(y<=MAX_COLUMN){
			c=leggereValoreAttacco(p, y, x);
			if(c=='~'){
				printf(CYAN);
			}
			if(c=='*'){
				printf(GREEN);
			}
			if(c=='!'){
				printf(YELLOW);
			}
			if(c=='X'){
				printf(ORANGE);
			}
			if(c=='#'){
				printf(RED);
			}
			printf("%c "RESET, c);
			y=successivo(y);
		}
		printf("  %d\n", x);
		x++;
	}
	printf("\n");
	printf("     ");
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	printf("\n");
}

/**
 * stampaTabelle()
 *
 * DESCRIZIONE
 * Stampa a video sia la tabella d'attacco che la tabella di difesa di un giocatore
 *
 * INPUT
 * P – giocatore di cui stampare le tabelle (attacco e difesa) - giocatore
 *
 * OUTPUT
 *
 * LAVORO
 * X – indice per scandire le righe delle tabelle – numerico – MIN_ROWS<=X<=MAX_ROWS
 * Y – indice per scandire le colone delle tabelle – carattere – MIN_COLUMN<=Y<=MAX_COLUMN
 * C – carattere contenente il valore da stampare - carattere
 */

void stampaTabelle(giocatore p){
	int x;
	char y, c;
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE);
	printf("Attacco");
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE);
	printf("Difesa");
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE+1);
	printf("\n");
	stampaCaratteri(' ', LARGHEZZACAMPO);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	printf("\n");
	stampaCaratteri(' ', LARGHEZZABORDOCOLUMNS);
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	stampaCaratteri(' ', LARGHEZZABORDOCOLUMNS-1);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	stampaCaratteri(' ', LARGHEZZABORDOCOLUMNS);
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	printf("\n");
	stampaCaratteri(' ', LARGHEZZACAMPO);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	printf("\n");
	x=MIN_ROWS;
	while(x<=MAX_ROWS){
		stampaCaratteri(' ', LARGHEZZABORDOROWS);
		if(x<10){
			printf(" ");
		}
		printf("%d   ", x);
		y=MIN_COLUMN;
		while(y<=MAX_COLUMN){
			c=leggereValoreAttacco(p, y, x);
			if(c=='~'){
				printf(CYAN);
			}
			if(c=='*'){
				printf(GREEN);
			}
			if(c=='!'){
				printf(YELLOW);
			}
			if(c=='X'){
				printf(ORANGE);
			}
			if(c=='#'){
				printf(RED);
			}
			printf("%c "RESET, c);
			y=successivo(y);
		}
		printf("  %d", x);
		if(x<10){
			printf(" ");
		}
		stampaCaratteri(' ', LARGHEZZABORDOROWS);
		stampaCaratteri('~', LARGHEZZASPAZIATURA);
		stampaCaratteri(' ', LARGHEZZABORDOROWS);
		if(x<10){
			printf(" ");
		}
		printf("%d   ", x);
		y=MIN_COLUMN;
		while(y<=MAX_COLUMN){
			c=leggereValoreDifesa(p, y, x);
			if(c=='~'){
				printf(CYAN);
			}
			if(c=='*'){
				printf(GREEN);
			}
			if(c=='!'){
				printf(YELLOW);
			}
			if(c=='X'){
				printf(ORANGE);
			}
			if(c=='#'){
				printf(RED);
			}
			printf("%c "RESET, c);
			y=successivo(y);
		}
		printf("  %d\n", x);
		x++;
	}
	stampaCaratteri(' ', LARGHEZZACAMPO);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	printf("\n");
	stampaCaratteri(' ', LARGHEZZABORDOCOLUMNS);
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	stampaCaratteri(' ', LARGHEZZABORDOCOLUMNS-1);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	stampaCaratteri(' ', LARGHEZZABORDOCOLUMNS);
	y=MIN_COLUMN;
	while(y<=MAX_COLUMN){
		printf("%c ", y);
		y=successivo(y);
	}
	printf("\n");
	stampaCaratteri(' ', LARGHEZZACAMPO);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	printf("\n");
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE);
	printf("Attacco");
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE);
	stampaCaratteri('~', LARGHEZZASPAZIATURA);
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE);
	printf("Difesa");
	stampaCaratteri('-', LARGHEZZABORDOINTESTAZIONE+1);
	printf("\n");
}
