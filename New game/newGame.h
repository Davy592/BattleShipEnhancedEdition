#ifndef NEWGAME_H_
#define NEWGAME_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"
#include "..\String\string.h"
#include "..\Giocatore\giocatore.h"

//Prototipi di newGame
void inserimentoDati(giocatore[]);
void posizionareNave(giocatore*, int);
int controlloNaveFuoriMappa(coordinata, int, int);
int controlloToccoAltreNavi(giocatore, coordinata, int, int);
void aggiungiNaveDifesa(giocatore*, coordinata, int, int);

#endif
