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
