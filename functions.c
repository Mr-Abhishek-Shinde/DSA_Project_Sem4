#include "structures.h"
#include <math.h>
#include <stdio.h>
#include <limits.h>
// let route be SR = < l0, l1, l2, l3 ... , ln >  
// l0 = node of worker current location
// we will initialize the route by node of worker i.e l0
void init_route(route *r, coordinate worker){
		(*r) = (location_node*)malloc(sizeof(location_node));
		(*r)->sequenced_location.x = worker.x;
		(*r)->sequenced_location.y = worker.y;
		(*r)->isOrigin = -1;
		(*r)->next_location_node = NULL;
		(*r)->corresponding_request = NULL;
		return;
}

void add_location_in_route(route *r, request *rq, int flag){
	location_node* l = malloc(sizeof(location_node));
	if(!flag){
		(l->sequenced_location).x = (rq->origin).x;
		(l->sequenced_location).y = (rq->origin).y;	
		l->isOrigin = 1;
	}
	else{
		(l->sequenced_location).x = (rq->destination).x;
		(l->sequenced_location).y = (rq->destination).y;
		l->isOrigin = 0;
	}
	l->next_location_node = NULL;
	l->corresponding_request = rq;
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
		time += time_between_nodes(prev->sequenced_location, curr->sequenced_location);
		prev = curr;
		curr = curr->next_location_node;
	}
	return time;
}

double time_between_nodes(coordinate n1, coordinate n2){
	double time_squared = (n1.x - n2.x) * (n1.x - n2.x) + (n1.y - n2.y) * (n1.y - n2.y);
	return sqrt(time_squared);
}

double flow_time(route r, request rq){
	double arr_destination = arrival_time(r, rq.destination);
	return arr_destination - rq.release_time;
}

void display_route(route r){
	location_node *n = r;
	while(n){
		printf("----coordinate----\n");
		printf("x, y = %lf, %lf\n", (n->sequenced_location).x, (n->sequenced_location).y);
		n = n->next_location_node;
	}
	return;
}

route insertion_operator(route r, worker w, request *rq){
	int count = 0;
	route r_new = findCurrentLocation(r, &w, rq);
	printf("----Displaying new route----\n");
	display_route(r_new);
//	printf("worker pickup - %d, worker capacity - %d\n", w.picked_up, w.capacity);
	location_node *rq_origin = (location_node *)malloc(sizeof(location_node));
	location_node *rq_destination = (location_node *)malloc(sizeof(location_node));

	rq_origin->sequenced_location = rq->origin;
	rq_origin->corresponding_request = rq;
	rq_origin->isOrigin = 1;

	rq_destination->sequenced_location = rq->destination;
	rq_destination->corresponding_request = rq;
	rq_destination->isOrigin = 0;

	location_node *l, *d, *l_final = NULL, *d_final = NULL;
	double obj_min = INT_MAX, obj;
	l = r_new;
	while(l){
		rq_origin->next_location_node = l->next_location_node;
		l->next_location_node = rq_origin;
		d = rq_origin;
		while(d){
			count++;
			rq_destination->next_location_node = d->next_location_node;
			d->next_location_node = rq_destination;
			if(constrain_satisfy(r_new, w, rq->release_time)){
//				printf("Inside constraint\n");
				obj = calculate_objective(r_new, rq->release_time);
//				printf("--------Objective - count %d- %lf----------\n", count, obj);
				if(obj < obj_min){
//					printf("objective - %lf\n", obj);
					l_final = l;
					d_final = d;
					obj_min = obj;
				}
			}
			else{
//				printf("count - %d\n", count);
			}
			d->next_location_node = rq_destination->next_location_node;
			d = d->next_location_node;
		}
		l->next_location_node = rq_origin->next_location_node;
		l = l->next_location_node;
	}
	if(l_final && d_final){
		rq_origin->next_location_node = l_final->next_location_node;
		l_final->next_location_node = rq_origin;
		rq_destination->next_location_node = d_final->next_location_node;
		d_final->next_location_node = rq_destination;
	}
	return r_new;
}

route findCurrentLocation(route r, worker *w, request *rq){
	double time = 0;
	int pickup = w->picked_up;
	location_node *n = r->next_location_node;
	location_node *p = r;//assuming that the first location in the route is the worker's starting location. it is neither origin nor destination.
	while(n){
		time += time_between_nodes(n->sequenced_location, p->sequenced_location);
		if(time > rq->release_time){
			time -= time_between_nodes(n->sequenced_location, p->sequenced_location);
			break;
		}
		if(n->isOrigin == 1)
			pickup += n->corresponding_request->capacity;
		else if(n->isOrigin == 0)
			pickup -= n->corresponding_request->capacity;
		p = n;
		n = n->next_location_node;
	}
	location_node *newNode = (location_node *)malloc(sizeof(location_node));
	coordinate vector;
	vector.x = (n->sequenced_location).x - (p->sequenced_location).x;
	vector.y = (n->sequenced_location).y - (p->sequenced_location).y;
	double magnitude = sqrt((vector.x) * (vector.x) + (vector.y) * (vector.y));
	vector.x = vector.x / magnitude;
	vector.y = vector.y / magnitude;
	double offset_time = rq->release_time - time;
	vector.x *= offset_time;
	vector.y *= offset_time;
	(newNode->sequenced_location).x = (p->sequenced_location).x + vector.x;
	(newNode->sequenced_location).y = (p->sequenced_location).y + vector.y;
	newNode->corresponding_request = NULL;
	newNode->isOrigin = -1;//neither origin nor destination
	newNode->next_location_node = n;
	p->next_location_node = newNode;
	(w->current_location).x = (newNode->sequenced_location).x;
	(w->current_location).y = (newNode->sequenced_location).y;
	w->picked_up = pickup;
	return newNode;
}

int constrain_satisfy(route r, worker w, double initial_time){
	int count = 0;
	double time = initial_time;
	int pickup = w.picked_up;
	location_node *p = r, *n = r->next_location_node;
	while(n){
		count++;
		time += time_between_nodes(p->sequenced_location, n->sequenced_location);
		if(n->isOrigin == 1){
			pickup += n->corresponding_request->capacity;
//			printf("pickup inside origin- %d\n", pickup);
			if(pickup > w.capacity){
//				printf("Returning 0 capacity constraint count no of interations - %d\n, pickup - %d, capacity - %d\n", count, pickup, w.capacity);
				return 0;
			}
		}
		else if(n->isOrigin == 0){
			if(time > n->corresponding_request->deadline_time){
//				printf("Returning 0 deadline constraint\n");
				return 0;
			}
			pickup -= n->corresponding_request->capacity;
//			printf("pickup inside destination- %d\n", pickup);
		}
		p = n;
		n = n->next_location_node;
	}
	return 1;
}

double calculate_objective(route r, double initial_time){
	double time = initial_time;
	location_node *p = r, *n = r->next_location_node;
	double sum_flow_time = 0;
	while(n){
		time += time_between_nodes(p->sequenced_location, n->sequenced_location);
		if(n->isOrigin == 0){
			sum_flow_time += time - n->corresponding_request->release_time;
			printf("%lf\n", time - n->corresponding_request->release_time);
		}
		n = n->next_location_node;
	}
	return sum_flow_time;
}
