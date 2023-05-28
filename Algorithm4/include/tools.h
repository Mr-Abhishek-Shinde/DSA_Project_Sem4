#ifndef TOOLS

#define TOOLS

#include "structures.h"

/* a raise to b - a^b */
double a_raise_b(double a, double b);

 /* find distance between a and b coordinate */
double distance_node(coordinate a, coordinate b);

 /* find min value between num1 and num2 */
double min(double num1, double num2);

/* returns max of a and b */
double max(double a, double b);

/* scale the unit_vector according to scale input */
void scale_vector(coordinate *result, coordinate unit_vector, double scale);

/* addition of two vector */
void add_vector(coordinate *result, coordinate a, coordinate b);

/* will find unit vector between a and b vector */
void find_unit_vector(coordinate *result,coordinate a, coordinate b);

#endif
