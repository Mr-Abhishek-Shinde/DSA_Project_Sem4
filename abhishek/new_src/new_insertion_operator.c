#include <stdlib.h>
#include <limits.h>

// insertion operator
void insertion_operator(Route r, Worker w, Request *new_request){
	double OBJ_MIN = INT_MAX, OBJ_NEW;
	
	location_node *li = NULL, *lj = NULL; // these are the nodes which will be used for iteration
        location_node *origin_i = NULL, *dest_j = NULL; // these are the nodes after which or and dr will get inserted

	int n = r.path.no_of_nodes;

	// Precalculation - pck, slk, thr, par, mobj
	Precalculation_set precalculate_set;
	precalculation(precalculate_set, *new_request);

	// Displaying the route before insertion:
	display_route(r);

	// Segment tree construction:
	ST st;

	init_ST(&st);
	construct_ST(&st, precalculation_set.par);

	// Handling the case of i == j:
	for(int i = 0; i < n; i++, li = li->next_location_node){
                if(check_capacity_constraint_iEqualj(w, *new_request, precalculation_set.pck, i) && check_deadline_constraint_iEqualj(li, *new_request, precalculation_set.slk, i)){
                        OBJ_NEW = obj_iEqualj(r, mobj, li, *new_request, i);
                        if(OBJ_NEW < OBJ_MIN){
                                OBJ_MIN = OBJ_NEW;
                                origin_i = li;
                                dest_i = li;
                        }
                }
        }

        li = NULL;
	int par_min;

	// Iterating the i:
	for(int i = n - 1; i >= 0; i--){
		// Updating leaf threshold with par in ST:
		update_par(st, precalculation_set.par, i + 1);

		// Checking for the capacity constraint:
		if(check_capacity_constraint(w, new_request, precalculation_set.pck[i + 1], i + 1) == 0){
			invalidate(st, precalculate_set.par, precalculate_set.brk);
		}

		// Checking for the deadline constraint:
		if(intial_deadline_condition(new_request, li, i, precalculate_set.slk) == 1){
			si = binary_search_thr(precalculate_set.thr, key, 0, n);
			par_min = min_par(st, si, n);
		}

		// Calculating the objective:
		OBJ_NEW = obj(r, i , j, li, lj, mobj, new_request);

		// updating (i*, j*) with (i, j) according to OBJ
		if(OBJ_MIN > OBJ_NEW){
			origin_i = li;
			dest_j = lj;
			OBJ_MIN = OBJ_NEW;
		}
		else{
			break;
		}
	}

	display_route(r);

	return;
}
	
