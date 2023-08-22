#ifndef CONSTRAINTS

#define CONSTRAINTS

#include "structures.h"

//New function for capacity for handling i=j cases
int check_capacity_constraint_iEqualj(Request new_request, double *pck_values, int i);

//New function for deadline for handling i=j cases
int check_deadline_constraint_iEqualj(location_node *li, Request new_request, double *slk_values, int i);

int check_capacity_constraint(Request newRequest, double *pck_values, int i);
int initial_deadline_condition(Request newRequest, location_node *li,  int i, double *slk);
#endif
