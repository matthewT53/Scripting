/*
	Name: Matthew Ta
	Date: 23/7/2015
	Description: Client to connect to cool server.
*/

// #include "server.h" // some functions used by the server can be re-used
#include "constants.h"

#define TOTAL_TASKS 6

// determine what the client wants to do
int clientAction(char *recvData, const int length);

// send a message to server
int message(const int socket);

// upload a file ot the server
int upload(const int socket);

// download a file from the server
int download(const int socket);

// show server's working directory
int printDirectory(const int socket);

// shutdown the server
int closeServer(const int socket);

// create the task menu for client
int createTaskMenuClient(int (*tasks[])(const int));

// determine the size of a file
int determineFileSize(FILE *f);

// some helper functions
void removeNewLine(char *str); // removes a new line char from the str





