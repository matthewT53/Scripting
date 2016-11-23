/*
    Name: Matthew Ta
    Date: 14/9/2015
    Description: Interface function prototypes for the graph GADT
*/

#include "userData.h"
#include "gConstants.h"

typedef struct _graphRep *Graph;

typedef int Vertex;
typedef int Edge;
typedef int Weight;

Graph newGraph(Vertex nV); // create a new graph

void insertVData(Graph g, Item data); // insert data about each vertex into the graph

void addVertex(Graph g, Item newData); // adds a new vertex into the graph

void connect(Graph g, Vertex v1, Vertex v2); // add a link or connection between two vertices

void disconnect(Graph g, Vertex v1, Vertex v2); // disconnects two vertices

void deleteGraph(Graph g); // frees the graph structure

void showGraph(Graph g); // hows the vertices and all the connections

int isPathDfs(Graph g, Vertex v, Vertex w); // returns true if there is a path

int isPathBfs(Graph g, Vertex v, Vertex w); // returns true if there is a path between v and w

// functions which use DFS
int isConnected(Graph g, Vertex v, Vertex w); // returns true if there is an edge between these two vertices

int hasCycle(Graph g, Vertex v); // returns true if the graph has a cycle

int connectedComponents(Graph g); // Assigns each vertex to a component and returns the # of components

// Hamilton/Euler path and circuits
int hasEulerPath(Graph g);
int hasEulerCircuit(Graph g);

int hasHamiltonPath(Graph g); // NP hard
int hasHamiltonCircuit(Graph g);

// minimal spanning tree
Graph findMst(Graph g); // uses Kruskal's algorithm
Graph findMstPrim(Graph g); // uses Prim's algorithm

// shortest path
Graph findShortestPath(Graph g, Vertex v); // returns a mst with shortest path from vertex v

// predicate functions

Vertex getnV(Graph g); // returns # vertices
Edge getnE(Graph g); // returns # edges
int getnC(Graph g);




