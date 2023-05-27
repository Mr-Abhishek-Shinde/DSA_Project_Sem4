#include <stdio.h>

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


// binary search in sorted array:
int binary_search_thr(double *thr_arr, int key, int i, int n){
	int l = i;
	int h = n;
	int m;

	while(l <= h){
		m = (l + h) / 2;

		if(thr_arr[m] == key){
			return m;
		}
		else if(thr_arr[m] > key && (m != 0 && thr_arr[m - 1] < key)){
			return m;
		}
		else{
			if(thr_arr[m] < key){
				l = m + 1;
			}
			else{
				h = m - 1;
			}
		}
	}

	return 0;
}	

int main(){
	double arr[] = {2.3, 4.3, 6.2, 9.7, 9.9, 12.5, 31.3, 21.5};

	printf("%d\n", binary_search_thr(arr, 6.2, 0, 7));
	printf("%d\n", binary_search_thr(arr, 6.2, 3, 7));
	printf("%d\n", binary_search_thr(arr, 5.1, 0, 7));
	printf("%d\n", binary_search_thr(arr, 31.3, 0, 7));
	printf("%d\n", binary_search_thr(arr, 1.2, 0, 7));
	printf("%d\n", binary_search_thr(arr, 2.4, 6, 7));

	return 0;
}






