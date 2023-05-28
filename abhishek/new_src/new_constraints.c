int check_capacity_constraint(Request new_request, double *pck_values, int i){
        int c = (ridesharing_state.worker.capacity - new_request.capacity);

        if(pck_values[i] <= c){
                return 1;
        }
        else{
                return 0;
        }
}

int initial_deadline_condition(Request new_request, location_node *li,  int i, double *slk){
	if(det(li, new_request.origin) <= slk[i]){
		return 1;
	}
	else{
		return 0;
	}
}
