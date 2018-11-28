#include "movementsADT.h"

typedef struct movement{
	date fecha;
	flightClass claseVuelo;
	moveType tipoMovimiento;
	char * origenOACI;
	char * destOACI;
	char * aerolinea;
}movement;

typedef struct movementsCDT{
	movement movements[BLOCK];
	size_t dim;
	moveTypeS week[7];
	moveComposition moveComp;
}movementsCDT;