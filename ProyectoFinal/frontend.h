#ifndef frontend_ok

#define frontend_ok

#define _GNU_SOURCE
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "getnum.h"
#include "random.h"
#include "TAD/airportADT.h"
#include "TAD/movementsADT.h"

movementsADT liftBlockMovements(char * p);

int interpretClasification(char * clasif);

int interpretMove(char * clasif);

tDate interpretDate(char * d);

int interpretClass(char * class);



#endif