#include "constraints.h"

//New function for capacity for handling i=j cases
int check_capacity_constraint_iEqualj(Worker w, Request new_request, double *pck_values, int i){
	return pck_values[i] <= (w.capacity - new_request.capacity);
}

//New function for deadline for handling i=j cases
int check_deadline_constraint_iEqualj(location_node *li, Request new_request, double *slk_values, int i){
	if(li->next_location)
		return 1;
	else
		return (distance_node(li, new_request.origin) + distance_node(new_request.origin, new_request.destination) + distance_node(new_request.destination, li->next_location_node) - distance_node(li, li->next_location_node)) <= slk[i];
}
