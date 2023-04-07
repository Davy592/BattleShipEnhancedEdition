#include "global.h"

/**
 * inputInteroCheck()
 *
 * DESCRIZIONE
 * Legge da tastiera un intero che rispetta le limitazioni
 *
 * INPUT
 * Min – valore minimo che puo assumere l’intero in input da tastiera – numerico – intero
 * Max – valore massimo che puo assumere l’intero letto da tastiera – numerico – intero
 *
 * OUTPUT
 * Out – intero letto da tastiera compreso fra min e max – numerico – intero
 *
 * LAVORO
 *
 */

int inputInteroCheck(int min, int max){
	int out;
	do{
		fflush(stdin);
		scanf("%d", &out);
		if(out<min || out>max){
			printf("Inserire un valore compreso fra %d e %d: ", min, max);
		}
	}while(out<min || out>max);
	return out;
}

/**
 * inputCharCheck()
 *
 * DESCRIZIONE
 * Legge da tastiera un carattere che rispetta le limitazioni
 *
 * INPUT
 * Min – valore minimo che puo assumere il carattere in input da tastiera – carattere
 * Max – valore massimo che puo assumere il carattere in input da tastiera – carattere
 *
 * OUTPUT
 * Out – carattere letto da tastiera compreso fra min e max – carattere
 *
 * LAVORO
 *
 */

char inputCharCheck(char min, char max){
	char out;
	do{
		fflush(stdin);
		scanf("%c", &out);
		if(out<min || out>max){
			printf("Inserire un valore compreso fra %c e %c: ", min, max);
		}
	}while(out<min || out>max);
	return out;
}

/**
 * minChar()
 *
 * DESCRIZIONE
 * Dati due caratteri restituisce quello minore (in ordine lessicografico) tra i due
 *
 * INPUT
 * A – primo carattere da confrontare – carattere
 * B – secondo carattere da confrontare – carattere
 *
 * OUTPUT
 * R – carattere minore (in ordine lessicografico) tra a e b – carattere
 *
 * LAVORO
 *
 */

char minChar(char a, char b){
	char r;
	if(a<b){
		r=a;
	}else{
		r=b;
	}
	return r;
}

/**
 * maxChar()
 *
 * DESCRIZIONE
 * Dati due caratteri restituisce quello maggiore (in ordine lessicografico) tra i due
 *
 * INPUT
 * A – primo carattere da confrontare – carattere
 * B – secondo carattere da confrontare – carattere
 *
 * OUTPUT
 * R – carattere maggiore (in ordine lessicografico) tra a e b – carattere
 *
 * LAVORO
 *
 */

char maxChar(char a, char b){
	char r;
	if(a>b){
		r=a;
	}else{
		r=b;
	}
	return r;
}

/**
 * minInt()
 *
 * DESCRIZIONE
 * Dati due interi restituisce quello minore tra i due.
 *
 * INPUT
 * A – primo intero da confrontare – numerico - intero
 * B – secondo intero da confrontare – numerico - intero
 *
 * OUTPUT
 * R – intero minore tra a e b – numerico - intero
 *
 * LAVORO
 *
 */

int minInt(int a, int b){
	int r;
	if(a<b){
		r=a;
	}else{
		r=b;
	}
	return r;
}

/**
 * maxInt()
 *
 * DESCRIZIONE
 * Dati due interi restituisce quello maggiore tra i due.
 *
 * INPUT
 * A – primo intero da confrontare – numerico - intero
 * B – secondo intero da confrontare – numerico - intero
 *
 * OUTPUT
 * R – intero maggiore tra a e b – numerico - intero
 *
 * LAVORO
 *
 */

int maxInt(int a, int b){
	int r;
	if(a>b){
		r=a;
	}else{
		r=b;
	}
	return r;
}

/**
 * dimNave()
 *
 * DESCRIZIONE
 * Ritorna la dimensione di una nave
 *
 * INPUT
 * numNave - numero della nave - numerico – MIN_SHIP<=intero<=MAX_SHIP
 *
 * OUTPUT
 * dim - dimensione della nave data - numerico - 1<=intero<=5
 *
 * LAVORO
 *
 */

int dimNave(int numNave){
	int dim;
	if(numNave==1){  //sulla base del numero di nave che sto inserendo posso ricavare la sua dimensione (faccio inserire le navi in ordine decrescente di dimensione)
		dim=5;
	}else if(numNave<=3){
		dim=4;
	}else if(numNave<=6){
		dim=3;
	}else if(numNave<=10){
		dim=2;
	}else{
		dim=1;
	}
	return dim;
}

/**
 * toUpperCase()
 *
 * DESCRIZIONE
 * Converte i caratteri da minuscoli a maiuscoli
 *
 * INPUT
 * c – carattere da convertire in maiuscolo se minuscolo - carattere
 *
 * OUTPUT
 * c – carattere ottenuto dopo la conversione - carattere
 *
 * LAVORO
 *
 */

char toUpperCase(char c){
	if(c>='a' && c<='z'){
		c=c-'a'+'A';
	}
	return c;
}

/**
 * upperCaseToInt()
 *
 * DESCRIZIONE
 * Converte una lettera maiuscola nel numero corrispondente ('A'=1, 'B'=2...)
 *
 * INPUT
 * c – lettera maiuscola da convertire in intero – carattere – MIN_ALPHABET<=carattere<=MAX_ALPHABET
 *
 * OUTPUT
 * n – intero ottenuto dalla conversione di c – numerico – N_MIN_ALPHABET<=intero<=N_MAX_ALPHABET
 *
 * LAVORO
 *
 */

int upperCaseToInt(char c){
	int n;
	n=c-'A'+1;
	return n;
}

/**
 * Successivo()
 *
 * DESCRIZIONE
 * Dato un carattere ASCII ritorna il carattere immediatamente successivo
 *
 * INPUT
 * c – lettera maiuscola di cui trovare la successiva – carattere – ‘A’<=carattere<=’Y’
 *
 * OUTPUT
 * s – lettera successiva di c – carattere – ‘B’<=carattere<=’Z’
 *
 * LAVORO
 *
 */

char successivo(char c){  //in C si può ottenere il successivo semplicemente sommando
	char s;
	s=c+1;
	return s;
}

/**
 * stampaCaratteri()
 *
 * DESCRIZIONE
 * Stampa a video lo stesso carattere ripetuto più volte
 *
 * INPUT
 * C – carattere da stampare – carattere
 * N – indica quante volte si deve stampare il carattere c – numerico – intero>=0
 *
 * OUTPUT
 *
 * LAVORO
 * I – variabile contatore per scandire le varie stampe – numerico – intero>=1
 */

void stampaCaratteri(char c, int n){
	int i;
	i=1;
	while(i<=n){
		printf("%c", c);
		i++;
	}
}
