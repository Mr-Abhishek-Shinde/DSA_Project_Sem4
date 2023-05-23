#include <stdio.h>
#include "structures.h"

typedef struct RideSharing_State{
    Route route;
    Set_of_requests set_of_requests;
    Worker worker;
}RideSharing_State;


void init_Ridesharing_State(RideSharing_State *ridesharing_state);
