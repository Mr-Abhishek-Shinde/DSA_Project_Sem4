#include "searching_and_sorting.h"
#include <stdlib.h>

void merge_karo(double *arr, int size, int l, int h){
	double *arr2 = malloc((h - l + 1) * sizeof(double));
	int i = l;
	int f = 0;
	int mid = (l + h) / 2;
	int j = mid + 1;
	while(i <= mid && j <= h){
		if(arr[i] < arr[j]){
			arr2[f++] = arr[i++];
		}
		else{
			arr2[f++] = arr[j++];
		}
	}
	while(i <= mid){
		arr2[f++] = arr[i++];
	}
	while(j <= h)
		arr2[f++] = arr[j++];
	i = l;
	f = 0;
	while(f < h - l + 1){
		arr[i++] = arr2[f++];
	}
}
void sort_karo(double *arr, int s, int l, int h){
	if(l == h){
		return;
	}
	sort_karo(arr, s, l, (l + h) / 2);
	sort_karo(arr, s, ((l + h) / 2) + 1, h);
	merge_karo(arr, s, l, h);
}

int binary_search_thr(double *arr, double key, int i, int n){
	int l = i;
	int h = n;
	int m;

	while(l <= h){
		m = (l + h) / 2;

		if(arr[m] == key){
			return m;
		}
		else if(arr[m] > key && (m != 0 && arr[m - 1] < key)){
			return m;
		}
		else{
			if(arr[m] < key){
				l = m + 1;
			}
			else{
				h = m - 1;
			}
		}
	}

	return l;
}
