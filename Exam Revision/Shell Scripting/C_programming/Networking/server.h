/* 
	Name: Matthew Ta
	Date: 14/7/2015
	Desciption: This header file contains prototypes for the interface functions for the server.
*/

#include "constants.h"

// arguments to be passed into each thread
typedef struct _threadArgs{
	int sock; // socket ID
	int sockStatus; // whether socket is free or busy in a thread
} threadArgs;

// what does the client want to do
int action(char *recvData, const int length);

// assembles an array of pointers to functions
void createTaskMenu(void * (*functions[])(void *));

// save a (encrypted) message to the server
void *writeMessage(void *threadArguments);

// receive a file from the client
void *takeFile(void *threadArguments);

// give a file to the client
void *giveFile(void *threadArguments);

// send the working directory to the client
void *directory(void *threadArguments);

// determine the size of a file
int determineFileSize(FILE *f);
