#include "nave.h"

//Funzioni d'accesso di nave

/**
 * leggerePos()
 *
 * DESCRIZIONE
 * Ritorna la coordinata iniziale di una nave
 *
 * INPUT
 * n – nave di cui leggere la coordinata della cella iniziale – nave
 *
 * OUTPUT
 * c – coordinata della cella iniziale della nave – coordinata
 *
 * LAVORO
 *
 */

coordinata leggerePos(nave n){
	coordinata c;
	c=n.pos;
	return c;
}

/**
 * leggereVerso()
 *
 * DESCRIZIONE
 * Ritorna il verso di una nave
 *
 * INPUT
 * n – nave di cui leggere il verso – nave
 *
 * OUTPUT
 * v – verso della nave – booleano – FALSO=orizzontale, VERO=verticale
 *
 * LAVORO
 *
 */

int leggereVerso(nave n){
	int v;
	v=n.verso;
	return v;
}

/**
 * leggereHp()
 *
 * DESCRIZIONE
 * Ritorna il numero di hp rimasti ad una nave
 *
 * INPUT
 * n – nave di cui leggere il numero di celle non ancora colpite – nave
 *
 * OUTPUT
 * Hp  – numero di celle non ancora colpite della nave – numerico – 0<=intero<=5
 *
 * LAVORO
 *
 */

int leggereHp(nave n){
	int h;
	h=n.hp;
	return h;
}

/**
 * scriverePos()
 *
 * DESCRIZIONE
 * Modifica la coordinata iniziale di una nave
 *
 * INPUT
 * n – nave di cui modificare la coordinata della cella iniziale – nave
 * c – nuovo valore della coordinata della cella iniziale della nave – coordinata
 *
 * OUTPUT
 * n – nave con la coordinata della cella iniziale modificata – nave
 *
 * LAVORO
 *
 */

void scriverePos(nave *n, coordinata c){
	n->pos=c;
}

/**
 * scrivereVerso()
 *
 * DESCRIZIONE
 * Modifica il verso di una nave
 *
 * INPUT
 * n – nave di cui modificare il verso – nave
 * verso – nuovo verso della nave – booleano – FALSO=orizzontale, VERO=verticale
 *
 * OUTPUT
 * n – nave con il verso modificato – nave
 *
 * LAVORO
 *
 */

void scrivereVerso(nave *n, int verso){
	n->verso=verso;
}

/**
 * scrivereHp()
 *
 * DESCRIZIONE
 * Modifica il numero di hp rimasti ad una nave
 *
 * INPUT
 * n – nave di cui modificare i punti vita rimanenti (celle non ancora colpite) – nave
 * hp – nuovo valore dei punti vita rimanenti della nave - numerico – 0<=intero<=5
 *
 * OUTPUT
 * n – nave con i punti vita rimanenti modificati – nave
 *
 * LAVORO
 *
 */

void scrivereHp(nave *n, int hp){
	n->hp=hp;
}

//Fine funzioni d'accesso
