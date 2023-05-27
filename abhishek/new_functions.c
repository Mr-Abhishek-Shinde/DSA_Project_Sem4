// precalculating mobj:
void mobj(Route r, double **mobj_values, Request newRequest){
        location_node *p = r.path;
        while(p->next_location_node){
                p = p->next_location_node;
        }

        double ft_curr = flow_time(r, *(p->corresponding_request), newRequest);
        int n = r.path.no_of_nodes;

        for(int i = n; i > 0; i--){
                if(i = n){
                        mobj[i][n] = 0;
                }
                else{
                        mobj[i][n] = max(ft_curr ,mobj[i + 1][n]);
                }
        }

        return;
}

