#include "structures.h"
#include "ridesharing.h"

void display_route(Route r);
void insert_node(Request *request, location_node *l, int index);
void insert_coordinate(location_node *l, double x, double y);
void update_route(Worker *w, location_node *before_worker);
void update_worker_route(Worker *w, Request *new_request);
void insertion_operator(Request *new_request);
