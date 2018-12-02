#include "backend.h"
#include "frontend.h"


int main(int args, char * argv[])
{
	if (args != 3) {
		printf ("La cantidad de argumentos recibida es errónea. Deben ser exactamente 2.\n");
		printf ("Recuerde que debe pasar los argumentos de la siguiente manera:\n");
		printf ("$user> ./main $PATH:aeropuertos.csv $PATH:movimientos.csv\n");
		return 1;
	}

	airportADT ap = createAirport();

	liftAirports(ap, argv[1]); //Almacena en el airportADT todos los aeropuertos del archivo.

	startFasterAirportSearch(ap); //Habiendo terminado la insercion de aeropuertos en el programa, se ejecuta esta funcion para poder usar funciones FAP.

	int ** week = (int**)createMatrix(7, NOCLASIF, sizeof(int)); //En estas dos matrices se almacenara los resultados de las queries 2 y 3 respectivamente.
	int ** moveComp = (int**)createMatrix(NOCLASS, NOCLASIF, sizeof(int));

	movementsADT mv;

	printf("Cargando...\n");
	printf("Espere un momento por favor\n");

	while((mv = liftBlockMovements(argv[2])) != NULL){ //Esta funcion almacena MBLOCK movimientos del archivo en el movementsADT. Si no quedan, devuelve NULL.

		matrixAddition((void**)week, (void**)getMovsByWeekDay(mv), 7, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts); //Aqui se actualizan los valores de las matrices
		matrixAddition((void**)moveComp, (void**)getMovsComposition(mv), NOCLASS, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts);//con los datos de los movimientos de este MBLOCK

		addBlockMovementsToAirport(mv, ap); //Le suma a cada aeropuerto la cantidad de movimientos que tuvo en el MBLOCK.


		freeMovements(mv);
	}

	menuEspecializado(ap, week, moveComp); //Implementacion simple de menu para efectuar las 3 queries.

	freeAirport(ap);
	freeMatrix((void**)week, 7);
	freeMatrix((void**)moveComp, NOCLASS);

	return 0;
}