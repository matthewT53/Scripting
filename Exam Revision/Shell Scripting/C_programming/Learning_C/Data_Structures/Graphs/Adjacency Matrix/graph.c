/*
	Name: Matthew Ta
	Date: 27/9/2015
	Description: Interface implementation for a directed graph
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "graph.h"
#include "priorityQueue.h"
#include "queue.h"
#include "stack.h"

#define CONNECTED 1
#define NO_CONNECTION 0

#define VISITED 1
#define UNVISITED 0

// constants for the shortest path
#define MAX_WEIGHT 100
#define NO_WEIGHT -1
#define USED_EDGE -1
#define INF 1000
#define NOT_ASSIGNED -1

// boolean constants
#define TRUE 1
#define FALSE 0

typedef struct _graphRep{
	int nV; // total number of vertices
	int nE; // total number of edges
	Edge **edges; // adj matrix representation of connections
	int **tc; // reachability matrix (transitive closure)
	int **wt; // weight matrix
} graphRep;

typedef struct _gEdge{
	Vertex v;
	Vertex w;
	Weight wt;
} gEdge;

void setArray(int *a, const int value, const int size);

// creates a new graph
Graph newGraph(Vertex nV)
{
	Graph newGraph = malloc(sizeof(graphRep));
	int i = 0;

	assert(newGraph != NULL);
	newGraph->nV = nV;
	newGraph->nE = 0; // initially there are no edges
	
	newGraph->edges = malloc(sizeof(Edge *) * nV); // create nV pointers
	newGraph->wt = malloc(sizeof(int *) * nV); // create nV weight ptrs
	assert(newGraph->edges != NULL);

	// allocate 10 vertices for each ptr
	for (i = 0; i < nV; i++){
		newGraph->edges[i] = malloc(sizeof(Vertex) * nV);
		newGraph->wt[i] = malloc(sizeof(int) * nV);
		assert(newGraph->edges[i] != NULL && newGraph->wt[i] != NULL);
		
		// clear each memory block
		memset(newGraph->wt[i], NO_WEIGHT, sizeof(int) * nV); 
		memset(newGraph->edges[i], 0, sizeof(Vertex) * nV); 
	}

	newGraph->tc = NULL;
	return newGraph;
}

// frees a graph
void deleteGraph(Graph g)
{
	int i = 0;

	// free the edges
	for (i = 0; i < g->nV; i++){
		free(g->edges[i]); 
	}

	free(g->edges);
		
	// free the transitive closure matrix
	if (g->tc != NULL){
		for (i = 0; i < g->nV; i++){
			free(g->tc[i]);
		}
	}

	free(g->tc);

	// free the weight matrix
	if (g->wt != NULL){
		for (i = 0; i < g->nV; i++){
			free(g->wt[i]);
		}
	}

	free(g->wt);

	free(g);
}

// adds a vertex creating a directed path
void addEdge(Graph g, Vertex v, Vertex w) 
{
	if ((v >= 0 && v < g->nV) && (w >= 0 && w < g->nV) && !g->edges[v][w]){ g->edges[v][w] = CONNECTED; g->nE++; }
}

// removes connection between two vertices
void removeEdge(Graph g, Vertex v, Vertex w)
{
	if ((v >= 0 && v < g->nV) && (w >= 0 && w < g->nV) && g->edges[v][w]) { g->edges[v][w] = NO_CONNECTION; g->nE--; }
}

// works only for paths of length 2
int reachability(Graph g, Vertex v, Vertex w)
{	
	void createClosure(Graph g);
	if (g->tc == NULL){ // create a new reachability matrix
		createClosure(g);
	}

	return g->tc[v][w];
}

void createClosure(Graph g) // O(v^3) time complexity
{
	int s = 0, t = 0, i = 0;

	// allocate memory for the tc matrix
	g->tc = malloc(sizeof(int *) * g->nV);
	for (i = 0; i < g->nV; i++){
		g->tc[i] = malloc(sizeof(Vertex) * g->nV);
	}

	// construct the tc matrix
	for (s = 0; s < g->nV; s++){
		for (t = 0; t < g->nV; t++){
			g->tc[s][t] = g->edges[s][t];
		}
	}

	// Warshall's algorithm
	for (i = 0; i < g->nV; i++){ // we want a transitive connection s->i->t
		for (s = 0; s < g->nV; s++){
			for (t = 0; t < g->nV; t++){
				if (g->tc[s][i] && g->tc[i][t]) { g->tc[s][t] = 1; }
			}
		}
	}

}

/*
	Note:
	* this is not Dijkstra's algorithm but instead it is prims
	* Dijkstra's algorithm uses a queue
	* fixed the bug where v was used for ege relaxation instead of curV
*/
	
Graph shortestPath(Graph g, Vertex v)
{
	Graph mst = newGraph(g->nV); // create a new mst graph
	Queue q = newQueue(); // create a new queue
	int *visitedVertices = malloc(sizeof(Vertex) * g->nV);
	int *dist = malloc(sizeof(int) * g->nV); // create the distance array
	int *pred = malloc(sizeof(int) * g->nV); // create the predecessor array, stores vertices passed through
	int total = 0, i = 0;
	Vertex curV = 0, w = 0;

	assert(visitedVertices != NULL && dist != NULL && pred != NULL);
	
	// clear all the memory blocks
	setArray(visitedVertices, UNVISITED, g->nV);
	setArray(dist, INF, g->nV);
	setArray(pred, -1, g->nV);

	visitedVertices[v] = VISITED; // mark the starting vertex as visited
	dist[v] = 0;
	
	enQueue(q, v); // add the starting vertex to the queue

	while ( !isEmptyQueue(q) ){
		curV = deQueue(q); // remvoe first element from queue
		for (w = 0; w < getnV(g); w++){
			if (g->wt[curV][w] == NO_WEIGHT) continue;
			if (dist[curV] + g->wt[curV][w] < dist[w]){ // edge relaxation
				dist[w] = dist[curV] + g->wt[curV][w];
				pred[w] = curV;
				enQueue(q,w);
			}
		}
	}
	

	// add the appropriate edges
	for (i = 0; i < g->nV; i++){
		if (pred[i] != NOT_ASSIGNED){
			addEdge(mst, pred[i], i);
			total += dist[i];
		}
	}

	deleteQueue(q);
	free(dist);
	free(pred);
	printf("Total = %d.\n", total);

	return mst;
}

/*
	Note:
	* change priority queue implementation
*/
Graph shortestPathPQ(Graph g, Vertex v)
{
	Graph mst = newGraph(g->nV);
	int *dist = malloc(sizeof(int) * g->nV); // create the distance array
	int *pred = malloc(sizeof(int) * g->nV); // create the predecessor array, stores vertices passed through
	PQueue q = newPQueue(); // create a new priority queue
	Vertex currentVertex = 0, w = 0;
	int i = 0;
	int total = 0;

	assert(dist != NULL && pred != NULL);
	
	// clear all the memory blocks
	setArray(dist, INF, g->nV);
	setArray(pred, -1, g->nV);

	dist[v] = 0;
	for (i = 0; i < g->nV; i++){
		joinPQueue(q, i, dist[i]);
	}
	
	reorder(q, NO_UPDATE, NO_UPDATE);
	while ( !isEmptyPQ(q) ){ // while priority queue is not empty
		currentVertex = leavePQueue(q);
		for (w = 0; w < getnV(g); w++){
			if (g->wt[currentVertex][w] == NO_WEIGHT) continue;
			if (g->wt[currentVertex][w] + dist[currentVertex] < dist[w]){
				dist[w] = g->wt[currentVertex][w] + dist[currentVertex];
				pred[w] = currentVertex;
				reorder(q, w, dist[w]); // updates the priority of vertex w as well
			}
		}
		reorder(q, NO_UPDATE, NO_UPDATE);
	}

	// construct the mst graph
	for (i = 0; i < getnV(g); i++){
		if (pred[i] != NOT_ASSIGNED){
			addEdge(mst, pred[i], i);		
			total += dist[i];
		}
	}

	printf("Total = %d.\n", total);
	deletePQueue(q);
	free(dist);
	free(pred);
	
	return mst;
}

int isPathDfs(Graph g, Vertex v, Vertex w)
{
	int isPath = FALSE;
	Stack s = newStack(); // create a new stack
	Vertex currentVertex = 0;
	int *visited = calloc(g->nV, sizeof(int)); // allocate + init to 0
	int i = 0;

	assert(visited != NULL);
	push(s, v); // push first vertex onto stack
	visited[v] = TRUE; // mark it as visited

	while ( !isEmptyStack(s) ){ // still have vertices to traverse
		currentVertex = pop(s); // get a vertex from the stack
		printf("Visiting: %d\n", currentVertex);
		visited[currentVertex] = TRUE; // mark it as visited
		if (currentVertex == w) { isPath = TRUE; }
		for (i = 0; i < g->nV; i++){ // search for a vertex we haven't visited
			if (g->edges[currentVertex][i] && !visited[i]){ // ignore pendants
				push(s, i); // push vertex onto stack
				visited[i] = TRUE;
			}
		}
	}

	free(visited);
	deleteStack(s);
	return isPath;
}

int isPathBfs(Graph g, Vertex v, Vertex w)
{
	int isPath = FALSE;
	Queue q = newQueue(); // create a new queue
	Vertex curV = 0;
	int *visited = calloc(g->nV, sizeof(int)); // allocate + init to 0
	int i = 0;

	assert(visited != NULL);
	enQueue(q, v);
	visited[v] = TRUE;

	while ( !isEmptyQueue(q) ){ // still have vertices to traverse
		curV = deQueue(q); // get a vertex from the queue
		printf("Visiting: %d.\n", curV);
		visited[curV] = TRUE; // mark it as visited
		if (curV == w) { isPath = TRUE; } 
		for (i = 0; i < g->nV; i++){ // find vertices to add to queue
			if (g->edges[curV][i] && !visited[i]){ // found a vertex to add
				enQueue(q, i); // add it to queue
				visited[i] = TRUE; // mark it as visited
			}
		}
	}	
	free(visited);
	deleteQueue(q);
	return isPath;
}

void addWeights(Graph g)
{
	int i, j;

	for (i = 0; i < g->nV; i++){
		for (j = 0; j < g->nV; j++){
			if (g->edges[i][j] == CONNECTED){
				g->wt[i][j] = rand() % MAX_WEIGHT;
			}
		}
	}
}

void setArray(int *a, int value, int max)
{	
	int i = 0;
	for ( i = 0; i < max; i++){ a[i] = value; } 
}

void showTc(Graph g)
{
	int i, j;
	
	for (i = 0; i < g->nV; i++){
		for (j = 0; j < g->nV; j++){
			printf("%d", (g->tc[i][j]) ? 1 : 0);
		}
		printf("\n");
	}
}

void showGraph(Graph g)
{
	int i, j;
	
	for (i = 0; i < g->nV; i++){
		for (j = 0; j < g->nV; j++){
			printf("%d", (g->edges[i][j]) ? CONNECTED : NO_CONNECTION);
		}
		printf("\n");
	}
}

void showWeights(Graph g)
{
	int i = 0, j = 0;
	for (i = 0; i < g->nV; i++){
		for (j = 0; j < g->nV; j++){
			printf("%3d", g->wt[i][j]);
		}
		printf("\n");
	}
}

int getnV(Graph g)
{
	return g->nV;
}

int getnE(Graph g)
{
	return g->nE;
}

