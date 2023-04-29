typedef struct coordinate{
                int x, y;
}coordinate;


typedef struct worker{
                coordinate current_location;
                int capacity;
                int picked_up;
}worker;

typedef struct request{
                coordinate origin, destination;
                double release_time, deadline_time;
                int capacity;
}request;

typedef struct set_of_requests{
        request **arr;
}set_of_requests;

typedef struct location_node{
                coordinate sequenced_location;
                struct location_node *next_location_node;
                request *corresponding_request;
}location_node;

typedef location_node *route;

void pre_calculate_pck(route r, int *pck_values);
int check_capacity_constraint(route r, worker w, request new_rq, int i, int j);
