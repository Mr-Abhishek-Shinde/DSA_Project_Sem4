#define ROUTE

#ifndef REQUEST
#include "route.h"
#endif

/** let request r = < or, dr, tr, er, cr >
 	where, 
 		or = origin of request
 		dr = destination of request
 		tr = release time of request
 		er = deadline time of request
 		cr = capacity of request  **/
typedef struct request{
		location_node *origin, *destination;
		double release_time, deadline_time;
		int capacity;
}request;


//Set of requests
typedef struct set_of_requests{
	request *arr;
	int size;
}set_of_requests;

double dis(location_node *a, location_node *b);
double arr(location_node *k);
double ddl(location_node *k);
void slk_time(double *slk);
void slk_intermediate(double *slk, location_node *n, int k);
