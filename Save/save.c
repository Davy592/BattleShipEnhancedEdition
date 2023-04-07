#include "save.h"

/**
 * SalvarePartita()
 *
 * DESCRIZIONE
 * Si occupa di leggere da tastiera il nome designato per il salvataggio, crea il file,
 * controlla eventuali duplicati ed esegue il salvataggio
 *
 * INPUT
 * P – giocatori di cui salvare la partita – array statico monodimensionale di giocatori – lunghezza=2
 *
 * OUTPUT
 * Fout – file su cui salvare la partita – file binario
 *
 * LAVORO
 * percorso - percorso del file su cui salvare la partita - stringa
 * nomeFile - nome del file su cui salvare la partita - stringa
 * scelta – indica se il giocatore ha scelto il file su cui (sovra)scrivere le informazioni - booleano
 */

void salvarePartita(giocatore p[]){
	FILE *fout;
	stringa percorso, nomeFile;
	int scelta;
	percorso=inizializzareStringa(LUNGHEZZAPERCORSO);
	nomeFile=inizializzareStringa(LUNGHEZZAPERCORSO);
	scelta=FALSO;
	do{
		printf("Inserire il nome da assegnare al salvataggio di questa partita: ");
		scanf("%s", nomeFile);
		copiareStringa(percorso, "C:\\BattleShip\\Salvataggi\\\0");
		concatenareStringa(percorso, nomeFile);
		concatenareStringa(percorso, ".dat\0");
		fout=fopen(percorso, "r");
		if(fout==NULL){
			fclose(fout);
			scelta=VERO;
			fout=fopen(percorso, "w");
			stampaTuttoFile(p, fout);
			fclose(fout);
		}else{
			fclose(fout);
			printf("Un file di salvataggio con questo nome e' gia' presente, sovrascriverlo? (0=NO, 1=SI): ");
			scelta=inputInteroCheck(FALSO, VERO);
			if(scelta==VERO){
				fout=fopen(percorso, "w");
				stampaTuttoFile(p, fout);
				fclose(fout);
			}
		}
	}while(scelta==FALSO);
	deinizializzareStringa(nomeFile);
	deinizializzareStringa(percorso);
}

/**
 * StampaTuttoFile()
 *
 * DESCRIZIONE
 * Stampa sul file di salvataggio tutte le informazioni inerenti i due giocatori e lo stato della partita
 *
 * INPUT
 * P – giocatori di cui stampare le informazioni su file – array statico monodimensionale di giocatori – lunghezza=2
 * fout - file su cui stampare le informazioni - file binario
 *
 * OUTPUT
 * fout - file con le informazioni dei giocatori stampate - file binario
 *
 * LAVORO
 * n - variabile d’appoggio per gli interi da stampare – numerico - intero
 * nome - nome del giocatore da stampare – stringa
 * i – indice per scandire i giocatori – numerico – intero>0
 */

void stampaTuttoFile(giocatore p[], FILE *fout){
	int i, n;
	stringa nome;
	i=MIN_PLAYER;
	while(i<=MAX_PLAYER){
		nome=inizializzareStringa(LUNGHEZZANOME);
		n=leggereTurno(p[i-1]);
		fwrite(&n, sizeof(int), 1, fout);
		leggereNome(p[i-1], nome);
		fwrite(nome, sizeof(char), LUNGHEZZANOME, fout);
		stampaFlottaFile(p[i-1], fout);
		n=leggereLargoRaggio(p[i-1]);
		fwrite(&n, sizeof(int), 1, fout);
		n=leggereBombardamento(p[i-1]);
		fwrite(&n, sizeof(int), 1, fout);
		n=leggereRadar(p[i-1]);
		fwrite(&n, sizeof(int), 1, fout);
		stampaAttaccoFile(p[i-1], fout);
		stampaDifesaFile(p[i-1], fout);
		deinizializzareStringa(nome);
		i++;
	}
}

/**
 * stampaFlottaFile()
 *
 * DESCRIZIONE
 * Stampa sul file di salvataggio le informazioni inerenti la flotta di un giocatore
 *
 * INPUT
 * P – giocatore di cui stampare su file la flotta – giocatore
 * Fout – file su cui stampare la flotta di p – file binario
 *
 * OUTPUT
 * Fout – file con la flotta di p stampata – file binario
 *
 * LAVORO
 * C – variabile d’appoggio per i caratteri da stampare – carattere
 * N – variabile d’appoggio per gli interi da stampare – numerico – intero
 * I – indice per scandire le navi della flotta di p – numeric – intero>0
 */

void stampaFlottaFile(giocatore p, FILE *fout){
	char c;
	int i, n;
	i=MIN_SHIP;
	while(i<=MAX_SHIP){
		c=leggereY(leggerePos(leggereValoreFlotta(p, i)));
		fwrite(&c, sizeof(char), 1, fout);
		n=leggereX(leggerePos(leggereValoreFlotta(p, i)));
		fwrite(&n, sizeof(int), 1, fout);
		n=leggereVerso(leggereValoreFlotta(p, i));
		fwrite(&n, sizeof(int), 1, fout);
		n=leggereHp(leggereValoreFlotta(p, i));
		fwrite(&n, sizeof(int), 1, fout);
		i++;
	}
}

/**
 * stampaAttaccoFile()
 *
 * DESCRIZIONE
 * Stampa sul file di salvataggio tutta la tabella d'attacco di un giocatore
 *
 * INPUT
 * P – giocatore di cui stampare su file la tabella d’attacco – giocatore
 * Fout – file su cui stampare la tabella d’attacco di p – file binario
 *
 * OUTPUT
 * Fout – file con la tabella d’attacco di p stampata – file binario
 *
 * LAVORO
 * C – variabile d’appoggio per i caratteri da stampare – carattere
 * X – indice per scandire le righe della tabella d’attacco di p – numerico – intero>0
 * Y – indice per scandire le colonne della tabella d’attacco di p - carattere
 */

void stampaAttaccoFile(giocatore p, FILE *fout){
	int x;
	char y, c;
	x=MIN_ROWS;
	while(x<=MAX_ROWS){
		y=MIN_COLUMN;
		while(y<=MAX_COLUMN){
			c=leggereValoreAttacco(p, y, x);
			fwrite(&c, sizeof(char), 1, fout);
			y=successivo(y);
		}
		x++;
	}
}

/**
 * stampaDifesaFile()
 *
 * DESCRIZIONE
 * Stampa sul file di salvataggio tutta la tabella di difesa di un giocatore
 *
 * INPUT
 * P – giocatore di cui stampare su file la tabella di difesa – giocatore
 * Fout – file su cui stampare la tabella di difesa di p – file binario
 *
 * OUTPUT
 * Fout – file con la tabella di difesa di p stampata – file binario
 *
 * LAVORO
 * C – variabile d’appoggio per i caratteri da stampare – carattere
 * X – indice per scandire le righe della tabella di difesa di p – numerico – intero>0
 * Y – indice per scandire le colonne della tabella di difesa di p - carattere
 */

void stampaDifesaFile(giocatore p, FILE *fout){
	int x;
	char y, c;
	x=MIN_ROWS;
	while(x<=MAX_ROWS){
		y=MIN_COLUMN;
		while(y<=MAX_COLUMN){
			c=leggereValoreDifesa(p, y, x);
			fwrite(&c, sizeof(char), 1, fout);
			y++;
		}
		x++;
	}
}
