#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int randIntInBetween(int a, int b){
	return rand() % (b - a + 1) + a;
}

double randNormalize(){
	return rand()/(double)RAND_MAX;
}

double randDoubleInBetween(double a, double b){
	return randNormalize()*(b - a) + a;
}

void randomize(){
	srand((int)time(NULL));
}

void shuffleArray(int input[], int dim){ 
	int aux, rand;
	for (int i = 0; i < dim; ++i)
	{
		rand = randIntInBetween(0, dim - 1);
		aux = input[i];
		input[i] = input[rand];
		input[rand] = aux;
	}
}

