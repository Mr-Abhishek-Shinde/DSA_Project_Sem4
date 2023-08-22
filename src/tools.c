#include "tools.h"
#include "math.h"
#include "global.h"
/* a raise to b - a^b */
double a_raise_b(double a, double b){
		if(b == 0)
			return 1;
		double result = a;
		for(int i = 0; i < (b - 1); i++){
				result = result * a;
		}
		return result;
}

 /* find distance between a and b coordinate */
double distance_node(coordinate a, coordinate b){
		double distance, delta_x, delta_y;
		delta_x = a.x - b.x;
		delta_y = a.y - b.y;
		distance = sqrt(a_raise_b(delta_x, 2) + a_raise_b(delta_y, 2));
		return distance;
}

 /* find min value between num1 and num2 */
double min(double num1, double num2){
		return (num1 > num2 ? num2 : num1);
}

/* returns max of a and b */
double max(double a, double b){
	return (a > b) ? a : b;
}

/* scale the unit_vector according to scale input */
void scale_vector(coordinate *result, coordinate unit_vector, double scale){
		(*result).x = unit_vector.x * scale;
		(*result).y = unit_vector.y * scale;
		return;
}

/* addition of two vector */
void add_vector(coordinate *result, coordinate a, coordinate b){
		(*result).x = a.x + b.x;
		(*result).y = a.y + b.y;
		return;
}

/* will find unit vector between a and b vector */
void find_unit_vector(coordinate *result, coordinate a, coordinate b){
		double magnitude = distance_node(a, b); 
		result->x = (b.x - a.x) / magnitude;
		result->y = (b.y - a.y) / magnitude;
		return;
}

