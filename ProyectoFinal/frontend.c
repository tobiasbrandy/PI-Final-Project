#include "frontend.h"

/*
*Recibe un string con una linea del archivo de movimientos con toda la informacion de un movimiento, un movementsADT, el delimitador de los datos en el string
*y la posicion donde se encuentra cada dato en el string (cuantos delimitadores hay que pasar para acceder a el).
*La funcion interpreta todos los datos del string y los transforma en el tipo de dato adecuado y luego hace un insert en el movementsADT que se le paso.
*Retorna OK o ERROR, segun corresponda.
*/
static int liftOneMovement(char * s, movementsADT mv, char * delim, int datePos, int classPos, int clasifPos, int moveTypePos, int origOACIPos, int destOACIPos, int airlinePos);

/*
*Recibe un string con la primera linea del archivo csv de movimientos que indica nombre y posicion de cada dato y el delimitador que los separa.
*Devuelve en el correspondiente parametro de salida la posicion (cantidad de delimitadores que hay que pasar para acceder al dato)
*de cada dato necesario para crear un movementsADT.
*Retorna OK o ERROR, segun corresponda.
*/
static int getInfoPositionMovements(char * s, char * delim, int * datePos, int * classPos, int * clasifPos, int * moveTypePos, int * origOACIPos, int * destOACIPos, int * airlinePos);

/*
*Recibe un string con una linea del archivo de aeropuertos con toda la informacion de un aeropuerto, un airportADT, el delimitador de los datos en el string
*y la posicion donde se encuentra cada dato en el string (cuantos delimitadores hay que pasar para acceder a el).
*La funcion interpreta todos los datos del string y los transforma en el tipo de dato adecuado y luego hace un insert en el airportADT que se le paso.
*Retorna OK o ERROR, segun corresponda.
*/
static int liftOneAirport(airportADT ap, char * s, char * delim, int oaciPos, int denomPos, int provincePos);

/*
*Recibe un string con la primera linea del archivo csv de aeropuertos que indica nombre y posicion de cada dato y el delimitador que los separa.
*Devuelve en el correspondiente parametro de salida la posicion (cantidad de delimitadores que hay que pasar para acceder al dato)
*de cada dato necesario para crear un movementsADT.
*Retorna OK o ERROR, segun corresponda.
*/
static int getInfoPositionAirport(char * s, char * delim, int * oaciPos, int * denomPos, int * provincePos);

/*
*Recibe un OACI. Devuelve 1 si el OACI puede ser de algun aeropuerto del archivo aeropuertos, es decir,
*que tenga exactamente 4 caracteres y no sea de la forma SA##. Retorna 0 de lo contrario.
*/
static int isAValidOACI(char * s);

/*
*Transforma un string con el dato de clase de movimiento y lo tranforma a un tipo de dato valido para movementsADT.
*/
static int interpretClass(char * class);

/*
*Transforma un string con el dato de fecha y lo tranforma a un tipo de dato valido para movementsADT.
*/
static tDate interpretDate(char * d);

/*
*Transforma un string con el dato de tipo de movimiento y lo tranforma a un tipo de dato valido para movementsADT.
*/
static int interpretType(char * clasif);

/*
*Transforma un string con el dato de calsificacion y lo tranforma a un tipo de dato valido para movementsADT.
*/
static int interpretClasification(char * clasif);

//FUNCIONES PARA MOVEMENT
movementsADT liftBlockMovements(char * p){

	static int endReached = 0;
	static long int filePosition = 0;
	static int datePos = -1, classPos = -1, clasifPos = -1, origOACIPos = -1, destOACIPos = -1, moveTypePos = -1, airlinePos = -1;
	static char * delim = ";";
	int ok; 
	FILE * movsFile;
	char * s = NULL; 
	size_t dim = 0;

	if(endReached)
		return NULL;

	movementsADT mv = createMovements();
 

	if( (movsFile = fopen(p, "r")) == NULL) {
		printf("No se pudo abrir el archivo %s\n", p); //Abro el archivo
		exit(1);
	}

	if(filePosition == 0){
		if(getline(&s, &dim, movsFile) == -1){
			printf("No se pudo leer el archivo %s\n", p); //Traigo la primera linea
			exit(1);
		}

		if(getInfoPositionMovements(s, delim, &datePos, &classPos, &clasifPos, &moveTypePos, &origOACIPos, &destOACIPos, &airlinePos) == -1){
			printf("El archivo ingresado para movimientos es invalido (%s).\n", p);
			exit(1);
		}
	}

	if(fseek(movsFile, filePosition, SEEK_SET)){ //Muevo el puntero a la posicion filePosition
		printf("Hubo un error recuperando la posicion en el archivo %s\n", p);
		exit(1);
	}

	for(int i=0; i < MBLOCK && !feof(movsFile); i++){

		if(getline(&s, &dim, movsFile) == -1){
			if(fgetc(movsFile) == EOF) //Si la ultima linea es vacia, el getline falla. Con esto lo atajo y activo el feof.
				endReached = 1;
			else{
				printf("No se pudo leer el archivo %s\n", p);
				exit(1);
			}
		}

		if(!feof(movsFile))
			*(s + strlen(s) - 1) = 0; //Borro el /n del final si no es el EOF

		if(!endReached){
			ok = liftOneMovement(s, mv, delim, datePos, classPos, clasifPos, moveTypePos, origOACIPos, destOACIPos, airlinePos);

			if(ok == -1){
				printf("Hubo un error en la insercion de un movimiento.\n");
				exit(1);
			}
		}

		free(s);
		s = NULL;
		dim = 0;
	}

	if((filePosition = ftell(movsFile)) == ERROR){ //Guarda la posicion en el archivo
		printf("Hubo un problema con la obtencion de la posicion en el archivo %s\n", p);
		exit(1);
	}

	if(feof(movsFile)){
		clearerr(movsFile);
		endReached = 1;
	}

	if(endReached && getDim(mv) == 0){
		freeMovements(mv, SHALLOW); //Shallow pues no se guardo ningun string. De todas maneras no cambia pues dim==0.
		mv = NULL;
	}
	

	fclose(movsFile);

	return mv; 

}

static int interpretClasification(char * clasif){

	if( strcmp(clasif, "Cabotaje") == 0){
		return CABOTAGE; 
	}
	else if( strcmp(clasif, "Internacional") == 0 ){
		return INTERNATIONAL; 
	}
	else
		return NA; 
}

static int interpretType(char * type){

	if( strcmp(type, "Aterrizaje") == 0)
		return LANDING; 
	else
		return TAKEOFF; 
}

static tDate interpretDate( char * d){ // d es "dd/mm/yyyy"
	tDate date; 

	date.day = atoi(d); 
	date.month = atoi(d + 3); 
	date.year = atoi(d + 6);

	return date; 
}

static int interpretClass( char * class ){

	if( strcmp(class, "Regular") == 0 ){
		return REGULAR; 
	}
	else if( strcmp(class, "No Regular") == 0 ){
		return NOREGULAR; 
	}
	else
		return PRIVATE;

}

static int isAValidOACI(char * s){

	if(strlen(s) != 4 || (*s == 'S' && *(s+1) == 'A' && isdigit(*(s+2)) && isdigit(*(s+3)))) //Debe tener 4 digitos y no ser SA##.
		return 0;
	return 1;

}

static int liftOneMovement(char * s, movementsADT mv, char * delim, int datePos, int classPos, int clasifPos, int moveTypePos, int origOACIPos, int destOACIPos, int airlinePos){

	int i = 0;
	char * t;
	tDate date;
	flightClassEnum class;
	flightClasifEnum clasification;
	moveTypeEnum moveType;
	char * origOACI = NULL;
	char * destOACI = NULL;
	char * airline = NULL;


	t = strtok(s, delim);

	while (t != NULL) {

		if(i == datePos)
			date = interpretDate(t);

		else if(i == classPos)
			class = interpretClass(t);

		else if(i == clasifPos)
			clasification = interpretClasification(t);


		else if(i == moveTypePos)
			moveType = interpretType(t);

		else if(i == origOACIPos){
			if(isAValidOACI(t)){
				origOACI = malloc(strlen(t) + 1); //sizeof(char) = 1
				strcpy(origOACI, t);
			}
		}

		else if(i == destOACIPos){
			if(isAValidOACI(t)){
				destOACI = malloc(strlen(t) + 1); //sizeof(char) = 1
				strcpy(destOACI, t);
			}
		}

		else if(i == airlinePos){
			if(!isspace(*t)){
				airline = malloc(strlen(t) + 1);
				strcpy(airline, t);
			}
		}

		i++;
		t = strtok (NULL, delim);
	}
	return insertMovements(mv, date, class, clasification, moveType, origOACI, destOACI, airline);
}

static int getInfoPositionMovements(char * s, char * delim, int * datePos, int * classPos, int * clasifPos, int * moveTypePos, int * origOACIPos, int * destOACIPos, int * airlinePos){
	int i = 0;
	char * t;

	t = strtok(s, delim);

	while (t != NULL) {


		if (strcmp (t, "Fecha") == 0)
			*datePos = i;

		else if (strcmp(t, "Clase de Vuelo") == 0)
			*classPos = i;

		else if (strcmp (t, "Clasificaci?n Vuelo") == 0)
			*clasifPos = i;

		else if (strcmp (t, "Tipo de Movimiento") == 0)
			*moveTypePos = i;

		else if (strcmp (t, "Origen OACI") == 0)
			*origOACIPos = i;

		else if (strcmp (t, "Destino OACI") == 0)
			*destOACIPos = i;

		else if (strcmp (t, "Aerolinea Nombre") == 0)
			*airlinePos = i;

		t = strtok(NULL, delim);
		i++;
	}

	if(*datePos == -1 || *classPos == -1 || *clasifPos == -1 || *moveTypePos == -1 || *origOACIPos == -1 || *destOACIPos == -1 || *airlinePos == -1)
		return ERROR;
	return OK;
}


//FUNCIONES PARA AIRPORT
void liftAirports(airportADT ap, char * fileName) {
	FILE * fp;
	
	if ((fp = fopen (fileName, "r")) == NULL) {
		printf ("Error while opening %s", fileName);
		exit(1);
	}
	int endReached = 0;
	char * delim = ";";
	char * s = NULL; size_t dim = 0;
	int oaciPos = -1, denomPos = -1, provinciaPos = -1, ok;

	
	if(getline(&s, &dim, fp) == ERROR){
		printf("No se pudo leer el archivo %s\n", fileName);
		exit(1);
	}

	if(getInfoPositionAirport(s, delim, &oaciPos, &denomPos, &provinciaPos) == ERROR){
		printf("El archivo ingresado de aeropuertos no es valido(%s).\n", fileName);
		exit(1);
	}

	free(s);
	s = NULL;
	dim = 0;

	while (!feof(fp)) { 

		if(getline(&s, &dim, fp) == ERROR){
			if(fgetc(fp) == EOF)	//Si la ultima linea es vacia, el getline falla. Con esto lo atajo y activo el feof.
				endReached = 1;
			else{
				printf("No se pudo leer el archivo %s\n", fileName);
				exit(1);
			}
		}

		if(!feof(fp))
			*(s + strlen(s) - 1) = 0; //Borro el /n del final si no es el EOF

		if(!endReached){
			ok = liftOneAirport(ap, s, delim, oaciPos, denomPos, provinciaPos);
			if(ok == ERROR){
				printf("Hubo un error en el almacenamiento de un aeropuerto\n");
				exit(1);
			}
		}

		free(s);
		s = NULL;
		dim = 0;
	}

	if(feof(fp)){
		clearerr(fp);
		endReached = 1;
	}

	fclose(fp);
	return;
}

static int getInfoPositionAirport(char * s, char * delim, int * oaciPos, int * denomPos, int * provincePos){
	int i = 0;
	char * token;

	token = strtok(s, delim);

	while (token != NULL) {


		if (strcmp (token, "oaci") == 0)
			*oaciPos = i;

		else if (strcmp(token, "denominacion") == 0)
			*denomPos = i;

		else if (strcmp (token, "provincia") == 0)
			*provincePos = i;

		token = strtok(NULL, delim);
		i++;
	}

	if(*oaciPos == -1 || *denomPos== -1 || *provincePos == -1)
		return ERROR;
	return OK;
}

static int liftOneAirport(airportADT ap, char * s, char * delim, int oaciPos, int denomPos, int provincePos){

	int i = 0;
	char * token;
	int stopReading = 0;
	char * oaci;
	char * denom = NULL;
	char * province = NULL;

	token = strtok(s, delim);

	while (token != NULL && stopReading != 1) {

		if(i == oaciPos) {
			if (!isspace(*token)){
				oaci = malloc(strlen(token) + 1);
				strcpy(oaci, token);
			}
			else
				stopReading = 1;
		}

		else if (i == denomPos){
			denom = malloc(strlen(token) + 1); //sizeof(char) = 1
			strcpy(denom, token);
		}

		else if (i == provincePos){
			province = malloc(strlen(token) + 1);
			strcpy(province, token);
		}

		i++;
		token = strtok (NULL, delim);
	}

	if (stopReading != 1)
		return insertAirport(ap, oaci, denom, province);
	else{
		if(denom != NULL)
			free(denom);
		if(province != NULL)
			free(province);
		return OK;
	}
}

void menu(tFunction functions[], size_t dim){

	int c = -1;
	int ok;

	while(c){
		printf("Menu:\n");
		printf("Que desea hacer?\n");
		printf("Recuerde que las funciones de query, de haber sido exitosas, no se ejecutaran nuevamente\n");

		printf("0 - Terminar programa\n");
		for (int i = 0; i < dim; ++i)
		{
			printf("%d - %s\n", i + 1, functions[i].description);
		}

		do{
			c = getint("Ingrese una opcion valida\n");
		}while(c < 0 || c > dim);

		if(c != 0){
			ok = functions[c-1].function(functions[c-1].argument);
			if(ok == OK)
				printf("La operacion se ha realizado con exito\n\n\n\n");
			else
				printf("Hubo un error con la operacion. Por favor intentelo de nuevo.\n");
		}
	}

}

void menuEspecializado(void * argument1, void * argument2, void * argument3){
	tFunction function1 = {(int (*)(void*))storeAirportsByMovs, "storeAirportsByMovs", "Realizar query 1, aeropuertos por cantidad de movimientos", argument1};
	tFunction function2 = {(int (*)(void*))storeMovsByWeekdayAndClasif, "storeMovsByWeekdayAndClasif", "Realizar query 2, movimientos por dia de la semana y clasificacion", argument2};
	tFunction function3 = {(int (*)(void*))storeMovsByClasifAndClass, "storeMovsByClasifAndClass", "Realizar query 3, movimientos por clase y clasificacion", argument3};

	tFunction functions[] = {function1, function2, function3};

	menu(functions, 3);
}