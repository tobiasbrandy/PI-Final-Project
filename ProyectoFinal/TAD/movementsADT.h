#include "../process.h"



movementsADT createMovements();

int insertMovements(movementsADT mov, tDate date, flightClassEnum class, flightClasifEnum clasification, moveTypeEnum moveType, char * origOACI, char * destOACI, char * airline);

void freeMovements(movementsADT mov);

tClasification * getMovsByWeekDay(movementsADT mov);

tClasification * getMovsComposition(movementsADT mov);

void printMovements(movementsADT mv); //testeo


