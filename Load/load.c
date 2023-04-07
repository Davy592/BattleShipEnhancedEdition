#include "load.h"

/**
 * aperturaFileSalvataggio()
 *
 * DESCRIZIONE
 * Si occupa di creare l'elenco dei file di salvataggio, visualizzare il menu di caricamento e caricare il file selezionato
 *
 * INPUT
 * P – giocatori di cui caricare i dati da file – array monodimensionale di giocatori statico – lunghezza=2
 *
 * OUTPUT
 * P – giocatori con i dati caricati da file - array monodimensionale di giocatori statico – lunghezza=2
 *
 * LAVORO
 * Scelta – indica il numero del file da cui eseguire il caricamento scelto – numerico – intero (-1 per gestione errori)
 * Percorso – percorso del file da cui caricare i dati – stringa
 * Elenco – file su cui elencare i file di salvataggio presenti – file di testo
 * nomeFile – nome del file da cui caricare i dati – stringa
 * fin – file da cui caricare i dati – file binario
 */

void aperturaFileSalvataggio(giocatore p[]){
	FILE *fin;
	int scelta;
	stringa percorso, nomeFile;
	percorso=inizializzareStringa(LUNGHEZZAPERCORSO);
	nomeFile=inizializzareStringa(LUNGHEZZAPERCORSO);
	system("cls");
	printf("Ecco l'elenco dei file di salvataggio disponibili:\n");
	system("dir \"C:\\BattleShip\\Salvataggi\\*.dat\" /a:-d-r-s-h /b > C:\\BattleShip\\Elenco.txt");
	scelta=sceltaFile();
	if(scelta!=-1){
		trovareNomeFile(nomeFile, scelta);
		copiareStringa(percorso, "C:\\BattleShip\\Salvataggi\\\0");
		concatenareStringa(percorso, nomeFile);
		fin=fopen(percorso, "r");  //il file si aprira sicuramente perche ho preso il suo nome dall'elenco pertanto sicuramente è presente nella cartella
		caricamentoDati(p, fin);
		fclose(fin);
	}else{
		scrivereTurno(&p[0], -1);
	}
	deinizializzareStringa(percorso);
	deinizializzareStringa(nomeFile);
}

/**
 * sceltaFile()
 *
 * DESCRIZIONE
 * Si occupa di visualizzare il menu di caricamento e leggere da tastiera la scelta dell'utente
 *
 * INPUT
 *
 * OUTPUT
 * Scelta – indica il numero del file da cui eseguire il caricamento scelto – numerico – intero (-1 per gestione errori)
 *
 * LAVORO
 * sceltaMax – indica il numero di file tra cui scegliere – numerico – intero (-1 se non ci sono file)
 */

int sceltaFile(){
	int scelta, sceltaMax;
	sceltaMax=stampaElenco();
	if(sceltaMax!=-1){
		printf("Inserire il numero del file di salvataggio che si vuole utilizzare: ");
		scelta=inputInteroCheck(1, sceltaMax);
	}else{
		scelta=-1;
	}
	return scelta;
}

/**
 * stampaElenco()
 *
 * DESCRIZIONE
 * Stampa a video l'elenco dei file di salvataggio disponibili o in alternativa eventuali errori di sorta
 *
 * INPUT
 *
 * OUTPUT
 * sceltaMax – indica quante voci sono state stampate, ossia tra quante voci massimo è possibile scegliere – numerico – intero (-1 per gestione errori errori)
 *
 * LAVORO
 * Elenco – file elenco da stamapre a video – file di testo
 * C – variabile d’appoggio per i caratteri da stampare a video - carattere
 */

int stampaElenco(){
	FILE *elenco;
	int sceltaMax;
	char c;
	elenco=fopen("C:\\BattleShip\\Elenco.txt", "r");
	if(elenco==NULL){
		printf("Errore apertura elenco.\n");
		sceltaMax=-1;
	}else{
		c=fgetc(elenco);
		if(c==EOF){
			printf("Elenco aperto correttamente. Nessun file di salvataggio trovato.\n");
			sceltaMax=-1;
		}else{
			sceltaMax=1;
			do{
				printf("%d) %c", sceltaMax, c);
				do{
					c=fgetc(elenco);
					printf("%c", c);
				}while(c!='\n' && c!=EOF);
				c=fgetc(elenco);
				if(c!=EOF){
					sceltaMax++;
				}
			}while(c!=EOF);
		}
	}
	fclose(elenco);
	return sceltaMax;
}

/**
 * trovareNomeFile()
 *
 * DESCRIZIONE
 * Dato il numero del file scelto ritorna il suo nome
 *
 * INPUT
 * Nome – stringa su cui scrivere il nome del file scelto – stringa
 * Scelta – indica il numero del file scelto – numerico – intero>0
 *
 * OUTPUT
 * Nome – stringa con il nome del file selezionato scritto - stringa
 *
 * LAVORO
 * Elenco – file elenco da cui leggere i nomi dei file tra cui scegliere – file di testo
 * rigaAtt – indica la riga che si sta leggendo attualmente dal file elenco – numerico – intero>0
 * i – indice per scandire gli elementi di nome – numerico – intero
 * c – variabile d’appoggio per i caratteri da scrivere nella stringa nome - carattere
 */

void trovareNomeFile(stringa nome, int scelta){
	FILE *elenco;
	int rigaAtt, i;
	char c;
	elenco=fopen("C:\\Battleship\\Elenco.txt", "r");  //il file si apre sicuramente altrimenti non sarei arrivato a richiamare questa funzione
	rigaAtt=1;
	i=1;
	do{
		do{
			c=fgetc(elenco);
			if(rigaAtt==scelta){
				if(c=='\n'){
					scrivereCarattereStringa(nome, i, FINESTRINGA);
				}else{
					scrivereCarattereStringa(nome, i, c);
				}
				i++;
			}
		}while(c!='\n' && c!=EOF);
		rigaAtt++;
	}while(rigaAtt<=scelta);
	fclose(elenco);
}

/**
 * caricamentoDati()
 *
 * DESCRIZIONE
 * Si occupa di leggere dal file di salvataggio selezionato tutti i dati presenti
 *
 * INPUT
 * P – giocatori di cui caricare i dati da file – array monodimensionale di giocatori statico – lunghezza=2
 * Fin – file da cui caricare i dati dei giocatori – file binario
 *
 * OUTPUT
 * P – giocatori con i dati caricati da fin - array monodimensionale di giocatori statico – lunghezza=2
 *
 * LAVORO
 * I – indice per scandire i giocatori – numerico – intero>0
 * N – variabile d’appoggio per gli interi da leggere da file – numerico – intero
 * Nome – nome letto da file - stringa
 */

void caricamentoDati(giocatore p[], FILE *fin){
	int i, n;
	stringa nome;
	nome=inizializzareStringa(LUNGHEZZANOME);
	i=MIN_PLAYER;
	while(i<=MAX_PLAYER){
		fread(&n, sizeof(int), 1, fin);
		scrivereTurno(&p[i-1], n);
		fread(nome, sizeof(char), LUNGHEZZANOME, fin);
		scrivereNome(&p[i-1], nome);
		inputFlottaFile(&p[i-1], fin);
		fread(&n, sizeof(int), 1, fin);
		scrivereLargoRaggio(&p[i-1], n);
		fread(&n, sizeof(int), 1, fin);
		scrivereBombardamento(&p[i-1], n);
		fread(&n, sizeof(int), 1, fin);
		scrivereRadar(&p[i-1], n);
		inputAttaccoFile(&p[i-1], fin);
		inputDifesaFile(&p[i-1], fin);
		i++;
	}
}

/**
 * inputFlottaFile()
 *
 * DESCRIZIONE
 * Si occupa di leggere da file tutte le navi appartenenti alla flotta di un giocatore
 *
 * INPUT
 * P – giocatore di cui prendere in input la flotta da file – giocatore
 * Fin – file da cui prendere in input la flotta di p – file binario
 *
 * OUTPUT
 * P – giocatore con la flotta presa in input da fin - giocatore
 *
 * LAVORO
 * I – indice per scandire le navi della flotta – numerico – intero>0
 * N – variabile d’appoggio per gli interi da leggere dal file – numerico – intero
 * M – variabile d’appoggio per gli interi da leggere dal file – numerico – intero
 * Y – variabile d’appoggio per i caratteri da leggere da file – carattere
 * C – variabile d’appoggio per le coordinate da passare alle sottofunzioni – coordinata
 */

void inputFlottaFile(giocatore *p, FILE *fin){
	coordinata c;
	int i, n, m;
	char y;
	i=MIN_SHIP;
	while(i<=MAX_SHIP){
		fread(&y, sizeof(char), 1, fin);
		fread(&n, sizeof(int), 1, fin);
		scrivereY(&c, y);
		scrivereX(&c, n);
		fread(&n, sizeof(int), 1, fin);
		fread(&m, sizeof(int), 1, fin);
		scrivereValoreFlotta(p, i, c, n, m);
		i++;
	}
}

/**
 * inputAttaccoFile()
 *
 * DESCRIZIONE
 * Si occupa di leggere dal file di salvataggio selezionato la tabella d'attacco di un giocatore
 *
 * INPUT
 * P – giocatore di cui prendere in input da file la tabella d’attacco – giocatore
 * Fin – file da cui prendere in input la tabella d’attacco di p – file binario
 *
 * OUTPUT
 * P – giocatore con la tabella d’attacco presa in input da fin - giocatore
 *
 * LAVORO
 * I – indice per scandire le righe della tabella d’attacco di p – numerico – intero>0
 * J – indice per scandire le colonne della tabella d’attacco di p – carattere
 * C – variabile d’appoggio per i caratteri da leggere dal file - carattere
 */

void inputAttaccoFile(giocatore *p, FILE *fin){
	int i;
	char j, c;
	i=MIN_ROWS;
	while(i<=MAX_ROWS){
		j=MIN_COLUMN;
		while(j<=MAX_COLUMN){
			fread(&c, sizeof(char), 1, fin);
			scrivereValoreAttacco(p, j, i, c);
			j=successivo(j);
		}
		i++;
	}
}

/**
 * inputDifesaFile()
 *
 * DESCRIZIONE
 * Si occupa di leggere dal file di salvataggio selezionato la tabella di difesa di un giocatore
 *
 * INPUT
 * P – giocatore di cui prendere in input da file la tabella di difesa – giocatore
 * Fin – file da cui prendere in input la tabella di difesa di p – file binario
 *
 * OUTPUT
 * P – giocatore con la tabella di difesa presa in input da fin - giocatore
 *
 * LAVORO
 * I – indice per scandire le righe della tabella di difesa di p – numerico – intero>0
 * J – indice per scandire le colonne della tabella di difesa di p – carattere
 * C – variabile d’appoggio per i caratteri da leggere dal file - carattere
 */

void inputDifesaFile(giocatore *p, FILE *fin){
	int i;
	char j, c;
	i=MIN_ROWS;
	while(i<=MAX_ROWS){
		j=MIN_COLUMN;
		while(j<=MAX_COLUMN){
			fread(&c, sizeof(char), 1, fin);
			scrivereValoreDifesa(p, j, i, c);
			j=successivo(j);
		}
		i++;
	}
}
