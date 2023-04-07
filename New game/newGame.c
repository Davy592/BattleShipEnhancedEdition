#include "newGame.h"

/**
 * inserimentoDati()
 *
 * DESCRIZIONE
 * Si occupa della lettura da tastiera e dell’inserimento di tutti i dati necessari a giocare una partita per entrambi i giocatori
 *
 * INPUT
 * P – giocatori di cui prendere in input i dati – array statico monodimensionale di giocatori – lunghezza=MAX_PLAYER
 *
 * OUTPUT
 * P – giocatori dopo l’inserimento dei dati – array statico monodimensionale di giocatori – lunghezza=MAX_PLAYER
 *
 * LAVORO
 * I – indice per scandire i giocatori – numerico – intero>0
 * J – indice per scandire le navi di un giocatore – numerico – intero>0
 * nome – stringa per contenere il nome del giocatore – stringa
 */

void inserimentoDati(giocatore p[]){
	int i, j;
	stringa nome;
	nome=inizializzareStringa(LUNGHEZZANOME);
	i=MIN_PLAYER;
	while(i<=MAX_PLAYER){
		scrivereTurno(&p[i-1], 0);  //uso i-1 perche in C i vettori partono da 0
		system("cls");
		printf("Tocca al ");
		if(i==1){
			printf(RED);
		}else{
			printf(BLUE);
		}
		printf("giocatore %d\n", i);
		printf(RESET);
		printf("Inserisci il tuo nome: ");
		if(i==1){
			printf(RED);
		}else{
			printf(BLUE);
		}
		scanf("%s", nome);
		printf(RESET);
		scrivereNome(&p[i-1], nome);
		riempireAttacco(&p[i-1], '~');
		riempireDifesa(&p[i-1], '~');
		j=MIN_SHIP;
		while(j<=MAX_SHIP){
			posizionareNave(&p[i-1], j);
			j++;
		}
		scrivereLargoRaggio(&p[i-1], MAX_LARGE);
		scrivereBombardamento(&p[i-1], MAX_BOMB);
		scrivereRadar(&p[i-1], MAX_RADAR);
		i++;
	}
	deinizializzareStringa(nome);
	return;
}

/**
 * posizionareNave()
 *
 * DESCRIZIONE
 * Si occupa di posizionare l’n-esima nave del giocatore, all’atto pratico si occupa di effettuare i vari controlli (assegnati alle varie sottofunzioni)
 * e in caso questi diano esito positivo procede ad aggiornare la tabella di difesa del giocatore e la sua flotta (anche questi aggiornamenti sono assegnati a una sottofunzione)
 *
 * INPUT
 * P - giocatore di cui posizionare una nave - giocatore
 * n - numero della nave da posizionare - numerico – MIN_SHIP<=intero<=MAX_SHIP
 *
 * OUTPUT
 * P - giocatore con una nave posizionata – giocatore
 *
 * LAVORO
 * dim - dimensione della nave da posizionare - numerico - 1<=intero<=5
 * c – coordinata iniziale della nave da posizionare - coordinata
 * verso - verso della nave da posizionare - booleano – FALSO=orizzontale, VERO=verticale
 * ripeti - valore per confermare i controlli  - booleano – FALSO=non ripeti, VERO=ripeti
 */

void posizionareNave(giocatore *p, int n){
	int dim, verso, ripeti;
	coordinata c;
	dim=dimNave(n);
	system("cls");
	printf("Situazione attuale (matrice difesa):\n");
	stampaDifesa(*p);
	printf("Si sta inserendo una nave di lunghezza %d\n", dim);
	do{
		do{
			printf("Inserire cella iniziale della nave (cella sinistra per navi orizzontali o cella in alto per navi verticali)\n");
			printf("Inserire la coordinata nel formato \"A-1\": ");
			c=inputCoordinataCheck(MIN_COLUMN, MAX_COLUMN, MIN_ROWS, MAX_ROWS); //controllo coordinate comprese tra A-1 e P-16
			if(dim!=1){  //prendo in input il verso solo se la nave non ha lunghezza 1
				printf("Inserire verso della nave\n");
				printf("Inserire 1 per verticale e 0 per orizzontale: ");
				verso=inputInteroCheck(FALSO, VERO);  //controllo verso compreso tra 0 e 1
			}else{
				verso=FALSO;
			}
			ripeti=controlloNaveFuoriMappa(c, verso, dim);
		}while(ripeti==VERO);  //se la nave esce fuori mappa faccio reinserire sia coordinate che verso
		//controllo che posizionando la nave non tocchi altre navi [controllo che tutte le celle attorno all'ipotetico piazzamento della nave (raggio 1) siano mare]
		ripeti=controlloToccoAltreNavi(*p, c, verso, dim);
	}while(ripeti==VERO);  //se il piazzamento non è valido faccio reinserire sia coordinata che verso
	//se il piazzamento è valido aggiorno sia la matrice di difesa che il vettore delle navi
	aggiungiNaveDifesa(p, c, verso, dim);
	scrivereValoreFlotta(p, n, c, verso, dim);
	system("pause");
}

/**
 * controlloNaveFuoriMappa()
 *
 * DESCRIZIONE
 * Date le coordinate iniziali, il verso e la dimensione della nave che si vuole inserire si occupa di controllare che la nave rimanga all’interno dei bordi della mappa
 *
 * INPUT
 * c – indica la coordinata iniziale della nave - coordinata
 * verso - indica il verso della nave – booleano – FALSO=orizzontale, VERO=verticale
 * dim - indica la dimensione della nave – numerico – 1<=intero<=5
 *
 * OUTPUT
 * ripeti - valore per confermare i controlli  - booleano – FALSO=non ripeti, VERO=ripeti
 *
 * LAVORO
 *
 */

int controlloNaveFuoriMappa(coordinata c, int verso, int dim){
	int ripeti;
	ripeti=FALSO;
	if(verso==VERO){  //controllo che la nave non esca fuori mappa
		if(leggereX(c)+dim-1>MAX_ROWS){  //formula per navi verticali
			printf("La nave esce fuori dal bordo mappa!\n\n");
			ripeti=VERO;
		}
	}else{
		if(leggereY(c)+dim-1>MAX_COLUMN){  //formula per navi orizzonati (in C eseguo normali somme su caratteri)
			printf("La nave esce fuori dal bordo mappa!\n\n");
			ripeti=VERO;
		}
	}
	return ripeti;
}

/**
 * controlloToccoAltreNavi()
 *
 * DESCRIZIONE
 * Date le coordinate iniziali, il verso e la dimensione della nave che si vuole inserire
 * si occupa di controllare che la nave non tocchi altre navi precedentemente piazzate dal giocatore
 *
 * INPUT
 * P - giocatore di cui controllare le navi- giocatore
 * c – indica la coordinata iniziale della nave - coordinata
 * verso - indica il verso della nave – booleano – FALSO=orizzontale, VERO=verticale
 * dim - indica le celle della nave non ancora colpite – numerico – 0<=intero<=5
 *
 * OUTPUT
 * ripeti - valore per confermare i controlli  - booleano – FALSO=non ripeti, VERO=ripeti
 *
 * LAVORO
 * startx - valore di partenza delle righe del controllo - numerico – MIN_ROWS<=intero<=MAX_ROWS
 * curx - valore effettivo delle x – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * endx - valore finale delle righe del controllo - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * starty - valore di partenza delle colonne del controllo - MIN_COLUMN<=carattere<=MAX_COLUMN
 * cury - valore effettivo delle y – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 * endy - valore finale delle colonne del controllo - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 */

int controlloToccoAltreNavi(giocatore p, coordinata c, int verso, int dim){
	int ripeti, startx, curx, endx;
	char starty, cury, endy;
	ripeti=FALSO;
	startx=maxInt(leggereX(c)-1, MIN_ROWS);  //definisco startx (riga iniziale) (controllo che non esca fuori bordo)
	starty=maxChar(leggereY(c)-1, MIN_COLUMN);  //definisco starty (colonna iniziale) (controllo che non esca fuori bordo) (in C eseguo normali somme su caratteri)
	if(verso==VERO){  //separo le formule per definire riga e cella finale sulla base del verso della nave
		endx=minInt(leggereX(c)+dim, MAX_ROWS);  //definisco endx (riga finale) (controllo che non esca fuori bordo)
		endy=minChar(leggereY(c)+1, MAX_COLUMN);  //definisco endy (colonna finale) (controllo che non esca fuori bordo) (in C eseguo normali somme su caratteri)
	}else{
		endx=minInt(leggereX(c)+1, MAX_ROWS);  //definisco endx (riga finale) (controllo che non esca fuori bordo)
		endy=minChar(leggereY(c)+dim, MAX_COLUMN);  //definisco endy (colonna finale) (controllo che non esca fuori bordo) (in C eseguo normali somme su caratteri)
	}
	curx=startx;
	while(curx<=endx){  //eseguo il vero e proprio controllo sull'area della nave
		cury=starty;
		while(cury<=endy){
			if(leggereValoreDifesa(p, cury, curx)!='~'){  //se una delle celle controllate non è mare allora il piazzamento non è valido
				ripeti=VERO;
			}
			cury=successivo(cury);
		}
		curx++;
	}
	if(ripeti==VERO){
		printf("Coordinate non valide, la nave cosi posizionata tocca altre navi.\n\n");
	}
	return ripeti;
}

/**
 * aggiungiNaveDifesa()
 *
 * DESCRIZIONE
 * Si occupa del vero e proprio aggiornamento della tabella di difesa del giocatore e della sua flotta (richiamata dopo l’esito positivo dei controlli precedenti)
 *
 * INPUT
 * P - giocatore di cui posizionare una nave sulla tabella di difesa - giocatore
 * c – indica la coordinata iniziale della nave - coordinata
 * verso - indica il verso della nave – booleano – FALSO=orizzontale, VERO=verticale
 * dim - indica la dimensione della nave – numerico – 1<=intero<=5
 *
 * OUTPUT
 * ripeti - valore per confermare i controlli  - booleano – FALSO=non ripeti, VERO=ripeti
 *
 * LAVORO
 *
 */

void aggiungiNaveDifesa(giocatore *p, coordinata c, int verso, int dim){
	int curx;
	char cury;
	if(verso==VERO){  //prima aggiorno la matrice, divido i casi in base al verso
		curx=leggereX(c);  //scorro la matrice in verticale (incremento la riga)
		while(curx<=leggereX(c)+dim-1){
			scrivereValoreDifesa(p, leggereY(c), curx, '*');
			curx++;
		}
	}else{
		cury=leggereY(c);  //scorro la matrice in orizzontale (incremento la colonna)
		while(cury<=leggereY(c)+dim-1){  //(in C eseguo normali somme su caratteri)
			scrivereValoreDifesa(p, cury, leggereX(c), '*');
			cury=successivo(cury);
		}
	}
}
