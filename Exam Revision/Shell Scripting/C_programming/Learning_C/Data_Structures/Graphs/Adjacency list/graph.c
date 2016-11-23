/*
    Name: Matthew Ta
    Date: 14/9/2015
    Description: Graph GADT functions
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <assert.h>

#include "graph.h"
#include "queue.h"
#include "stack.h"

#define ADJACENT_VERTEX 1
#define NOT_ASSIGNED -1
#define VISITED 1
#define UNVISITED 0

// constants for weights
#define MAX_DISTANCE 100
#define MAX_WEIGHT 1000
#define NO_WEIGHT -1
	
typedef struct _gNode *Node;

// adjacency list representation for a graph
typedef struct _graphRep{
    Node *vertices; // array of ptrs to nodes
    Vertex nV; // number of vertices
    Edge nE; // number of edges
	Item *vData; // data for each vertex
	int nC; // # of components
	int *components; // array of ptrs to nodes of the same compo
	int **weights; // weights of each edge
} graphRep;

typedef struct _gNode{
	Vertex vNum;
	Node next;
} gNode;

typedef struct _gEdge{
	Vertex v;
	Vertex w;
	Weight wt; // quantity of the edge e.g distance, time etc
} gEdge;

void setArray(int *a, int value, int max);
void markVisited(int *visitedArray, Vertex v); // sets a vertex as visited

// functions for edges and MST
gEdge *createEdges(Graph g, int *numEdges); // creates edges from the vertex connections
Edge findBestEdge(gEdge *eArray, Vertex *vArray, const int totalEdges); // finds the best edge to add to MST
void insertEdge(Graph g, gEdge e); // inserts an edge into the graph
void removeEdge(Graph g, gEdge e); // removes an edge from a graph

// sorting edges
void sortEdges(gEdge *ue, const int lo, const int high); // sorts the edges in ue into se
int partition(gEdge *array, const int lo, const int hi);
void swap(gEdge *array, const int i, const int j);

void addWeights(Graph g); // adds weights to the graph

Graph newGraph(Vertex nV)
{
	Graph g = malloc(sizeof(graphRep));
	Node *newVertices = malloc(sizeof(Node) * nV);
	assert(g != NULL && newVertices != NULL);

	int i = 0;
	
	g->vertices = newVertices;
	g->nV = nV;
	g->nE = 0; // initially there are no edges
	
	for (i = 0; i < nV; i++){
		g->vertices[i] = NULL;
	}

	g->components = malloc(sizeof(int) * nV);
	assert(g->components != NULL);
	setArray(g->components, NOT_ASSIGNED, nV);
	g->nC = nV; // initially there are no edges so there are nV components
	
	g->weights = malloc(sizeof(int *) * nV);
	for (i = 0; i < nV; i++){
		g->weights[i] = malloc(sizeof(int) * nV);
		setArray(g->weights[i], NO_WEIGHT, nV);
	}

	addWeights(g); // add some weights to the edges

	return g;
}

void insertVData(Graph g, Item data)
{
	int i = 0;
	g->vData = malloc(sizeof(Item) * g->nV);
	
	for (i = 0; i < g->nV; i++){
		g->vData[i] = &data[i];
	}
}

void addWeights(Graph g)
{
	int i = 0, j = 0;
	for (i = 0; i < g->nV; i++){
		for (j = 0; j < g->nV; j++){
			if (isConnected(g, i, j)){
				g->weights[i][j] = rand() % MAX_DISTANCE;
			}
		}	
	}
}

void deleteGraph(Graph g) // O(n^2)
{
    Node currentV = NULL, tempNode = NULL;
    int i = 0;

    for (i = 0; i < g->nV; i++){
        currentV = g->vertices[i];
        while (currentV != NULL){
            tempNode = currentV;
            currentV = currentV->next;
            free(tempNode);
        }
    }

	free(g->vData); // prevent memory leaks
	free(g->components);
    free(g);
}

// v1 now points to v2 and v2 now points to v1 in the adjacency table
void connect(Graph g, Vertex v1, Vertex v2) // O(1)
{
    Node n = NULL;

	Node newNode(Vertex v); // copies vertex data into a new node and returns the new node 
	void addNode(Node *vl, Node n); // adds a new node into the vertex list
    
	if ( !isConnected(g, v1, v2) ){ // don't connect if the two vertices are already connected
		printf("Connecting vertex: %d with vertex: %d\n", v1, v2);
		n = newNode(v2);
		addNode(&g->vertices[v1], n);
		n = newNode(v1);
		addNode(&g->vertices[v2], n);
		g->nE++;
	}
}

Node newNode(Vertex v)
{
	Node n = malloc(sizeof(gNode));
	assert(n != NULL);
	n->vNum = v;
	n->next = NULL;
	return n;
}

void addNode(Node *vl, Node n)
{
	n->next = *vl;
	*vl = n;
}

void disconnect(Graph g, Vertex v1, Vertex v2) // O(n)
{
	void deleteNode(Graph g, Vertex v, Vertex w); // deletes a vertex w from vlist[v]
	printf("Disconnecting v = %d and w = %d\n", v1, v2);
	deleteNode(g, v1, v2);
	deleteNode(g, v2, v1);
    g->nE--;
}

void deleteNode(Graph g, Vertex v, Vertex w) // also need to account for the first ndoe in the lsit
{
	Node cur = NULL, prev = NULL;
	cur = g->vertices[v];

	if (cur != NULL){
		if (cur->vNum != w){
			while (cur != NULL){
				if (cur->vNum == w){
					prev->next = cur->next;
					free(cur);
					break;
				}
				prev = cur;
				cur = cur->next;
			}
		}

		else{ // deleting first node
			g->vertices[v] = cur->next;
			free(cur);
		}
	}
}

// checks if two vertices are neighbours (adjacent)
int isConnected(Graph g, Vertex v, Vertex w)
{
    int connected = FALSE;

	int findNode(Graph g, Vertex v, Vertex w); // finds a vertex w in the vertex list v

	connected = findNode(g, v, w);
	if (connected){
		connected = findNode(g, w, v);
	}

    return connected;
}

int findNode(Graph g, Vertex v, Vertex w)
{
	Node cur = g->vertices[v];
	int returnValue = FALSE;

	while (cur != NULL){
		if (cur->vNum == w){
			returnValue = TRUE;
			break;
		}
		cur = cur->next;
	}
	return returnValue;
}


int isPathDfs(Graph g, Vertex v, Vertex w)
{
	Stack s = newStack();
	int *visitedVertices = malloc(sizeof(int) * g->nV); // create the visited array
	Node currentV, searchV;
	int isPath = FALSE;
	Vertex vertexNum = 0;
	
	assert(visitedVertices != NULL);
	setArray(visitedVertices, UNVISITED, g->nV);
	push(s, v);
	markVisited(visitedVertices, v);
	currentV = g->vertices[v];

	while ( !isEmptyStack(s) ){
		searchV = currentV;
		while ( searchV != NULL && visitedVertices[searchV->vNum] ){
			searchV = searchV->next;
		}

		if (searchV == NULL){
			pop(s);
			if ( (vertexNum = getTop(s) != -1) ){ currentV = g->vertices[vertexNum]; }
		}

		else{
			currentV = g->vertices[searchV->vNum];
			if (currentV->vNum == w) { isPath = TRUE; }
			markVisited(visitedVertices, searchV->vNum);
			push(s, searchV->vNum);
		}

	}
		
	free(visitedVertices);
	deleteStack(s);
	return isPath;
}


int isPathBfs(Graph g, Vertex v, Vertex w)
{
	Node currentV = g->vertices[v], searchV = NULL;
	Vertex vertexNum = v;
	Queue q = newQueue();
	int isPath = FALSE;
	int *visitedArray = malloc(sizeof(int) * g->nV);

	assert(visitedArray != NULL);
	setArray(visitedArray, UNVISITED, g->nV);
	markVisited(visitedArray, vertexNum); // mark first vertex as visited
	enQueue(q, vertexNum);

	while ( !isEmptyQueue(q) ) {
		currentV = g->vertices[deQueue(q)];
		showQueue(q);
		printf("At vertex: %d\n", currentV->vNum);
		searchV = currentV;
		while ( searchV != NULL ){
			if ( !visitedArray[searchV->vNum] ){
				printf("Enqueued vertex: %d\n", searchV->vNum);
				enQueue(q, searchV->vNum);
				markVisited(visitedArray, searchV->vNum);
				if (searchV->vNum == w){
					isPath = TRUE;
				}
			}

			searchV = searchV->next;
		}

	}
	
	free(visitedArray);
	deleteQueue(q);
	return isPath;
}

void markVisited(int *visitedArray, Vertex v)
{
	visitedArray[v] = VISITED;
}

/*
	Notes:
	* utilises DFS
	* locates if there is a cycle from a specific vertex

*/
int hasCycle(Graph g, Vertex v)
{
	int cycle = FALSE;
	Stack s = newStack();
	Node currentV, searchV;
	Vertex vertexNum = 0;
	int *visitedArray = malloc(sizeof(int) * g->nV);
	int moves = 0;

	currentV = g->vertices[v];
	push(s, v);
	assert(visitedArray != NULL);
	setArray(visitedArray, UNVISITED, g->nV);
	markVisited(visitedArray, v);

	while ( !isEmptyStack(s) ){
		searchV = currentV;
		showStack(s);
		while ( searchV != NULL && visitedArray[searchV->vNum] ){
			if (searchV->vNum == v && moves > 1) { cycle = TRUE; }
			searchV = searchV->next;
		}

		if (searchV == NULL){
			pop(s);
			vertexNum = getTop(s);
			if ( vertexNum != -1 ) { currentV = g->vertices[vertexNum]; moves--; }
		}

		else{
			currentV = g->vertices[searchV->vNum];
			push(s, searchV->vNum);
			markVisited(visitedArray, searchV->vNum);
			moves++;
		}
	
	}

	free(visitedArray);
	deleteStack(s);
	return cycle;
}

// very expensive operation
int connectedComponents(Graph g)
{
	Stack s = NULL;
	int *visitedArray = malloc(sizeof(int) * g->nV);
	Node curV = NULL, searchV = NULL;
	Vertex startvNum = 0;
	int cc = 0;

	int findVertex(Graph g); // finds a vertex not in the current component of the graph
	void assignComponents(Graph g, int *vArray, int cNum); // assigns a component to each vertex in the graph g
	
	assert(visitedArray != NULL);
	setArray(g->components, NOT_ASSIGNED, g->nV); // reset to detect new components

	while ( startvNum < g->nV ){ // run while there a vertices in diff components
		s = newStack();
		setArray(visitedArray, UNVISITED, g->nV);
		push(s, startvNum);
		curV = g->vertices[startvNum];
		markVisited(visitedArray, startvNum); // O(1)

		// do the DFS at a vertex
		while ( !isEmptyStack(s) ){
			searchV = curV;
			while ( searchV != NULL && visitedArray[searchV->vNum] ){ // O(V)
				searchV = searchV->next;
			}

			if ( searchV == NULL ){ // all vertices around the cur vertex have been visited
				pop(s);
				if ( getTop(s) != -1 ){ curV = g->vertices[getTop(s)]; }
			}

			else{
				curV = g->vertices[searchV->vNum];
				push(s, searchV->vNum);
				markVisited(visitedArray, searchV->vNum);
			}
		}

		// find a vertex not in the visited array
		cc++;
		assignComponents(g, visitedArray, cc);
		startvNum = findVertex(g);
		deleteStack(s); // reset the stack
	}
	
	g->nC = cc;
	free(visitedArray);
	return cc;
}

int hasEulerPath(Graph g)
{
	Node cur = NULL;
	int isEulerPath = FALSE, oddVertices = 0, degree = 0, i = 0;

	// test if the graph is connected
	if ( getnC(g) == 1 ){ // only connected if the # components is 1
		while ( i < g->nV ){
			cur = g->vertices[i];
			degree = 0;
			while ( cur != NULL ){
				degree++;
				cur = cur->next;
			}

			if ( degree % 2 != 0 ){
				oddVertices++;
			}

			i++;
		}
		
		if ( oddVertices == 2 ){ // if 2 vertices have odd degree then it is an euler path
			isEulerPath = TRUE;
		}
	}
	return isEulerPath;
}

int hasEulerCircuit(Graph g)
{
	Node cur = NULL;
	int i = 0, degree = 0, isEulerCircuit = TRUE;

	if ( getnC(g) == 1 ){ // grpah is connected
		while ( i < g->nV ){
			cur = g->vertices[i];
			degree = 0;
			while ( cur != NULL ){
				degree++;
				cur = cur->next;
			}

			if ( degree % 2 != 0 ){ // one vertex is not even
				isEulerCircuit = FALSE;
				break;
			}
			i++;
		}
	}

	return isEulerCircuit;
}


int hasHamiltonPath(Graph g)
{
	Node cur = NULL;
	int i = 0, degree = 0, verticesDegreeOne = 0;
	int isHamilton = TRUE;

	if (getnC(g) == 1){ // similiar to Euler, can only be hamilton if connected
		while (i < g->nV){
			cur = g->vertices[i];
			degree = 0; // degree of each vertex
			while (cur != NULL){
				
				cur = cur->next;
			}

			if (degree == 1){ 
				verticesDegreeOne++;
			}

			if (degree > 2 || verticesDegreeOne > 2){
				isHamilton = FALSE;
				break;
			}
			i++;
		}
	}

	return isHamilton;
}

// produces the wrong solution in some cases
int hasHamiltonCircuit(Graph g) // NP hard
{
	Node cur = NULL;
	int isHamCircuit = TRUE, i = 0, degree = 0;
			
	if (getnC(g) == 1){
		while (i < g->nV){
			cur = g->vertices[i];
			degree = 0;
			while (cur != NULL){
				degree++;
				cur = cur->next;
			}

			if (degree < (g->nV / 2)){
				isHamCircuit = FALSE;
				break;
			}
			i++;
		}
	}
	return isHamCircuit;
}

/*
	Notes:
	* finds Mst using Kruskal's algorithm
	* O(VE)
	* requires a dfs to check for cycles
*/
Graph findMst(Graph g)
{
	Graph mst = newGraph(g->nV); // create an empty minimal spanning tree
	gEdge *edgeArray = NULL, *sortedEdges = NULL;
	int curEdge = 0, totalEdges = 0;
	
	edgeArray = createEdges(g, &totalEdges);
	sortedEdges = edgeArray;
	sortEdges(sortedEdges, 0, g->nE - 1); // quicksort

	while (curEdge < totalEdges && curEdge < g->nE){
		insertEdge(mst, sortedEdges[curEdge]);
		if (hasCycle(mst, sortedEdges[curEdge].v)){ // dfs to find cycle
			removeEdge(mst, sortedEdges[curEdge]);
		}
		curEdge++;
	}
	
	return mst;
}

/*
	Notes:
	* finds mst using Prim's algorithm
	* O(VE)
*/
Graph findMstPrim(Graph g)
{
	Graph mst = newGraph(g->nV);
	Vertex *visitedV = malloc(sizeof(Vertex) * g->nV); // mark as 1 if visited and 0 otherwise
	gEdge *edgeArray = NULL;
	int verticesAdded = 0, totalEdges = 0;
	Edge ePos = 0;

	edgeArray = createEdges(g, &totalEdges); // create the array of edges based on g

	sortEdges(edgeArray, 0, totalEdges - 1);

	setArray(visitedV, UNVISITED, g->nV);	
	visitedV[0] = VISITED;
	verticesAdded++;	

	while (verticesAdded < g->nV){
		ePos = findBestEdge(edgeArray, visitedV, totalEdges);
		verticesAdded++;
		insertEdge(mst, edgeArray[ePos]); // insert the edge into the mst
	}
	
	return mst;
}

/*
	Notes:
	* Similar to Prim's algorithm
	* so similiar to the adj matrix, the path may not be the shortest

*/
Graph findShortestPath(Graph g, Vertex v)
{
	Graph mst = newGraph(g->nV); // create an empty mst graph
	Queue q = newQueue(); // create a new queue
	int *distance = malloc(sizeof(int) * g->nV); // create a distance array
	int *pred = malloc(sizeof(int) * g->nV); // create a pred array
	Vertex currentVertex = 0, w = 0;
	Node curV = NULL;
	gEdge edgeToInsert;
	int i = 0;
	
	setArray(distance, MAX_WEIGHT, g->nV); // set all the distances to infinite
	setArray(pred, NOT_ASSIGNED, g->nV); // no vertices have any preds

	distance[v] = 0;

	for (i = 0; i < g->nV; i++){
		enQueue(q, i);
	}
	
	while ( !isEmptyQueue(q) ){
		currentVertex = deQueue(q);
		curV = g->vertices[currentVertex];
		printf("currentVertex = %d.\n", currentVertex);
		while (curV != NULL){
			w = curV->vNum;
			if (distance[currentVertex] + g->weights[currentVertex][w] < distance[w]){ // edge relaxation
				distance[w] = distance[currentVertex] + g->weights[currentVertex][w];
				pred[w] = currentVertex;
			}
			curV = curV->next;
		}
	}
	
	// fill in the mst graph
	for (i = 0; i < g->nV; i++){
		if (pred[i] != NOT_ASSIGNED){
			edgeToInsert.v = pred[i];
			edgeToInsert.w = i;
			insertEdge(mst, edgeToInsert);
		}
	}

	return mst;
}

// the edges are sorted in order of weight so the first edge that this function finds will be the smallest valid edge
Edge findBestEdge(gEdge *eArray, Vertex *vArray, const int totalEdges)
{
	Edge curE, bestE = NOT_ASSIGNED;

	for (curE = 0; curE < totalEdges; curE++){
		if ( vArray[eArray[curE].v] && !vArray[eArray[curE].w] ){ // v is an element of vArray and w is not
			bestE = curE;
			vArray[eArray[curE].w] = VISITED;
			break;
		}

		if ( vArray[eArray[curE].w] && !vArray[eArray[curE].v] ){ // w is an element of vArray and v is not
			bestE = curE;
			vArray[eArray[curE].v] = VISITED;
			break;
		}
	}

	return bestE;
}

gEdge *createEdges(Graph g, int *numEdges)
{
	gEdge *e = malloc(sizeof(gEdge) * g->nE);
	int *alreadyAdded = malloc(sizeof(Vertex) * g->nV); // prevent adding duplicate edges
	int curEdge = 0;
	Node cur = NULL;
	Vertex v = 0; // keeps track of current vertex

	srand(time(NULL));
	setArray(alreadyAdded, UNVISITED, g->nV);
	
	while (v < g->nV){
		alreadyAdded[v] = VISITED;
		cur = g->vertices[v];
		while (cur != NULL){
			if (alreadyAdded[cur->vNum] == UNVISITED){
				e[curEdge].v = v; 
				e[curEdge].w = cur->vNum; 
				e[curEdge++].wt = g->weights[v][cur->vNum];
			}
			cur = cur->next;
		}
		v++;
	}

	*numEdges = curEdge;
	return e;
}

gEdge fixRelaxComparison(gEdge reversedEdge, int startDistance)
{
	gEdge e;
	if (startDistance >= MAX_WEIGHT){
		e.v = reversedEdge.w;
		e.w = reversedEdge.v;
		e.wt = reversedEdge.wt;
	}

	else{
		e = reversedEdge;
	}
	return e;
}


void insertEdge(Graph g, gEdge e) // wrapper for connect()
{
	connect(g, e.v, e.w);
}

void removeEdge(Graph g, gEdge e) // wrapper for disconnect()
{
	disconnect(g, e.v, e.w);
}

void sortEdges(gEdge *array, const int lo, const int high)
{
    int pivot = 0;
    if (lo >= high){ // base case
        return;
    }

    pivot = partition(array, lo, high);
    sortEdges(array, lo, pivot - 1);   
    sortEdges(array, pivot + 1, high);
}

int partition(gEdge *array, const int lo, const int high)
{
    Weight value = array[lo].wt;
    int i = lo + 1, j = high;
    
    while (TRUE){
        while (array[i].wt <= value && i < j){ // find an element larger than pivot
            i++;
        }

        while (value < array[j].wt && j > i){ // find element smaller than pivot
            j--;
        }

        if (i == j){
            break; // array has been paritioned
        }

        swap(array, i, j); // swap smallest and largest
    }

    // at this point the part of the array has been paritioned
    j = array[i].wt < value ? i : i - 1;
    swap(array, lo, j);
    return j;
}

void swap(gEdge *array, const int i, const int j)
{
	gEdge temp;
	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
}

void setArray(int *a, int value, int max)
{	
	int i = 0;
	for ( i = 0; i < max; i++){ a[i] = value; } 
}

int findVertex(Graph g)
{
	Vertex v;
	for ( v = 0; v < g->nV; v++ ){
		if ( g->components[v] == NOT_ASSIGNED ){
			break;
		}
	}
	return v;
}

void assignComponents(Graph g, int *vArray, int cNum)
{
	int i = 0;
	for ( i = 0; i < g->nV; i++ ){
		if ( vArray[i] == VISITED ){
			g->components[i] = cNum;
		}
	}
}

void showGraph(Graph g)
{
    Node currentV;
    int i = 0, connections = 0;
    char *intToAddr(int dev); // returns the string form of a device

    for (i = 0; i < g->nV; i++){
        connections = 0;
        currentV = g->vertices[i];
        printf("%s is connected to:\n", g->vData[i]->IpAddr);
        while (currentV != NULL){
            printf("\t%s which is a %s.\n", g->vData[currentV->vNum]->IpAddr, intToAddr(g->vData[currentV->vNum]->deviceType));
            currentV = currentV->next;
            connections++;
        }
    
        if (connections == 0){
            printf("No connections.\n");
        }
    } 

    printf("\n");
}

char *intToAddr(int dev)
{
    char *str = NULL;
    if (dev == ROUTER)
        str = "Router";
    else if (dev == PHONE)
        str = "Phone";
    else if (dev == DESKTOP)
        str = "Desktop";
    else if (dev == LAPTOP)
        str = "Laptop";
    else if (dev == PRINTER)
        str = "Printer";
    else
        str = NULL;
    
    return str;
}

Vertex getnV(Graph g)
{
    return g->nV;
}

Edge getnE(Graph g)
{
    return g->nE;
}

int getnC(Graph g)
{
	return g->nC;
}

