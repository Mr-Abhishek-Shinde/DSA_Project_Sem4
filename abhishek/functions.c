#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include "structures.h"

// Function to precalculate pck values of all the locations:
// pck(k) is defined as the number of requests picked but not delivered after w arrives at lk
int *pck_values;

void pre_calculate_pck(route r, int *pck_values){
	pck_values[0] = 0;

	location_node *p = r.path->next_location_node;
	int i = 1;
	int pck_k = pck_values[0];

	request *req;
	
	while(p){
		req = p->corresponding_request;

		if(p == req->or){
			pck_k += req->capacity;
		}
		else if(p == req->dr){
			pck_k -= req->capacity;
		}

		pck_values[i] = pck_k;
		p = p->next_location_node;
		i++;
	}

	return;
}

// Function to check if capacity constraint is violated:
int check_capacity_constraint(worker w, request new_request, int i, int j){
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
				
// Helper functions:
double time_between_nodes(coordinate n1, coordinate n2){
	double time_squared = ((n1.x - n2.x) * (n1.x - n2.x)) + ((n1.y - n2.y) * (n1.y - n2.y));
	return sqrt(time_squared);
}

double arrival_time(route r, coordinate l){
	double time = 0;
	location_node *prev = r.path;
	location_node *curr = r.path->next_location_node;
        
	while(((prev->sequenced_location).x != l.x) || ((prev->sequenced_location).y != l.y)){
                time += time_between_nodes(prev->sequenced_location, curr->sequenced_location);
                prev = curr;
                curr = curr->next_location_node;
        }
        
	return time;
}

double flow_time(route r, request rq){
        double arr_destination = arrival_time(r, rq.dr->sequenced_location);
        return arr_destination - rq.release_time;
}

int max(int a, int b){
	return (a > b ? a : b);
}

// precalculating mobj:
void mobj(route r, double **mobj_values){
	double ft_curr = 0;

	location_node *q, *p = r.path;
	for(int i = 0; p != NULL; i++, p = p->next_location_node){
		q = r.path;
		
		for(int j = 0; q != NULL ; j++, q = q->next_location_node){
			if(i > j){
				mobj_values[i][j] = INT_MAX;
			}
			else if( i == 0 &&  j == 0){
				mobj_values[i][j] = 0;
			}
			else{
				if(q == q->corresponding_request->dr){ //check if q is a destination
					ft_curr = flow_time(r, *(q->corresponding_request));
				}
				else{
					ft_curr = 0;
				}
			 
				mobj_values[i][j] = max(mobj_values[i][j-1], ft_curr);
			}
		}
	}
	return;
}

// Functions to calculate the objective:
double max_of_mf(double mf1, double mf2, double mf3, double mf4){
	double max_mf = mf1;

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

double obj(route r, int i, int j, location_node *li, location_node *lj, double **mobj_values, request *new_rq){
	double mf1, mf2, mf3, mf4;
	int n = r.no_of_nodes;
	location_node *or = new_rq->or;
	location_node *dr = new_rq->dr;

	mf1 = mobj_values[0][i];

	if(i == j){
		mf2 = 0;
		mf3 = dis(li, or) + dis(or, dr) + dis(dr, li->next_location_node) - dis(li, li->next_location_node) + mobj_values[i + 1][n];
		mf4 = arr(li) + dis(li, or) + dis(or, dr) - new_rq->release_time;
	}
	else{
		mf2 = det(li, or) + mobj_values[i + 1][j];
		mf3 = det(li, or) + det(lj, dr) + mobj_values[j + 1][n];
		mf4 = arr(lj) + det(li, or) + dis(lj, dr) - new_rq->release_time;
	}


	return max_of_mf(mf1, mf2, mf3, mf4);
}


