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
* Recibe un array de estructuras de aeropuertos reducidos cuyo orden coincide con la lista y reemplaza los valores
* de movimientos de la lista por los del array.
*/
//void updateMovsWithArray(airportMini * airportMini); CREO QUE NO HACE FALTA!

/*
* Almacena en un archivo de texto los aeropuertos junto con la cantidad de movimientos de manera descendente.
*/
int storageByMovs(airportADT ap);

void printAirport(airportADT ap); //Funcion de testeo.


