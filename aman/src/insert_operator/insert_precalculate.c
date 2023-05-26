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

void insert_node(RideSharing_State *ridesharing_state, Request *request, location_node *l, int index){

    location_node *path = ridesharing_state->route.path;

    if(!path){
         ridesharing_state->route.path = l;
         ridesharing_state->route.path->next_location_node = NULL;
         ridesharing_state->route.path->corresponding_request  = request;
         ridesharing_state->route.no_of_nodes++;
         ridesharing_state->route.path->index = index;
         return;
    }

    while(path->next_location_node)
        path = path->next_location_node;

    path->next_location_node = l;
    path = path->next_location_node;
    path->next_location_node = NULL;
    path->corresponding_request = request;
    ridesharing_state->route.no_of_nodes++;
    path->index = index;

    return;
}


void update_route(Route *r, Worker *w, location_node *before_worker){
    location_node *traversal = r->path, *tmp = NULL;

    while(traversal != before_worker){
        tmp = traversal;
        traversal  = traversal->next_location_node;
        free(tmp);
        r->no_of_nodes--;
    }

    r->path = (location_node*)malloc(sizeof(location_node));
    r->path->sequenced_location = w->current_location;
    r->path->next_location_node = traversal->next_location_node;
    r->path->index = 0;
    r->path->corresponding_request = NULL;
    r->no_of_nodes++;

    free(traversal);
    r->no_of_nodes--;

    return;
}

void update_worker_route(Route *r, Worker *w, Request *new_request){

    int w_picked = 0;
    // here a and b are nodes between which our new locaton of worker will lie
	location_node *a, *b = NULL;
	coordinate unit_vector_ab, scaled_vector_aw;
	double scale_aw, distance;

        a = r->path;
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

        w->picked_up = w_picked;

        if(!a->next_location_node){
            w->picked_up -= a->corresponding_request->capacity;
            w->current_location = a->sequenced_location;
        }
        else{
	    	b = a->next_location_node;
		    find_unit_vector(&unit_vector_ab, a->sequenced_location, b->sequenced_location);
		    scale_aw = new_request->release_time - distance;
		    scale_vector(&scaled_vector_aw, unit_vector_ab, scale_aw);
		    add_vector(&w->current_location, a->sequenced_location, scaled_vector_aw);
        }
		// update route
        update_route(r, w, a);
		return;
}	

// precalculation
void pre_calculation(Route r, double **slk_values, double **pck_values, double ***mobj_values, Request new_request, Worker worker){
		*slk_values = (double*)malloc(sizeof(double)*r.no_of_nodes);
		*pck_values = (double*)malloc(sizeof(double)*r.no_of_nodes);
		*mobj_values = (double**)malloc(sizeof(double*)*r.no_of_nodes);
		for(int i = 0; i < r.no_of_nodes; i++){
			(*mobj_values)[i] = (double*)malloc(sizeof(double)*r.no_of_nodes);	
		}
		slk_time(r, *slk_values, new_request);
		pre_calculate_pck(r, *pck_values, worker);
		/* mobj(r, *mobj_values, new_request); */
        return;
}

// insertion operator
void insertion_operator(Route r, Worker w, Request *new_request){
		double OBJ_MIN = INT_MAX, OBJ_NEW;
        double *slk_values = NULL, *pck_values = NULL, **mobj = NULL;
		location_node *li, *lj;    // this pointer will itterate through loops
		location_node *origin_i = NULL, *dest_j = NULL;    // this pointer is address of that node after which or and dr will get inserted
		li = r.path;
		lj = li;

		// precalculation
		pre_calculation(r, &slk_values, &pck_values, &mobj, *new_request, w);
        /* printf("After precalculation\n"); */
        display_route(r); 
		for(int i = 0; i < r.no_of_nodes; i++, li = li->next_location_node){
                lj = li;
				for(int j = i; j < r.no_of_nodes; j++, lj = lj->next_location_node){
                        display_route(r);
                        /* printf("i: %d\tj: %d\n", i, j); */
						if(check_capacity_constraint(w, *new_request, pck_values, i, j) ){
                            if( check_deadline_constraint(r, slk_values, i, j, (*new_request).origin, (*new_request).destination, li, lj, *new_request)){
					        	/* if(check_deadline_constraint(r, slk_values, i, j, (*new_request).origin, (*new_request).destination, li, lj, *new_request)){ */
					        			OBJ_NEW = obj(r, i , j, li, lj, mobj, new_request); 

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

