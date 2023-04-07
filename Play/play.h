#ifndef PLAY_H_
#define PLAY_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"
#include "..\Giocatore\giocatore.h"
#include "..\String\string.h"
#include "..\Save\save.h"

//Prototipi di play
int gioca(giocatore[]);
int operazioniPossibili(giocatore);
void eseguireOperazione(giocatore[], int, int);
void sparareColpoClassico(giocatore[], int, char, int);
int trovareNave(giocatore, char, int);
void affondaNave(giocatore[], int, int);
void sparareLargoRaggio(giocatore[], int);
void sparareBombardamento(giocatore[], int);
void usareRadar(giocatore[], int);
void analizzareCella(giocatore[], int, char, int);
int controllaNavi(giocatore);

#endif
