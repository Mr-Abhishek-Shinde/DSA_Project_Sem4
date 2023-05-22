#include "structures.h"

double time_between_nodes(coordinate n1, coordinate n2);
double arrival_time(Route r, coordinate l);
double flow_time(Route r, Request rq);
void mobj(Route r, double **mobj_values);
double max_of_mf(double mf1, double mf2, double mf3, double mf4);
double obj(Route r, int i, int j, location_node *li, location_node *lj, double **mobj_values, Request *new_rq);
