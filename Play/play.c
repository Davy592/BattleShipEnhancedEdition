#include "play.h"

/**
 * gioca()
 *
 * DESCRIZIONE
 * Si occupa di stamapare l'interfaccia grafica della partita e di reiterarne le varie fasi
 *
 * INPUT
 * p - array dei giocatori che giocano- array monodimensionale di giocatori statico
 *
 * OUTPUT
 * chi – chi ha fatto l’ultima mossa e ha vinto la partita (o -1 in caso di partita non completata) - numerico – MIN_PLAYER<=intero<=MAX_PLAYER
 *
 * LAVORO
 * chi – giocatore a cui tocca giocare - numerico – MIN_PLAYER<=intero<=MAX_PLAYER
 * avversario – giocatore che subisce la giocata avversaria - numerico – MIN_PLAYER<=intero<=MAX_PLAYER
 * scelta – operazione scelta - numerico - 1<=intero<=5
 * vinto - controllo vittoria – booleano – FALSO=perdente, VERO=vincente
 * nome – nome del giocatore a cui tocca giocare – stringa
 */

int gioca(giocatore p[]){
	stringa nome;
	int chi, avversario, scelta, vinto;
	nome=inizializzareStringa(LUNGHEZZANOME);
	do{
		chi=(leggereTurno(p[0])+leggereTurno(p[1]))%MAX_PLAYER;  //formula modificata per ottenere valore compreso fra 0 e 1 (in C uso l'operazione %)
		avversario=(chi+1)%MAX_PLAYER;  //formula modificata per ottenere valore compreso fra 0 e 1 (in C uso l'operazione %)
		incrementareTurno(&p[chi]);
		leggereNome(p[chi], nome);
		system("cls");
		printf("Tocca a ");
		if(chi==0){
			printf(RED);
		}else{
			printf(BLUE);
		}
		printf("%s\n\n", nome);
		printf(RESET);
		stampaTabelle(p[chi]);
		printf("\n");
		scelta=operazioniPossibili(p[chi]);
		eseguireOperazione(p, chi, scelta);
		vinto=controllaNavi(p[avversario]);
		system("pause");
	}while(vinto==FALSO && leggereTurno(p[chi])!=-1);  //finche qualcuno non ha vinto oppure quanlcuno non ha deciso di uscire (eventualmente salvando)
	if(vinto==FALSO){
		chi=-1;
	}
	return chi;
}

/**
 * operazioniPossibili()
 *
 * DESCRIOZIONE
 * Si occupa di stampare a video tutte le operazioni che un giocatore può compiere
 *
 * INPUT
 * p - giocatore di cui controllare i colpi eseguibili – giocatore
 *
 * OUTPUT
 * scelta – operazione scelta - numerico - 1<=intero<=5
 *
 * LAVORO
 * i - contatore delle operazioni eseguibili - numerico - 1<=intero<=5
 */

int operazioniPossibili(giocatore p){
	int i, scelta;
	printf("Ecco i colpi che ti e' possibile sparare:\n");
	i=1;
	printf("%d) Colpo classico\n", i);
	if(leggereLargoRaggio(p)>MIN_LARGE){
		i++;
		printf("%d) Colpo a largo raggio (ancora %d)\n", i, leggereLargoRaggio(p));
	}
	if(leggereBombardamento(p)>MIN_BOMB && leggereTurno(p)>=MIN_TURNO_BOMB){
		i++;
		printf("%d) Bombardamento (ancora %d)\n", i, leggereBombardamento(p));
	}
	if(leggereRadar(p)>MIN_RADAR){
		i++;
		printf("%d) Radar (ancora %d)\n", i, leggereRadar(p));
	}
	i++;
	printf("%d) Salva ed esci.\n", i);
	i++;
	printf("%d) Esci.\n", i);
	printf("Inserire il numero corrispondente alla scelta: ");
	scelta=inputInteroCheck(1, i);
	return scelta;
}

/**
 * eseguireOperazione()
 *
 * DESCRIZIONE
 * Dato il numero dell'operazione scelta questa funzione si occupa di eseguirla (spesso affidandosi ad altre sottofunzioni)
 *
 *
 * INPUT
 * p - array dei giocatori coinvolti nell’operazione - array monodimensionale di giocatori statico
 * chi – giocatore che esegue l’operazione - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 * scelta – operazione da eseguire (precedentemente scelta dall’utente) – numerico – 1<=intero
 *
 * OUTPUT
 * p - array dei giocatori dopo l’esecuzione dell’operazione - array monodimensionale di giocatori statico
 *
 * LAVORO
 * c – coordinata del (eventuale) colpo classico - coordinata
 * i – contatore della scelta – numerico
 */

void eseguireOperazione(giocatore p[], int chi, int scelta){
	coordinata c;
	int i;
	i=1;
	if(i==scelta){
		printf("Inserire la cella da colpire.\n");
		printf("Inserire la coordinata nel formato \"A-1\": ");
		c=inputCoordinataCheck(MIN_COLUMN, MAX_COLUMN, MIN_ROWS, MAX_ROWS);
		sparareColpoClassico(p, chi, leggereY(c), leggereX(c));
	}
	if(leggereLargoRaggio(p[chi])>MIN_LARGE){
		i++;
		if(i==scelta){
			sparareLargoRaggio(p, chi);
		}
	}
	if(leggereBombardamento(p[chi])>MIN_BOMB && leggereTurno(p[chi])>=MIN_TURNO_BOMB){
		i++;
		if(i==scelta){
			sparareBombardamento(p, chi);
		}
	}
	if(leggereRadar(p[chi])>MIN_RADAR){
		i++;
		if(i==scelta){
			usareRadar(p, chi);
		}
	}
	i++;
	if(i==scelta){
		decrementareTurno(&p[chi]);  //decremento il turno perche prima l'ho incrementato ma il giocatore ha deciso di salvare e non giocare il turno
		salvarePartita(p);
		scrivereTurno(&p[chi], -1);  //setto il turno del giocatore che salva la partita a -1 per indicare di terminare la partita (seppur non sia finita)
	}
	i++;
	if(i==scelta){
		scrivereTurno(&p[chi], -1);  //setto il turno del giocatore che salva la partita a -1 per indicare di terminare la partita (seppur non sia finita)
	}
}

/**
 * sparareColpoClassico()
 *
 * DESCRIZIONE
 * Spara un colpo classico e mostra a video il risultato
 *
 * INPUT
 * p - array dei giocatori coinvolti nel colpo classico - array monodimensionale di giocatori statico
 * chi – indica il giocatore che compia l’azione - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 * x – riga dove effettuare l’azione - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * y - colonna dove effettuare l’azione - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 *
 * OUTPUT
 * P - array dei giocatori coinvolti nel colpo classico avvenuto - array monodimensionale di giocatori statico
 *
 * LAVORO
 * c - carattere presente nella cella prima che si compia l’azione - carattere
 * n - numero della nave colpita - numerico – MIN_SHIP<=intero<=MAX_SHIP
 * avversario - indica il giocatore che subisce l’azione - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 */

void sparareColpoClassico(giocatore p[], int chi, char y, int x){
	int n, avversario;
	char c;
	avversario=(chi+1)%2;
	c=leggereValoreDifesa(p[avversario], y, x);  //il carattere letto dalla matrice di difesa dell'avversario
	if(c=='*' || c=='!'){  //se ho colpito un pezzo di nave non ancora colpito
		n=trovareNave(p[avversario], y, x);  //trovo la nave che ho colpito
		decrementareHp(&p[avversario], n);  //decremento gli hp della nave colpita
		if(leggereHp(leggereValoreFlotta(p[avversario], n))==0){  //se dopo il colpo ho affondato la nave
			printf(RED"%c-%d colpito e affondato.\n"RESET, y, x);  //stampo esito
			affondaNave(p, chi, n);  //aggiorno le matrici
		}else{  //altrimenti
			printf(ORANGE"%c-%d colpito.\n"RESET, y, x);  //stampo esito
			scrivereValoreAttacco(&p[chi], y, x, 'X');  //aggiorno matrice d'attacco di chi spara
			scrivereValoreDifesa(&p[avversario], y, x, 'X');  //aggiorno matrice di difesa di chi subisce
		}
	}else if(c=='~' || c=='-'){  //se non ho colpito nulla
		printf("%c-%d mancato.\n", y, x);  //stampo esito
		scrivereValoreAttacco(&p[chi], y, x, 'O');
		scrivereValoreDifesa(&p[avversario], y, x, 'O');
	}else if(c=='X'){  //se ho colpito un pezzo di nave precedentemente colpito
		printf(ORANGE"%c-%d gia' colpito.\n"RESET, y, x);  //stampo esito e non aggiorno nulla
	}else if(c=='#'){  //se ho colpito una nave precedentemente affondata
		printf(RED"%c-%d gia' colpito e affondato.\n"RESET, y, x);  //stampo esito e non aggiorno nulla
	}else if(c=='O'){  //se ho colpito un punto precedentemente mancato
		printf("%c-%d gia' mancato.\n", y, x);  //stampo esito e non aggiorno nulla
	}
}

/**
 * trovareNave()
 *
 * DESCRIZIONE
 * Data una cella individua la nave appartenente alla flotta del giocatore che passa da quella cella
 *
 * INPUT
 * p – giocatore di cui individuare la nave - giocatore
 * x – riga della cella colpita - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * y - colonna della cella colpita - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 *
 * OUTPUT
 * nave - nave che passa dalla cella colpita - numerico – MIN_SHIP<=intero<=MAX_SHIP
 *
 * LAVORO
 * I – indice per scandire le navi - numerico – MIN_SHIP<=intero<=MAX_SHIP
 * Startx – indica la riga della cella iniziale della nave attualmente analizzata – numerico – MIN_ROWS<=intero<=MAX_ROWS
 * Starty – indica la colonna della cella iniziale della nave attualmente analizzata – carattere – MIN_COLUMN<=caratt<=MAX_COLUMN
 */

int trovareNave(giocatore p, char y, int x){
	int i, nave, startx, starty;
	i=MIN_SHIP;
	do{
		startx=leggereX(leggerePos(leggereValoreFlotta(p, i)));
		starty=leggereY(leggerePos(leggereValoreFlotta(p, i)));
		if(leggereVerso(leggereValoreFlotta(p, i))==VERO){
			if(starty==y && x>=startx && x<=startx+dimNave(i)-1){
				nave=i;
			}
		}else{
			if(startx==x && y>=starty && y<=starty+dimNave(i)-1){  //(in C eseguo delle normali somme su caratteri)
				nave=i;
			}
		}
		i++;
	}while(i<=MAX_SHIP);
	return nave;
}

/**
 * affondaNave()
 *
 * DESCRIZIONE
 * Si occupa di aggiornare le tabelle d'attacco e di difesa dei giocatori nel momento in cui una nave affonda
 *
 * INPUT
 * p - array dei giocatori di cui aggiornare le tabelle - array monodimensionale di giocatori statico
 * chi – giocatore che ha affondato una nave avversaria - numerico – MIN_PLAYER<=intero<=MAX_PLAYER
 * n - numero della nave affondata - numerico – MIN_SHIP<=intero<=MAX_SHIP
 *
 * OUTPUT
 * p - array dei giocatori con le tabelle aggiornate - array monodimensionale di giocatori statico
 *
 * LAVORO
 * avversario – giocatore la cui nave è stata affondata - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 * x - riga iniziale su cui è posizionata la nave - numerico – MIN_ROWS<=intero<=MAX_ROWS
 * endx – riga finale su cui è posizionata la nave- numerico - MIN_ROWS<=intero<=MAX_ROWS
 * y - colonna iniziale su cui è posizionata la nave - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 * endy - colonna finale su cui è posizionata la nave - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 */

void affondaNave(giocatore p[], int chi, int n){
	int avversario, x, endx;
	char y, endy;
	avversario=(chi+1)%2;
	y=leggereY(leggerePos(leggereValoreFlotta(p[avversario], n)));
	x=leggereX(leggerePos(leggereValoreFlotta(p[avversario], n)));
	if(leggereVerso(leggereValoreFlotta(p[avversario], n))==VERO){  //se la nave colpita è in verticale
		endx=x+dimNave(n)-1;
		while(x<=endx){  //scorro la lunghezza della nave sulle righe
			scrivereValoreAttacco(&p[chi], y, x, '#');  //aggiorno la matrice d'attacco di chi spara
			scrivereValoreDifesa(&p[avversario], y, x, '#');  //aggiorno la matrice di difesa di chi subisce
			x++;
		}
	}else{  //altrimenti
		endy=y+dimNave(n)-1;  //(in C eseguo delle normali somme su caratteri)
		while(y<=endy){  //scorro la lunghezza della nave sulle colonne
			scrivereValoreAttacco(&p[chi], y, x, '#');  //aggiorno la matrice d'attacco di chi spara
			scrivereValoreDifesa(&p[avversario], y, x, '#');  //aggiorno la matrice di difesa di chi subisce
			y=successivo(y);
		}
	}
}

/**
 * sparareLargoRaggio()
 *
 * DESCRIZIONE
 * Spara un colpo a largo raggio (suddiviso in 9 colpi classici)
 *
 * INPUT
 * p - array dei giocatori coinvolti nello sparo a largo raggio - array monodimensionale di giocatori statico
 * chi – indica il giocatore che compia l’azione - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 *
 * OUTPUT
 * p - array dei giocatori dopo lo sparo - array monodimensionale di giocatori statico
 *
 * LAVORO
 * startx - numero riga iniziale colpita dallo sparo- numerico - MIN_ROWS<=intero<=MAX_ROWS
 * curx – riga della cella che si sta sparando attualmente  - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * endx - numero riga finale colpita dallo sparo - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * starty - carattere colonna iniziale colpita dallo sparo - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 * cury – colonna della cella che si sta sparando attualmente - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 * endy - carattere colonna finale colpita dallo sparo - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 * c - coordinata centrale - coordinata
 */

void sparareLargoRaggio(giocatore p[], int chi){
	int startx, curx, endx;
	char starty, cury, endy;
	coordinata c;
	decrementareLargoRaggio(&p[chi]);
	printf("Inserire la cella da colpire a largo raggio.\n");
	printf("Inserire la coordinata nel formato \"A-1\": ");
	c=inputCoordinataCheck(MIN_COLUMN, MAX_COLUMN, MIN_ROWS, MAX_ROWS);
	startx=maxInt(leggereX(c)-1, MIN_ROWS);  //definisco startx (riga iniziale) (controllo che non esca fuori bordo)
	starty=maxChar(leggereY(c)-1, MIN_COLUMN);  //definisco starty (colonna iniziale) (controllo che non esca fuori bordo) (in C eseguo delle normali somme su caratteri)
	endx=minInt(leggereX(c)+1, MAX_ROWS);  //definisco endx (riga finale) (controllo che non esca fuori bordo)
	endy=minChar(leggereY(c)+1, MAX_COLUMN);  //definisco endy (colonna finale) (controllo che non esca fuori bordo) (in C eseguo delle normali somme su caratteri)
	curx=startx;
	while(curx<=endx){
		cury=starty;
		while(cury<=endy){
			sparareColpoClassico(p, chi, cury, curx);
			cury=successivo(cury);
		}
		curx++;
	}
}

/**
 * sparareBombardamento()
 *
 * DESCRIZIONE
 * Esegue un bombardamento (suddiviso in 16 colpi classici)
 *
 * INPUT
 * p - array dei giocatori coinvolti nel bombardamento - array monodimensionale di giocatori statico
 * chi - chi compie il bombardamento - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 *
 * OUTPUT
 * p - array dei giocatori dopo il bombardamento - array monodimensionale di giocatori statico
 *
 * LAVORO
 * verso – verso del bombardamento – booleano – FALSO=orizzontale, VERO=verticale
 * x - riga su cui compere il bombardamento - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * y - colonna su cui compiere il bombardamento - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 */

void sparareBombardamento(giocatore p[], int chi){
	int verso, x;
	char y;
	decrementareBombardamento(&p[chi]);
	printf("Inserire se si vuole bombardare una colonna o una riga.\n");
	printf("Inserire 0 per riga o 1 per colonna: ");
	verso=inputInteroCheck(FALSO, VERO);  //controllo verso compreso tra 0 e 1
	if(verso==VERO){
		printf("Inserire la colonna da bombardare: ");
		y=inputCharCheck(MIN_COLUMN, MAX_COLUMN);
		x=MIN_ROWS;
		while(x<=MAX_ROWS){
			sparareColpoClassico(p, chi, y, x);
			x++;
		}
	}else{
		printf("Inserire la riga da bombardare: ");
		x=inputInteroCheck(MIN_ROWS, MAX_ROWS);
		y=MIN_COLUMN;
		while(y<=MAX_COLUMN){
			sparareColpoClassico(p, chi, y, x);
			y=successivo(y);
		}
	}
}

/**
 * usareRadar()
 *
 * DESCRIZIONE
 * Usa il radar (suddiviso in 9 analizza cella)
 *
 * INPUT
 * p - array dei giocatori con il radar da usare - array monodimensionale di giocatori statico
 * chi – chi utilizza il radar- numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 *
 * OUTPUT
 * p - array dei giocatori dopo l’uso del radar - array monodimensionale di giocatori statico
 *
 * LAVORO
 * c - coordinata centrale – coordinata
 * startx - numero riga iniziale - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * curx – riga della cella che si sta analizzando attualmente  - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * endx - numero riga finale - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * starty - carattere colonna iniziale - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 * cury – colonna della cella che si sta analizzando attualmente - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 * endy - carattere colonna finale - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 */

void usareRadar(giocatore p[], int chi){
	int startx, curx, endx;
	char starty, cury, endy;
	coordinata c;
	decrementareRadar(&p[chi]);
	printf("Inserire la cella su cui usare il radar.\n");
	printf("Inserire la coordinata nel formato \"A-1\": ");
	c=inputCoordinataCheck(MIN_COLUMN, MAX_COLUMN, MIN_ROWS, MAX_ROWS);
	startx=maxInt(leggereX(c)-1, MIN_ROWS);  //definisco startx (riga iniziale) (controllo che non esca fuori bordo)
	starty=maxChar(leggereY(c)-1, MIN_COLUMN);  //definisco starty (colonna iniziale) (controllo che non esca fuori bordo) (in C eseguo delle normali somme su caratteri)
	endx=minInt(leggereX(c)+1, MAX_ROWS);  //definisco endx (riga finale) (controllo che non esca fuori bordo)
	endy=minChar(leggereY(c)+1, MAX_COLUMN);  //definisco endy (colonna finale) (controllo che non esca fuori bordo) (in C eseguo delle normali somme su caratteri)
	curx=startx;
	while(curx<=endx){
		cury=starty;
		while(cury<=endy){
			analizzareCella(p, chi, cury, curx);
			cury=successivo(cury);
		}
		curx++;
	}
}

/**
 * analizzareCella()
 *
 * DESCRIZIONE
 * Analizza una cella col radar e mostra a video il risultato
 *
 * INPUT
 * p - giocatori coinvolti nell’analisi - array monodimensionale di giocatori statico
 * chi - chi compie l’analisi - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 * x – riga della cella da analizzare - numerico - MIN_ROWS<=intero<=MAX_ROWS
 * y - colonna della cella da analizzare - carattere - MIN_COLUMN<=carattere<=MAX_COLUMN
 *
 * OUTPUT
 * p - giocatori dopo l’analisi- array monodimensionale di giocatori statico
 *
 * LAVORO
 * c - carattere letto nella tabella dell’avversario - carattere
 * avversario - chi subisce l’analisi - numerico - MIN_PLAYER<=intero<=MAX_PLAYER
 */

void analizzareCella(giocatore p[], int chi, char y, int x){
	int avversario;
	char c;
	avversario=(chi+1)%2;
	c=leggereValoreDifesa(p[avversario], y, x);  //il carattere letto dalla matrice di difesa dell'avversario
	if(c=='*' || c=='!'){  //se ho colpito un pezzo di nave non ancora colpito
		printf(YELLOW"%c-%d nave.\n"RESET, y, x);
		scrivereValoreAttacco(&p[chi], y, x, '!');
		scrivereValoreDifesa(&p[avversario], y, x, '!');
	}else if(c=='~' || c=='-'){  //se non ho colpito nulla
		printf("%c-%d vuoto.\n", y, x);  //stampo esito
		scrivereValoreAttacco(&p[chi], y, x, '-');
		scrivereValoreDifesa(&p[avversario], y, x, '-');
	}else if(c=='X'){  //se ho colpito un pezzo di nave precedentemente colpito
		printf(ORANGE"%c-%d gia' colpito.\n"RESET, y, x);  //stampo esito e non aggiorno nulla
	}else if(c=='#'){  //se ho colpito una nave precedentemente affondata
		printf(RED"%c-%d gia' colpito e affondato.\n"RESET, y, x);  //stampo esito e non aggiorno nulla
	}else if(c=='O'){  //se ho colpito un punto precedentemente mancato
		printf("%c-%d gia' mancato.\n", y, x);  //stampo esito e non aggiorno nulla
	}
}

/**
 * controllaNavi()
 *
 * DESCRIZIONE
 * Controlla gli hp di tutte le navi appartenenti alla flotta di un giocatore per capire se l'avversario ha vinto
 *
 * INPUT
 * P – giocatore di cui controllare le navi - giocatore
 *
 * OUTPUT
 * Vinto – indica se il giocatore avversario ha vinto, ossia se tutte le navi del giocatore da controllare sono affondate – booleano – FALSO=perdente, VERO=vincente
 *
 * LAVORO
 * I – indice per scandire le navi del giocatore – numerico – MIN_SHIP<=intero<=MAX_SHIP
 */

int controllaNavi(giocatore p){
	int i, vinto;
	vinto=VERO;
	i=MIN_SHIP;
	while(i<=MAX_SHIP){
		if(leggereHp(leggereValoreFlotta(p, i))!=0){  //se c'è almeno una nave con più di 0 hp
			vinto=FALSO;  //allora non abbaimo un vincitore
		}
		i++;
	}
	return vinto;
}
