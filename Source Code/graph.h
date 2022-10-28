// graph.h
//    graph.h/graph.c implement graph data structures and helper
//    functions for working with those data structures

// edge:
//    u,v = vertices (vertices represented as ints)
//    weight = edge weight
typedef struct {
    int u;
    int v;
    float weight;
} edge;

// graph:
//    Edge list implementation
typedef struct {
    edge *list;
    int num_nodes;
    int num_edges;
} graph;

// test_raphs:
//    Predefined graphs with predefined MST weights to be used
//    for testing correctness of algorithm.
//    graphs and mst_weights are parallel arrays
typedef struct {
    graph *graphs;
    float *mst_weights;
    int num_graphs;
} test_graphs;


// generateGraphAtRandom
graph *generateGraphAtRandom(int numberOfNodes);

 

// testGraph() Return an array of test_graphs for correctness checking
test_graphs *testGraph();

// graph_edge_sort(g): Sort edge list of g
void sortGraphEdge(graph *g);

// printGraph(g):  Print graph (for debugging purposes)
void printGraph(graph *g);

// testsGraph():  Run tests on graph generation functions
int testsGraph();

// Memory deallocation functions
void freeGraph(graph *g);
void freeGraphtest(test_graphs *ts);
