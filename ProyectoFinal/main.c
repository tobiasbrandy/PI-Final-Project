#include "TAD/airportADT.h"
#include "TAD/movementsADT.h"

int main(/* int numOfFiles, dataType data[] */) // data[0] almacena el nombre, data[1] 1er arg hasta data[numOfFiles] 
{
	/*airportADT aero = createAirport();
	aero = insertAirport(aero, "SAME", "pepelopi", "provincia");
	aero = insertAirport(aero, "BODS", "2", "a");
	aero = insertAirport(aero, "FOPS", "3", "s");
	aero = insertAirport(aero, "SUDF", "4", "g");
	aero = insertAirport(aero, "UDIS", "6", "h");
	aero = insertAirport(aero, "AIFO", "5", "j");
	aero = insertAirport(aero, "AAAA", "7", "k");
	aero = insertAirport(aero, "PODR", "8", "n");
	aero = insertAirport(aero, "IDYS", "9", "b");
	aero = insertAirport(aero, "ZIOS", "11", "v");
	aero = insertAirport(aero, "ZION", "10", "provincia");

	printAirport(aero);

	int dim;

	tAirport ** array = airportToArray(aero, &dim);

	for (int i = 0; i < dim; ++i)
	{
		printf("%s\n", array[i]->oaci);
	}

	array[0]->movements = 7;
	array[1]->movements = 1;
	array[2]->movements = 2;
	array[3]->movements = 3;
	array[4]->movements = 3;
	array[5]->movements = 67;
	array[6]->movements = 78;
	array[7]->movements = 9;
	array[8]->movements = 9;
	array[9]->movements = 74;

	airportADT aero2 = cpyAirportByMovs(aero);

	printAirport(aero);
	printAirport(aero2);


	free(array);

	freeAirport(aero);
	freeAirport(aero2);*/

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