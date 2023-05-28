#include <stdlib.h>
#include "global.h"

void init_Ridesharing_State(RideSharing_State *ridesharing_state){

    ridesharing_state->route.path = (location_node*)malloc(sizeof(location_node));
    ridesharing_state->route.path->next_location_node = NULL;
    ridesharing_state->route.path->prev_location_node = NULL;
    ridesharing_state->route.path->corresponding_request = NULL;
    ridesharing_state->route.path->index = 0;
    ridesharing_state->route.no_of_nodes = 1;
    ridesharing_state->route.path->sequenced_location.x = 0;
    ridesharing_state->route.path->sequenced_location.y = 4;

    ridesharing_state->worker.current_location.x = X_CORD;
    ridesharing_state->worker.current_location.y = Y_CORD;

    ridesharing_state->worker.capacity = CAPACITY;
    ridesharing_state->worker.picked_up = 0;

    ridesharing_state->set_of_requests.arr = NULL;
    ridesharing_state->set_of_requests.size = 0;
    
    return;
}

void init_request(Request *request, double orx, double ory, double drx, double dry, double release_time, double deadline_time, int capacity){
    request->origin = (location_node*)malloc(sizeof(location_node));
    request->destination = (location_node*)malloc(sizeof(location_node));

    insert_coordinate(request->origin, orx, ory);
    insert_coordinate(request->destination, drx, dry);

    request->origin->next_location_node = NULL;
    request->origin->prev_location_node = NULL;
    request->origin->corresponding_request = request;
    request->destination->next_location_node = NULL;
    request->destination->prev_location_node = NULL;
    request->destination->corresponding_request = request;

    request->release_time = release_time;
    request->deadline_time = deadline_time;
    request->capacity = capacity;

    return;
}
