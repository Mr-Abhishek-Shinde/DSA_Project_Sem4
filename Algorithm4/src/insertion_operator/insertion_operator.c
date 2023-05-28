#include <limits.h>
#include "ridesharing.h"
#include "mobj.h"
#include "mathematics.h"
#include "constraints.h"
#include <stdlib.h>
#include <float.h>

#define CAPACITY (4)
#define NNODES (6)

void display_route(Route r){
	int i = 0;
	location_node *p = r.path;
	coordinate sq;
	//request cr;
	//for(int i = 0; i < r.no_of_nodes; i++){
	while(p){
        /* printf("%p\n", p); */
		sq = p->sequenced_location;
		//cr = p.corresponding_request;
		/* printf("Coordinates of %dth location node are: (%f, %f)\n", i++, 1.0, 1.0); //sq.x, sq.y); */
		p = p->next_location_node;
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
         (ridesharing_state.route).path->corresponding_request  = request;
         (ridesharing_state.route).no_of_nodes++;
         (ridesharing_state.route).path->index = index;
         return;
    }

    while(path->next_location_node)
        path = path->next_location_node;

    path->next_location_node = l;
    path = path->next_location_node;
    path->next_location_node = NULL;
    path->corresponding_request = request;
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
		    add_vector(a->sequenced_location, scaled_vector_aw);
        }
		// update route
        update_route(a);
		return;
}	





// insertion operator
void insertion_operator(Request *new_request){
		double OBJ_MIN = INT_MAX, OBJ_NEW;
        double *slk_values = NULL, *pck_values = NULL, **mobj = NULLi, *thr = NULL, *par = NULL;
		location_node *li, *lj;    // this pointer will itterate through loops
		location_node *origin_i = NULL, *dest_j = NULL;    // this pointer is address of that node after which or and dr will get inserted
		li = r.path;
		lj = li;

		// precalculation
		pre_calculation(r, &slk_values, &pck_values, &mobj, &thr, &par,*new_request, w);
        /* printf("After precalculation\n"); */
        display_route(r); 
	//Handling i = j cases.
	for(int i = 0; i < r.no_of_nodes; i++, li = li->next_location_node){
		if(check_capacity_constraint_iEqualj(w, *new_request, pck_values, i) && check_deadline_constraint_iEqualj(li, *new_request, slk_values, i)){
			OBJ_NEW = obj_iEqualj(r, mobj, li, *new_request, i);
			if(OBJ_NEW < OBJ_MIN){
				OBJ_MIN = OBJ_NEW;
				origin_i = li;
				dest_i = lj;
			}
		}
	}
		for(int i = 0; i < r.no_of_nodes; i++, li = li->next_location_node){
                lj = li;
				for(int j = i; j < r.no_of_nodes; j++, lj = lj->next_location_node){
                        display_route(r);
                        /* printf("i: %d\tj: %d\n", i, j); */
						if(check_capacity_constraint(w, *new_request, pck_values, i, j) ){
                            if( check_deadline_constraint(r, slk_values, i, j, (*new_request).origin, (*new_request).destination, li, lj, *new_request)){
					        	/* if(check_deadline_constraint(r, slk_values, i, j, (*new_request).origin, (*new_request).destination, li, lj, *new_request)){ */
					        			//OBJ_NEW = obj(r, i , j, li, lj, mobj, new_request); 
									OBJ_NEW = obj(*mobj, li, *new_request, min_par, r.no_of_nodes);

					        			// update (i*, j*) with (i, j) according to OBJ
                                        /* printf("%f\t%f\n", OBJ_MIN, OBJ_NEW); */
					        			if(OBJ_MIN > OBJ_NEW){
					        					origin_i = li;
					        					dest_j = lj;
					        					OBJ_MIN = OBJ_NEW;
					        			}
					        	}
                            }
                        else{
                            break;
                        }
				}
		} 
        /* printf("Outside of for loop\n"); */
		// insert node after li and lj
/*        if(origin_i){
		    insert(new_request->origin, origin_i); 
        }
        else
            return;

        if(origin_i == dest_j)
            insert(new_request->destination, new_request->origin);
        else
		    insert((*new_request).destination, dest_j);

		new_request->origin->index = r.no_of_nodes + 1;
		new_request->destination->index = r.no_of_nodes + 2;
		r.no_of_nodes += 2;  */
        display_route(r); 
		return;
} 

//New obj function
double obj(double *mobj, location_node *li, Request new_request, double min_par, int noOfNodes){
	double cmp1, cmp2, cmp3;
	int ind = li->index;
	cmp1 = mobj[0];
	if(ind == (noOfNodes - 1)){
		cmp2 = det(li, new_request.destination);
	}
	else{
		cmp2 = det(li, new_request.destination) + mobj[ind + 1];
	}
	cmp3 = det(li, new_request.destination) + min_par;
	return max(cmp1, min(cmp2, cmp3));
}



//New function for calculation for obj for i=j cases
double obj_iEqualj(Route r, double *mobj, location_node *li, Request new_request, int i){
	double cmp1;
	double cmp2;
	cmp1 = mobj[0];
	if((i + 1) == r.no_of_nodes){
		cmp2 = det(li, new_request.origin);
	}
	else{
		cmp2 = det(li, new_request.origin) + mobj[i + 1];
	}
	return max(cmp1, cmp2);
}




