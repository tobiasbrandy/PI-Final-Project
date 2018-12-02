#ifndef library_ok

#define library_ok

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getnum.h"
#include "TAD/airportADT.h"

#define MBLOCK 5000 //Este numero fue determinado de manera experimental tratando de minimizar el tiempo de procesamiento.
#define BLOCK 50
#define NOCLASIF 2 //Cantidad de clasificaciones
#define NOCLASS 3 //Cantidad de clases
#define ERROR -1
#define OK 1

typedef struct movementsCDT * movementsADT;
typedef enum {SUNDAY=0, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY} weekday;
typedef enum {REGULAR=0, NOREGULAR, PRIVATE} flightClassEnum;
typedef enum {CABOTAGE=0, INTERNATIONAL, NA} flightClasifEnum;
typedef enum {TAKEOFF=0, LANDING} moveTypeEnum; 

typedef struct date{
	char day;
	char month;
	size_t year;
}tDate;


#include "TAD/movementsADT.h"

/*
*Recibe una fecha y devuelve el dia de la semana. 0=Domingo, 1=Lunes,...
*/
weekday dateToWeekday(tDate date);

/*
*Implementacion generica de la busqueda binaria. De no encontrarse el elemento retorna -1.
*/
int binarySearch(void ** array, size_t dim, void * elem, int (*comp)(void*, void*));

/*
*Implementacion generica de la suma matricial. Las matrices deben tener el mismo tamaño.
*/
void matrixAddition(void ** matrix1, void ** matrix2, size_t dimF, size_t dimC, size_t bytes, void (*add)(void*, void*));

/*
*Crea una matriz de row*col. Se le debe brindar el tamaño del tipo  de la matriz. (ej. sizeof(int))
*/
void ** createMatrix(size_t row, size_t col, size_t bytes);

/*
*Libera una matriz de row filas.
*/
void freeMatrix(void ** matrix, size_t row);

/*
*Suma dos enteros. Guarda el resultado en int1.
*/
void addInts(int * int1, int * int2);

/*
*Le suma al airportADT los movimientos del movementsADT. De haber un problema lo informa por salida estandar.
*/
void addBlockMovementsToAirport(movementsADT mv, airportADT ap);

/*
*Crea un archivo nuevo dia_semana.csv (si ya existe uno lo borra) y guarda en el archivo
*la cantidad de movimientos que hubo segun dia de la semana y clasificacion.
*Responde a la query 2. Retorna OK o ERROR.
*/
int storeMovsByWeekdayAndClasif(int ** week);

/*
*Crea un archivo nuevo composicion.csv (si ya existe uno lo borra) y guarda en el archivo
*la cantidad de movimientos que hubo segun clase y clasificacion.
*Responde a la query 3. Retorna OK o ERROR.
*/
int storeMovsByClasifAndClass(int ** moveComp);

#endif