#ifndef movements_ok

#define movements_ok

#include "../backend.h"

movementsADT createMovements();

int insertMovements(movementsADT mov, tDate date, flightClassEnum class, flightClasifEnum clasification, moveTypeEnum moveType, char * origOACI, char * destOACI, char * airline);

void freeMovements(movementsADT mov);

int ** getMovsByWeekDay(movementsADT mov);

int ** getMovsComposition(movementsADT mov);

moveTypeEnum getMoveType(movementsADT mv, int i);

char * getDestOACI(movementsADT mv, int i);

char * getOrigOACI(movementsADT mv, int i);

size_t getDim(movementsADT mv);

void printMovements(movementsADT mv); //testeo

#endif
