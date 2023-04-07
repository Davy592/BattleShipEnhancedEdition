#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <stdio.h>
#include <stdlib.h>

#define LUNGHEZZAPERCORSO 200
#define LUNGHEZZANOME 80
#define LUNGHEZZARIGA 120
#define LARGHEZZACAMPO 57
#define LARGHEZZASPAZIATURA 6
#define LARGHEZZABORDOINTESTAZIONE 25
#define LARGHEZZABORDOCOLUMNS 13
#define LARGHEZZABORDOROWS 8
#define MIN_ROWS 1
#define MAX_ROWS 16
#define MIN_COLUMN 'A'
#define MAX_COLUMN 'P'
#define MIN_SHIP 1
#define MAX_SHIP 15
#define MIN_LARGE 0
#define MAX_LARGE 3
#define MIN_BOMB 0
#define MAX_BOMB 1
#define MIN_TURNO_BOMB 10
#define MIN_RADAR 0
#define MAX_RADAR 3
#define MIN_PLAYER 1
#define MAX_PLAYER 2
#define VERO 1
#define FALSO 0
#define RED "\x1b[31m"
#define ORANGE "\x1b[31;1m"  //Bright Red
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
//#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

//Prototipi di funzioni globali
int inputInteroCheck(int, int);
char inputCharCheck(char, char);
char minChar(char, char);
char maxChar(char, char);
int minInt(int, int);
int maxInt(int, int);
int dimNave(int);
char toUpperCase(char);
int upperCaseToInt(char);
char successivo(char);
void stampaCaratteri(char, int);

#endif
