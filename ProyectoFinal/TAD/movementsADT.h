#include "../process.h"



movementsADT createMovements();

int insertMovement(tDate date, flightClassEnum flightClass, moveTypeEnum moveType, char * origOACI, char * destOACI, char * airline);

void freeMovements(movementsADT movements);

tClasification * getMovsByWeekDay(movementsADT movements);

tComposition getMovsComposition(movementsADT movements);



