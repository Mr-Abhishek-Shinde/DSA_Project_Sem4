#include "structures.h"

// let route be SR = < l0, l1, l2, l3 ... , ln >  
// l0 = node of worker current location
// we will initialize the route by node of worker i.e l0
void init_route(route *r, coordinates worker){
		(*r) = (location_node*)malloc(sizeof(location_node));
		(*r)->sequenced_location.x = worker.x;
		(*r)->sequenced_location.y = worker.y;
		(*r)->next_location_node = NULL;
		return;
}




