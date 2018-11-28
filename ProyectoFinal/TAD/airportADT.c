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

static airportADT insertAirportByMovs(airportADT airport, airportADT rta){
	if(rta == NULL || airport->movements > rta->movements){

		airportADT aux = malloc(sizeof(airportCDT));
		strcpy(aux->oaci, airport->oaci);
		strcpy(aux->denomination, airport->denomination);
		strcpy(aux->province, airport->province);
		aux->movements = airport->movements;
		aux->tail = rta;
		return aux;
	}
	/* El paso inductivo tambien lo hago cuando airport->movements == rta->movements porque airport 
	ya esta ordenado alfabeticamente por OACI, entonces si cuando son iguales dejo que este primero el de 
	airport, me estoy garantizando que el orden secundario sea alfabetico.*/

	rta->tail = insertAirportByMovs(airport, rta->tail);
	return rta;
}

static airportADT cpyAirportByMovs(airportADT airport){  //Es static porque nuestro TAD no soporta que la lista este ordenada por movimiento.
	airportADT rta = NULL;
	airportADT aux = airport;
	while(aux != NULL){
		rta = insertAirportByMovs(aux, rta);
		aux=aux->tail;
	}
	return rta;
}




