#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <corecrt_math.h>
#include <stdbool.h>
#include "graph.h"
#include "disjoint-set.h"


 
 
float maximumWeight = 0.0f; // global variable to hold maximum weight of each MST 



// Kruskal's algorithm: calculate and returns the weight of an MST 
float kruskal(graph *graph) {
    // Running MST weight
    float mst_weight = 0.0f;

    // sort edges of graph by weight
    sortGraphEdge(graph);


    ds_forest *f = makeForest(graph->num_nodes);
    

    for (int n = 0; n < graph->num_nodes; n++)
        makeSet(f, n);

    for (int e = 0; e < graph->num_edges; e++) {
        int node_u = graph->list[e].u;
        int node_v = graph->list[e].v;
        if (find(f, node_u) != find(f, node_v)) {
            mst_weight += graph->list[e].weight;
	    // Conditional necessary for multiple runs
	    if (graph->list[e].weight > maximumWeight)
		maximumWeight = graph->list[e].weight;
            ds_union(f, node_u, node_v);
        }
    }

    // Free memory of disjoint set forest
    burnForest(f);

    // Return MST weight
    return mst_weight;
}


bool gaurdForInvalidArguments(int orchestrationSwitch, int numberOfVertices, int numberOfTrials,  int* value)
{
	// Check against invalid args
	if (orchestrationSwitch > 4 || orchestrationSwitch < 0)
		fprintf(stderr, "orchestrationSwitch %d does not exist  \ncontinue in normal mode...\n", orchestrationSwitch);
	else if (numberOfVertices <= 1) {
		fprintf(stderr, "numberOfVertices should be greater than 1\n");
		return true;
	}
	else if (numberOfTrials <= 0) {
		fprintf(stderr, "numberOfTrials should be greater than 0\n");
		return true;
	}
 	return false;
}

bool testOnPredefinedGraphs(const int orchestrationSwitch, int* value)
{
	// orchestrationSwitch 1: verfy correctness of code by running on a predefined graphs precalculated MST weights and compare  
	if (orchestrationSwitch == 1) {
		test_graphs *res = testGraph();
		for (int n = 0; n < res->num_graphs; n++) { 
			if (fabsf(res->mst_weights[n] - kruskal(&res->graphs[n])) < 0.00001) // check if calculated weight by using Kruska's algorithem is equal to the predefined weight
				printf("Test result %d: Ok\n", n);
			else
				printf("Test result %d: FAIL\n", n);
		}
		*value = 0;
		return true;
	}
	return false;
}


bool testToVerifyGraphGeneration(const int orchestrationSwitch, int* value)
{
	// orchestrationSwitch 2: verify the correctness of graph generation and the disjoint set implementation  
    if (orchestrationSwitch !=  2) {return false;}
		testsDisjointSet(); testsGraph();
		*value = 0;
		return true;
   }


bool prinOutAverageRuntime(const int orchestrationSwitch, const int numberOfVertices, const int numberOfTrials, int totalTime, int* value)
{
	// orchestrationSwitch 4:  Print out the average runtime  
	if (orchestrationSwitch == 4) {
		int msec = totalTime * 1000 / CLOCKS_PER_SEC;
		printf("{%d, %f}\n", numberOfVertices, (float) msec / numberOfTrials);
		*value = 0;
		return true;
	}
	return false;
}

bool printOutMaxEdgeWeight(const int orchestrationSwitch, int* value)
{
	// orchestrationSwitch 3:  Print out the maximum edge weight of MSTs 
	if (orchestrationSwitch == 3) {
		printf("Maximum Edge Weight: %f\n", maximumWeight);
		*value = 0;
		return true;
	}
	return false;
}



void printOutTheResults(const int numberOfVertices, const int numberOfTrials, float totalWeight)
{
	float averageWeight = totalWeight / numberOfTrials;
	// Print out the results
	printf("%f %d %d\n", averageWeight, numberOfVertices, numberOfTrials   );
}





int main( ) {

	
	 // initial parameters
    const int orchestrationSwitch =5;
    const int numberOfVertices = 16;
    const int numberOfTrials =5;

	
	
	// gaurd for checking the initial parameters
    int Gaurdvalue; if (gaurdForInvalidArguments(orchestrationSwitch, numberOfVertices, numberOfTrials,  &Gaurdvalue)) exit(0);


	
    // orchestrationSwitch 1: verfy correctness of code by running on a predefined graphs precalculated MST weights  
    int value1; if (testOnPredefinedGraphs(orchestrationSwitch, &value1)) return value1;

	
    // orchestrationSwitch 2: verify the correctness of graph generation and the disjoint set implementation  
    int value2;  if (testToVerifyGraphGeneration(orchestrationSwitch, &value2)) return value2;

	 
 
    int totalTime = 0; 
    srand(time(NULL)); // Seeding the rand function with the current time
    float totalWeight = 0.0;
    for (int i = 0; i < numberOfTrials; ++i) {   
	graph *gr = generateGraphAtRandom( numberOfVertices); // generate the graph
	const clock_t startTime = clock();
	totalWeight += kruskal(gr); // Kruskal's algorithm
	totalTime += clock() - startTime;  // get the running time of the Kruskal's algorithm
	free(gr->list);
    free(gr);
    }

	
	
	
	// orchestrationSwitch 3:  Print out the maximum edge weight of MSTs 
	int value3;  if (printOutMaxEdgeWeight(orchestrationSwitch, &value3)) return value3;


    // orchestrationSwitch 4:  Print out the average runtime  
    int value4; if (prinOutAverageRuntime(orchestrationSwitch, numberOfVertices, numberOfTrials, totalTime, &value4)) return value4;

	

	// print out the results
    printOutTheResults(numberOfVertices, numberOfTrials, totalWeight);

	
    return 0;
}



