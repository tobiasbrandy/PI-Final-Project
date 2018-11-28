#include "airportADT.h"

typedef struct airportCDT{

	tAirport airport;
	struct airportCDT * tail;

}airportCDT;

airportADT createAirport(){
	return NULL;
}

void freeAirport(airportADT ap){
	if(ap != NULL){
		freeAirport(ap->tail);
		free(ap);
	}
}

airportADT insertAirport(airportADT ap, char * oaci, char * denomination, char * province){
	int c;
	if(ap == NULL || (c = strcmp(ap->airport.oaci, oaci)) > 0){ //Si no esta en el TAD, lo agrega.

		airportADT aux = malloc(sizeof(airportCDT));
		aux->airport.oaci = oaci;
		aux->airport.denomination = denomination;
		aux->airport.province = province;
		aux->airport.movements = 0;
		aux->tail = ap;
		return aux;

	}
	if(c == 0){ //Si los oaci coinciden, hace un update.

		ap->airport.denomination = denomination;
		ap->airport.province = province;
		return ap;
	}

	ap->tail = insertAirport(ap->tail, oaci, denomination, province);
	return ap;
}

tAirport ** airportToArray(airportADT ap, int * dim){

	int k = 0;
	tAirport ** rta = NULL;
	airportADT aux = ap;

	while(aux != NULL){
		if(k % BLOCK == 0)
			rta = realloc(rta, (k+BLOCK)*sizeof(tAirport*));

		rta[k++] = &(aux->airport);
		aux = aux->tail;
	}
	rta = realloc(rta, k*sizeof(tAirport*));
	*dim = k;
	return rta;
}

static airportADT insertAirportByMovs(airportADT ap, airportADT rta){
	if(rta == NULL || ap->airport.movements > rta->airport.movements){

		airportADT aux = malloc(sizeof(airportCDT));
		aux->airport.oaci = ap->airport.oaci;
		aux->airport.denomination = ap->airport.denomination;
		aux->airport.province = ap->airport.province;
		aux->airport.movements = ap->airport.movements;
		aux->tail = rta;
		return aux;
	}
	/* El paso inductivo tambien lo hago cuando ap->airport->movements == rta->airport->movements porque ap 
	ya esta ordenado alfabeticamente por OACI, entonces si cuando son iguales dejo que este primero el de 
	ap, me estoy garantizando que el orden secundario sea alfabetico.*/

	rta->tail = insertAirportByMovs(ap, rta->tail);
	return rta;
}

/*
* Crea una copia de la lista y la ordena ordenada según la cantidad de movimientos de manera descendente y secundariamente
* alfabéticamente por código OACI
*/
static airportADT cpyAirportByMovs(airportADT ap){  //Es static porque nuestro TAD no soporta que la lista este ordenada por movimiento.
	airportADT rta = NULL;
	airportADT aux = ap;
	while(aux != NULL){
		rta = insertAirportByMovs(aux, rta);
		aux=aux->tail;
	}
	return rta;
}

void printAirport(airportADT ap){ //Funcion de testeo
	airportADT aux = ap;
	while(aux != NULL){
		printf("OACI: %s; Deno: %s; Prov: %s; Mov: %ld \n", aux->airport.oaci, aux->airport.denomination, aux->airport.province, aux->airport.movements);
		aux=aux->tail;
	}
	printf("\n");
}




