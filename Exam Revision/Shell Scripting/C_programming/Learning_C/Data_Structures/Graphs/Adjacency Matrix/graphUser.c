/*
	Name: Matthew Ta
	Date: 27/9/2015
	Description: Use the graph interface for a directed graph 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph.h"

#define NUM_VERTICES 10
#define MAX_CONNECTIONS 30

int main(void)
{
	Graph g = newGraph(NUM_VERTICES);
	int i = 0;
	Vertex v, w;

	srand(time(NULL));
	for (i = 0; i < MAX_CONNECTIONS; i++){
		v = rand() % 10;
		w = rand() % 10;
		addEdge(g, v, w);
	}

	addWeights(g);
	printf("Original adj matrix: \n");
	showGraph(g);

	printf("Reachability: %d to %d = %s.\n", 0, 5, reachability(g, 0, 5) ? "TRUE" : "FALSE");	
	showTc(g);

	printf("Shortest path from vertex 0:\n");
	Graph mst = shortestPath(g, 0);
	showGraph(mst);
	// showWeights(g);
	deleteGraph(mst);

	printf("Shortest path from vertex 0 (pq):\n");
	mst = shortestPathPQ(g, 0);
	showGraph(mst);
	//showWeights(g);
	deleteGraph(mst);

	printf("Testing traversal methods:\n");
	int path = isPathDfs(g, 0, 5);
	printf("Path (DFS) = %s.\n", path ? "TRUE" : "FALSE");
	path = isPathBfs(g, 0, 5);
	printf("Path (BFS) = %s.\n", path ? "TRUE" : "FALSE");

	deleteGraph(g);
	return EXIT_SUCCESS;
}
