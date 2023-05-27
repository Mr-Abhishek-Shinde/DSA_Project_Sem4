void mobj(Route r, double *mobj_values, Request newRequest){
	location_node *p = r.path;
	int n = r.path.no_of_nodes;

	mobj_helper(r, p, mobj_values, newRequest, n, 0);

	return;
}

void mobj_helper(Route r, location_node *li, double *mobj_values, Request newRequest, int n, int i){
	if(i == n - 1){
		mobj_values[i] = flow_time(r, *(p->corresponding_request), newRequest);
		return;
	}
	else{
		double ft_curr;

		if(li == li->corresponding_request->destination){
			ft_curr = flow_time(r, *(q->corresponding_request), newRequest);
                }
                else{
                	ft_curr = 0;
		}

		mobj_helper(r, li->next_location_node, mobj_values, newRequest, n, i + 1);
		mobj_values[i] = max(ft_curr, mobj_values[i + 1]);
	}

	return;
}









