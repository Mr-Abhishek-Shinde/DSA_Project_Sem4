#include <stdlib.h>
#include "structures.h"

int *pck_values;

// Function to precalculate pck values of all the locations:
// pck(k) is defined as the number of requests picked but not delivered after w arrives at lk
void pre_calculate_pck(route r, int *pck_values){
	int size_of_route = 0;

	route p = r;
	while(p){
		size_of_route++;
		p = p->next_location_node;
	}

	pck_values = (int *)malloc(sizeof(int) * size_of_route);

	pck_values[0] = 0;

	p = r->next_location_node;
	int i = 1;
	while(p){
		int pck_k = pck_values[i-1];

		request *req = p->corresponding_request;

		if((p->sequenced_location.x == req->origin.x) && (p->sequenced_location.y == req->origin.y)){
			pck_k += req->capacity;
		}
		else if((p->sequenced_location.x == req->destination.x) && (p->sequenced_location.y == req->destination.y)){
			pck_k -= req->capacity;
		}

		pck_values[i] = pck_k;
		p = p->next_location_node;
		i++;
	}

	return;
}

int check_capacity_constraint(route r, worker w, request new_rq, int i, int j){
	int c = (w.capacity - new_rq.capacity);
	
	if((pck_values[i] <= c) && (pck_values[j] <= c)){
		return 1;
	}
	else{
		return 0;
	}
}
			
	 


