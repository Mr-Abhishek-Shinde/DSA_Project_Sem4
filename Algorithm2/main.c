#include <stdio.h>
#include "insertion_operator.h"

Ridesharing_State ridesharing_state;
int main(){

    Request request;

    request request1;

    init_states(&ridesharing_state);

    update_worker_route(ridesharing_state.route, ridesharing_state.worker, &new_request);
    insertion_operator(ridesharing_state.route, ridesharing_state.worker, &new_request);

    return 0;
}
