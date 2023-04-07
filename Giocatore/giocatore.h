#ifndef GIOCATORE_H_
#define GIOCATORE_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"
#include "..\String\string.h"
#include "..\Coordinata\coordinata.h"
#include "..\Nave\nave.h"

typedef struct{
	int turno;
	stringa nome;
	char attacco[MAX_ROWS][MAX_ROWS];
	char difesa[MAX_ROWS][MAX_ROWS];
	nave flotta[MAX_SHIP];
	int largoRaggio;
	int bombardamento;
	int radar;
}giocatore;

//Prototipi di giocatore
int leggereTurno(giocatore);
void leggereNome(giocatore, stringa);
char leggereValoreAttacco(giocatore, char, int);
char leggereValoreDifesa(giocatore, char, int);
nave leggereValoreFlotta(giocatore, int);
int leggereLargoRaggio(giocatore);
int leggereBombardamento(giocatore);
int leggereRadar(giocatore);
void scrivereTurno(giocatore*, int);
void incrementareTurno(giocatore*);
void decrementareTurno(giocatore*);
void inizializzareNome(giocatore*);
void deinizializzareNome(giocatore*);
void scrivereNome(giocatore*, char[]);
void scrivereValoreDifesa(giocatore*, char, int, char);
void scrivereValoreAttacco(giocatore*, char, int, char);
void scrivereValoreFlotta(giocatore*, int, coordinata, int, int);
void scrivereLargoRaggio(giocatore*, int);
void decrementareLargoRaggio(giocatore*);
void scrivereBombardamento(giocatore*, int);
void decrementareBombardamento(giocatore*);
void scrivereRadar(giocatore*, int);
void decrementareRadar(giocatore*);
void decrementareHp(giocatore*, int);
void riempireDifesa(giocatore*, char);
void riempireAttacco(giocatore*, char);
void stampaDifesa(giocatore);
void stampaAttacco(giocatore);
void stampaTabelle(giocatore);

#endif
