#include <stdlib.h>
#include "ridesharing.h"

void init_Ridesharing_State(RideSharing_State *ridesharing_state){

    ridesharing_state->route.path = (location_node*)malloc(sizeof(location_node));
    ridesharing_state->route.path->next_location_node = NULL;
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
