#include "ridesharing.h"

void init_Ridesharing_State(RideSharing_State *ridesharing_state){
    ridesharing_state->route.path = NULL;
    ridesharing_state->route.no_of_nodes = 0;

    ridesharing_state->worker.current_location.x = 0;
    ridesharing_state->worker.current_location.y = 0;

    ridesharing_state->worker.capacity = 7;
    ridesharing_state->worker.picked_up = 0;

    ridesharing_state->set_of_requests.arr = NULL;
    ridesharing_state->set_of_requests.size = 0;
    
    return;
}
