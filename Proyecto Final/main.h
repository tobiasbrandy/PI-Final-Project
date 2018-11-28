#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getnum.h"
#include "random.h"

#define BLOCK 150

typedef struct moveTypeS{
	long int cabotaje;
	long int internacional;
}moveTypeS;

typedef struct moveComposition{
	moveTypeS regular;
	moveTypeS notRegular;
	moveTypeS private;
}moveComposition;

typedef struct date{
	char day;
	char month;
	size_t year;
}date;

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

