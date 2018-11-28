#include "../process.h"

typedef struct airportCDT * airportADT;

airportADT createAirport();

/*
* Inserta un nuevo aeropuerto a la lista. Los ordena alfabéticamente según el código OACI.
*/
airportADT insertAirport(airportADT airport, char * oaci, char * denomination, char * province);

void freeAirport(airportADT airport);

/*
* Crea un array de una estructura de aeropuertos reducidos, que solo tienen el OACI y la cantidad de movimientos.
*/
airportADT * airportToArray(airportADT airport, int * dim);

/*
* Recibe un array de estructuras de aeropuertos reducidos cuyo orden coincide con la lista y reemplaza los valores
* de movimientos de la lista por los del array.
*/
//void updateMovsWithArray(airportMini * airportMini); CREO QUE NO HACE FALTA!

/*
* Crea una copia de la lista que está ordenada según la cantidad de movimientos de manera descendente y secundariamente
* alfabéticamente por código OACI
*/
//static airportADT cpyAirportByMovs(airportADT airport); NO TIENE QUE IR EN EL .H PORQUE ES STATIC.

/*
* Almacena en un archivo de texto los aeropuertos junto con la cantidad de movimientos de manera descendente.
*/
int storageByMovs(airportADT airport);
