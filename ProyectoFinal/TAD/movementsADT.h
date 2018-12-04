#ifndef movements_ok

#define movements_ok

#include "../backend.h"

/*
*Crea un nuevo movementsTAD
*/
movementsADT createMovements();

/*
*Inserta un nuevo movimiento al TAD. A todos los strings se les hace un shallow copy,
*por lo que se deben ingresar strings que se encuentren en una zona segura y no tocarlos; pueden ser const.
*Retorna OK o ERROR.
*/
int insertMovements(movementsADT mov, tDate date, flightClassEnum class, flightClasifEnum clasification, moveTypeEnum moveType, char * origOACI, char * destOACI, char * airline);

/*
*Libera el TAD. En el parametro deepFlag puede ir SHALLOW o DEEP, que indica si tambien se desea liberar
*los strings dentro del TAD. Como los strings ingresados pueden estar en el heap, como no, es necesaria esta opcion.
*/
void freeMovements(movementsADT mov, int deepFlag);

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
