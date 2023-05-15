typedef struct coordinate{
                int x, y;
}coordinate;


typedef struct worker{
                coordinate current_location;
                int capacity;
                int picked_up;
}worker;

typedef struct request{
                struct location_node *or, *dr;
                double release_time, deadline_time;
                int capacity;
}request;

typedef struct set_of_requests{
        request *arr;
	int size;
}set_of_requests;

typedef struct location_node{
                coordinate sequenced_location;
                struct location_node *next_location_node;
                struct request *corresponding_request;
		int index;
}location_node;

typedef struct route{
	location_node *path;
	int no_of_nodes;
} route;

void pre_calculate_pck(route r, int *pck_values);
int check_capacity_constraint(worker w, request new_rq, int i, int j);
double time_between_nodes(coordinate n1, coordinate n2);
double arrival_time(route r, coordinate l);
double flow_time(route r, request rq);
void mobj(route r, double **mobj_values);
double obj(route r, int i, int j, location_node *li, location_node *lj, double **mobj_values, request *new_rq);

double dis(location_node *a, location_node *b);
double arr(location_node *k);
double det(location_node *k, location_node *p);
