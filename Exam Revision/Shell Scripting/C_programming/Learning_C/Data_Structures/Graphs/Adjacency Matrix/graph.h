/*
	Name: Matthew Ta
	Date: 27/9/2015
	Description: Graph adj matrix representation interface (directed graph)
*/

typedef struct _graphRep *Graph;
typedef int Vertex;
typedef int Edge;
typedef int Weight;

Graph newGraph(Vertex nV); // creates a new graph
void deleteGraph(Graph g); // deletes a graph

void addEdge(Graph g, Vertex v, Vertex w); // adds an edge between vertex v and vertex w
void removeEdge(Graph g, Vertex v, Vertex w); // removes the edge between vertex v and vertex w

int reachability(Graph g, Vertex v, Vertex w); // is v reachable from w
void showTc(Graph g); // shows the transitive matrix
void showGraph(Graph g); // shows the graph
void showWeights(Graph g); // shows the weight of the graph

// shortest paths
void addWeights(Graph g);
Graph shortestPath(Graph g, Vertex v); // Dijkstra's algorithm
Graph shortestPathPQ(Graph g, Vertex v); // shortest path using a priority queue

// graph Traversals
int isPathDfs(Graph g, Vertex v, Vertex w); // DFS for path
int isPathBfs(Graph g, Vertex v, Vertex w); // BFS for path

// predicate functions
int getnV(Graph g); 
int getnE(Graph g);




