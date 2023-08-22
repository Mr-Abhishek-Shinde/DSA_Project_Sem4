#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "segment_tree.h"
#include "global.h"
#include "tools.h"

/*! initialization of segment tree */
void init_ST(ST *st){
    st->arr = NULL;
    st->size = 0;
    return;
}

/*! helping recurssive function for constrct Segment tree */
void construct_helper(double *st, int node, int start_index_thr, int end_index_thr){
    if(start_index_thr == end_index_thr){
        st[node] = INT_MAX;
        return;
    }
    construct_helper(st, 2*node + 1, start_index_thr, (start_index_thr + end_index_thr)/2);
    construct_helper(st, 2*node + 2, (start_index_thr + end_index_thr)/2 + 1, end_index_thr);

    st[node] = INT_MAX;
    return;
}

/*! construction of segment tree with initialization according given array*/
void construct_ST(ST *st, double *arr){
    st->arr = (double *) malloc(sizeof(double) * 4 * ridesharing_state.route.no_of_nodes);
    st->size = ridesharing_state.route.no_of_nodes;
    construct_helper(st->arr, 0, 0, st->size - 1);
    return;
}

/*! insert of par(i+1) at index i */
void update_par_helper(double *st, int node, int start_index, int end_index, double par, int i){
    if(start_index == end_index){
        st[node] = par;
        return;
    }
    st[node] = min(st[node], par);
    if(i >= start_index && i <= (start_index + end_index)/2)
        update_par_helper(st, 2*node + 1, start_index, (start_index + end_index)/2, par, i);
    else
        update_par_helper(st, 2*node + 2,(start_index + end_index)/2 + 1, end_index, par, i);
    return;
}

void update_par(ST st, double par, int index_to_insert){
    update_par_helper(st.arr, 0, 0, st.size - 1, par, index_to_insert);
    return;
}

/* helper function for min par */
 double min_par_helper(double *st, int node, int start_index, int end_index, int si, int ei){
    if(si <= start_index && ei >= end_index){
            return st[node];
    }
    double min_value = INT_MAX;
    if(si >= start_index && si <= (start_index + end_index) / 2){
        min_value = min(min_value, min_par_helper(st, 2*node + 1, start_index, (end_index + start_index) / 2, si, ei));
    }
    else if((si >= (start_index + end_index) / 2 + 1) && si <= end_index){
       min_value = min(min_value, min_par_helper(st, 2*node + 2, (start_index + end_index) / 2 + 1, end_index, si, ei));
    }
    else if(si > end_index){
        return INT_MAX;
    }
    if(ei >= start_index && ei <= (start_index + end_index)/2){
        min_value = min(min_value, min_par_helper(st, 2*node + 1, start_index, (end_index + start_index) / 2, si, ei));
    }
    else if((ei >= (start_index + end_index) / 2 + 1) && ei <= end_index){
        min_value = min(min_value, min_par_helper(st, 2*node + 2, (start_index + end_index) / 2 + 1, end_index, si, ei));
    }
    else if(ei < start_index){
        return INT_MAX;
    }

    return min_value;
}

/*! returns min par(j) */
double min_par(ST st, int si, int ei){
   if(si > ei){
	return INT_MAX;
    }
    return min_par_helper(st.arr, 0, 0, st.size - 1, si, ei);
}   

/* display segment tree */ 
void display(ST st, int size){
    int i, j;
    for(i = 0; i <= log2(size) + 1; i++){
        for(int k = a_raise_b(2, i); k < size; k++){
            printf("\t");
        }
        for(j = a_raise_b(2, i) - 1; j < a_raise_b(2, i + 1) - 1; j++){
            printf("%15.4f\t", st.arr[j]);
        }
        printf("\n");
    }
}

/*! recurssive function for invalidate the node according to brk */
void invalidate_node(double *st, int node, double par_j, int si, int ei){
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
void invalidate(ST st, double *par, int *brk){
    double  par_j;
    par_j = par[*brk];
    invalidate_node(st.arr, 0, par_j, 0, 6);
    (*brk)--;
    return;
}





