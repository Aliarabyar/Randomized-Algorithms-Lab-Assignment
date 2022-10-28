 

//    p and rank are parallel arrays for keeping track of disjoint sets; size is the size of both arrays;
typedef struct {
    int *p; // parent array
    int *rank; // rank array
    int size;
} ds_forest;

 
//    allocates memory for disjoint sets
//    size provided up front to avoid need for resizing
ds_forest *makeForest(int size);

 
//    deallocates memory used by f
void burnForest(ds_forest *f);

 
//    makes a set in f for x  (this could be done in makeForest, however we do it here to maintain the structure of the algorithm  as the excess work is negligible)
void makeSet(ds_forest *f, int x);

 
//    returns the root of the set of x in f
int find(ds_forest *f, int x);

 
//    union the sets of x and y
int ds_union(ds_forest *f, int x, int y);

 
//    run tests to verify correctness of disjoint set implementation
int testsDisjointSet();
