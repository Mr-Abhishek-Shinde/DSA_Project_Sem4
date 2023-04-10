#include <stdlib.h>
#include <limits.h>
#include "FenwickTree.h"
#include <stdio.h>

void initFenwickTree(FenwickTree *t){
	t->A = NULL;
	t->s = 0;
	return;
}
void makeFenwickTree(FenwickTree *t, int *arr, int size){
	t->A = (int *)calloc(sizeof(int), size + 1);
	t->s = size + 1;
	t->A[0] = 0;
	int j = 0;
	for(int i = 1; i < size + 1; i++){
		j = i;
		while(j < size + 1){
			t->A[j] += arr[i - 1];
			j = getNext(j);
		}
	}
	return;
}
int getParent(int n){
	return n - (n & -n);
}

int getNext(int n){
	return n + (n & -n);
}

void printFenwickTree(FenwickTree t){
	for(int i = 0; i < t.s; i++){
		printf("%d ", t.A[i]);
	}
	printf("\n");
	return;
}

void updateFenwickTree(FenwickTree *t, int *arr, int size, int ind, int value){
	int diff = value - arr[ind];
	arr[ind] += diff;
	int i = ind + 1;
	while(i < t->s){
		t->A[i] += diff;
		i = getNext(i);
	}
	return;
}

int getSum(FenwickTree t, int ind){
	int result = 0;
	int i = ind + 1;
	while(i != 0){
		result += t.A[i];
		i = getParent(i);
	}
	return result;
}
