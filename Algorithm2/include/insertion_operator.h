#include "structures.h"
#include "ridesharing.h"

void display_route(Route r);
void insert_node(RideSharing_State *ridesharing_state, Request *request, location_node *l, int index);
void insert_coordinate(location_node *l, double x, double y);
void update_route(Route *r, Worker *w, location_node *before_worker);
void update_worker_route(Route *r, Worker *w, Request *new_request);
void pre_calculation(Route r, double *slk_values, double *pck_values, double **mobj_values);
void insertion_operator(Route r, Worker w, Request *new_request);
