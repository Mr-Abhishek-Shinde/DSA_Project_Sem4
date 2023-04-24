#include <stdlib.h>

// coordinates of any location (origin or destination or worker's current location) 
typedef struct coordinates{
		int x, y;
}coordinates;


/** let worker be w = < ow, cw > 
	where,
 		ow = current location of worker
		cw = capacity of worker **/ 

typedef struct worker{
		coordinates start;
		int capacity;
}worker;


/** let request r = < or, dr, tr, er, cr >
 	where, 
 		or = origin of request
 		dr = destination of request
 		tr = release time of request
 		er = deadline time of request
 		cr = capacity of request  **/

typedef struct request{
		coordinates origin, destination;
		double release_time, deadline_time;
		int capacity;
}request;


// route is defined as set of location of origin and destination 
// below structure is node for route
typedef struct location_node{
		coordinates sequenced_location;
		struct location_node *next_location_node;
}location_node;

typedef location_node *route;

void init_route(route *r, coordinates worker);
double delivery_time(route r);
double flow_time();
void insertion_operator(int index, coordinates c, route *r);
double find_objective();
int check_deadline_constraint();
int check_capacity_constraint();
		
