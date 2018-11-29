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
	tClasification * week;
	//int week[7][2];
	tClasification * moveComp;
	//int moveComp[3][2];

}movementsCDT;

movementsADT createMovements(){
	movementsADT mov = malloc(sizeof(movementsCDT));
	mov->week = calloc(7, sizeof(tClasification));
	mov->moveComp = calloc(3, sizeof(tClasification));
	mov->dim = 0;
	return mov;
}

void freeMovements(movementsADT mov){
	free(mov->week);
	free(mov->moveComp);
	free(mov);
}

int insertMovements(movementsADT mov, tDate date, flightClassEnum class, flightClasifEnum clasification, moveTypeEnum moveType, char * origOACI, char * destOACI, char * airline){

	if(mov->dim >= MBLOCK)
		return 0;

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
		mov->week[c][clasification]++; //Contabiliza para la query 2
		mov->moveComp[class][clasification]++; //Contabiliza para la query 3
	}

	return 1;
}

tClasification * getMovsByWeekDay(movementsADT mov){
	return mov->week;
}

tClasification * getMovsComposition(movementsADT mov){
	return mov->moveComp;
}

void printMovements(movementsADT mv){

	for (int i = 0; i < mv->dim; ++i)
	{
		printf("class:%d clasif:%d mvType:%d orOACI:%s dtOACI:%s airline:%s\n", mv->movements[i].class, mv->movements[i].clasification, mv->movements[i].moveType, mv->movements[i].origOACI, mv->movements[i].destOACI, mv->movements[i].airline);
	}
	printf("\n");
}
