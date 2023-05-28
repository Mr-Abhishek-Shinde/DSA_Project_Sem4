int check_capacity_constraint(Worker w, Request newRequest, double *pck_values, int i){
        int c = (w.capacity - new_request.capacity);

        if(pck_values[i] <= c){
                return 1;
        }
        else{
                return 0;
        }
}

int initial_deadline_condition(Request newRequest, location_node *li,  int i, double *slk){
	if(det(li, newRequest.origin) <= slk[i]){
		return 1;
	}
	else{
		return 0;
	}
}
