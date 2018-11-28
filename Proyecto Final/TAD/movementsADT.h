#include "../main.h"



movementsADT createMovements();

int insertMovement(date fecha, flightClass claseVuelo, moveType tipoMovimiento, char * origenOACI, char * destOACI, char * aerolinea);

void freeMovements(movementsADT movements);

tClass * getMovsByWeekDay(movementsADT movements);

moveComposition getMovsComposition(movementsADT movements);



