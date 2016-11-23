/*
    Name: Matthew Ta
    Date: 14/9/2015
    Description: Uses the graph interface to create good looking graphs
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "gConstants.h"

#define NUM_VERTICES 5

int ipAddrToV(char *ipAddr, Item info);

int main(void)
{
    Graph g = NULL;
    Item someData = malloc(sizeof(item) * NUM_VERTICES);
    // printf("Inside program.\n");
    strcpy(someData[0].IpAddr, "192.168.0.1");
    someData[0].deviceType = ROUTER;
    // printf("Avoided seg fault (1).\n");
    strcpy(someData[1].IpAddr, "192.168.0.11");
    someData[1].deviceType = LAPTOP;
    strcpy(someData[2].IpAddr, "192.168.0.23");
    someData[2].deviceType = PRINTER;
    strcpy(someData[3].IpAddr, "192.168.0.220");
    someData[3].deviceType = PHONE;
    strcpy(someData[4].IpAddr, "192.168.0.25");
    someData[4].deviceType = DESKTOP;

    g = newGraph(NUM_VERTICES);
	insertVData(g, someData);
    if (g != NULL) // remvoe this when finished implmenting
        printf("Graph worked\n");
    showGraph(g);
    connect(g, ipAddrToV("192.168.0.1", someData), ipAddrToV("192.168.0.11", someData)); // not an efficient method sicne function calls are expensive
    connect(g, ipAddrToV("192.168.0.1", someData), ipAddrToV("192.168.0.25", someData));
    connect(g, ipAddrToV("192.168.0.1", someData), ipAddrToV("192.168.0.220", someData));
    connect(g, ipAddrToV("192.168.0.23", someData), ipAddrToV("192.168.0.25", someData));
    printf("Connected: %s.\n", isConnected(g, ipAddrToV("192.168.0.25", someData), ipAddrToV("192.168.0.11", someData)) ? "TRUE" : "FALSE");
    showGraph(g);
    disconnect(g, ipAddrToV("192.168.0.1", someData), ipAddrToV("192.168.0.25", someData));
    printf("nV: %d and nE: %d\n", getnV(g), getnE(g));
    showGraph(g);

	printf("isPathDfs(): v = 1 to v = 2 %s\n", isPathDfs(g, 1, 2) ? "Is path" : "No path");

	connect(g, ipAddrToV("192.168.0.1", someData), ipAddrToV("192.168.0.23", someData));
	connect(g, ipAddrToV("192.168.0.11", someData), ipAddrToV("192.168.0.25", someData));
	printf("Finding minimal spanning tree.\n");
	Graph mst = findMst(g);
	insertVData(mst, someData);
	showGraph(mst);
	deleteGraph(mst);

	printf("Finding minimal spanning tree (Prim):\n");
	mst = findMstPrim(g);
	insertVData(mst, someData);
	showGraph(mst);
	deleteGraph(mst);

	printf("Finding shortest path from vertex: %d.\n", 0);
	mst = findShortestPath(g, 0);
	insertVData(mst, someData);
	showGraph(mst);
	deleteGraph(mst);

	printf("Testing connected components.\n");
	connectedComponents(g); // set the number of components
	printf("Has Euler path: %s\n", hasEulerPath(g) ? "TRUE" : "FALSE");
	printf("Has Euler circuit: %s\n", hasEulerCircuit(g) ? "TRUE" : "FALSE");
	printf("\n");	
	showGraph(g);
	printf("isPathBfs(): v = 0 to v = 4 %s\n", isPathBfs(g, 0, 4) ? "Is path" : "No path");
	printf("Has cycle from vertex: %d = %s.\n", 0, hasCycle(g, 0) ? "TRUE" : "FALSE"); 

	printf("Number of connected components: %d.\n", connectedComponents(g));
	printf("isPathDfs(): v = 1 to v = 2 %s\n", isPathDfs(g, 1, 2) ? "Is path" : "No path");
	printf("Has Hamilton path: %s\n", hasHamiltonPath(g) ? "TRUE" : "FALSE");
	printf("has Hamilton circuit: %s\n", hasHamiltonCircuit(g) ? "TRUE" : "FALSE");
	disconnect(g, 0, 1);
	disconnect(g, 2, 4);
	showGraph(g);
	printf("After disconnecting cc: %d\n", connectedComponents(g));
	disconnect(g, 1, 4);
	printf("cc = %d\n", connectedComponents(g));

	printf("Finding minimal spanning tree again.\n");
	mst = findMst(g);
	insertVData(mst, someData);
	showGraph(mst);
	deleteGraph(mst);

    deleteGraph(g);
    free(someData);
    return EXIT_SUCCESS;
}

int ipAddrToV(char *ipAddr, Item info) // O(n)
{
    int i = 0;
    for (i = 0; i < NUM_VERTICES; i++){
        if (strcmp(ipAddr, info[i].IpAddr) == 0){
            break;
        }
    }
    return i;
}
