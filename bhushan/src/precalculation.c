#include "precalculation.h"
#include "searching_and_sorting.h"
void precalculation_set_init(Precalculation_set *precalculation_set){
	precalculation_set->pck = NULL;
	precalculation_set->slk = NULL;
	precalculation_set->thr = NULL;
	precalculation_set->mobj = NULL;
	precalculation_set->par = NULL;
	precalculation_set->sorted_thr = NULL;
	return;
}
void malloc_precalculation_set(Precalculation_set *precalculate_set){
	precalculation_set->pck = (double *) malloc(sizeof(double) * ridesharing_state.no_of_nodes);
	precalculation_set->slk = (double *) malloc(sizeof(double) * ridesharing_state.no_of_nodes);
	precalculation_set->thr = (double *) malloc(sizeof(double) * ridesharing_state.no_of_nodes);
	precalculation_set->mobj = (double *) malloc(sizeof(double) * ridesharing_state.no_of_nodes);
	precalculation_set->par = (double *) malloc(sizeof(double) * ridesharing_state.no_of_nodes);
	precalculation_set->sorted_thr = (double *) malloc(sizeof(double) * ridesharing_state.no_of_nodes);
	return;
}
void precalculate(Precalculation_set *precalculation_set, Request new_request){
		malloc_precalculation_set(pre_calculate_pck);
	precalculate_slk(precalculation_set->slk, new_request);
	precalculate_pck(precalculation_set->pck);
	precalculate_thr(precalculation_set->slk, precalculation_set->thr, new_request);
	precalculate_mobj(precalculation_set->mobj, new_request);
	precalculate_par(precalculation_set->par, precalculation_set->mobj, new_request);
	precalculate_sorted_thr(precalculation_set->sorted_thr, precalculation_set->thr);
        return;
}
void precalculate_slk(double *slk_values, Request new_request){
	dis_from_origin[0] = 0;
	slk_values[r.no_of_nodes - 1] = DBL_MAX;
	int k = 0;
	precalculate_slk_helper(slk_values, r.path, k, newRequest);
	return;

}
void precalculate_slk_helper(double *slk_values, location_node *n, Request new_request){
	if(k == (r.no_of_nodes - 1)){
                n->index = k;
		return;
        }

	dis_from_origin[k+1] = distance_node(n->sequenced_location, n->next_location_node->sequenced_location) + dis_from_origin[k]; // it will find the distance from origin to kth node
        n->index = k;

	precalculate_slk_helper(r, slk, n->next_location_node, k+1, newRequest);
	slk_values[k] = min(slk_values[k+1], ddl(n->next_location_node) - arr(r, n->next_location_node, newRequest));
	return;
}
void precalculate_pck(double *pck_values){
	pck_values[0] = worker.picked_up;

	location_node *p = r.path->next_location_node;
	int i = 1;
	double pck_k = pck_values[0];
	
	Request *req;
	
	while(p){
		req = p->corresponding_request;
	
		if(p == req->origin){
			pck_k += req->capacity;
		}
		else if(p == req->destination){
			pck_k -= req->capacity;
		}
	
		pck_values[i] = pck_k;
		p = p->next_location_node;
		i++;
	}

	return;
}
void precalculate_thr(double *slk_values, double *thr_values, Request new_request){
	int i = 0;
	location_node *p = r.path;
	double cmp1, cmp2;
	while(p){
		cmp1 = slk_values[i] - det(p, new_request.destination);
		cmp2 = new_request.deadline_time - arr(r, p, new_request) - distance_node(p->sequenced_location, (new_request.destination)->sequenced_location);
		thr_values[i] = min(cmp1, cmp2);
		p = p->next_location;
		i++;
	}
	return;
}
void precalculate_mobj(double *mobj_values, Request new_request){
	location_node *p = r.path;
	int n = r.path.no_of_nodes;
	precalculate_mobj_helper(r, p, mobj_values, newRequest, n, 0);
	return;

}

void precalculate_mobj_helper(location_node *li, double *mobj_values, Request new_request, int n, int i){
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

		precalculate_mobj_helper(li->next_location_node, mobj_values, newRequest, n, i + 1);
		mobj_values[i] = max(ft_curr, mobj_values[i + 1]);
	}

	return;

}
void precalculate_par(double *par_values, double *mobj_values, Request new_request){
	int i = 0;
	location_node *p = r.path;
	double cmp1, cmp2;
	while(p){
		if(i + 1 < r.no_of_nodes){
			cmp1 = det(p, new_request.destination) + mobj_values[i + 1];
		}
		else{
			cmp1 = det(p, new_request.destination);//mobj is 0
		}
		cmp2 = arr(r, p, new_request) + distance_node(p->sequenced_node, (new_request.destination)->sequenced_location) - new_request.release_time;
		par_values[i] = max(cmp1, cmp2);
		p = p->next_location_node;
		i++;
	}
	return;
}
void precalculate_sorted_thr(double *sorted_thr, double *thr){
	for(int i = 0; i < r.no_of_nodes; i++){
		sorted_thr[i] = thr[i];
	}
	sort_karo(sorted_thr, r.no_of_nodes, 0, r.no_of_nodes - 1);
	return;
}
