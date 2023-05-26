#ifndef CONSTRAINTS

#define CONSTRAINTS

#include "structures.h"

double time_between_nodes(coordinate n1, coordinate n2);
void pre_calculate_pck(Route route, double *pck_values, Worker worker);
double ddl(location_node *k);
void slk_intermediate(Route r, double *slk, location_node *n, int k, Request new_request);
void slk_time(Route route, double *slk, Request new_request);
double arr(Route route, location_node *k, Request new_request);
void insert(location_node *a, location_node *b);
double det(location_node *k, location_node *p);
int check_capacity_constraint(Worker w,  Request new_request, double *pck_values, int i, int j);
int check_deadline_constraint(Route route, double *slk, int i, int j, location_node *origin, location_node *destination, location_node *li, location_node *lj, Request newRequest);
double dis_index(location_node *a, location_node *b);

#endif