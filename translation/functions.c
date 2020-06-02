#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))

// ------------------------- DEFINITIONS -------------------------

typedef struct IntArr{
	int * arr;
	int size;
} IntArr;

typedef struct DoubleArr{
	double * arr;
	int size;
} DoubleArr;

// ---------- Product ----------

// Product Int Arr & Int
IntArr * _prodIntArrInt(IntArr * arr, int num);
IntArr * _prodIntIntArr(int num, IntArr * arr);

// Product Int Arr & Double
DoubleArr * _prodIntArrDouble(IntArr * arr, double num);
DoubleArr * _prodDoubleIntArr(double num, IntArr * arr);

// Product Double Arr & Double
DoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num);
DoubleArr * _prodDoubleDoubleArr(double num, DoubleArr * arr);

// Product Double Arr & Int
DoubleArr * _prodDoubleArrInt(DoubleArr * arr, int num);
DoubleArr * _prodIntDoubleArr(int num, DoubleArr * arr);

// Product Double Arr & Double Arr
DoubleArr * _prodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);

// Product Int Arr & Int Arr
IntArr * _prodIntArrIntArr(IntArr * arr1, IntArr * arr2);

// Product Int Arr & Double Arr
DoubleArr * _prodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);
DoubleArr * _prodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);

// ---------- Sum ----------

// Sum Int Arr & Int
IntArr * _sumIntArrInt(IntArr * arr, int num);
IntArr * _sumIntIntArr(int num, IntArr * arr);

// Sum Int Arr & Double
DoubleArr * _sumIntArrDouble(IntArr * arr, double num);
DoubleArr * _sumDoubleIntArr(double num, IntArr * arr);

// Sum Double Arr & Double
DoubleArr * _sumDoubleArrDouble(DoubleArr * arr, double num);
DoubleArr * _sumDoubleDoubleArr(double num, DoubleArr * arr);

// Sum Double Arr & Int
DoubleArr * _sumDoubleArrInt(DoubleArr * arr, int num);
DoubleArr * _sumIntDoubleArr(int num, DoubleArr * arr);

// Sum Double Arr & Double Arr
DoubleArr * _sumDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);

// Sum Int Arr & Int Arr
IntArr * _sumIntArrIntArr(IntArr * arr1, IntArr * arr2);

// Sum Int Arr & Double Arr
DoubleArr * _sumDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);
DoubleArr * _sumIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);

// Sum Str & Str
char * _sumStrStr(char * str1, char * str2);

// ---------- Subs ----------

// Subs Int Arr & Int
IntArr * _subsIntArrInt(IntArr * arr, int num);

// Subs Int Arr & Double
DoubleArr * _subsIntArrDouble(IntArr * arr, double num);

// Subs Double Arr & Double
DoubleArr * _subsDoubleArrDouble(DoubleArr * arr, double num);

// Subs Double Arr & Int
DoubleArr * _subsDoubleArrInt(DoubleArr * arr, int num);

// Subs Double Arr & Double Arr
DoubleArr * _subsDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);

// Subs Int Arr & Int Arr
IntArr * _subsIntArrIntArr(IntArr * arr1, IntArr * arr2);

// Subs Int Arr & Double Arr
DoubleArr * _subsDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);
DoubleArr * _subsIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);

// ---------- Div ----------

// Div Int Arr & Int
DoubleArr * _divIntArrInt(IntArr * arr, int num);

// Div Int Arr & Double
DoubleArr * _divIntArrDouble(IntArr * arr, double num);

// Div Double Arr & Double
DoubleArr * _divDoubleArrDouble(DoubleArr * arr, double num);

// Div Double Arr & Int
DoubleArr * _divDoubleArrInt(DoubleArr * arr, int num);

// Div Double Arr & Double Arr
DoubleArr * _divDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2);

// Div Int Arr & Int Arr
DoubleArr * _divIntArrIntArr(IntArr * arr1, IntArr * arr2);

// Div Int Arr & Double Arr
DoubleArr * _divDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2);
DoubleArr * _divIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2);

// ---------- Other ----------

void _printIntArr(IntArr * arr);
void _printDoubleArr(DoubleArr * arr);

// ------------------------- IMPLEMENTATIONS -------------------------

// ---------- Product ----------

// Product Int Arr & Int
IntArr * _prodIntArrInt(IntArr * arr, int num){
	IntArr * res = malloc(sizeof(IntArr));
	int * resArr = malloc(sizeof(int) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] * num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
IntArr * _prodIntIntArr(int num, IntArr * arr){
	return _prodIntArrInt(arr, num);
}

// Product Int Arr & Double
DoubleArr * _prodIntArrDouble(IntArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
DoubleArr * _prodDoubleIntArr(double num, IntArr * arr){
	return _prodIntArrDouble(arr, num);
}

// Product Double Arr & Double
DoubleArr * _prodDoubleArrDouble(DoubleArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
DoubleArr * _prodDoubleDoubleArr(double num, DoubleArr * arr){
	return _prodDoubleArrDouble(arr, num);
}

// Product Double Arr & Int
DoubleArr * _prodDoubleArrInt(DoubleArr * arr, int num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] * num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
DoubleArr * _prodIntDoubleArr(int num, DoubleArr * arr){
	return _prodDoubleArrInt(arr, num);
}

// Product Double Arr & Double Arr
DoubleArr * _prodDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] * arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Product Int Arr & Int Arr
IntArr * _prodIntArrIntArr(IntArr * arr1, IntArr * arr2){
	IntArr * res = malloc(sizeof(IntArr));
	int * resArr = malloc(sizeof(int) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] * arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Product Int Arr & Double Arr
DoubleArr * _prodDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] * arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}
DoubleArr * _prodIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){
	return _prodDoubleArrIntArr(arr2, arr1);
}

// ---------- Sum ----------

// Sum Int Arr & Int
IntArr * _sumIntArrInt(IntArr * arr, int num){
	IntArr * res = malloc(sizeof(IntArr));
	int * resArr = malloc(sizeof(int) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] + num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
IntArr * _sumIntIntArr(int num, IntArr * arr){
	return _sumIntArrInt(arr, num);
}

// Sum Int Arr & Double
DoubleArr * _sumIntArrDouble(IntArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
DoubleArr * _sumDoubleIntArr(double num, IntArr * arr){
	return _sumIntArrDouble(arr, num);
}

// Sum Double Arr & Double
DoubleArr * _sumDoubleArrDouble(DoubleArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
DoubleArr * _sumDoubleDoubleArr(double num, DoubleArr * arr){
	return _sumDoubleArrDouble(arr, num);
}

// Sum Double Arr & Int
DoubleArr * _sumDoubleArrInt(DoubleArr * arr, int num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] + num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}
DoubleArr * _sumIntDoubleArr(int num, DoubleArr * arr){
	return _sumDoubleArrInt(arr, num);
}

// Sum Double Arr & Double Arr
DoubleArr * _sumDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] + arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Sum Int Arr & Int Arr
IntArr * _sumIntArrIntArr(IntArr * arr1, IntArr * arr2){
	IntArr * res = malloc(sizeof(IntArr));
	int * resArr = malloc(sizeof(int) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] + arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Sum Int Arr & Double Arr
DoubleArr * _sumDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] + arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}
DoubleArr * _sumIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){
	return _sumDoubleArrIntArr(arr2, arr1);
}

// Sum Str & Str
char * _sumStrStr(char * str1, char * str2){
	char * buffer = malloc(1 + strlen(str1) + strlen(str2));
	sprintf(buffer, "%s%s", str1, str2);
	return buffer;
}

// ---------- Subs ----------

// Subs Int Arr & Int
IntArr * _subsIntArrInt(IntArr * arr, int num){
	IntArr * res = malloc(sizeof(IntArr));
	int * resArr = malloc(sizeof(int) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (arr->arr[i] - num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Subs Int Arr & Double
DoubleArr * _subsIntArrDouble(IntArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Subs Double Arr & Double
DoubleArr * _subsDoubleArrDouble(DoubleArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Subs Double Arr & Int
DoubleArr * _subsDoubleArrInt(DoubleArr * arr, int num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] - num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Subs Double Arr & Double Arr
DoubleArr * _subsDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Subs Int Arr & Int Arr
IntArr * _subsIntArrIntArr(IntArr * arr1, IntArr * arr2){
	IntArr * res = malloc(sizeof(IntArr));
	int * resArr = malloc(sizeof(int) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (arr1->arr[i] - arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Subs Int Arr & Double Arr
DoubleArr * _subsDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}
DoubleArr * _subsIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){
	return _subsDoubleArrIntArr(arr2, arr1);
}

// ---------- Div ----------

// Div Int Arr & Int
DoubleArr * _divIntArrInt(IntArr * arr, int num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Div Int Arr & Double
DoubleArr * _divIntArrDouble(IntArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Div Double Arr & Double
DoubleArr * _divDoubleArrDouble(DoubleArr * arr, double num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Div Double Arr & Int
DoubleArr * _divDoubleArrInt(DoubleArr * arr, int num){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr->size);
	int i = 0;for(i = 0; i < arr->size; i++){resArr[i] = (double)(arr->arr[i] / num);}
	res->arr = resArr;
	res->size = arr->size;
	return res;
}

// Div Double Arr & Double Arr
DoubleArr * _divDoubleArrDoubleArr(DoubleArr * arr1, DoubleArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Div Int Arr & Int Arr
DoubleArr * _divIntArrIntArr(IntArr * arr1, IntArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}

// Div Int Arr & Double Arr
DoubleArr * _divDoubleArrIntArr(DoubleArr * arr1, IntArr * arr2){
	DoubleArr * res = malloc(sizeof(DoubleArr));
	double * resArr = malloc(sizeof(double) * arr1->size);
	int i = 0;for(i = 0; i < arr1->size; i++){resArr[i] = (double)(arr1->arr[i] - arr2->arr[i]);}
	res->arr = resArr;
	res->size = arr1->size;
	return res;
}
DoubleArr * _divIntArrDoubleArr(IntArr * arr1, DoubleArr * arr2){
	return _divDoubleArrIntArr(arr2, arr1);
}

// ---------- Other ----------

void _printIntArr(IntArr * arr){
	int i = 0;
	printf("[");
	for (i = 0; i < arr->size; i++){
		if (i == arr->size - 1){
			printf("%d]\n", arr->arr[i]);
		} else {
			printf("%d ", arr->arr[i]);
		}
	}
}

void _printDoubleArr(DoubleArr * arr){
	int i = 0;
	printf("[");
	for (i = 0; i < arr->size; i++){
		if (i == arr->size - 1){
			printf("%f]\n", arr->arr[i]);
		} else {
			printf("%f ", arr->arr[i]);
		}
	}
}
