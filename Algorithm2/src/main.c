#include <stdlib.h>
#include <stdio.h>
#include "insertion_operator.h"

void request(Request *request, double orx, double ory, double drx, double dry, double release_time, double deadline_time, int capacity){
    request->origin = (location_node*)malloc(sizeof(location_node));
    request->destination = (location_node*)malloc(sizeof(location_node));

    insert_coordinate(request->origin, orx, ory);
    insert_coordinate(request->destination, drx, dry);

    request->origin->next_location_node = NULL;
    request->origin->corresponding_request = request;
    request->destination->next_location_node = NULL;
    request->destination->corresponding_request = request;

    request->release_time = release_time;
    request->deadline_time = deadline_time;
    request->capacity = capacity;

    return;
}


RideSharing_State ridesharing_state;

int main(){

    Request r1, r2, r3, newRequest;
    

    init_Ridesharing_State(&ridesharing_state);

    request(&r1, 4, 4, 10, 4, 0, 25, 1);
    request(&r2, 8, 8, 4, 0, 0, 37, 1);
    request(&r3, 10, 2, 10, 0, 0, 33, 1);

    insert_node(&ridesharing_state, &r1, r1.origin, 1);
    insert_node(&ridesharing_state, &r2, r2.origin, 2);
    insert_node(&ridesharing_state, &r1, r1.destination, 3);
    insert_node(&ridesharing_state, &r3, r3.origin, 4);
    insert_node(&ridesharing_state, &r3, r3.destination, 5);
    insert_node(&ridesharing_state, &r2, r2.destination, 6);

    request(&newRequest, 4, 6, 6, 2, 2, 26, 1);
    update_worker_route(&ridesharing_state.route, &ridesharing_state.worker, &newRequest);
    display_route(ridesharing_state.route);
    /* printf("\n"); */
    /* printf("%d\n", ridesharing_state.worker.picked_up); */
    insertion_operator(ridesharing_state.route, ridesharing_state.worker, &newRequest); 
    /* display_route(ridesharing_state.route); */

    return 0;
}
