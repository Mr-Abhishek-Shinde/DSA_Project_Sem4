#ifndef PRECALCULATION

#define PRECALCULATION

typedef struct Precalculation_set{
	double *pck;
	double *slk;
	double *thr;
	double *mobj;
	double *par;
	double *sorted_thr;
}Precalculation_set;

void precalculation_set_init(Precalculation_set *precalculation_set);
void malloc_precalculation_set(Precalculation_set *precalculation_set);
void precalculate(Precalculation_set *precalculation_set, Request new_request);
void precalculate_slk(double *slk_values, Request new_request);
void precalculate_slk_helper(double *slk_values, location_node *n, int k, Request new_request);
void precalculate_pck(double *pck_values);
void precalculate_thr(double *slk_values, double *thr_values, Request new_request);
void precalculate_mobj(double *mobj_values, Request new_request);
void precalculate_mobj_helper(location_node *p, double *mobj_values, Request new_request, int n, int i);
void precalculate_par(double *par_values, double *mobj_values, Request new_request);
void precalculate_sorted_thr(double *sorted_thr, double *thr);

#endif
