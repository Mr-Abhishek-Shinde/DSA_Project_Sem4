#include <stdio.h>
#include <float.h>
#include "constraints.h"
#include "mathematics.h"

extern Route r;

#define NNODE (sizeof(r.path) / sizeof(int))

int dis_from_origin[NNODE];

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
				
// slk_intermediate
void slk_intermediate(Route r, double *slk, location_node *n, int k, Request newRequest){
		if(k == (r.no_of_nodes - 1)){
                n->index = k;
				return;
        }

		dis_from_origin[k+1] = distance_node(n->sequenced_location, n->next_location_node->sequenced_location) + dis_from_origin[k]; // it will find the distance from origin to kth node
        n->index = k;

		slk_intermediate(r, slk, n->next_location_node, k+1, newRequest);
		slk[k] = min(slk[k+1], ddl(n->next_location_node) - arr(r, n->next_location_node, newRequest));
		return;
}

// main slake time function
// slk(k)(slake time) - maximum tolerable time for detour after lk
void slk_time(Route r, double *slk, Request newRequest){
		dis_from_origin[0] = 0;
		slk[r.no_of_nodes - 1] = DBL_MAX;
		int k = 0;
		slk_intermediate(r, slk, r.path, k, newRequest);
		return;
}

// det(k, p) - the detour time of inserting location p after lk
double det(location_node *k, location_node *p){
		double detour;
        if(!k->next_location_node){
            return distance_node(k->sequenced_location, p->sequenced_location);
        }
		detour = distance_node(k->sequenced_location, p->sequenced_location) + distance_node(p->sequenced_location, k->next_location_node->sequenced_location);// - distance_node(k->sequenced_location, k->next_location_node->sequenced_location);
		return detour;
}

// arr(k) (arrival time) - it will be time from origin to current node
double arr(Route r, location_node *k, Request newRequest){
		int arr_time;
		arr_time = dis_index(r.path, k);   // Route means from Worker to k
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

// check deadline constraints
int check_deadline_constraint(Route r, double *slk, int i, int j, location_node *origin, location_node *destination, location_node *li, location_node *lj, Request newRequest){
        /* if(!li->next_location_node) */
            /* return 1; */

		// first condition
		if(det(li, origin) > slk[i]){
				return 0;
        }


		if(i != j){
				// second condition
				if(det(li, origin) + det(lj, destination) > slk[j])
						return 0;
				else{
						// third condition
						if(arr(r, lj, newRequest) + det(li, origin) + distance_node(lj->sequenced_location, destination->sequenced_location) > destination->corresponding_request->deadline_time)
								return 0;
						else
								return 1;
				}
		}
		else{
				// second conditio
				if(li->next_location_node && distance_node(li->sequenced_location, origin->sequenced_location) + distance_node(origin->sequenced_location, destination->sequenced_location) + distance_node(destination->sequenced_location, li->next_location_node->sequenced_location) - distance_node(li->sequenced_location, li->next_location_node->sequenced_location) > slk[i]){
						return 0;
                }
				else{
						// third condition cheking
						//if(arr(li) + dis(li, origin) + dis(origin, destination) > slk[i] > destination->corresponding_request->deadline_time)
						if(arr(r, li, newRequest) + distance_node(li->sequenced_location, origin->sequenced_location) + distance_node(origin->sequenced_location, destination->sequenced_location) > destination->corresponding_request->deadline_time){
								return 0;
                        }
						else{
								return 1;
                        }
				}
		}
} 
