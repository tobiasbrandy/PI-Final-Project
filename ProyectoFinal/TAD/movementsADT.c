#include "movementsADT.h"

typedef struct movement{

	tDate date;
	flightClassEnum class; //REGULAR, NO REGULAR, PRIVADO
	flightClasifEnum clasification; //CABOTAJE, INTERNACIONAL, NA
	moveTypeEnum moveType; //DESPEGUE, ATERRIZAJE
	char * origOACI;
	char * destOACI;
	char * airline;

}tMovement;


typedef struct movementsCDT{

	tMovement movements[MBLOCK];
	size_t dim;
	int ** week;
	//int week[7][2];
	int ** moveComp;
	//int moveComp[3][2];

}movementsCDT;

movementsADT createMovements(){
	movementsADT mov = malloc(sizeof(movementsCDT));
	mov->week = (int**)createMatrix(7, NOCLASIF, sizeof(int));
	mov->moveComp = (int**)createMatrix(NOCLASS, NOCLASIF, sizeof(int));
	mov->dim = 0;
	return mov;
}

void freeMovements(movementsADT mov){
	if(mov != NULL){
		freeMatrix((void**)mov->week, 7);
		freeMatrix((void**)mov->moveComp, NOCLASS);
		free(mov);
	}
}

int insertMovements(movementsADT mov, tDate date, flightClassEnum class, flightClasifEnum clasification, moveTypeEnum moveType, char * origOACI, char * destOACI, char * airline){

	if(mov == NULL || mov->dim >= MBLOCK)
		return -1;

	mov->movements[mov->dim].date = date;
	mov->movements[mov->dim].class = class;
	mov->movements[mov->dim].clasification = clasification;
	mov->movements[mov->dim].moveType = moveType;
	mov->movements[mov->dim].origOACI = origOACI;
	mov->movements[mov->dim].destOACI = destOACI;
	mov->movements[mov->dim].airline = airline;
	mov->dim++;

	if(clasification != NA){
		weekday c = dateToWeekday(date);
		if(c == -1)
			return -1;
		mov->week[c][clasification]++; //Contabiliza para la query 2
		mov->moveComp[class][clasification]++; //Contabiliza para la query 3
	}

	return 1;
}

int ** getMovsByWeekDay(movementsADT mov){
	return mov->week;
}

int ** getMovsComposition(movementsADT mov){
	return mov->moveComp;
}

moveTypeEnum getMoveType(movementsADT mv, int i){
	return mv->movements[i].moveType;
}

char * getDestOACI(movementsADT mv, int i){
	return mv->movements[i].destOACI;
}


char * getOrigOACI(movementsADT mv, int i){
	return mv->movements[i].origOACI;
}

size_t getDim(movementsADT mv){
	return mv->dim;
}

void printMovements(movementsADT mv){

	for (int i = 0; i < mv->dim; ++i)
	{
		printf("class:%d clasif:%d mvType:%d orOACI:%s dtOACI:%s airline:%s\n", mv->movements[i].class, mv->movements[i].clasification, mv->movements[i].moveType, mv->movements[i].origOACI, mv->movements[i].destOACI, mv->movements[i].airline);
	}
	printf("\n");
}
