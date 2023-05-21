#include "structures.h"

double time_between_nodes(coordinate n1, coordinate n2);
double arrival_time(route r, coordinate l);
double flow_time(route r, request rq);
void mobj(route r, double **mobj_values);
double max_of_mf(double mf1, double mf2, double mf3, double mf4);
double obj(route r, int i, int j, location_node *li, location_node *lj, double **mobj_values, request *new_rq);
