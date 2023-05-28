#include <stdio.h>
#include "structures.h"

int main(){
	route r;
	worker w;
	w.current_location.x = 0;
	w.current_location.y = 4;
	w.capacity = 6;
	w.picked_up = 0;
	init_route(&r, w.current_location);
	request rq1, rq2, rq3, rq_new;

	rq1.origin.x = 4;
	rq1.origin.y = 4;
	rq1.destination.x = 10;
	rq1.destination.y = 4;
	rq1.release_time = 0;
	rq1.deadline_time = 25;
	rq1.capacity = 1;

	rq2.origin.x = 8;
	rq2.origin.y = 8;
	rq2.destination.x = 4;
	rq2.destination.y = 0;
	rq2.release_time = 0;
	rq2.deadline_time = 37;
	rq2.capacity = 1;

	rq3.origin.x = 10;
	rq3.origin.y = 2;
	rq3.destination.x = 10;
	rq3.destination.y = 0;
	rq3.release_time = 0;
	rq3.deadline_time = 33;
	rq3.capacity = 1;

	rq_new.origin.x = 9;
	rq_new.origin.y = 7;
	rq_new.destination.x = 10;
	rq_new.destination.y = 3;
	rq_new.release_time = 2;
	rq_new.deadline_time = 30;
	rq_new.capacity = 1;

	add_location_in_route(&r, &rq1, 0);
	add_location_in_route(&r, &rq2, 0);
	add_location_in_route(&r, &rq1, 1);
	add_location_in_route(&r, &rq3, 0);
	add_location_in_route(&r, &rq3, 1);
	add_location_in_route(&r, &rq2, 1);

	r = insertion_operator(r, w, &rq_new);
	printf("Route after insertion of the new request:\n");
	display_route(r);
	printf("max flow time - %lf\n", calculate_objective(r, rq_new.release_time));
	return 0;
}
