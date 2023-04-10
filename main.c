#include <stdio.h>
#include "FenwickTree.h"

int main(){
	FenwickTree t;
	initFenwickTree(&t);
	int arr[] = {3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3};
/*	printf("getParent of %d - %d\n",4, getParent(4));
	printf("getParent of %d - %d\n", 8, getParent(8));
	printf("getParent of %d - %d\n", 9, getParent(9));
	printf("getParent of %d - %d\n", 5, getParent(5));
	printf("getNext of %d - %d\n", 4, getNext(4));
	printf("getNext of %d - %d\n", 8, getNext(8));
	printf("getNext of %d - %d\n", 9, getNext(9));
	printf("getNext of %d - %d\n", 5, getNext(5));*/
	makeFenwickTree(&t, arr, 11);
	printFenwickTree(t);
	updateFenwickTree(&t, arr, 11, 3, 9);
	printFenwickTree(t);
	printf("Sum of ind 0 to %d is %d\n", 5, getSum(t, 5));
	return 0;
}
