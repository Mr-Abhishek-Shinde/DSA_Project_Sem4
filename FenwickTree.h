typedef struct FenwickTree{
	int *A;
	int s;
}FenwickTree;

void initFenwickTree(FenwickTree *);
void makeFenwickTree(FenwickTree *, int *, int);
void updateFenwickTree(FenwickTree *, int *, int, int, int);
int getParent(int);
int getNext(int);
void printFenwickTree(FenwickTree);
int getSum(FenwickTree , int);
