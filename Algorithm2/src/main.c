#include <stdio.h>
#include "insertion_operator.h"

void request(Request *request, double orx, double ory, double drx, double dry, double release_time, double deadline_time, int capacity){
    request->origin = (location_node*)malloc(sizeof(location_node));
    request->destination = (location_node*)malloc(sizeof(location_node));

    insert_coordinate(request->origin, orx, ory);
    insert_coordinate(request->origin, drx, dry);

    request->release_time = release_time;
    request->deadline_time = deadline_time;
    request->capacity = capacity;

    return;
}

Ridesharing_State ridesharing_state;

int main(){

    Request request;
    

    init_Ridesharing_State(&ridesharing_state);

    request(&request, 4, 4, 10, 4, 0, 25, 1);
    insert_node(&ridesharing_state, request, request.origin, 1);

    request(&request, 8, 8, 4, 0, 0, 25, 1);
    insert_node(&ridesharing_state, request, request.origin, 2);
    insert_node(&ridesharing_state, request, request.destination, 3);

    request(&request, 10, 2, 10, 4, 0, 25, 1);
    insert_node(&ridesharing_state, request, request.origin, 4);
    insert_node(&ridesharing_state, request, request.destination, 5);
    insert_node(&ridesharing_state);

    update_worker_route(ridesharing_state.route, ridesharing_state.worker, &new_request, 6);
    insertion_operator(ridesharing_state.route, ridesharing_state.worker, &new_request, 7);

    return 0;
}
