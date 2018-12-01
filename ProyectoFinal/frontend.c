#include "frontend.h"

static int liftOneMovement(char * s, movementsADT mv);

movementsADT liftBlockMovements(char * p){
	static int endReached = 0;
	static long int filePosition = 0;
	int ok; 
	FILE * movsFile;
	char * s = NULL; 
	size_t dim = 0;
	int endFlag = 0;

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
		free(s);
		s = NULL;
		dim = 0;
	}

	if(fseek(movsFile, filePosition, SEEK_SET)){ //Muevo el puntero a la posicion filePosition
		printf("Hubo un error recuperando la posicion en el archivo\n");
		exit(1);
	}

	for(int i=0; i < MBLOCK && !feof(movsFile); i++){

		if(getline(&s, &dim, movsFile) == -1){
			if(fgetc(movsFile) == EOF)
				endFlag = 1;
			else{
				printf("No se pudo leer el archivo\n");
				exit(1);
			}
		}

		if(!feof(movsFile))
			*(s + strlen(s) - 1) = 0; //Borro el /n del final si no es el EOF

		if(!endFlag){
			ok = liftOneMovement(s, mv);

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

int interpretClasification(char * clasif){

	if( strcmp(clasif, "Cabotaje") == 0){
		return CABOTAGE; 
	}
	else if( strcmp(clasif, "Internacional") == 0 ){
		return INTERNATIONAL; 
	}
	else
		return NA; 
}

int interpretMove(char * clasif){

	if( strcmp(clasif, "Aterrizaje") == 0)
		return LANDING; 
	else
		return TAKEOFF; 
}

tDate interpretDate( char * d){ // d es "dd/mm/yyyy"
	tDate date; 

	date.day = atoi(d); 
	date.month = atoi(d + 3); 
	date.year = atoi(d + 6);

	return date; 
}

int interpretClass( char * class ){

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

	if(strlen(s) != 4 || (*s == 'S' && *(s+1) == 'A' && isdigit(s+2) && isdigit(s+3))) //Debe tener 4 digitos y no ser SA##.
		return 0;
	return 1;

}
static int liftOneMovement(char * s, movementsADT mv){
	static const char delim[2]= ";";
	char * strings[3];
	char * t;

	t = strtok(s, delim);
	tDate date= interpretDate(t);

	strtok(NULL, delim); //Me salteo uno

	t = strtok(NULL, delim); 
	flightClassEnum class= interpretClass(t); 
		
	t = strtok(NULL, delim);
	flightClasifEnum clasification = interpretClasification(t); 
		
	t = strtok(NULL, delim); 
	moveTypeEnum moveType = interpretMove(t); 
		

	for (int i = 0; i < 3; ++i)
	{
		t = strtok(NULL, delim);
		//Me fijo que los oacis sean de aeropuertos validos. Si no lo son guardo el valor null.
		if((i != 0 && i != 1) || isAValidOACI(t)){

			strings[i] = malloc(strlen(t) + 1); //sizeof(char) = 1
			strcpy(strings[i], t);

		}else
			strings[i] = NULL;
	}
	//strings[0] = origOACI, strings[1] = destOACI, strings[2] = airport;
	return insertMovements(mv, date, class, clasification, moveType, strings[0], strings[1], strings[2]);
}