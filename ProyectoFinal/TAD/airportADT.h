#ifndef airport_ok

#define airport_ok

typedef struct airportCDT * airportADT;

#include "../backend.h"

/*
*Crea un nuevo airportTAD
*/
airportADT createAirport();

/*
*Inserta un nuevo aeropuerto a airportADT, o modifica la denominacion y provincia de ya existir
*un aeropuerto con el OACI ingresado.
*Los ordena alfabéticamente según el código OACI. A todos los strings se les hace un shallow copy,
*por lo que se deben ingresar strings que se encuentren en una zona segura y no tocarlos, pueden ser const.
*Devuelve OK si todo salio bien, y ERROR si hubo algun problema.
*/
int insertAirport(airportADT ap, char * oaci, char * denomination, char * province);

/*
*Libera airportADT. En el parametro deepFlag puede ir SHALLOW o DEEP, que indica si tambien se desea liberar
*los strings dentro de la estructura tAirport. Como los strings ingresados pueden estar en el heap, como no, es necesaria esta opcion.
*/
void freeAirport(airportADT ap, int deepFlag);

/*
*Crea un archivo nuevo movimientos_aeropuerto.csv (si ya existe uno lo borra)
*y almacena en el archivo los aeropuertos del TAD junto con
*la cantidad de movimientos ordenado de manera descendente y luego por OACI.
*Responde a la query 1.
*Devuelve OK si todo salio bien, y ERROR si hubo algun problema.
*/
int storeAirportsByMovs(airportADT ap);

/*
*Crea un array de punteros a tAirport y lo guarda en el header del TAD. 
*De haberse modificado el TAD (creacion, insercion, etc), el usuario debe ejecutar esta funcion antes de usar cualquier funcion catalogada FAS (Faster Airport Search).
*/
void startFasterAirportSearch(airportADT ap);

/*
*Libera ciertas regiones de memoria reservadas por startFasterAirportSearch.
*Se recomienda ejecutar esta funcion luego de terminar de usar una tanda de funciones FAS.
*De todas maneras, si no se ejecuta, freeAirport se encargara de liberar esas zonas.
*/
void stopFasterAirportSearch(airportADT ap);

/*
*Le suma un movimiento al aeropuerto del TAD cuyo oaci coincide con el ingresado. Si no hay aeropuerto con oaci que coincida, no hace nada.
*Utiliza la funcion binarySearch ubicada en backend.c.
*Funcion FAS. Retorna OK o ERROR.
*/
int addMovementToAirport(airportADT ap, char * oaci);

/*
*Imprime a salida estandar todos los aeropuertos del TAD.
Funcion de testeo.
*/
void printAirport(airportADT ap);

#endif


