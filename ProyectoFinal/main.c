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

	storeAirportsByMovs(ap); //Almacena en el archivo correspondiente la Query 1.
	storeMovsByWeekdayAndClasif(week); //Almacena en el archivo correspondiente la Query 2.
	storeMovsByClasifAndClass(moveComp); //Almacena en el archivo correspondiente la Query 3.

	freeAirport(ap);
	freeMatrix((void**)week, 7);
	freeMatrix((void**)moveComp, NOCLASS);

	//FINAL MAIN. YA ESTA!!!!!!
	*/

/*
	stringvToFile (vectorStrings, movimientos_aeropuestos, .csv) // cada query la va a llamar una vez, permite elegir la extensión del archivo
*/


}

/* void stringvToFile (char ** stringv, char * fileName, char * extent) {
	char * validExtent;
	
	if (*extent != '.') {
		validExtent = ".";
		strcat (validExtent, extension);
	}
	else validExtent = extension;
	
	strcat (fileName, validExtent);
	
	FILE * newFile = fopen(fileName, "w");

	while (*stringv != NULL) {
		fputs (*(stringv++), newFile);
		fputc ('\n', newFile);
	}

	if (fclose(newfile) != 0)
		perror ("An error ocurred while writing\n");
} */