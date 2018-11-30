#include "airportADT.h"

typedef struct airportNode * apNode;

typedef struct airportNode{

	tAirport airport;
	struct airportNode * tail;

}airportNode;

typedef struct airportCDT{

	tAirport ** tAirportArray; //Array que permite la facil busqueda de un airport espcifico.
	size_t dim;
	apNode first;

}airportCDT;

airportADT createAirport(){
	return calloc(1, sizeof(airportCDT));
}

static void freeAirportRec(apNode node){
	if(node != NULL){
		freeAirportRec(node->tail);
		free(node);
	}
}

void freeAirport(airportADT ap){
	if(ap != NULL){
		freeAirportRec(ap->first);
		if(ap->tAirportArray != NULL)
			free(ap->tAirportArray);
		free(ap);
	}
}

static apNode insertAirportRec(apNode node, char * oaci, char * denomination, char * province){
	int c;
	if(node == NULL || (c = strcmp(node->airport.oaci, oaci)) > 0){ //Si no esta en el TAD, lo agrega.

		apNode aux = malloc(sizeof(airportNode));
		aux->airport.oaci = oaci;
		aux->airport.denomination = denomination;
		aux->airport.province = province;
		aux->airport.movements = 0;
		aux->tail = node;
		return aux;

	}
	if(c == 0){ //Si los oaci coinciden, hace un update.

		node->airport.denomination = denomination;
		node->airport.province = province;
		return node;
	}

	node->tail = insertAirportRec(node->tail, oaci, denomination, province);
	return node;
}

void insertAirport(airportADT ap, char * oaci, char * denomination, char * province){
	if(ap != NULL)
		ap->first = insertAirportRec(ap->first, oaci, denomination, province);
}

static tAirport ** airportToArray(apNode node, size_t * dim){

	int k = 0;
	tAirport ** rta = NULL;
	apNode aux = node;

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

void startFasterAirportSearch(airportADT ap){ 
	if(ap == NULL)
		return;

	if(ap->tAirportArray != NULL){
		free(ap->tAirportArray);
		ap->dim = 0;
	}
	ap->tAirportArray = airportToArray(ap->first, &ap->dim);
}

void stopFasterAirportSearch(airportADT ap){ 
	if(ap != NULL){
		if(ap->tAirportArray != NULL)
			free(ap->tAirportArray);
		ap->tAirportArray = NULL;
		ap->dim = 0;
	}
}

static apNode insertAirportByMovs(apNode node, apNode rta){
	if(rta == NULL || node->airport.movements > rta->airport.movements){

		apNode aux = malloc(sizeof(airportNode));
		aux->airport.oaci = node->airport.oaci;
		aux->airport.denomination = node->airport.denomination;
		aux->airport.province = node->airport.province;
		aux->airport.movements = node->airport.movements;
		aux->tail = rta;
		return aux;
	}
	/* El paso inductivo tambien lo hago cuando node->airport->movements == rta->airport->movements porque node 
	ya esta ordenado alfabeticamente por OACI, entonces si cuando son iguales dejo que este primero el de 
	node, me estoy garantizando que el orden secundario sea alfabetico.*/

	rta->tail = insertAirportByMovs(node, rta->tail);
	return rta;
}

/*
* Crea una copia de la lista y la ordena ordenada según la cantidad de movimientos de manera descendente y secundariamente
* alfabéticamente por código OACI
*/
static airportADT cpyAirportByMovs(airportADT ap){  //Es static porque nuestro TAD no soporta que la lista este ordenada por movimiento.
	if(ap == NULL)
		return NULL;
	airportADT rta = createAirport();
	apNode aux = ap->first;
	while(aux != NULL){
		rta->first = insertAirportByMovs(aux, rta->first);
		aux=aux->tail;
	}
	return rta;
}

static int comptAirportOACI(tAirport * airport, char * oaci){
	return strcmp(airport->oaci, oaci);
}

int addMovementToAirport(airportADT ap, char * oaci){ //Funcion FAS.
	if(ap == NULL || oaci == NULL)
		return -1;

	if(ap->tAirportArray == NULL || ap->dim == 0){
		printf("There aren't any elements in the ADT or startFasterAirportSearch() wasn't executed\n");
		printf("Remember to execute startFasterAirportSearch() before using a FAS function if a change to the TAD was made.\n");
		return -1;
	}

	int i = binarySearch((void**)ap->tAirportArray, ap->dim, oaci, (int (*)(void*,void*))comptAirportOACI);
	if(i >= 0){
		ap->tAirportArray[i]->movements++;
		return 1;
	}

	return -1;
}

int storeAirportsByMovs(airportADT ap){
	static int repeat;
	if(repeat != 0)
		return 1;
	repeat++;

	airportADT ap2 = cpyAirportByMovs(ap);

	FILE * fp;

	fp = fopen ("movimientos_aeropuerto.csv","w");
	if(fp == NULL){
		printf("Hubo un error con el creado del archivo movimientos_aeropuerto.csv\n");
		return -1;
	}

	fprintf(fp, "OACI;Denominación;Movimientos\n");

	apNode aux = ap2->first;
 
	while(aux != NULL){
		fprintf (fp, "%s;%s;%ld\n", aux->airport.oaci, aux->airport.denomination, aux->airport.movements);
		aux = aux->tail;
	}

	fclose (fp);

	freeAirport(ap2);
	return 1;
}


void printAirport(airportADT ap){ //Funcion de testeo
	apNode aux = ap->first;
	while(aux != NULL){
		printf("OACI: %s; Deno: %s; Prov: %s; Mov: %ld \n", aux->airport.oaci, aux->airport.denomination, aux->airport.province, aux->airport.movements);
		aux=aux->tail;
	}
	printf("\n");
}

void printTAirportArray(airportADT ap){ //Funcion de testeo
	for (int i = 0; i < ap->dim; ++i)
	{
		printf("%s\n", ap->tAirportArray[i]->oaci);
	}
}



