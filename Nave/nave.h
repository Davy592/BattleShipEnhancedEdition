#ifndef NAVE_H_
#define NAVE_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"
#include "..\Coordinata\coordinata.h"

typedef struct{
	coordinata pos;
	int verso;
	int hp;
}nave;

//Prototipi di nave
coordinata leggerePos(nave);
int leggereVerso(nave);
int leggereHp(nave);
void scriverePos(nave*, coordinata);
void scrivereVerso(nave*, int);
void scrivereHp(nave*, int);

#endif
