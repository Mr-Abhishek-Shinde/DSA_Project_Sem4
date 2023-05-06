#include <math.h>
#include "route.h"
#include "request.h"

route r;

// a raise to b - a^b
double a_raise_b(double a, double b){
		double result = a;
		for(int i = 0; i < (b - 1); i++){
				result = result * a;
		}
		return result;
}

// find distance between a and b coordinate
double distance(coordinate a, coordinate b){
		double distance, delta_x, delta_y;
		delta_x = a.x - b.y;
		delta_y = a.y - b.y;
		distance = sqrt(a_raise_b(delta_x, 2) + a_raise_b(delta_y, 2));
		return distance;
}

// this functions will find the distance between a and b node in route
double dis(location_node *a, location_node *b){
		double dis = 0;
		location_node *temp = a;
		while(temp != b->next_location_node){
				dis += distance(a->sequenced_location, a->next_location_node);
				temp = temp->next_location_node;
		}
		return dis;
}

// arr(k) (arrival time) - it will be time from origin to current node
double arr(location_node *k, route r){
		int arr_time;
		arr_time = dis(r.path, k);   // route means from worker to k
		arr_time += k->corresponding_request->release_time;
		return arr_time;
}

// ddl(k) function - latest time to arrive at lk without violating the deadline constraints
double ddl(location_node *k){
		double total_time;
		k_request = k->corresponding_request;

		if(k_request->origin == k->sequenced_location){
				total_time = k_request->deadline_time - dis(k_request->origin, k_request->destination);
		}
		else if(k_request->destination == k->sequenced_location){
				total_time = k_request->deadline_time;
		}
		return total_time;
}
				
// find min value between num1 and num2
double min(double num1, double num2){
		return (num1 > num2 ? num2 : num1);
}

// slk_intermediate
void slk_intermediate(double *slk, location_node *n, int k){
		if(k == r.no_of_nodes)
				return;
		slk_intermediate(slk, n->next_location_node, k+1);
		slk[k] = min(slk[k+1], ddl(n->next_location_node) - arr(n->next_location_node));
		return;
}

// main slake time function
// slk(k)(slake time) - maximum tolerable time for detour after lk
void slk_time(double *slk){
		slk[r.no_of_nodes] = 0;
		int k = 0;
		slk_intermediate(slk, r.path, k);
		return;
}

// det(k, p) - the detour time of inserting location p after lk
double det(location_node *k, location_node *p){
		double detour;
		detour = dis(k, p) + dis(p, k->location_node) - dis(k, k->location_node);
		return detour;
}

// check deadline constraints
int check_deadline_constraint(double *slk, int i, int j, location_node *or, location_node *dr, location_node *li, location_node *lj){
		// first condition
		if(det(i, or) > slk[i])
				return 0;

		if(i != j){
				// second condition
				if(det(i, or) + det(j, dr) > slk[j])
						return 0;
				else{
						// third condition
						if(arr(j) + det(li, or) + dis(lj, dr) > dr->corresponding_request->deadline_time)
								return 0;
						else
								return 1;
				}
		}
		else{
				// second condition
				if(dis(li, or) + dis(or, dr) + dis(dr, li>location_node) - dis(li, li->next_location_node) > slk[i])
						return 0;
				else{
						// third condition cheking
						if(arr(li) + dis(li, or) + dis(or, dr) > slk(i) > dr->corresponding_request->deadline_time)
								return 0;
						else
								return 1;
				}
		}
}

// insertion of a node after b 
void insert(location_node *a, location_node *b){
		location_node *temp = b->next_location_node;
		b->next_location_node = a;
		a->next_location_node = temp;
		return;
}

// insertion operator
void insertion_operator(double *pck, double *slk, location_node *or, location_node *dr){
		double OBJ_MIN = INT_MAX, OBJ;
		location_node *li, *lj;    // this pointer will itterate through loops
		location_node *origin_i, *dest_j;    // this pointer is address of that node after which or and dr will get inserted
		li = r.path;
		lj = li->next_location_node;
		for(int i = 0; i < r.no_of_nodes; i++){
				for(int j = i; j < r.no_of_nodes; j++){
						if(check_capacity_constraint() && check_deadline_constraint(slk, i, j, or, dr, li, lj)){
								// compute mf1, mf2, mf3, mf4
								
								// OBJ = max(mf1, mf2, mf3, mf4)

								// update (i*, j*) with (i, j) according to OBJ
								if(OBJ_MIN > OBJ){
										origin_i = li;
										origin_j = lj;
										OBJ_MIN = OBJ;
								}
						}
						lj = lj->next_location_node;
						
				}
				li = li->next_location_node;
		}
		// insert node after li and lj
		insert(or, origin_i);
		insert(dr, destination_j);
		or->index = r.no_of_nodes + 1;
		dr->index = r.no_of_nodes + 2;
		r.no_of_nodes += 2;
		return;
}

// I have to write the function for precalculation of arr(k), ddl(k), dis(k)
// - but affter every insertion we have to update whole array of arr(k) and also ddl(k), dis(k)
