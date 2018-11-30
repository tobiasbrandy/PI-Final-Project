#include "library.h"


int main(/* int numOfFiles, dataType data[] */) // data[0] almacena el nombre, data[1] 1er arg hasta data[numOfFiles] 
{
	/*
	//INICIO MAIN

	airportADT ap = createAirport();
	movementsADT mv;
	liftAirport(ap, ...); //Funcion que lee de aeropuertos.csv y hace insert a airportADT de todos los aeropuertos validos. FRONT
	startFasterAirportSearch(ap); //Creo el array de aeropuertos para buscar mas rapido.

	int ** week = (int**)createMatrix(7, NOCLASIF, sizeof(int)); //Matriz de 7*2 que guarda la informacion para la query2.
	int ** moveComp = (int**)createMatrix(NOCLASS, NOCLASIF, sizeof(int)); //Matriz de 3*2 que guarda la informacion para la query 3.

	while(mv = liftnMovements(...)){ //Funcion que lee movimientos.csv y hace insert a movementsADT de n movimientos.FRONT! El while corta cuando ya no hay movimientos en el archivo.

		matrixAddition((void**)week, (void**)getMovsByWeekDay(mv), 7, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts); //Sumo los valores para la query 2 de este bloque.
		matrixAddition((void**)moveComp, (void**)getMovsComposition(mv), NOCLASS, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts); //Sumo los valores para el query 3 de este bloque.

		addBlockMovementsToAirport(mv, ap); //Le suma a cada aeropuerto la cantidad de movimientos que tuvo en el bloque.

		freeMovements(mv);
	}


	//Almacena en el archivo correspondiente la Query 1.
	storeAirportsByMovs(ap);

	//Almacena en el archivo correspondiente la Query 2.
	storeMovsByWeekdayAndClasif(week);

	//Almacena en el archivo correspondiente la Query 3.
	storeMovsByClasifAndClass(moveComp);

	freeAirport(ap);
	freeMatrix((void**)week, 7);
	freeMatrix((void**)moveComp, NOCLASS);



	//FINAL MAIN. YA ESTA!!!!!!
	*/

/*
	stringvToFile (vectorStrings, movimientos_aeropuestos, .csv) // cada query la va a llamar una vez, permite elegir la extensión del archivo
*/

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

	printf("Query 1\n");
	storeAirportsByMovs(ap);

	printf("Query 2\n");
	storeMovsByWeekdayAndClasif(week);

	printf("Query 3\n");
	storeMovsByClasifAndClass(moveComp);


	freeAirport(ap);
	freeMatrix((void**)week, 7);
	freeMatrix((void**)moveComp, NOCLASS);
*/
}


/*void stringvToFile (char ** stringv, char * fileName, char * extent) {
	char * validExtent, aux, validExtent;
	
	if (*extent != '.') {
		validExtent = ".";
		strcat (validExtent, extent);
	}
	else validExtent = extent;

	strcpy(fullName, fileName);
	
	strcat (fullName, validExtent);
	
	FILE * newFile = fopen(fullName, "w");

	while (*stringv != NULL) {
		fputs (*(stringv++), newFile);
		fputc ('\n', newFile);
	}

	if (fclose(newfile) != 0)
		perror ("An error ocurred while writing\n");
}*/