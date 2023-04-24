#include "structures.h"
#include <math.h>

// let route be SR = < l0, l1, l2, l3 ... , ln >  
// l0 = node of worker current location
// we will initialize the route by node of worker i.e l0
void init_route(route *r, coordinates worker){
		(*r) = (location_node*)malloc(sizeof(location_node));
		(*r)->sequenced_location.x = worker.x;
		(*r)->sequenced_location.y = worker.y;
		(*r)->next_location_node = NULL;
		(*r)->corresponding_request = NULL;
		return;
}

void add_location_in_route(route *r, request rq, int flag){
	location_node* l = malloc(sizeof(location_node));
	if(!flag){
		(l->sequenced_location).x = rq.origin.x;
		(l->sequenced_location).y = rq.origin.y;	
	}
	else{
		(l->sequenced_location).x = rq.destination.x;
		(l->sequenced_location).y = rq.destination.y;
	}
	l->next_location_node = NULL;
	l->corresponding_request = &rq;
	location_node *n = *r;
	while(n->next_location_node){
		n = n->next_location_node;
	}
	n->next_location_node = l;
	return;
}

double arrival_time(route r, coordinate l){
	double time = 0;
	location_node *prev = r;
	location_node *curr = r->next_location_node;
	while(((prev->sequenced_location).x != l.x) || ((prev->sequenced_location).y != l.y)){
		time += time_between_nodes(*prev, *curr);
		prev = curr;
		curr = curr->next_location_node;
	}
	return time;
}

double time_between_node(coordinate n1, coordinate n2){
	time_squared = (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
	return sqrt(time_squared);
}

double flow_time(route r, request rq){
	double arr_destination = arrival_time(r, rq.destination);
	return arr_destination - rq.release_time;
}

int is_route_feasible(route r, worker w){
}
