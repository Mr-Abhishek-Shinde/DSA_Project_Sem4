#include <stdlib.h>
#include <stdio.h>
#include "insertion_operator.h"




RideSharing_State ridesharing_state;

int main(){

    Request r1, r2, r3, newRequest;
    
    init_Ridesharing_State(&ridesharing_state);

    request_init(&r1, 4, 4, 10, 4, 0, 25, 1);
    request_init(&r2, 8, 8, 4, 0, 0, 37, 1);
    request_init(&r3, 10, 2, 10, 0, 0, 33, 1);

    insert_node(&r1, r1.origin, 1);
    insert_node(&r2, r2.origin, 2);
    insert_node(&r1, r1.destination, 3);
    insert_node(&r3, r3.origin, 4);
    insert_node(&r3, r3.destination, 5);
    insert_node(&r2, r2.destination, 6);

    request_init(&newRequest, 4, 6, 6, 2, 2, 26, 1);
    update_worker_route(&newRequest);
    display_route(ridesharing_state.route);
    /* printf("\n"); */
    /* printf("%d\n", ridesharing_state.worker.picked_up); */
    insertion_operator(&newRequest); 
    /* display_route(ridesharing_state.route); */

    return 0;
}
