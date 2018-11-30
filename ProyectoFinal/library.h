#ifndef library_ok

#define library_ok

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getnum.h"
#include "random.h"
#include "TAD/airportADT.h"

#define MBLOCK 150
#define BLOCK 50
#define NOCLASIF 2
#define NOCLASS 3

typedef struct movementsCDT * movementsADT;
typedef enum {SUNDAY=0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY} weekday;
typedef enum {REGULAR=0, NOREGULAR, PRIVATE} flightClassEnum;
typedef enum {CABOTAGE=0, INTERNATIONAL, NA} flightClasifEnum;
typedef enum {TAKEOFF=0, LANDING} moveTypeEnum; 

typedef struct airport{
	char * oaci;
	char * denomination;
	char * province;
	long int movements;
}tAirport;

typedef struct date{
	char day;
	char month;
	size_t year;
}tDate;

typedef struct function{
	int (*function)(void*);
	char * nombre;
	char * description;
	void * argument;
}tFunction;


#include "TAD/movementsADT.h"

weekday dateToWeekday(tDate date);

int binarySearch(void ** array, size_t dim, void * elem, int (*comp)(void*, void*));

void matrixAddition(void ** matrix1, void ** matrix2, size_t dimF, size_t dimC, size_t bytes, void (*add)(void*, void*));

void ** createMatrix(size_t row, size_t col, size_t bytes);

void freeMatrix(void ** matrix, size_t row);

void addInts(int * int1, int * int2);

void addBlockMovementsToAirport(movementsADT mv, airportADT ap);

int storeMovsByWeekdayAndClasif(int ** week);

int storeMovsByClasifAndClass(int ** moveComp);

void menu(tFunction functions[], size_t dim);

void menuEspecializado(void * argument1, void * argument2, void * argument3);


//FUNCIONES QUE FALTAN. Nombres tentativos jajajaj.

//Funciones Front

//liftAirportADTfromcsv();
//liftBlockMovementsFromcsv();size_t

//Funciones de almacenamiento

//storeMovementByWeekday(); (Query 2)
//storeMovementByComposition(); (Query 3)

#endif