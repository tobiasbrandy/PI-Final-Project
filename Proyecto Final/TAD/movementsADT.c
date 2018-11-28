#include "movementsADT.h"
#include "process.h"

typedef struct movement{

	tDate date;
	flightClassEnum class; //REGULAR, NO REGULAR, PRIVADO
	flightClasifEnum clasification; //CABOTAJE, INTERNACIONAL, NA
	moveTypeEnum moveType; //DESPEGUE, ATERRIZAJE
	char * origOACI;
	char * destOACI;
	char * airline;

}tMovement;


typedef struct movementsCDT{

	tMovement movements[BLOCK];
	size_t dim;
	tClass week[7];
	tComposition moveComp;

}movementsCDT;
