#ifndef airport_ok

#define airport_ok

typedef struct airportCDT * airportADT;

#include "../backend.h"

airportADT createAirport();

/*
* Inserta un nuevo aeropuerto a la lista. Los ordena alfabéticamente según el código OACI.
*/
void insertAirport(airportADT ap, char * oaci, char * denomination, char * province);

void freeAirport(airportADT ap);

/*
* Almacena en un archivo de texto los aeropuertos junto con la cantidad de movimientos de manera descendente.
*/
int storeAirportsByMovs(airportADT ap);

//Si se modifico el TAD (insercion, remocion, etc), el usuario debe ejecutar esta funcion antes de usar cualquier funcion catalogada FAS (Faster Airport Search).
void startFasterAirportSearch(airportADT ap);

//Se recomienda ejecutar esta funcion luego de terminar de usar una tanda de funciones FAS.
void stopFasterAirportSearch(airportADT ap);

//Funcion FAS!
int addMovementToAirport(airportADT ap, char * oaci);

void printAirport(airportADT ap); //Funcion de testeo.

void printTAirportArray(airportADT ap); //funcion de testeo

#endif


