#include "../main.h"

typedef struct airportCDT * airportADT;

airportADT createAirport();

/*
* Inserta un nuevo aeropuerto a la lista. Los ordena alfabéticamente segun el OACI.
*/
airportADT insertAirport(char * oaci, char * denom, char * province);

void freeAirport(airportADT airport);

/*
*Crea un array de una estructura de aeropuertos reducidos, que solo tienen el OACI y la cantidad de movimientos.
*/
airportMini * airportToArray(airportADT airport, int * dim);

/*
*Recibe un array de estructuras de aeropuertos reducidos cuyo orden coincide con la lista y reemplaza los valores
*de movimientos de la lista por los del array.
*/
void updateMovsWithArray(airportMini * airportMini);

/*
*Crea una copia de la lista que esta ordenada segun la cantidad de movimientos de manera descendiente y secundariamente
*por el orden del OACI.
*/
//static airportADT sortByMovs(airportADT airport); NO TIENE QUE IR EN EL .H PORQUE ES STATIC.

/*
*Almacena en un archivo de texto los aeropuertos juntos con la cantidad de movimientos de manera descendiente.
*/
int storageByMovs(airportADT airport);
