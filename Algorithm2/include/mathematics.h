

#ifndef MATHEMATICS

#define MATHEMATICS 

#include "structures.h"

double a_raise_b(double a, double b);
double distance(coordinate a, coordinate b);
double dis(location_node *a, location_node *b);
double min(double num1, double num2);
int max(int a, int b);
void scale_vector(coordinate unit_vector, double scale, coordinate *result);
void add_vector(coordinate a, coordinate b, coordinate *result);
void find_unit_vector(coordinate a, coordinate b, coordinate *result);


#endif
