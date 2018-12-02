#include "backend.h"
#include "frontend.h"


int main(int args, char argv[])
{
	if (args != 2) {
		printf("La cantidad de argumentos ingresada es errónea\n");
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

	freeAirport(ap);
	freeMatrix((void**)week, 7);
	freeMatrix((void**)moveComp, NOCLASS);

	return 0;
}

	//FINAL MAIN. YA ESTA!!!!!!

	//PARA TESTEAR!!
	/*airportADT ap = createAirport();

	insertAirport(ap, "SAME", "ezeiza", "lanus");
	insertAirport(ap, "AMBE", "ezeiza", "lanus");
	insertAirport(ap, "FOEP", "ezeiza", "lanus");
	insertAirport(ap, "FISH", "ezeiza", "lanus");
	insertAirport(ap, "PFHT", "ezeiza", "lanus");
	insertAirport(ap, "MVGS", "ezeiza", "lanus");
	insertAirport(ap, "PAID", "ezeiza", "lanus");
	insertAirport(ap, "MFHT", "ezeiza", "lanus");
	insertAirport(ap, "APWE", "ezeiza", "lanus");
	insertAirport(ap, "MNDG", "ezeiza", "lanus");
	insertAirport(ap, "PEID", "ezeiza", "lanus");
	insertAirport(ap, "QPWO", "ezeiza", "lanus");
	insertAirport(ap, "FHDS", "ezeiza", "lanus");
	insertAirport(ap, "FHGE", "ezeiza", "lanus");
	insertAirport(ap, "FBYT", "ezeiza", "lanus");
	insertAirport(ap, "DNYR", "ezeiza", "lanus");

	startFasterAirportSearch(ap);

	movementsADT mv = createMovements();

	tDate date0 = {10, 6, 2000};
	tDate date1 = {11, 6, 2000};
	tDate date2 = {12, 6, 2000};
	tDate date3 = {13, 6, 2000};
	tDate date4 = {14, 6, 2000};
	tDate date5 = {15, 6, 2000};
	tDate date6 = {16, 6, 2000};

	insertMovements(mv, date0, REGULAR, CABOTAGE, TAKEOFF, "SAME", "MFHT", "Aerolineas");
	insertMovements(mv, date6, NOREGULAR, INTERNATIONAL, LANDING, "SAME", "QPWO", "Aerolineas");
	insertMovements(mv, date5, REGULAR, CABOTAGE, TAKEOFF, "APWE", "DNYR", "Aerolineas");
	insertMovements(mv, date4, PRIVATE, NA, LANDING, "FOEP", "AMBE", "Aerolineas");
	insertMovements(mv, date3, PRIVATE, INTERNATIONAL, TAKEOFF, "QPWO", "DNYR", "Aerolineas");
	insertMovements(mv, date2, NOREGULAR, CABOTAGE, TAKEOFF, "SAME", "AMBE", "Aerolineas");
	insertMovements(mv, date1, REGULAR, INTERNATIONAL, TAKEOFF, "APWE", "QPWO", "Aerolineas");
	insertMovements(mv, date0, REGULAR, CABOTAGE, LANDING, "SAME", "AMBE", "Aerolineas");
	insertMovements(mv, date5, PRIVATE, CABOTAGE, LANDING, "APWE", "AMBE", "Aerolineas");
	insertMovements(mv, date6, REGULAR, CABOTAGE, LANDING, "SAME", "AMBE", "Aerolineas");
	insertMovements(mv, date6, NOREGULAR, INTERNATIONAL, TAKEOFF, "QPWO", "MFHT", "Aerolineas");
	insertMovements(mv, date3, PRIVATE, CABOTAGE, LANDING, "SAME", "AMBE", "Aerolineas");
	insertMovements(mv, date2, NOREGULAR, INTERNATIONAL, TAKEOFF, "MFHT", "APWE", "Aerolineas");
	insertMovements(mv, date2, NOREGULAR, INTERNATIONAL, LANDING, "APWE", "FOEP", "Aerolineas");
	insertMovements(mv, date0, REGULAR, INTERNATIONAL, TAKEOFF, "SAME", "AMBE", "Aerolineas");
	insertMovements(mv, date1, REGULAR, CABOTAGE, LANDING, "APWE", "AMBE", "Aerolineas");
	insertMovements(mv, date1, NOREGULAR, INTERNATIONAL, TAKEOFF, "DNYR", "QPWO", "Aerolineas");
	insertMovements(mv, date4, PRIVATE, INTERNATIONAL, TAKEOFF, "MFHT", "DNYR", "Aerolineas");
	insertMovements(mv, date4, NOREGULAR, CABOTAGE, LANDING, "MFHT", "AMBE", "Aerolineas");
	insertMovements(mv, date0, REGULAR, INTERNATIONAL, TAKEOFF, "QPWO", "AMBE", "Aerolineas");

	int ** week = (int**)createMatrix(7, NOCLASIF, sizeof(int));
	int ** moveComp = (int**)createMatrix(NOCLASS, NOCLASIF, sizeof(int));

	matrixAddition((void**)week, (void**)getMovsByWeekDay(mv), 7, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts);
	matrixAddition((void**)moveComp, (void**)getMovsComposition(mv), NOCLASS, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts);

	addBlockMovementsToAirport(mv, ap);

	freeMovements(mv);
}
