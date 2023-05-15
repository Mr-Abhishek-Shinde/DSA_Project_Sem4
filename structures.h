#include <stdlib.h>

// coordinates of any location (origin or destination or worker's current location) 
typedef struct coordinate{
		int x, y;
}coordinate;


/** let worker be w = < ow, cw > 
	where,
 		ow = current location of worker
		cw = capacity of worker **/ 

typedef struct worker{
		coordinate current_location;
		int capacity;
		int picked_up;
}worker;


/** let request r = < or, dr, tr, er, cr >
 	where, 
 		or = origin of request
 		dr = destination of request
 		tr = release time of request
 		er = deadline time of request
 		cr = capacity of request  **/

typedef struct request{
		coordinate origin, destination;
		double release_time, deadline_time;
		int capacity;
}request;

//Set of requests
typedef struct set_of_requests{
	request **arr;
}set_of_requests;

// route is defined as set of location of origin and destination 
// below structure is node for route
typedef struct location_node{
		coordinate sequenced_location;
		struct location_node *next_location_node;
		request *corresponding_request;
}location_node;

typedef location_node *route;

void init_route(route *r, coordinate worker);
void add_location_in_route(route *r, request rq, int flag);
double arrival_time(route r, coordinate l);
double flow_time(route r, request rq);
double time_between_node(coordinate n1, coordinate n2);
int is_route_feasible(route r, worker w);
void insertion_operator(int index, coordinates c, route *r);
//double find_objective();
int check_deadline_constraint(route r, location_node l, worker w);
int check_capacity_constraint(route r, location_node l, worker w);
		













