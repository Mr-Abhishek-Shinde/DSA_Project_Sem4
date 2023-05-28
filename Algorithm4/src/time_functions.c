#include <stdio.h>
#include <float.h>
#include "constraints.h"
#include "time_functions.h"
#include "tools.h"
#include "global.h"

// distance between given index
double dis_index(location_node *a, location_node *b){
		return (dis_from_origin[b->index] - dis_from_origin[a->index]);
}

// ddl(k) function - latest time to arrive at lk without violating the deadline constraints
double ddl(location_node *k){
		double total_time;
		Request *k_request = k->corresponding_request;

		//if((k_request->origin.x == k->sequenced_location.x) && (k_request->origin.y == k->sequenced_location.y)){
		if(k_request->origin == k){
			//	total_time = k_request->deadline_time - dis(k_request->origin, k_request->destination);
				total_time = k_request->deadline_time - dis_index(k, k_request->destination);
		}
		else if(k_request->destination == k){
				total_time = k_request->deadline_time;
		}
		return total_time;
}
				
// det(k, p) - the detour time of inserting location p after lk
double det(location_node *k, location_node *p){
		double detour;
        if(!k->next_location_node){
            return distance_node(k->sequenced_location, p->sequenced_location);
        }
		detour = distance_node(k->sequenced_location, p->sequenced_location) + distance_node(p->sequenced_location, k->next_location_node->sequenced_location) - distance_node(k->sequenced_location, k->next_location_node->sequenced_location);
		return detour;
}

// arr(k) (arrival time) - it will be time from origin to current node
double arr(location_node *k, Request newRequest){
		location_node *p = ridesharing_state.route.path;
		double arr_time;
		arr_time = dis_index(p, k);   // Route means from Worker to k
		arr_time += newRequest.release_time;
		return arr_time;
}

// insertion of a node after b 
void insert(location_node *a, location_node *b){
		location_node *temp = b->next_location_node;
		b->next_location_node = a;
		a->next_location_node = temp;
		return;
}

// flow time of rq. 
double flow_time(Request rq, Request newRequest){
        double arr_destination = arr(rq.destination, newRequest);
        return arr_destination - rq.release_time;
}
