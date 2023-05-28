#include "structures.h"

void display_route(Route r);
void insert_node(Request *request, location_node *l, int index);
void insert_coordinate(location_node *l, double x, double y);
void update_route(location_node *before_worker);
void update_worker_route(Request *new_request);
void insertion_operator(Request *new_request);
double obj(double *mobj, location_node *li, Request new_request, double min_par, int noOfNodes);
double obj_iEqualj(double *mobj, location_node *li, Request new_request, int i);
