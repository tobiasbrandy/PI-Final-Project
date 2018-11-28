#include "process.h"

/*int isEqual(int * a, int * b){
	return *a == *b;
}

int isInArray(void * elem, void * v, size_t dim, int (*isEqual)(void*,void*), size_t bytes){
	for (int i = 0; i < dim; ++i)
		if(isEqual(elem, (char*)v + i*bytes))
			return 1;
	return 0;
}

int isIncluded(void * v1, void * v2, size_t dim1, size_t dim2, int (*isEqual)(void*,void*), size_t bytes){ //Esta incluido v2 en v1.
	for (int i = 0; i < dim2; ++i)
		if(!isInArray((char*)v2 + i*bytes, v1, dim1, isEqual, bytes))
			return 0;
	return 1;
}

int funcion(void * v1, void * v2, size_t dim1, size_t dim2, int (*isEqual)(void*,void*), size_t bytes){
	if(isIncluded(v2, v1, dim2, dim1, isEqual, bytes))
		return 1;
	else if(isIncluded(v1, v2, dim1, dim2, isEqual, bytes))
		return 2;
	else
		return 0;
}*/

int main()
{

}