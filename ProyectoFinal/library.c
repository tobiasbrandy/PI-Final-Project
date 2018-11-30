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
   		printf("ohno\n");
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


void ** createMatrix(int row, int col, int bytes){
	void ** rta = malloc(row*sizeof(void*));
	for (int i = 0; i < row; ++i)
	{
		rta[i] = calloc(col, bytes);
	}
	return rta;
}

void freeMatrix(void ** matrix, int row){
	for (int i = 0; i < row; ++i)
	{
		free(matrix[i]);
	}
	free(matrix);
}

void matrixAddition(void ** matrix1, void ** matrix2, int dimF, int dimC, int bytes, void (*add)(void*, void*)){
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

	char * oaci;
	size_t dim = getDim(mv);

	for (int i = 0; i < dim; ++i)
	{
		if (getMoveType(mv, i) == LANDING)
			oaci = getDestOACI(mv, i);
		else
			oaci = getOrigOACI(mv, i);

		addMovementToAirport(ap, oaci);
	}
}

