#include "airportADT.h"

typedef struct airportCDT{

	char * oaci;
	char * denomination;
	char * province;
	long int movements;
	struct airportCDT * tail;

}airportCDT;

airportADT createAirport(){
	return NULL;
}

void freeAirport(airportADT airport){
	if(airport != NULL){
		freeAirport(airport->tail);
		free(airport);
	}
}

airportADT insertAirport(airportADT airport, char * oaci, char * denomination, char * province){
	int c;
	if(airport == NULL || (c = strcmp(airport->oaci, oaci)) > 0){ //Si no esta en el TAD, lo agrega.

		airportADT aux = malloc(sizeof(airportCDT));
		strcpy(aux->oaci, oaci);
		strcpy(aux->denomination, denomination);
		strcpy(aux->province, province);
		aux->movements = 0;
		aux->tail = airport;
		return aux;

	}
	if(c == 0){ //Si los oaci coinciden, hace un update.

		strcpy(airport->denomination, denomination);
		strcpy(airport->province, province);
		return airport;
	}

	airport->tail = insertAirport(airport->tail, oaci, denomination, province);
	return airport;
}

airportADT * airportToArray(airportADT airport, int * dim){

	int k = 0;
	airportADT * rta = NULL;
	airportADT aux = airport;

	while(airport != NULL){
		if(k % BLOCK == 0)
			rta = realloc(rta, (k+BLOCK)*sizeof(airportADT));

		rta[k++] = aux;
		aux = aux->tail;
	}
	rta = realloc(rta, k*sizeof(airportADT));
	*dim = k;
	return rta;
}



