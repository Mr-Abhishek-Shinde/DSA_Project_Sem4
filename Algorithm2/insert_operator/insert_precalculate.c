#include "structures.h"
#include "mobj.h"
#include "mathematics.h"
#include "constraints.h"
#include <stdlib.h>
#include <float.h>

void update_route(route r, worker w, location_node *before_worker){
    location_node *traversal = r.path, *tmp = NULL;

    while(traversal == before_worker){
        tmp = traversal;
        free(tmp);
        traversal  = traversal->next_location_node;
    }

    w.current_location->next_location_node = traversal->next_location_node;

    free(traversal);
    return;
}

void update_worker_route(route r, worker w, request *new_request){

        // here a and b are nodes between which our new locaton of worker will lie
		location_node *a, *b = NULL;
		coordinate unit_vector_ab, scaled_vector_aw;
		double scale_aw, distance;

        a = r.path;
        distance = 0;
        
		while(a->next_location_node){
				distance += distance(a->sequenced_location, a->next_location_node->sequenced_location);
				if(distance >= new_request->release_time){
						break;
				}
				a = a->next_location_node;
		}

        if(!a->next_location_node){
            w.current_location = a;
            return;
        }

		b = a->next_location_node;

		find_unit_vector(&unit_vector_ab, a->sequenced_location, b->sequenced_location);
		scale_aw = new_request->release_time - a->corresponding_request->release_time;
		scale_vector(&scaled_vector_aw, unit_vector_ab, scaled_vector_aw);
		add_vector(&w.current_location, a->sequenced_location, scaled_vector_ab);

		// update route
        update_route(r, w, a);
		return;
}	

// precalculation
void pre_calculation(route r, double *slk_values, double *pck_values, double **mobj_values){
		slk_values = (double*)malloc(sizeof(double)*r.no_of_nodes);
		pck_values = (double*)malloc(sizeof(double)*r.no_of_nodes);
		mobj_values = (double**)malloc(sizeof(double*)*r.no_of_nodes);
		for(int i = 0; i < r.no_of_nodes; i++){
			mobj_values[i] = (double*)malloc(sizeof(double*)*r.no_of_nodes);	
		}
		slk_time(r, slk_values);
		pre_calculate_pck(r, pck_values);
		mobj(r, mobj_values);
        return;
}

// insertion operator
void insertion_operator(route r, worker w, request *new_request){
		double OBJ_MIN = DBL_MAX, OBJ_NEW;
        double *slk_values = NULL, *pck_values = NULL, **mobj = NULL;
		location_node *li, *lj;    // this pointer will itterate through loops
		location_node *origin_i = NULL, *dest_j = NULL;    // this pointer is address of that node after which or and dr will get inserted
		li = r.path;
		lj = li;

		// precalculation
		pre_calculation(r, slk_values, pck_values, mobj);
		for(int i = 0; i < r.no_of_nodes; i++, li = li->next_location_node){
				for(int j = i; j < r.no_of_nodes; j++, lj = lj->next_location_node){
						if(check_capacity_constraint(w, *new_request, pck_values, i, j) && check_deadline_constraint(r, slk_values, i, j, (*new_request).origin, (*new_request).destination, li, lj)){

								// OBJ_NEW = max(mf1, mf2, mf3, mf4)
								OBJ_NEW = obj(r, i , j, li, lj, mobj, new_request); 

								// update (i*, j*) with (i, j) according to OBJ
								if(OBJ_MIN > OBJ_NEW){
										origin_i = li;
										dest_j = lj;
										OBJ_MIN = OBJ_NEW;
								}
						}
				}
		}
		// insert node after li and lj
		insert((*new_request).origin, origin_i);
		insert((*new_request).destination, dest_j);
		(*new_request).origin->index = r.no_of_nodes + 1;
		(*new_request).destination->index = r.no_of_nodes + 2;
		r.no_of_nodes += 2;
		return;
} 

