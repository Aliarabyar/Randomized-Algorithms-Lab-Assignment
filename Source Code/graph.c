
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "graph.h"

 
#define SQUARE(x) ((x) * (x))
#define MIN(x,y) (((x) <= (y)) ? (x) : (y))

 
 
static void mergeGraphEdge(edge *, int, int, int, edge *);

 
	//  Generates graph numberOfNodes vertices where edge lengths are assigned random values between 0 and 1 (numberOfNodes must be > 1)
graph *generateGraphAtRandom(int numberOfNodes) {
    // allocate memory
    graph *g = (graph *) malloc(sizeof(graph));
    g->num_nodes = numberOfNodes;
    g->num_edges = g->num_nodes;
    g->list = (edge *) malloc(sizeof(edge) * g->num_edges);

    // for values of numberOfNodes > max_width_cutoff do not include  edges of width > max_width as these edges will not be in MST (see writeup for more info)
    const int max_width_cutoff = 10000;
    const float max_width = .002F;
    
    // generate edges random edge weights for graph, dynamically updating the size of the edge list to allow for more edges;
       int e = 0;
    for (int i = 1; i < numberOfNodes; ++i) {
	for (int j = 0; j < i; ++j) {
	    float w = (float) rand() / RAND_MAX;
	    if (numberOfNodes < max_width_cutoff || w < max_width) {
		if (e >= g->num_edges) {
		    g->num_edges *= 2;
		    g->list = realloc(g->list, sizeof(edge) * g->num_edges);
		}
		edge e_local = { .u = i, .v = j, .weight = w };
		g->list[e++] = e_local;
	    }
	}
    }
    // reset num_edges based on number of edges actually added
    g->num_edges = e;
    
    return g;
}
  
 
//    helper function for mergesort implementation
void mergeGraphEdge(edge *src, int s1, int s2, int end, edge *dest) {
    int i, l, r;
    for (i = s1, l = s1, r = s2; l < s2 && r < end; ++i) 
	dest[i] = (src[l].weight <= src[r].weight) ? src[l++] : src[r++];
    if (l < s2) {
	for (; i < end; ++i, ++l)
	    dest[i] = src[l];	
    }
    else {
	for (; i < end; ++i, ++r) 
	    dest[i] = src[r];	
    }
}

 
//    implementation of mergesort
void sortGraphEdge(graph *g) {
    int n = g->num_edges;
    edge *a = g->list;
    edge *b = malloc(sizeof(edge) * n);
    for (int m = 1; m < n; m *= 2) {
	for (int i = 0; i < n; i += 2 * m) {
	    mergeGraphEdge(a, i, MIN(i + m, n), MIN(i + 2 * m, n), b);
	}
	edge *temp = a;
	a = b;
	b = temp;
    }
    if (a != g->list) {
	memcpy(g->list, a, sizeof(edge) * n);
	free(a);
    }
    else
	free(b);
}

void printGraph(graph *g) {
    printf("# of Nodes: %d\n", g->num_nodes);
    printf("# of Edges: %d\n", g->num_edges);
    printf("Edge Weights: [");
    for (int i = 0; i < g->num_edges; ++i) {
	printf("%s%.02f", (i == 0) ? "" : ", ", g->list[i].weight);
    }
    printf("]\n");
 
}

 
// tests the number of nodes and edge weights
 int testsGraph() {
     int num_nodes = 20;
    graph *g = generateGraphAtRandom(num_nodes);
    assert(g->num_nodes == num_nodes);
    for (int i = 0; i < g->num_edges; ++i) {
	assert(g->list[i].weight <= 1);
	assert(g->list[i].weight >= 0);
    }

    return 0;
}



test_graphs *testGraph() {
    test_graphs *graphs = (test_graphs *) malloc(sizeof(test_graphs));
    graphs->num_graphs = 4;
    graphs->graphs = malloc(sizeof(edge) * graphs->num_graphs);
    graphs->mst_weights = malloc(sizeof(float) * graphs->num_graphs);

    edge *edge0 = malloc(sizeof(edge) * 0);   edge *edge1 = malloc(sizeof(edge) * 1);  edge *edge2 = malloc(sizeof(edge) * 3);    edge *edge3 = malloc(sizeof(edge) * 6);
    edge localEdge1[1] = { { .u = 0, .v = 1, .weight = 0.5F } }; 
    edge localEdge2[3] = { { .u = 0, .v = 1, .weight = 0.1F }, { .u = 1, .v = 2, .weight = 0.7F }, { .u = 2, .v = 0, .weight = 0.5F } };
    edge localEdge3[6] = { { .u = 0, .v = 1, .weight = 1.0F }, { .u = 0, .v = 2, .weight = 0.6F }, { .u = 0, .v = 3, .weight = 0.4F },  { .u = 1, .v = 2, .weight = 0.3f }, { .u = 1, .v = 3, .weight = 0.1f }, { .u = 2, .v = 3, .weight = 0.2f } };
	
    edge1 = localEdge1; edge2 = localEdge2; edge3 = localEdge3;
    
    graphs->graphs[0].list = edge0;graphs->graphs[0].num_nodes = 1; graphs->graphs[0].num_edges = 0; graphs->mst_weights[0] = 0.0F;
    graphs->graphs[1].list = edge1; graphs->graphs[1].num_nodes = 2;  graphs->graphs[1].num_edges = 1;   graphs->mst_weights[1] = 0.5F;
    graphs->graphs[2].list = edge2;  graphs->graphs[2].num_nodes = 3; graphs->graphs[2].num_edges = 3; graphs->mst_weights[2] = 0.6F;
    graphs->graphs[3].list = edge3; graphs->graphs[3].num_nodes = 4; graphs->graphs[3].num_edges = 6; graphs->mst_weights[3] = 0.7F;

    return graphs;
}

 

void freeGraphtest(test_graphs *ts) {
    for (int i = 0; i < ts->num_graphs; ++i)
	free(ts->graphs[i].list);
    free(ts->graphs);
    free(ts->mst_weights);
    free(ts);
}
