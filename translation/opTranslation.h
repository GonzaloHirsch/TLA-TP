#ifndef _OP_TRANSLATION_H
#define _OP_TRANSLATION_H

#include "../node.h"
#include "translation.h"
#include <string.h>
#include <stdio.h>

char * processOperation(GenericNode * gn);

#endif

/*
#include <stdio.h>
#include <stdlib.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

typedef struct IntArr{
	int * arr;
	int size;
} IntArr;

typedef struct DoubleArr{
	double * arr;
	int size;
} DoubleArr;

DoubleArr * _prodIntArrInt(IntArr * arr, int num);
DoubleArr * _prodIntArrDouble(IntArr * arr, double num);
DoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num);
void printIntArr(int * arr, int size);
void printDoubleArr(double * arr, int size);

DoubleArr * _prodIntArrInt(IntArr * arr, int num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

DoubleArr * _prodIntArrDouble(IntArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

DoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

void printIntArr(int * arr, int size){
	int i = 0;
	for (i = 0; i < size; i++){
		printf("%d ", arr[i]);
	}
	printf("\n");
}

void printDoubleArr(double * arr, int size){
	int i = 0;
	for (i = 0; i < size; i++){
		printf("%f ", arr[i]);
	}
	printf("\n");
}

int main(){
	int ar[] = {1,2,3};
	IntArr * a = malloc(sizeof(IntArr));
	a->arr = ar;
	a->size = NELEMS(ar);
	_prodDoubleArrDouble(_prodIntArrDouble(a, 2.5), 3);
	//_prodDoubleArrDouble()
	//_prodDoubleArrDouble(_prodDoubleArrDouble(b, 3.5, NELEMS(b), malloc(sizeof(double) * NELEMS(b))), 2.5, NELEMS(_prodDoubleArrDouble(b, 3.5, NELEMS(b), malloc(sizeof(double) * NELEMS(b)))), malloc(sizeof(double) * NELEMS(b)));
	printIntArr(a->arr, a->size);
	return 0;

*/