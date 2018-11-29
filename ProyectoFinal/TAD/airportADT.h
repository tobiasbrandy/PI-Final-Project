#include "../process.h"

typedef struct airportCDT * airportADT;

airportADT createAirport();

/*
* Inserta un nuevo aeropuerto a la lista. Los ordena alfabéticamente según el código OACI.
*/
airportADT insertAirport(airportADT ap, char * oaci, char * denomination, char * province);

void freeAirport(airportADT ap);

/*
* Crea un array de una estructura de aeropuertos reducidos, que solo tienen el OACI y la cantidad de movimientos.
*/
tAirport ** airportToArray(airportADT ap, int * dim);

/*
* Almacena en un archivo de texto los aeropuertos junto con la cantidad de movimientos de manera descendente.
*/
int storageByMovs(airportADT ap);

void printAirport(airportADT ap); //Funcion de testeo.


