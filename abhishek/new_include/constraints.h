#ifndef CONSTRAINTS

#define CONSTRAINTS

#include "structures.h"

int check_capacity_constraint(Worker w, Request newRequest, double *pck_values, int i);
int initial_deadline_condition(Request newRequest, location_node *li,  int i, double *slk);

#endif
