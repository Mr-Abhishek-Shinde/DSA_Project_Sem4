#ifndef TIME_FUNCTIONS

#define TIME_FUNCTIONS


double time_between_nodes(coordinate c1, coordinate c2);
void insert(location_node *a, location_node *b);
double ddl(location_node *k);
double arr(location_node *k, Request new_request);
double det(location_node *k, location_node *p);
double distance_index(location_node *a, location_node *b);
double distance_node(coordinate , coordinate);
double flow_time(Request, Request);

#endif
