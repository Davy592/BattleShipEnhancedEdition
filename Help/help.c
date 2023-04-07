#include "help.h"

/**
 * stampareHelp()
 *
 * DESCRIZIONE
 * Stampa a video il contenuto del file regole
 *
 * INPUT
 *
 * OUTPUT
 *
 * LAVORO
 * C – variabile d’appoggio per i caratteri da stampare a video – carattere
 * Regole – file contenente le regole che vanno stampate a video – file di testo
 */

void stampareHelp(){
	char c;
	FILE *regole;
	regole=fopen("C:\\Battleship\\Regole.txt", "r");
	system("cls");
	if(regole==NULL){
		printf("Errore nell'apertura del file regole!\n");
	}else{
		c=fgetc(regole);
		while(c!=EOF){
			printf("%c", c);
			c=fgetc(regole);
		}
		printf("\n\n");
	}
	fclose(regole);
}
