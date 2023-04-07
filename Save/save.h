#ifndef SAVE_H_
#define SAVE_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"
#include "..\String\string.h"
#include "..\Giocatore\giocatore.h"

//Prototipi di save
void salvarePartita(giocatore[]);
void stampaTuttoFile(giocatore[], FILE*);
void stampaFlottaFile(giocatore, FILE*);
void stampaAttaccoFile(giocatore, FILE*);
void stampaDifesaFile(giocatore, FILE*);

#endif
