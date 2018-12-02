#include "backend.h"
#include "frontend.h"


int main(int args, char * argv[])
{
	if (args != 3) {
		printf ("La cantidad de argumentos recibida es errónea\n");
		printf ("Recuerde que debe pasar los argumentos de la siguiente manera:\n");
		printf ("$user> ./main $PATH:aeropuertos.csv $PATH:movimientos.csv\n");
		return 1;
	}

	airportADT ap = createAirport();

	liftAirports(ap, argv[1]);

	startFasterAirportSearch(ap);

	int ** week = (int**)createMatrix(7, NOCLASIF, sizeof(int));
	int ** moveComp = (int**)createMatrix(NOCLASS, NOCLASIF, sizeof(int));

	movementsADT mv;

	printf("Cargando...\n");
	printf("Espere un momento por favor\n");

	while((mv = liftBlockMovements(argv[2])) != NULL){ //Funcion que lee movimientos.csv y hace insert a movementsADT de n movimientos.FRONT! El while corta cuando ya no hay movimientos en el archivo.

		matrixAddition((void**)week, (void**)getMovsByWeekDay(mv), 7, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts); //Sumo los valores para la query 2 de este bloque.
		matrixAddition((void**)moveComp, (void**)getMovsComposition(mv), NOCLASS, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts); //Sumo los valores para el query 3 de este bloque.

		addBlockMovementsToAirport(mv, ap); //Le suma a cada aeropuerto la cantidad de movimientos que tuvo en el bloque.


		freeMovements(mv);
	}

	menuEspecializado(ap, week, moveComp); //Implementacion de menu para efectuar las 3 querys.

	freeAirport(ap, DEEP);
	freeMatrix((void**)week, 7);
	freeMatrix((void**)moveComp, NOCLASS);

	return 0;
}