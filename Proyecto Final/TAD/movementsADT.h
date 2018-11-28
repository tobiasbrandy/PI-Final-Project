#include "process.h"



movementsADT createMovements();

int insertMovement(tDate date, flightClassEnum flightClass, moveTypeEnum tipoMovimiento, char * origOACI, char * destOACI, char * airline);

void freeMovements(movementsADT movements);

tClass * getMovsByWeekDay(movementsADT movements);

tComposition getMovsComposition(movementsADT movements);



