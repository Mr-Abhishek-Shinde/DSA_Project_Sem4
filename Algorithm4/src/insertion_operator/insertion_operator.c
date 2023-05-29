#include <limits.h>
#include "tools.h"
#include "constraints.h"
#include <stdlib.h>
#include <limits.h>
#include "global.h"
#include "insertion_operator.h"
#include "time_functions.h"
#include "precalculation.h"
#include "segment_tree.h"
#include "searching_and_sorting.h"
#include <stdio.h>
#include <float.h>

#define CAPACITY (4)
#define NNODES (6)

void display_route(Route r){
	location_node *p = r.path;
	coordinate sq;
	while(p){
		sq = p->sequenced_location;
		p = p->next_location_node;
		printf("x - %f\ty - %f\n", sq.x, sq.y);
	}
	return;
}

void insert_coordinate(location_node *l, double x, double y){
    l->sequenced_location.x = x;
    l->sequenced_location.y = y;
    return;
}

void insert_node(Request *request, location_node *l, int index){

    location_node *path = ridesharing_state.route.path;

    if(!path){
         (ridesharing_state.route).path = l;
         (ridesharing_state.route).path->next_location_node = NULL;
         (ridesharing_state.route).path->prev_location_node = NULL; 
         (ridesharing_state.route).path->corresponding_request  = request;
         (ridesharing_state.route).no_of_nodes++;
         (ridesharing_state.route).path->index = index;
         return;
    }

    while(path->next_location_node)
        path = path->next_location_node;

    path->next_location_node = l;
    l->prev_location_node = path;
    l->next_location_node = NULL;
    l->corresponding_request = request;
    l->index = index;
    ridesharing_state.route.no_of_nodes++;
    path->index = index;

    return;
}


void update_route(location_node *before_worker){
    location_node *traversal = ridesharing_state.route.path, *tmp = NULL;

    while(traversal != before_worker){
        tmp = traversal;
        traversal  = traversal->next_location_node;
        free(tmp);
        ridesharing_state.route.no_of_nodes--;
    }

    ridesharing_state.route.path = (location_node*)malloc(sizeof(location_node));
    (ridesharing_state.route.path)->sequenced_location = ridesharing_state.worker.current_location;
    (ridesharing_state.route.path)->next_location_node = traversal->next_location_node;
    (ridesharing_state.route.path)->prev_location_node = NULL;
    if(traversal->next_location_node){
	    traversal->next_location_node->prev_location_node = ridesharing_state.route.path;
    }
    (ridesharing_state.route.path)->index = 0;
    (ridesharing_state.route.path)->corresponding_request = NULL;
    ridesharing_state.route.no_of_nodes++;

    free(traversal);
    ridesharing_state.route.no_of_nodes--;

    return;
}

void update_worker_route(Request *new_request){

    int w_picked = 0;
    // here a and b are nodes between which our new locaton of worker will lie
	location_node *a, *b = NULL;
	coordinate unit_vector_ab, scaled_vector_aw;
	double scale_aw, distance;

        a = ridesharing_state.route.path;
        distance = 0;
        
		while(a->next_location_node){
            if(a->corresponding_request){
                if(a->corresponding_request->origin == a){
                    w_picked += a->corresponding_request->capacity;
                }
                else{
                    w_picked -= a->corresponding_request->capacity;
                }
            }
				distance += distance_node(a->sequenced_location, a->next_location_node->sequenced_location);
				if(distance >= new_request->release_time){        
				    distance -= distance_node(a->sequenced_location, a->next_location_node->sequenced_location);
					break;
				}
				a = a->next_location_node;
		}

        ridesharing_state.worker.picked_up = w_picked;

        if(!a->next_location_node){
            ridesharing_state.worker.picked_up -= a->corresponding_request->capacity;
            ridesharing_state.worker.current_location = a->sequenced_location;
        }
        else{
	    	b = a->next_location_node;
		    find_unit_vector(&unit_vector_ab, a->sequenced_location, b->sequenced_location);
		    scale_aw = new_request->release_time - distance;
		    scale_vector(&scaled_vector_aw, unit_vector_ab, scale_aw);
		    add_vector(&ridesharing_state.worker.current_location, a->sequenced_location, scaled_vector_aw);
        }
		// update route
        update_route(a);
		return;
}	


void insertion_operator(Request *new_request){
	double OBJ_MIN = INT_MAX, OBJ_NEW;
	
	location_node *li = NULL, *lj = NULL; // these are the nodes which will be used for iteration
        location_node *origin_i = NULL, *dest_j = NULL; // these are the nodes after which or and dr will get inserted
	
	int size = ridesharing_state.route.no_of_nodes;
	
	// Precalculation - pck, slk, thr, par, mobj
	Precalculation_set precalculate_set;
	precalculate(&precalculate_set, *new_request);
	// Segment tree construction:
	ST st;
	init_ST(&st);
	double *st_arr = (double *) malloc(sizeof(double) * ridesharing_state.route.no_of_nodes);
	for(int i = 0; i < size; i++){
		st_arr[i] = INT_MAX;
	}
	construct_ST(&st, st_arr);
	li = ridesharing_state.route.path;
	// Handling the case of i == j:
	for(int i = 0; i < size; i++, li = li->next_location_node){
                if(check_capacity_constraint_iEqualj(*new_request, precalculate_set.pck, i) && check_deadline_constraint_iEqualj(li, *new_request, precalculate_set.slk, i)){

                        OBJ_NEW = obj_iEqualj(precalculate_set.mobj, li, *new_request, i);
                        if(OBJ_NEW < OBJ_MIN){
                                OBJ_MIN = OBJ_NEW;
                                origin_i = li;
                                dest_j = li;
                        }
                }
        }
        li = ridesharing_state.route.path;
	while(li->next_location_node){
		li = li->next_location_node;
	}
	li = li->prev_location_node;
	double par_min;
	int brk = size - 1;
	int si;
	double minimum_par = DBL_MAX;
	// Iterating the i:
	for(int i = size - 2; i >= 0; i--){
		// Updating leaf threshold with par in ST:
		si = binary_search_thr(precalculate_set.sorted_thr, precalculate_set.thr[i + 1], 0, size - 1);
		update_par(st, precalculate_set.par[i + 1], si);

		// Checking for the capacity constraint:
		if(check_capacity_constraint(*new_request, precalculate_set.pck, i + 1) == 0){
			invalidate(st, precalculate_set.par, &brk);
		}
		else{
			// Checking for the deadline constraint:
			if(initial_deadline_condition(*new_request, li, i, precalculate_set.slk) == 1){
				si = binary_search_thr(precalculate_set.sorted_thr, det(li, new_request->origin), 0, size - 1);
				par_min = min_par(st, si, size - 1);
				// Calculating the objective:
				OBJ_NEW = obj(precalculate_set.mobj, li, *new_request, par_min, size);
				insert_value_in_flowtime_file(OBJ_NEW);
				// updating (i*, j*) with (i, j) according to OBJ
				if(OBJ_MIN > OBJ_NEW){
					origin_i = li;
					minimum_par = par_min;
					OBJ_MIN = OBJ_NEW;
				}
			}
		}
		li = li->prev_location_node;
	}
	if(minimum_par != DBL_MAX){
		lj = ridesharing_state.route.path;
		for(int j = 0; j < ridesharing_state.route.no_of_nodes; j++){
			if(precalculate_set.par[j] == minimum_par){
				dest_j = lj;
				break;
			}
			lj = lj->next_location_node;
		}
	}
	if(origin_i)
		insert(new_request->origin, origin_i);
	else
		return;
	if(origin_i == dest_j){
		insert(new_request->destination, new_request->origin);
	}
	else
		insert(new_request->destination, dest_j);
	insert_data_in_newroute_file();
	return;
}


//New obj function
double obj(double *mobj, location_node *li, Request new_request, double par_min, int noOfNodes){
	double cmp1, cmp2, cmp3;
	int ind = li->index;
	cmp1 = mobj[0];
	if(ind == (noOfNodes - 1)){
		cmp2 = det(li, new_request.origin);
	}
	else{
		cmp2 = det(li, new_request.origin) + mobj[ind + 1];
	}
	cmp3 = det(li, new_request.origin) + par_min;
	return max(cmp1, max(cmp2, cmp3));
}



//New function for calculation for obj for i=j cases
double obj_iEqualj(double *mobj, location_node *li, Request new_request, int i){
	double cmp1;
	double cmp2;
	cmp1 = mobj[0];
	if((i + 1) == ridesharing_state.route.no_of_nodes){
		cmp2 = arr(li, new_request) + distance_node(li->sequenced_location, (new_request.origin)->sequenced_location) + distance_node((new_request.origin)->sequenced_location, (new_request.destination)->sequenced_location) - new_request.release_time;
	}
	else{
		cmp2 = distance_node(li->sequenced_location, (new_request.origin)->sequenced_location) + distance_node((new_request.origin)->sequenced_location, (new_request.destination)->sequenced_location) + distance_node((new_request.destination)->sequenced_location, li->next_location_node->sequenced_location) - distance_node(li->sequenced_location, li->next_location_node->sequenced_location) + mobj[i + 1];
	}
	return max(cmp1, cmp2);
}




