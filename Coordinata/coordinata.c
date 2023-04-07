#include "coordinata.h"

//Funzioni d'accesso di coordinata

/**
 * leggereY()
 *
 * DESCRIZIONE
 * Restituisce l'ordinata di una coordinata
 *
 * INPUT
 * c – coordinata di cui leggere la colonna – coordinata
 *
 * OUTPUT
 * r – colonna di c – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 *
 * LAVORO
 *
 */

char leggereY(coordinata c){
	char r;
	r=c.y;
	return r;
}

/**
 * leggereX()
 *
 * DESCRIZIONE
 * Restituisce l'ascissa di una coordinata
 *
 * INPUT
 * c – coordinata di cui leggere la riga – coordinata
 *
 * OUTPUT
 * r – riga di c – numerico – MIN_ROWS<=intero<=MAX_ROWS
 *
 * LAVORO
 *
 */

int leggereX(coordinata c){
	int r;
	r=c.x;
	return r;
}

/**
 * scrivereY()
 *
 * DESCRIZIONE
 * Modifica l'ordinata di una coordianta
 *
 * INPUT
 * c – coordinata di cui scrivere la colonna – coordinata
 * r – valore da scrivere come colonna di c – carattere – MIN_COLUMN<=carattere<=MAX_COLUMN
 *
 * OUTPUT
 * c – coordinata con colonna modificata – coordinata
 *
 * LAVORO
 *
 */

void scrivereY(coordinata *c, char r){
	c->y=r;
}

/**
 * scrivereX()
 *
 * DESCRIZIONE
 * Modifica l'ascissa di una coordianta
 *
 * INPUT
 * c – coordinata di cui scrivere la riga – coordinata
 * r – valore da scrivere come riga di c – numerico – MIN_ROWS<=intero<=MAX_ROWS
 *
 * OUTPUT
 * c – coordinata con riga modificata – coordinata
 *
 * LAVORO
 *
 */

void scrivereX(coordinata *c, int r){
	c->x=r;
}

//Fine funzioni d'accesso

/**
 * inputCoordinataCheck()
 *
 * DESCRIZIONE
 * Legge da tastiera una coordinata (ascissa ed ordinata) che rispetta le limitazioni
 *
 * INPUT
 * minY – valore minimo che può assumere la colonna della coordinata letta da tastiera – carattere
 * maxY – valore massimo che può assumere la colonna della coordinata letta da tastiera – carattere
 * minX – valore minimo che può assumere la riga della coordinata letta da tastiera – numerico - intero
 * maxX – valore massimo che può assumere la riga della coordinata letta da tastiera – numerico – intero
 *
 * OUTPUT
 * C – coordinata letta da tastiera che rispetta le limitazioni – coordinata
 *
 * LAVORO
 * Y – colonna letta da tastiera – carattere
 * X – riga letta da tastiera – numerico – intero
 */

coordinata inputCoordinataCheck(char minY, char maxY, int minX, int maxX){
	coordinata c;
	char y;
	int x;
	do{
		fflush(stdin);
		scanf("%c-%d", &y, &x);
		//printf("Ho preso %c-%d\n\n\n", y, x);
		y=toUpperCase(y);
		if(y<minY || y>maxY || x<minX || x>maxX){
			printf("La colonna deve essere compresa fra %c e %c e la riga deve essere compresa fra %d e %d: ", minY, maxY, minX, maxX);
		}
	}while(y<minY || y>maxY || x<minX || x>maxX);
	scrivereY(&c, y);
	scrivereX(&c, x);
	return c;
}
