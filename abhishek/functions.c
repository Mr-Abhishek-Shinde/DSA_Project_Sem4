#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "structures.h"

// Helper function:
int get_route_size(route r){
	int k = 0;
	route p = r;
        while(p){
                k++;
                p = p->next_location_node;
        }

	return k;
}

// Function to precalculate pck values of all the locations:
// pck(k) is defined as the number of requests picked but not delivered after w arrives at lk
int *pck_values;

void pre_calculate_pck(route r, int *pck_values){
	int size_of_route = get_route_size(r);

	pck_values = (int *)malloc(sizeof(int) * size_of_route);

	pck_values[0] = 0;

	route p = r->next_location_node;
	int i = 1;
	int pck_k = pck_values[0];
	request *req;
	
	while(p){
		req = p->corresponding_request;

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

// Function to check if capacity constraint is violated:
int check_capacity_constraint(route r, worker w, request new_rq, int i, int j){
	int c = (w.capacity - new_rq.capacity);
	
	int result;

	if((pck_values[i] <= c) && (pck_values[j] <= c)){
		result = 1;
	}
	else{
		return 0;
	}

	for(int k = i + 1; k < j; k++){
		if(pck_values[k] > c){
			result = 0;
		}
	}

	return result;
}
			
// Helper functions:
double time_between_nodes(coordinate n1, coordinate n2){
        double time_squared = ((n1.x - n2.x) * (n1.x - n2.x)) + ((n1.y - n2.y) * (n1.y - n2.y));
        return sqrt(time_squared);
}

double arrival_time(route r, coordinate l){
        double time = 0;
        location_node *prev = r;
        location_node *curr = r->next_location_node;
        
	while(((prev->sequenced_location).x != l.x) || ((prev->sequenced_location).y != l.y)){
                time += time_between_nodes(prev->sequenced_location, curr->sequenced_location);
                prev = curr;
                curr = curr->next_location_node;
        }
        
	return time;
}

double flow_time(route r, request rq){
        double arr_destination = arrival_time(r, rq.destination);
        return arr_destination - rq.release_time;
}

int max(int a, int b){
	return (a > b ? a : b);
}

// precalculating mobj:
void mobj(route r, double **mobj_values){
	int size_of_route = get_route_size(r);
	mobj_values = (double **)malloc(sizeof(double*) * (size_of_route + 1));

	for(int i = 0; i <= size_of_route + 1; i++){
		mobj_values[i] = (double *)malloc(sizeof(double) * (size_of_route + 1));
	}

	int ft_curr_rq = 0;

	route p = r;
	for(int i = 0; p != NULL; i++){
		route q = r;
		
		for(int j = 0; q != NULL ; j++){
			if(i > j - 1){
				mobj_values[i][j] = INT_MAX;
			}
			else{
				if((q->sequenced_location.x == q->corresponding_request->destination.x) && (q->sequenced_location.y == q->corresponding_request->destination.y)){
					ft_curr_rq = flow_time(r, *(q->corresponding_request));
				}
				else{
					ft_curr_rq = 0;
				}
			 
				mobj_values[i][j] = max(mobj_values[i][j-1], ft_curr_rq);
			}

			q = q->next_location_node;
		}
		p = p->next_location_node;
	}

	return;
}


// Functions to calculate the objective:
double max_of_mf(float mf1, float mf2, float mf3, float mf4){
	float max_mf = mf1;

	if(mf2 > max_mf){
		max_mf = mf2;
	}
	if(mf3 > max_mf){
		max_mf = mf3;
	}
	if(mf4 > max_mf){
		max_mf = mf4;
	}

	return max_mf;
}

double obj(route r, int i, int j, location_node *li, location_node *lj, double **mobj_values, request new_rq){
	double mf1, mf2, mf3, mf4;
	int n = get_route_size(r);

	// malloc two location nodes for origin and destination of new request:
	location_node *new_origin = (location_node *)malloc(sizeof(location_node));
	new_origin->sequenced_location = new_rq.origin;
	new_origin->next_location_node = NULL;
	new_origin->corresponding_request = &new_rq;

	location_node *new_destination = (location_node *)malloc(sizeof(location_node));
	new_destination->sequenced_location = new_rq.destination;
        new_destination->next_location_node = NULL;
        new_destination->corresponding_request = &new_rq;

	mf1 = mobj_values[0][i];

	mf2 = det(li, new_origin) + mobj_values[i + 1][j];

	mf3 = det(li, new_origin) + det(lj, new_destination) + mobj_values[j + 1][n];

	mf4 = arr(li) + dis(li, new_origin) + dis(new_origin, new_destination);

	return max_of_mf(mf1, mf2, mf3, mf4);
}





