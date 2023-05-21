#include "structures.h"

void pre_calculate_pck(route r, double *pck_values){
	pck_values[0] = 0;

	location_node *p = r.path->next_location_node;
	int i = 1;
	double pck_k = pck_values[0];

	request *req;
	
	while(p){
		req = p->corresponding_request;

		if(p == req->origin){
			pck_k += req->capacity;
		}
		else if(p == req->destination){
			pck_k -= req->capacity;
		}

		pck_values[i] = pck_k;
		p = p->next_location_node;
		i++;
	}

	return;
}

int check_capacity_constraint(worker w, request new_request, double *pck_values, int i, int j){
	int c = (w.capacity - new_request.capacity);
	
	int result;

	if((pck_values[i] <= c) && (pck_values[j] <= c)){
		result = 1;
	}
	else{
		return 0;
	}

	for(int k = i + 1; k <= j; k++){
		if(pck_values[k] > c){
			result = 0;
			break;
		}
	}

	return result;
}
