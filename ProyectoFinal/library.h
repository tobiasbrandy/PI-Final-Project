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


#include "TAD/movementsADT.h"

weekday dateToWeekday(tDate date);

int binarySearch(void ** array, size_t dim, void * elem, int (*comp)(void*, void*));

void matrixAddition(void ** matrix1, void ** matrix2, int dimF, int dimC, int bytes, void (*add)(void*, void*));

void ** createMatrix(int row, int col, int bytes);

void freeMatrix(void ** matrix, int row);

void addInts(int * int1, int * int2);

void addBlockMovementsToAirport(movementsADT mv, airportADT ap);


//FUNCIONES QUE FALTAN. Nombres tentativos jajajaj.

//Funciones Front

//liftAirportADTfromcsv();
//liftBlockMovementsFromcsv();



//Funciones Procesamiento

//binarySearchAirportOACI();



//Funciones de almacenamiento

//storeMovementByWeekday(); (Query 2)
//storeMovementByComposition(); (Query 3)

#endif