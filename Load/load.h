#ifndef LOAD_H_
#define LOAD_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"
#include "..\String\string.h"
#include "..\Giocatore\giocatore.h"

//Prototipi di load
void aperturaFileSalvataggio(giocatore[]);
int sceltaFile();
int stampaElenco();
void trovareNomeFile(char[], int);
void caricamentoDati(giocatore[], FILE*);
void inputFlottaFile(giocatore*, FILE*);
void inputAttaccoFile(giocatore*, FILE*);
void inputDifesaFile(giocatore*, FILE*);

#endif
