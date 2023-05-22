#include "structures.h"

void update_route(route r, worker w, location_node *before_worker);
void update_worker_route(route r, worker w, request *new_request);
void pre_calculation(route r, double *slk_values, double *pck_values, double **mobj_values);
void insertion_operator(route r, worker w, request *new_request);
