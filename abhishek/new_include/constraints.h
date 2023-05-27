#ifndef CONSTRAINTS

#define CONSTRAINTS

#include "structures.h"

int check_capacity_constraint(Worker w,  Request new_request, double *pck_values, int i, int j);
int check_deadline_constraint(Route route, double *slk, int i, int j, location_node *origin, location_node *destination, location_node *li, location_node *lj, Request newRequest);

#endif
