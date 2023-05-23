#include "mathematics.h"
#include "math.h"
#define MATH

// a raise to b - a^b
double a_raise_b(double a, double b){
		double result = a;
		for(int i = 0; i < (b - 1); i++){
				result = result * a;
		}
		return result;
}

// find distance between a and b coordinate
double distance_node(coordinate a, coordinate b){
		double distance, delta_x, delta_y;
		delta_x = a.x - b.x;
		delta_y = a.y - b.y;
		distance = sqrt(a_raise_b(delta_x, 2) + a_raise_b(delta_y, 2));
		return distance;
}

// this functions will find the distance between a and b node in Route
double dis(location_node *a, location_node *b){
		double dis = 0;
		location_node *temp = a;
		while(temp != b->next_location_node){
				dis += distance_node(a->sequenced_location, a->next_location_node->sequenced_location);
				temp = temp->next_location_node;
		}
		return dis;
}

// find min value between num1 and num2
double min(double num1, double num2){
		return (num1 > num2 ? num2 : num1);
}

int max(int a, int b){
	return (a > b ? a : b);
}

void scale_vector(coordinate *result, coordinate unit_vector, double scale){
		(*result).x = unit_vector.x * scale;
		(*result).y = unit_vector.y * scale;
		return;
}

void add_vector(coordinate *result, coordinate a, coordinate b){
		(*result).x = a.x + b.x;
		(*result).y = a.y + b.y;
		return;
}

void find_unit_vector(coordinate *result, coordinate a, coordinate b){
		double magnitude = distance_node(a, b); 
		result->x = (b.x - a.x) / magnitude;
		result->y = (b.x - a.x) / magnitude;
		return;
}
