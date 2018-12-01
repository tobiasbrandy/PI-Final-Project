#include "backend.h"
#include "frontend.h"


int main(/* int numOfFiles, dataType data[] */) // data[0] almacena el nombre, data[1] 1er arg hasta data[numOfFiles] 
{

	airportADT ap = createAirport();

	liftAirports(ap, "aeropuertos.csv");

	startFasterAirportSearch(ap);

	int ** week = (int**)createMatrix(7, NOCLASIF, sizeof(int));
	int ** moveComp = (int**)createMatrix(NOCLASS, NOCLASIF, sizeof(int));

	movementsADT mv;

	while((mv = liftBlockMovements("movimientos.csv")) != NULL){ //Funcion que lee movimientos.csv y hace insert a movementsADT de n movimientos.FRONT! El while corta cuando ya no hay movimientos en el archivo.

		matrixAddition((void**)week, (void**)getMovsByWeekDay(mv), 7, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts); //Sumo los valores para la query 2 de este bloque.
		matrixAddition((void**)moveComp, (void**)getMovsComposition(mv), NOCLASS, NOCLASIF, sizeof(int), (void (*)(void*, void*))addInts); //Sumo los valores para el query 3 de este bloque.

		addBlockMovementsToAirport(mv, ap); //Le suma a cada aeropuerto la cantidad de movimientos que tuvo en el bloque.


		freeMovements(mv);

	}


	menuEspecializado(ap, week, moveComp);


	freeAirport(ap, 1);
	freeMatrix((void**)week, 7);
	freeMatrix((void**)moveComp, NOCLASS);

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