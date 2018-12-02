#ifndef movements_ok

#define movements_ok

#include "../backend.h"

/*
*Crea un nuevo movementsTAD
*/
movementsADT createMovements();

/*
*Inserta un nuevo movimiento al TAD. A todos los strings se les hace un deep copy, asique es seguro liberarlos.
*Retorna OK o ERROR.
*/
int insertMovements(movementsADT mov, tDate date, flightClassEnum class, flightClasifEnum clasification, moveTypeEnum moveType, char * origOACI, char * destOACI, char * airline);

/*
*Libera el TAD.
*/
void freeMovements(movementsADT mov);

/*
*Retorna una matriz de 7*NOCLASIF que almacena la cantidad de movimientos del TAD segun dia de la semana y clasificacion.
*/
int ** getMovsByWeekDay(movementsADT mov);

/*
*Retorna una matriz de NOCLASS*NOCLASIF que almacena la cantidad de movimientos del TAD segun la clase y clasificacion.
*/
int ** getMovsComposition(movementsADT mov);

/*
*Retorna el tipo del movimiento i.
*/
moveTypeEnum getMoveType(movementsADT mv, int i);

/*
*Retorna el OACI de destino del movimiento i.
*/
char * getDestOACI(movementsADT mv, int i);

/*
*Retorna el OACI de origen del movimiento i.
*/
char * getOrigOACI(movementsADT mv, int i);

/*
*Retorna la cantidad de elementos del TAD.
*/
size_t getDim(movementsADT mv);

/*
*Imprime el TAD a salida estandar. Funcion de testeo.
*/
void printMovements(movementsADT mv);

#endif
