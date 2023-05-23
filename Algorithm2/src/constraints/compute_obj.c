#include <stdio.h>
#include <limits.h>
#include <math.h>
#include "constraints.h"
#include "mathematics.h"
#include "structures.h"

// Helper functions:
double time_between_nodes(coordinate n1, coordinate n2){
	double time_squared = ((n1.x - n2.x) * (n1.x - n2.x)) + ((n1.y - n2.y) * (n1.y - n2.y));
	return sqrt(time_squared);
}

double flow_time(Route r, Request rq){
        double arr_destination = arr(r, rq.destination);
        return arr_destination - rq.release_time;
}


// precalculating mobj:
void mobj(Route r, double **mobj_values){
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
				if(q == q->corresponding_request->destination){ //check if q is a destination
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

double obj(Route r, int i, int j, location_node *li, location_node *lj, double **mobj_values, Request *new_rq){
	double mf1, mf2, mf3, mf4;
	int n = r.no_of_nodes;
	location_node *or = new_rq->origin;
	location_node *dr= new_rq->destination;

	mf1 = mobj_values[0][i];

	if(i == j){
		mf2 = 0;
		mf3 = dis(li, or) + dis(or, dr) + dis(dr, li->next_location_node) - dis(li, li->next_location_node) + mobj_values[i + 1][n];
		mf4 = arr(r, li) + dis(li, or) + dis(or, dr) - new_rq->release_time;
	}
	else{
		mf2 = det(li, or) + mobj_values[i + 1][j];
		mf3 = det(li, or) + det(lj, dr) + mobj_values[j + 1][n];
		mf4 = arr(r, lj) + det(li, or) + dis(lj, dr) - new_rq->release_time;
	}


	return max_of_mf(mf1, mf2, mf3, mf4);
}


