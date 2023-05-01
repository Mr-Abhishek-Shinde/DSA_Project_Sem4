#include "structures.h"

#define REQUEST

#ifndef ROUTE
#include "requests.h"
#endif

/** let worker be w = < ow, cw > 
	where,
 		ow = current location of worker
		cw = capacity of worker **/ 
typedef struct worker{
		coordinate current_location;
		int capacity;
		int picked_up;
}worker;


// below structure is node for route
typedef struct location_node{
		coordinate sequenced_location;
		struct location_node *next_location_node;
		request *corresponding_request;
		int index;    // it is for simplicity for precalculation - basically it is index of node
}location_node;

// route is defined as set of location of origin and destination 
typedef struct route{
		location_node *path;
		int no_of_nodes;
}route;


