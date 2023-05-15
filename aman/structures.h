#include <stdlib.h>

// coordinates of any location (origin or destination or worker's current location) 
typedef struct coordinate{
		int x, y;
}coordinate;

/** let request r = < or, dr, tr, er, cr >
 	where, 
 		or = origin of request
 		dr = destination of request
 		tr = release time of request
 		er = deadline time of request
 		cr = capacity of request  **/
typedef struct request{
		struct location_node *or, *dr;
		double release_time, deadline_time;
		int capacity;
}request; 


//Set of requests
typedef struct set_of_requests{
	request *arr;
	int size;
}set_of_requests; 

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
		struct request *corresponding_request;
		int index;    // it is for simplicity for precalculation - basically it is index of node
}location_node; 

// route is defined as set of location of origin and destination 
typedef struct route{
		location_node *path;
		int no_of_nodes;
}route; 

double dis(location_node *a, location_node *b);
double arr(location_node *k);
double ddl(location_node *k);
void slk_time(double *slk);
void slk_intermediate(double *slk, location_node *n, int k); 

// helping functions
double a_raise_b(double a, double b);
double distance(coordinate a, coordinate b);
double min(double num1, double num2);









