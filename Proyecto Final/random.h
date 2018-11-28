#ifndef D_RANDOM
#define D_RANDOM

int randIntInBetween(int a, int b);

double randNormalize();

double randDoubleInBetween(double a, double b);

void randomize(); //Ejecutar una sola vez antes de utilizar caulquier funcion de la libreria.

void shuffle(int input[], int dim);

#endif