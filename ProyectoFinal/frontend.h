#ifndef frontend_ok

#define frontend_ok

#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getnum.h"
#include "TAD/airportADT.h"
#include "TAD/movementsADT.h"

typedef struct function{
	int (*function)(void*);
	char * nombre;
	char * description;
	void * argument;
}tFunction;

/*
*Retorna un nuevo movementsADT con los siguientes MBOLCK movimientos (o los que queden)
*guardados en el archivo de texto p.
*De haber algun problema en el proceso se lo informara al usuario 
*mediante la salida estandar y cortara ejecucion.
*/
movementsADT liftBlockMovements(char * p);

/*
*Inserta en el TAD de aeropuertos ap todos los aeropuertos guardados en el archivo de texto filename
*que tengan OACI.
*De haber algun problema en el proceso se lo informara al usuario mediante 
*la salida estandar y cortara ejecucion.
*/
void liftAirports(airportADT ap, char * fileName);

/*
*Implementacion de menu relativamente generica.
*/
void menu(tFunction functions[], size_t dim);

/*
*Realiza las preparaciones necesarias para utilizar la funcion menu para los fines de este programa.
*/
void menuEspecializado(void * argument1, void * argument2, void * argument3);


#endif