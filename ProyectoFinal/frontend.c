#include "frontend.h"

static int liftOneMovement(char * s, movementsADT mv, char * delim, int datePos, int classPos, int clasifPos, int moveTypePos, int origOACIPos, int destOACIPos, int airlinePos);
static int getInfoPositionMovements(char * s, char * delim, int * datePos, int * classPos, int * clasifPos, int * moveTypePos, int * origOACIPos, int * destOACIPos, int * airlinePos);
static int liftOneAirport(airportADT ap, char * s, char * delim, int oaciPos, int denomPos, int provincePos);
static int getInfoPositionAirport(char * s, char * delim, int * oaciPos, int * denomPos, int * provincePos);

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
			printf("No se pudo leer el archivo\n"); //Me salteo la primera linea
			exit(1);
		}

		if(getInfoPositionMovements(s, delim, &datePos, &classPos, &clasifPos, &moveTypePos, &origOACIPos, &destOACIPos, &airlinePos) == -1){
			printf("El archivo ingresado para movimientos es invalido\n");
			exit(1);
		}
	}

	if(fseek(movsFile, filePosition, SEEK_SET)){ //Muevo el puntero a la posicion filePosition
		printf("Hubo un error recuperando la posicion en el archivo\n");
		exit(1);
	}

	for(int i=0; i < MBLOCK && !feof(movsFile); i++){

		if(getline(&s, &dim, movsFile) == -1){
			if(fgetc(movsFile) == EOF)
				endReached = 1;
			else{
				printf("No se pudo leer el archivo\n");
				exit(1);
			}
		}

		if(!feof(movsFile))
			*(s + strlen(s) - 1) = 0; //Borro el /n del final si no es el EOF

		if(!endReached){
			ok = liftOneMovement(s, mv, delim, datePos, classPos, clasifPos, moveTypePos, origOACIPos, destOACIPos, airlinePos);

			if(ok == -1){
				printf("Hubo un error en la insercion al movementsADT.\n");
				exit(1);
			}
		}

		free(s);
		s = NULL;
		dim = 0;
	}

	if((filePosition = ftell(movsFile)) == -1){ //Guarda la posicion en el archivo
		printf("Hubo un problema con la obtencion de la posicion en el archivo\n");
		exit(1);
	}

	if(feof(movsFile)){
		clearerr(movsFile);
		endReached = 1;
	}

	if(endReached && getDim(mv) == 0){
		freeMovements(mv);
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

static int interpretMove(char * clasif){

	if( strcmp(clasif, "Aterrizaje") == 0)
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
			moveType = interpretMove(t);

		else if(i == origOACIPos){
			if(isAValidOACI(t)){
				origOACI = malloc(strlen(t) + 10); //sizeof(char) = 1
				strcpy(origOACI, t);
			}
		}

		else if(i == destOACIPos){
			if(isAValidOACI(t)){
				destOACI = malloc(strlen(t) + 10); //sizeof(char) = 1
				strcpy(destOACI, t);
			}
		}

		else if(i == airlinePos){
			if(!isspace(*t)){
				airline = malloc(strlen(t) + 10);
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
	*clasifPos = 3; //Por ahora

	t = strtok(s, delim);

	while (t != NULL) {


		if (strcmp (t, "Fecha") == 0)
			*datePos = i;

		else if (strcmp(t, "Clase de Vuelo") == 0)
			*classPos = i;

		/*else if (strcmp (t, "Clasificacion") == 0)
			*clasifPos = i;*/

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
		//printf("%d %d %d %d %d %d %d\n", *datePos, *classPos, *clasifPos, *moveTypePos, *origOACIPos, *destOACIPos, *airlinePos);

	if(*datePos == -1 || *classPos == -1 || *clasifPos == -1 || *moveTypePos == -1 || *origOACIPos == -1 || *destOACIPos == -1 || *airlinePos == -1)
		return -1;
	return 1;
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

	
	if(getline(&s, &dim, fp) == -1){
		printf("No se pudo leer el archivo\n");
		exit(1);
	}

	if(getInfoPositionAirport(s, delim, &oaciPos, &denomPos, &provinciaPos) == -1){
		printf("El archivo ingresado de aeropuertos no es valido.\n");
		exit(1);
	}

	free(s);
	s = NULL;
	dim = 0;

	while (!feof(fp)) { 

		if(getline(&s, &dim, fp) == -1){
			if(fgetc(fp) == EOF)
				endReached = 1;
			else{
				printf("No se pudo leer el archivo\n");
				exit(1);
			}
		}

		if(!endReached){
			ok = liftOneAirport(ap, s, delim, oaciPos, denomPos, provinciaPos);
			if(ok == -1){
				printf("No se pudo almacenar el aeropuerto, datos ingresados incorrectos\n");
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
		return -1;
	return 1;
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
		return 1;
	}
}