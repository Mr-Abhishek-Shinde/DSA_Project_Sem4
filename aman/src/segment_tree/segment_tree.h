#define SIZE_OF_ST(N)           (4*N)      
#define TOP_INDEX_ST            (0)    
#define START_INDEX_ARR         (0)

typedef double *ST;

/*! initialization of segment tree */
void init_ST(ST *st);

/*! construct segment tree */
void construct_ST(ST *st, int size);

/*! insert of par(i+1) at index i */
void insert_par(ST st, int node, int start_index, int end_index, double par, int i);

/*! returns min par(j) */
int min_par(ST st);

/*! invalidate function */
void invalidate(ST st, int *par, int *brk);
