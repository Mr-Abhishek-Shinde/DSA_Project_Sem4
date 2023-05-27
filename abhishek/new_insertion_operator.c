#include <stdlib.h>
#include <limits.h>

// insertion operator
void insertion_operator(Route r, Worker w, Request *new_request){
	double OBJ_MIN = INT_MAX, OBJ_NEW;
	
	location_node *li, *lj; // these are the nodes which will be used for iteration
        location_node *origin_i = NULL, *dest_j = NULL; // these are the nodes after which or and dr will get inserted

	int n = r.path.no_of_nodes;

	// Precalculation - pck, slk, thr, par, mobj
	Precalculation_set precalculate_set;
	precalculation(precalculate_set, *new_request);

	// Displaying the route before insertion:
	display_route(r);

	// Segment tree construction:
	/* insert code here */

	// Handling the case of i == j:
	for(int i = 0; i < n; i++){
		/* insert code here */
	}

	// Iterating the i:
	for(int i = n - 1; i >= 0; i--){
		// Updating leaf threshold with par in ST:
		/* insert code here */

		// Checking for the capacity constraint:
		/* insert code here */

		// Checking for the deadline constraint:
		/* insert code here */
		/* query the min. value of par(j) from segment in ST */

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
	
