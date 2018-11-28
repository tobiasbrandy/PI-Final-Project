#ifndef library_ok

#include <stdio.h>
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
typedef enum {REGULAR, NOREGULAR, PRIVADOMN, PRIVADOME} flightClassEnum;
typedef enum {CABOTAJE, INTERNACIONAL, NA} flightClasifEnum;
typedef enum {DESPEGUE, ATERRIZAJE} moveTypeEnum; 

typedef struct airport{
	char * oaci;
	char * denomination;
	char * province;
	long int movements;
}tAirport;

typedef struct flightClasification{
	long int cabotage;
	long int international;
}tClasification;

typedef struct composition{
	tClasification regular;
	tClasification notRegular;
	tClasification private;
}tComposition;

typedef struct date{
	char day;
	char month;
	size_t year;
}tDate;

/*typedef struct airportMini{ //Para la busqueda binaria. CREO QUE NO HACE FALTA!
	char * oaci;
	long int movements;
}airportMini;
*/


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