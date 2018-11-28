#include "../main.h"

typedef struct movementsCDT * movementsADT;
typedef enum {REGULAR, NOREGULAR, PRIVADOMN, PRIVADOME} flightClass;
typedef enum {CABOTAJE, INTERNACIONAL, NA} flightClasification;
typedef enum {DESPEGUE, ATERRIZAJE} moveType; 

movementsADT createMovements();

int insertMovement(date fecha, flightClass claseVuelo, moveType tipoMovimiento, char * origenOACI, char * destOACI, char * aerolinea);

void freeMovements(movementsADT movements);

moveTypeS * getMovsByWeekDay(movementsADT movements);

moveComposition getMovsComposition(movementsADT movements);



