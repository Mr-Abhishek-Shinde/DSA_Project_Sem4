#include <stdio.h>
#include "insertion_operator.h"

void request(Request *request, coordinate or, coordinate dr, double release_time, double deadline_time, int capacity){
    request->origin = (location_node*)malloc(sizeof(location_node));
    request->destination = (location_node*)malloc(sizeof(location_node));

    insert_coordinate(request->origin, or.x, or.y);
    insert_coordinate(request->origin, dr.x, dr.y);

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
    insert_node(&ridesharing_state, request, request.origin);

    request(&request, 8, 8, 4, 0, 0, 25, 1);
    insert_node(&ridesharing_state, request, request.origin);
    insert_node(&ridesharing_state, request, request.destination);

    request(&request, 10, 2, 10, 4, 0, 25, 1);
    insert_node(&ridesharing_state, request, request.origin);
    insert_node(&ridesharing_state, request, request.destination);
    insert_node(&ridesharing_state);

    update_worker_route(ridesharing_state.route, ridesharing_state.worker, &new_request);
    insertion_operator(ridesharing_state.route, ridesharing_state.worker, &new_request);

    return 0;
}
