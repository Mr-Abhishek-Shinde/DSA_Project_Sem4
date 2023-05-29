

#ifndef STRUCTURES

#define STRUCTURES 
#include <stdio.h>
#define CAPACITY    (4)
#define X_CORD      (0)
#define Y_CORD      (4)   

// coordinates of any location (origin or destination or worker's current location) 
typedef struct coordinate{
		double x, y;
}coordinate;

/** let request r = < or, dr, tr, er, cr >
 	where, 
 		or = origin of request
 		dr = destination of request
 		tr = release time of request
 		er = deadline time of request
 		cr = capacity of request  **/
typedef struct Request{
		struct location_node *origin, *destination;
		double release_time, deadline_time;
		int capacity;
}Request; 


void init_request(Request *request, double orx, double ory, double drx, double dry, double release_time, double deadline_time, int capacity);
//Set of requests
typedef struct Set_of_requests{
	Request *arr;
	int size;
}Set_of_requests; 

void request_init();
/** let worker be w = < ow, cw > 
	where,
 		ow = current location of worker
		cw = capacity of worker **/ 
typedef struct Worker{
		coordinate current_location;
	int capacity;
		int picked_up;
}Worker; 


// below structure is node for route
typedef struct location_node{
		coordinate sequenced_location;
		struct location_node *next_location_node;
		struct location_node *prev_location_node;
		struct Request *corresponding_request;
		int index;    // it is for simplicity for precalculation - basically it is index of node
}location_node; 

// route is defined as set of location of origin and destination 
typedef struct Route{
		location_node *path;
		int no_of_nodes;
}Route; 


typedef struct RideSharing_State{
    Route route;
    Set_of_requests set_of_requests;
    Worker worker;
}RideSharing_State;

typedef struct files{
	FILE *prevRoute;
	FILE *newRoute;
	FILE *flowTime;
}Files;

void init_Ridesharing_State(RideSharing_State *ridesharing_state);
void files_init();
void insert_data_in_newroute_file();
void insert_data_in_prevroute_file();
void insert_value_in_flowtime_file(double);
#endif






