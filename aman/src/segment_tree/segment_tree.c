#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "segment_tree.h"


double min(double num1, double num2){
		return (num1 > num2 ? num2 : num1);
}

double a_raise_b(double a, double b){
	double result = 1, num = a;
	for(int i = 0; i < b; i++){
		result = result * num;
	}
	return result;
}

/*! initialization of segment tree */
void init_ST(ST *st){
    *st = NULL;
    return;
}


/*! helping recurssive function for constrct Segment tree */
void construct(ST st, int node, int start_index, int end_index){
    if(start_index == end_index){
        st[node] = INT_MAX;
        return;
    }
    construct(st, 2*node + 1, start_index, (start_index + end_index)/2);
    construct(st, 2*node + 2, (start_index + end_index)/2 + 1, end_index);

    st[node] = INT_MAX;
    return;
}

/*! construction of segment tree with initialization of INT_MAX */
void construct_ST(ST *st, int size){
    (*st) = (double*)malloc(sizeof(double)*SIZE_OF_ST(size));
    construct(*st, 0, 0, size-1);
    return;
}

/*! insert of par(i+1) at index i */
void insert_par(ST st, int node, int start_index, int end_index, double par, int i){
    if(start_index == end_index){
        st[node] = par;
        return;
    }
    st[node] = min(st[node], par);
    if(i >= start_index && i <= (start_index + end_index)/2)
        insert_par(st, 2*node + 1, start_index, (start_index + end_index)/2, par, i);
    else
        insert_par(st, 2*node + 2,(start_index + end_index)/2 + 1, end_index, par, i);
    return;
}

/*! returns min par(j) */
int min_par(ST st){
    return st[TOP_INDEX_ST];
}

/* display segment tree */ 
void display(ST st, int size){
    int i, j;
    for(i = 0; i <= log2(size) + 1; i++){
        for(int k = a_raise_b(2, i); k < size; k++){
            printf("\t");
        }
        for(j = a_raise_b(2, i) - 1; j < a_raise_b(2, i + 1) - 1; j++){
            printf("%8.4f\t", st[j]);
        }
        printf("\n");
    }
}

/*! recurssive function for invalidate the node according to brk */
void invalidate_node(ST st, int node, int par_j, int si, int ei){
    if(si == ei){
        st[node] = INT_MAX;
        return;
    }

    if(st[node] > par_j)
        return;
    else{
        if(st[2*node + 1] <= par_j)
            invalidate_node(st, 2*node + 1, par_j, si, (si + ei)/2);
        else if(st[2*node + 2] <= par_j)
            invalidate_node(st, 2*node + 2, par_j, (si + ei)/2 + 1, ei);
    }
    st[node] = min(st[2*node + 1], st[2*node + 2]);
    return;
}

/*! invalidate function */
void invalidate(ST st, int *par, int *brk){
    int par_j;

    par_j = par[*brk];
    invalidate_node(st, START_INDEX_ARR, par_j, 0, 6);
    (*brk)--;
    return;
}

int main(){
    ST st;
    init_ST(&st);
    construct_ST(&st, 7);
    display(st, 7);
    insert_par(st, 0, 0, 6, 5, 0);
    insert_par(st, 0, 0, 6, 8, 1);
    insert_par(st, 0, 0, 6, 3, 2);
    insert_par(st, 0, 0, 6, 6, 3);
    insert_par(st, 0, 0, 6, 1, 4);
    display(st, 7);
    printf("MIN: %d\n", min_par(st));
    invalidate_node(st, TOP_INDEX_ST, 1, 0, 6);
    display(st, 7);
    printf("MIN: %d\n", min_par(st));
    return 0;
}





