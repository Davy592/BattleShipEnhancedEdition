#ifndef COORDINATA_H_
#define COORDINATA_H_

#include <stdio.h>
#include <stdlib.h>

#include "..\Global\global.h"

typedef struct{
	char y;
	int x;
}coordinata;

//Prototipi di coordinata
char leggereY(coordinata);
int leggereX(coordinata);
void scrivereY(coordinata*, char);
void scrivereX(coordinata*, int);
coordinata inputCoordinataCheck(char, char, int, int);

#endif
