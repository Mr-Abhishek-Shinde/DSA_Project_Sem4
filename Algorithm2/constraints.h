#ifndef CONSTRAINTS

#define CONSTRAINTS

#include "structures.h"

void pre_calculate_pck(route r, double *pck_values);
double ddl(location_node *k);
void slk_intermediate(route r, double *slk, location_node *n, int k);
void slk_time(route r, double *slk);
double arr(route r, location_node *k);
void insert(location_node *a, location_node *b);
double det(location_node *k, location_node *p);
int check_capacity_constraint(worker w, request new_request, double *pck_values, int i, int j);
int check_deadline_constraint(route r, double *slk, int i, int j, location_node *origin, location_node *destination, location_node *li, location_node *lj);

#endif
