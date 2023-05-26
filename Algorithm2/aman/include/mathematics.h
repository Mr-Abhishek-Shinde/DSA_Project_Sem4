

#ifndef MATHEMATICS

#define MATHEMATICS 

#include "structures.h"

double a_raise_b(double a, double b);
double distance_node(coordinate a, coordinate b);
double dis(location_node *a, location_node *b);
double min(double num1, double num2);
int max(int a, int b);
void scale_vector(coordinate *result, coordinate unit_vector, double scale);
void add_vector(coordinate *result, coordinate a, coordinate b);
void find_unit_vector(coordinate *result,coordinate a, coordinate b);


#endif
