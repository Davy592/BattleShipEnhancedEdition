#include "string.h"

//Funzioni d'accesso di stringa

/**
 * inizializzareStringa()
 *
 * DESCRIZIONE
 * Inizializza la memoria per contenere una stringa
 *
 * INPUT
 * n - lunghezza della stringa da inizializzare - numerico - intero>=0
 *
 * OUTPUT
 * s - stringa inizializzata - stringa
 *
 * LAVORO
 *
 */

stringa inizializzareStringa(int N){
	stringa S;
	S=(stringa)malloc(sizeof(char)*(N+1)); //La stringa da restituire per avere N caratteri piu' quello terminatore
	scrivereCarattereStringa(S, 1, FINESTRINGA);
	return S;
}

/**
 * deinizializzareStringa()
 *
 * DESCRIZIONE
 * Libera la memoria occupata da una stringa
 *
 * INPUT
 * s - stringa di cui liberare la memoria - stringa
 *
 * OUTPUT
 * s - stringa deinizializzata - stringa
 *
 * LAVORO
 *
 */

void deinizializzareStringa(stringa S){
	if(S!=NULL){
		free(S);
		S=NULL;
	}
}

/**
 * leggereCarattereStringa()
 *
 * DESCRIZIONE
 * Ritorna un carattere di una stringa
 *
 * INPUT
 * S – stringa di cui leggere un carattere – stringa
 * I – posizione del carattere da leggere – numerico - intero
 *
 * OUTPUT
 * C – carattere in posizione i di S - carattere
 *
 * LAVORO
 *
 */

char leggereCarattereStringa(stringa S, int i){
	char c; // il carattere letto
	c=*(S+i-1);  //(-1) perche in C i vettori partono da 0.
	return c;
}

/**
 * scrivereCarattereStringa()
 *
 * DESCRIZIONE
 * Modifica un carattere di una stringa
 *
 * INPUT
 * S – stringa di cui modificare un carattere – stringa
 * I – posizione del carattere da modificare – numerico – intero
 * C – carattere da inserire in posizione i di S - carattere
 *
 * OUTPUT
 * S – stringa con il carattere in posizione i modificato - stringa
 *
 * LAVORO
 *
 */

void scrivereCarattereStringa(stringa S, int i, char c){
	*(S+i-1)=c;  //(-1) perche in C i vettori partono da 0.
}

/**
 * leggereDimensioneStringa()
 *
 * DESCRIZIONE
 * Ritorna la lunghezza di una stringa
 *
 * INPUT
 * S – stringa di cui leggere la dimensione - stringa
 *
 * OUTPUT
 * Dim – dimensione di S – numerico – intero>=0
 *
 * LAVORO
 *
 */

int leggereDimensioneStringa(stringa S){
	int dim; // La dimensione di S
	dim=0;
	while(leggereCarattereStringa(S, dim+1)!=FINESTRINGA){
		dim++;
	}
	return dim;
}

/**
 * copiareStringa()
 *
 * DESCRIZIONE
 * Copia il contenuto di una stringa dentro un'altra
 *
 * INPUT
 * D – dove copiare la stringa S (destinazione) - stringa
 * S – stringa da copiare (sorgente) – stringa
 *
 * OUTPUT
 * D – stringa dopo la copia di S - stringa
 *
 * LAVORO
 * I – indice per scandire i caratteri di S – numerico - intero
 */

void copiareStringa(stringa D, stringa S){
	int i;
	if(S!=NULL){
		D=(stringa)realloc(D, (leggereDimensioneStringa(S)+1)*sizeof(char));  //realloco della dimensione della sorgente +1 per il FINESTRINGA
		i=1;
		while(leggereCarattereStringa(S, i)!=FINESTRINGA){
			scrivereCarattereStringa(D, i, leggereCarattereStringa(S, i));
			i++;
		}
		scrivereCarattereStringa(D, i, FINESTRINGA);
	}
}

/**
 * accodareCarattereStringa()
 *
 * DESCRIZIONE
 * Accoda un singolo carattere ad una stringa
 *
 * INPUT
 * S – stringa a cui accodare un carattere – stringa
 * c – carattere da accodare a S - carattere
 *
 * OUTPUT
 * S – stringa con carattere accodato - stringa
 *
 * LAVORO
 * N – lunghezza di S – numerico – intero>=0
 */

void accodareCarattereStringa(stringa S, char c){
	int N; // La dimensione di S
	N=leggereDimensioneStringa(S);
	S=(stringa)realloc(S, (N+2)*sizeof(char));
	scrivereCarattereStringa(S, N+1, c);
	scrivereCarattereStringa(S, N+2, FINESTRINGA);
}

/**
 * concatenareStringa()
 *
 * DESCRIZIONE
 * Concatena due stringhe (di fatto accoda il contenuto della seconda stringa alla prima)
 *
 * INPUT
 * D – stringa a cui concatenarne un'altra (destinazione) – stringa
 * S – stringa da concatenare a D (sorgente) - stringa
 *
 * OUTPUT
 * D – stringa dopo la concatenazione con S - stringa
 *
 * LAVORO
 * I – indice per scandire i caratteri di S – numerico – intero>0
 */

void concatenareStringa(stringa D, stringa S){
	int i;
	i=1;
	while(leggereCarattereStringa(S, i)!=FINESTRINGA){
		accodareCarattereStringa(D, leggereCarattereStringa(S, i));
		i++;
	}
}
