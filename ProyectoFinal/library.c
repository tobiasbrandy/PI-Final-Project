#include "library.h"


weekday dateToWeekday(tDate date){

	struct tm time;

	time.tm_year = date.year - 1900;
   	time.tm_mon = date.month - 1;
   	time.tm_mday = date.day;
   	time.tm_hour = 0;
   	time.tm_min = 0;
   	time.tm_sec = 1;
   	time.tm_isdst = -1;

   	int err = mktime(&time);
   	if(err == -1){
   		printf("No ah sido posible crear la estructura time\n");
   		return -1;
   	}

   	return time.tm_wday;
}

int binarySearch(void * array[], size_t dim, void * elem, int (*comp)(void*, void*)){ //comp funciona de la manera estandar.
	int c;
	int lowerBound = 0;
	int upperBound = dim-1;
	int midPoint;

	while(lowerBound <= upperBound){

	// Calculo midPoint
    midPoint = (lowerBound + upperBound) / 2;

    if((c = comp(array[midPoint], elem)) == 0) // Lo encontre
        return midPoint;

	else if(c < 0) //Esta en la mitad de arriba.

		lowerBound = midPoint + 1;

    else //Esta en la mitad de abajo.

        upperBound = midPoint - 1;
	}

	return -1; //No estaba
}


void ** createMatrix(size_t row, size_t col, size_t bytes){
	void ** rta = malloc(row*sizeof(void*));
	for (int i = 0; i < row; ++i)
	{
		rta[i] = calloc(col, bytes);
	}
	return rta;
}

void freeMatrix(void ** matrix, size_t row){
	for (int i = 0; i < row; ++i)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void matrixAddition(void ** matrix1, void ** matrix2, size_t dimF, size_t dimC, size_t bytes, void (*add)(void*, void*)){
	for (int i = 0; i < dimF; ++i)
	{
		for (int j = 0; j < dimC; ++j)
		{
			add((char*)matrix1[i] + j*bytes, (char*)matrix2[i] + j*bytes);
		}
	}
}

void addInts(int * int1, int * int2){
	*int1 += *int2;
}

void addBlockMovementsToAirport(movementsADT mv, airportADT ap){
	if(mv == NULL || ap == NULL)
		return;

	char * oaci;
	size_t dim = getDim(mv);

	for (int i = 0; i < dim; ++i)
	{
		if (getMoveType(mv, i) == LANDING)
			oaci = getDestOACI(mv, i);
		else
			oaci = getOrigOACI(mv, i);

		if(oaci != NULL)
			addMovementToAirport(ap, oaci);
	}
}

int storeMovsByWeekdayAndClasif(int ** week){
	static char * weekdays[7] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};

	FILE * fp;

	fp = fopen ("dia_semana.csv","w");
	if(fp == NULL){
		printf("Hubo un error con el creado del archivo dia_semana.csv\n");
		return -1;
	}

	fprintf(fp, "Día;Cabotaje;Internacional;Total\n");
 
	for (int i = 0; i < 7; ++i)
			fprintf(fp, "%s;%d;%d;%d\n", weekdays[i], week[i][CABOTAGE], week[i][INTERNATIONAL], week[i][CABOTAGE]+week[i][INTERNATIONAL]);

	fclose (fp);

	return 1;

}

int storeMovsByClasifAndClass(int ** moveComp){
		static char * clasif[NOCLASIF] = {"Cabotaje", "Internacional"};
		static char * class[NOCLASS] = {"Regular", "No Regular", "Vuelo Privado"};


	FILE * fp;

	fp = fopen ("composicion.csv","w");
	if(fp == NULL){
		printf("Hubo un error con el creado del archivo composicion.csv\n");
		return -1;
	}

	fprintf(fp, "Clasificación de Vuelo;Clase de Vuelo;Movimientos\n");
 
	for (int i = 0; i < NOCLASS; ++i)
		for (int j = 0; j < NOCLASIF; ++j)
			fprintf(fp, "%s;%s;%d\n", clasif[j], class[i], moveComp[i][j]);

	fclose (fp);

	return 1;

}

