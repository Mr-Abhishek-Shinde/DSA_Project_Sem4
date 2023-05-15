#include <math.h>
#include <stdlib.h>
#include <float.h>
#include "structures.h"

route r;
double *slk_values;
double *pck_values;
double **mobj_values;

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
				dis += distance(a->sequenced_location, a->next_location_node->sequenced_location);
				temp = temp->next_location_node;
		}
		return dis;
}

double dis_from_origin[20];

// distance between given index
double dis_index(location_node *a, location_node *b){
		return (dis_from_origin[a->index] - dis_from_origin[b->index]);
}

// arr(k) (arrival time) - it will be time from origin to current node
double arr(location_node *k){
		int arr_time;
		arr_time = dis_index(r.path, k);   // route means from worker to k
		arr_time += k->corresponding_request->release_time;
		return arr_time;
}

// ddl(k) function - latest time to arrive at lk without violating the deadline constraints
double ddl(location_node *k){
		double total_time;
		request *k_request = k->corresponding_request;

		//if((k_request->or.x == k->sequenced_location.x) && (k_request->or.y == k->sequenced_location.y)){
		if(k_request->or == k){
			//	total_time = k_request->deadline_time - dis(k_request->or, k_request->dr);
				total_time = k_request->deadline_time - dis_index(k, k_request->dr);
		}
		else if(k_request->dr == k){
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
		dis_from_origin[k+1] = distance(n->sequenced_location, n->next_location_node->sequenced_location) + dis_from_origin[k]; // it will find the distance from origin to kth node
		slk_intermediate(slk, n->next_location_node, k+1);
		slk[k] = min(slk[k+1], ddl(n->next_location_node) - arr(n->next_location_node));
		return;
}

// main slake time function
// slk(k)(slake time) - maximum tolerable time for detour after lk
void slk_time(route r, double *slk){
		dis_from_origin[0] = 0;
		slk[r.no_of_nodes] = 0;
		int k = 0;
		slk_intermediate(slk, r.path, k);
		return;
}

// det(k, p) - the detour time of inserting location p after lk
double det(location_node *k, location_node *p){
		double detour;
		detour = dis(k, p) + dis(p, k->next_location_node) - dis(k, k->next_location_node);
		return detour;
}

// check deadline constraints
int check_deadline_constraint(double *slk, int i, int j, location_node *or, location_node *dr, location_node *li, location_node *lj){
		// first condition
		if(det(li, or) > slk[i])
				return 0;

		if(i != j){
				// second condition
				if(det(li, or) + det(lj, dr) > slk[j])
						return 0;
				else{
						// third condition
						if(arr(lj) + det(li, or) + dis(lj, dr) > dr->corresponding_request->deadline_time)
								return 0;
						else
								return 1;
				}
		}
		else{
				// second condition
				if(dis(li, or) + dis(or, dr) + dis(dr, li->next_location_node) - dis(li, li->next_location_node) > slk[i])
						return 0;
				else{
						// third condition cheking
						//if(arr(li) + dis(li, or) + dis(or, dr) > slk[i] > dr->corresponding_request->deadline_time)
						if(arr(li) + dis(li, or) + dis(or, dr) > dr->corresponding_request->deadline_time)
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


// precalculation functions
// mobj()

// pck()


void scale_vector(coordinate unit_vector, double scale, coordinate *result){
		(*result).x = unit_vector.x * scale;
		(*result).y = unit_vector.y * scale;
		return;
}

void add_vector(coordinate a, coordinate b, coordinate *result){
		(*result).x = a.x + b.x;
		(*result).y = a.y + b.y;
		return;
}

void update_index_and_dis(route r){
		location_node *temp = r.path;
		int i = 1;
		dis_from_origin[i] = 0;
		while(temp && temp->next_location_node){
				temp->index = i - 1;
				dis_from_origin[i] = distance(temp->sequenced_location, temp->next_location_node->sequenced_location) + dis_from_origin[i-1];
				i++;
				temp = temp->next_location_node;
		}
		temp->next_location_node->index = i - 1;
		return;
}

void find_unit_vector(coordinate a, coordinate b, coordinate *result){
		double magnitude = distance(a, b); 
		result->x = (b.x - a.x) / magnitude;
		result->y = (b.x - a.x) / magnitude;
		return;
}

void update_worker_route(route r, worker w, request *new_request){
		location_node *a= r.path, *b = NULL;
		coordinate unit_vector_ab, scaled_vector_ab;
		double d, dis = 0;
		while(1){
				dis = distance(a->sequenced_location, a->next_location_node->sequenced_location) + dis;
				if(dis >= new_request->release_time){
						break;
				}
				a = a->next_location_node;
		}
		b = a->next_location_node;
		find_unit_vector(a->sequenced_location, b->sequenced_location, &unit_vector_ab);
		d = new_request->release_time - a->corresponding_request->release_time;
		scale_vector(unit_vector_ab, d, &scaled_vector_ab);
		add_vector(a->sequenced_location, scaled_vector_ab, &w.current_location);

		location_node *start_node = (r.path);
		start_node->next_location_node = a;
		
		// update route
		update_index_and_dis(r);
		return;
}	

// precalculation
void pre_calculation(route r){
		slk_values = (double*)malloc(sizeof(double)*r.no_of_nodes);
		pck_values = (double*)malloc(sizeof(double)*r.no_of_nodes);
		mobj_values = (double**)malloc(sizeof(double*)*r.no_of_nodes);
		for(int i = 0; i < r.no_of_nodes; i++){
			mobj_values[i] = (double*)malloc(sizeof(double*)*r.no_of_nodes);	
		}
		slk_time(r, slk_values);
		pck(r, pck_values);
		mobj(mobj_values);
}

// insertion operator
void insertion_operator(route r, worker w, request new_request){
		double OBJ_MIN = DBL_MAX, OBJ_NEW;
		location_node *li, *lj;    // this pointer will itterate through loops
		location_node *origin_i = NULL, *dest_j = NULL;    // this pointer is address of that node after which or and dr will get inserted
		li = r.path;
		lj = li;

		// precalculation
		pre_calculation(r);
		for(int i = 0; i < r.no_of_nodes; i++, li = li->next_location_node){
				for(int j = i; j < r.no_of_nodes; j++, lj = lj->next_location_node){
						if(check_capacity_constraint(r, w, new_request, i, j) && check_deadline_constraint(slk_values, i, j, new_request.or, new_request.dr, li, lj)){

								// OBJ_NEW = max(mf1, mf2, mf3, mf4)
								OBJ_NEW = Compute_OBJ_NEW(r, i , j li, lj, mobj_values, new_request); 

								// update (i*, j*) with (i, j) according to OBJ
								if(OBJ_MIN > OBJ_NEW){
										origin_i = li;
										dest_j = lj;
										OBJ_MIN = OBJ_NEW;
								}
						}
				}
		}
		// insert node after li and lj
		insert(new_request.or, origin_i);
		insert(new_request.dr, dest_j);
		new_request.or->index = r.no_of_nodes + 1;
		new_request.dr->index = r.no_of_nodes + 2;
		r.no_of_nodes += 2;
		return;
} 

// I have to write the function for precalculation of arr(k), ddl(k), dis(k)
// - but affter every insertion we have to update whole array of arr(k) and also ddl(k), dis(k)
