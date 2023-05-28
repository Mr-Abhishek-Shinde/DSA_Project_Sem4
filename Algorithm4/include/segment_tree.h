#define SIZE_OF_ST(N)           (4*N)      
#define TOP_INDEX_ST            (0)    
#define START_INDEX_ARR         (0)

typedef struct ST{
    double *arr;
    int size;
}ST;

/*! initialization of segment tree */
void init_ST(ST *st);

/*! construct segment tree */
void construct_ST(ST *st, double *arr);

/*! insert of par(i+1) at index i */
void update_par(ST st, double par, int index_to_insert);
/*! returns min par(j) */
double min_par(ST st, int si, int ei);

/*! invalidate function */
void invalidate(ST st, double *par, int *brk);
