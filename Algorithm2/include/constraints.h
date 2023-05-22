#ifndef CONSTRAINTS

#define CONSTRAINTS

#include "structures.h"

void pre_calculate_pck(Route route, double *pck_values);
double ddl(location_node *k);
void slk_intermediate(Route route, double *slk, location_node *n, int k);
void slk_time(Route route, double *slk);
double arr(Route route, location_node *k);
void insert(location_node *a, location_node *b);
double det(location_node *k, location_node *p);
int check_capacity_constraint(Worker w, Request new_request, double *pck_values, int i, int j);
int check_deadline_constraint(Route route, double *slk, int i, int j, location_node *origin, location_node *destination, location_node *li, location_node *lj);
double dis_index(location_node *a, location_node *b);

#endif
