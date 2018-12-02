#include "airportADT.h"

typedef struct airportNode * apNode;

typedef struct airport{
	char * oaci;
	char * denomination;
	char * province;
	long int movements;
}tAirport;

typedef struct airportNode{

	tAirport airport;
	struct airportNode * tail;

}airportNode;

typedef struct airportCDT{

	tAirport ** tAirportArray; //Array que permite la facil busqueda de un airport espcifico.
	size_t dim;
	apNode first;

}airportCDT;

/*
*Recibe un puntero a estructura airportNode y la libera.
*/
static void freeAirportRec(apNode node);

/*
*Recibe el OACI, la denominacion y provincia de un aeropuerto en forma de string, la cantidad de movimientos y 
cual es el siguiente aeropuerto en la lista, y crea un nodo para insertar en la lista de aeropuertos de airportADT.
*Devuelve un puntero al nodo. 
*/
static apNode createAirportNode(char * oaci, char * denomination, char * province, long int movements, apNode tail);

/*
*Funcion recursiva para insertar nodos a la lista de aeropuertos de airportADT de forma alfabetica por OACI.
*/
static apNode insertAirportRec(apNode node, char * oaci, char * denomination, char * province);

/*
*Recibe una lista de aeropuertos y devuelve un vector de punteros a estructura aeropuerto 
*con los mismos aeropuertos y orden que en la lista. dim es un parametro de salida donde
*se guarda el tamano del array (cantidad de aeropuertos en el TAD).
*/
static tAirport ** airportToArray(apNode node, size_t * dim);

/*
*Funcion recursiva que inserta un nodo en la lista rta que tiene la misma informacion
*que el primer elemento de node. Lo hace en orden por cantidad de movimientos de forma descendente
*y luego por orden alfabetico del OACI.
*/
static apNode insertAirportByMovs(apNode node, apNode rta);

/*
*Crea un nuevo airportADT con la misma informacion que ap pero ordenado por
*cantidad de movimientos de forma descendente y luego por orden alfabetico del OACI.
*/
static airportADT cpyAirportByMovs(airportADT ap);

/*
*Compara el string oaci con el oaci de la estructura aeropuerto.
Devuelve lo mismo que strcmp (lo estandar).
*/
static int comptAirportOACI(tAirport * airport, char * oaci);


airportADT createAirport(){
	return calloc(1, sizeof(airportCDT));
}

static void freeAirportRec(apNode node){
	if(node != NULL){
		free(node->airport.oaci);
		free(node->airport.denomination);
		free(node->airport.province);
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

static apNode createAirportNode(char * oaci, char * denomination, char * province, long int movements, apNode tail){
	apNode aux = malloc(sizeof(airportNode));

	aux->airport.oaci = malloc(strlen(oaci) + 1);
	strcpy(aux->airport.oaci, oaci);

	aux->airport.denomination = malloc(strlen(denomination) + 1);
	strcpy(aux->airport.denomination, denomination);

	aux->airport.province = malloc(strlen(province) + 1);
	strcpy(aux->airport.province, province);

	aux->airport.movements = movements;
	aux->tail = tail;

	return aux;
}

static apNode insertAirportRec(apNode node, char * oaci, char * denomination, char * province){
	int c;
	if(node == NULL || (c = strcmp(node->airport.oaci, oaci)) > 0){ //Si no esta en el TAD, lo agrega.

		return createAirportNode(oaci, denomination, province, 0, node);
	}

	if(c == 0){ //Si los oaci coinciden, hace un update.

		node->airport.denomination = realloc(node->airport.denomination, strlen(denomination) + 1);
		strcpy(node->airport.denomination, denomination);

		node->airport.province = realloc(node->airport.province, strlen(province) + 1);
		strcpy(node->airport.province, province);
		return node;
	}

	node->tail = insertAirportRec(node->tail, oaci, denomination, province);
	return node;
}

int insertAirport(airportADT ap, char * oaci, char * denomination, char * province){
	if(ap == NULL || oaci == NULL || denomination == NULL || province == NULL)
		return ERROR;

	ap->first = insertAirportRec(ap->first, oaci, denomination, province);
	return OK;
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

		return createAirportNode(node->airport.oaci, node->airport.denomination, node->airport.province, node->airport.movements, rta);

	}
	/* El paso inductivo tambien lo hago cuando node->airport->movements == rta->airport->movements porque node 
	ya esta ordenado alfabeticamente por OACI, entonces si cuando son iguales dejo que este primero el de 
	node, me estoy garantizando que el orden secundario sea alfabetico.*/

	rta->tail = insertAirportByMovs(node, rta->tail);
	return rta;
}

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
		return ERROR;


	if(ap->tAirportArray == NULL || ap->dim == 0){
		printf("There aren't any elements in the ADT or startFasterAirportSearch() wasn't executed\n");
		printf("Remember to execute startFasterAirportSearch() before using a FAS function if a change to the TAD was made.\n");
		return ERROR;
	}


	int i = binarySearch((void**)ap->tAirportArray, ap->dim, oaci, (int (*)(void*,void*))comptAirportOACI);

	if(i >= 0)
		ap->tAirportArray[i]->movements++;

	return OK;
}

int storeAirportsByMovs(airportADT ap){
	static int repeat;

	if(repeat != 0)
		return OK;

	airportADT ap2 = cpyAirportByMovs(ap);

	FILE * fp;

	fp = fopen ("movimientos_aeropuerto.csv","w");
	if(fp == NULL){
		printf("Hubo un error con el creado del archivo movimientos_aeropuerto.csv. Intentelo nuevamente.\n");
		return ERROR;
	}

	fprintf(fp, "OACI;Denominación;Movimientos\n");

	apNode aux = ap2->first;
 
	while(aux != NULL){
		fprintf (fp, "%s;%s;%ld\n", aux->airport.oaci, aux->airport.denomination, aux->airport.movements);
		aux = aux->tail;
	}

	fclose(fp);

	freeAirport(ap2);

	repeat++;
	return OK;
}

void printAirport(airportADT ap){ //Funcion de testeo
	apNode aux = ap->first;
	while(aux != NULL){
		printf("OACI: %s; Deno: %s; Prov: %s; Mov: %ld \n", aux->airport.oaci, aux->airport.denomination, aux->airport.province, aux->airport.movements);
		aux=aux->tail;
	}
	printf("\n");
}
