#ifndef STRING_H_
#define STRING_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"

#define FINESTRINGA '\0'

typedef char* stringa;

//Prototipi di string
stringa inizializzareStringa(int); // Inizializza una stringa per contenere N cartteri più quello terminatore.
void deinizializzareStringa(stringa); // Rilascia la memoria della stringa
char leggereCarattereStringa(stringa, int); // Legge i-esimo carattere della stringa
void scrivereCarattereStringa(stringa, int, char); // scrive c nella i-esima posizione
int leggereDimensioneStringa(stringa); // Legge la dimensione della stringa S
void copiareStringa(stringa, stringa); // Crea una copia di S
void accodareCarattereStringa(stringa, char); // Accoda il carattere c a S
void concatenareStringa(stringa, stringa); // Crea la concatenazione di S, T

#endif
