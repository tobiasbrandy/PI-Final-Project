#ifndef library_ok

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getnum.h"
#include "random.h"

#define library_ok
#define MBLOCK 150
#define BLOCK 50

typedef struct movementsCDT * movementsADT;
typedef enum {SUNDAY=0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY} weekday;
typedef enum {REGULAR=0, NOREGULAR, PRIVATE} flightClassEnum;
typedef enum {CABOTAGE=0, INTERNATIONAL, NA} flightClasifEnum;
typedef enum {TAKEOFF=0, LANDING} moveTypeEnum; 

typedef flightClasifEnum tClasification[2];
//typedef tClasification tComposition[3]; No me funciono no se porque. Pero como esta ahora si funciona.

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

weekday dateToWeekday(tDate date);
int binarySearch(void ** array, size_t dim, void * elem, int (*comp)(void*, void*));


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