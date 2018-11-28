#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getnum.h"
#include "random.h"

#define BLOCK 150

typedef struct movementsCDT * movementsADT;
typedef enum {REGULAR, NOREGULAR, PRIVADOMN, PRIVADOME} flightClassEnum;
typedef enum {CABOTAJE, INTERNACIONAL, NA} flightClasifEnum;
typedef enum {DESPEGUE, ATERRIZAJE} moveTypeEnum; 

typedef struct movement{
	long int cabotage;
	long int international;
}tMovement;

typedef struct moveComposition{
	tMovement regular;
	tMovement notRegular;
	tMovement private;
}moveComposition;

typedef struct date{
	char day;
	char month;
	size_t year;
}tDate;

typedef struct airportMini{
	char * OACI;
	long int movimientos;
}airportMini;



//FUNCIONES QUE FALTAN. Nombres tentativos jajajaj.

//Funciones Front

//liftAirportADTfromcsv();
//liftBlockMovementsFromcsv();



//Funciones Procesamiento

//binarySearchAirportOACI();



//Funciones de almacenamiento

//storeMovementByWeekday(); (Query 2)
//storeMovementByComposition(); (Query 3)

