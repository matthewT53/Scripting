/*
	Name: Matthew Ta
	Date: 22/7/2015
	Description: Client for server
*/

/*
	Notes: still need to work on the messaging function, client hangs after it sends the message maybe because the server doesnt send a response.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <assert.h>

#include "client.h"

#define STN_BUFFER 500

// #define DEBUG

int main(void)
{
	struct addrinfo hints, *results;
	struct addrinfo *ptr, *exitPtr = NULL;
	int sock = 0, status = 0, foundAddress = FALSE;
	int bytesSent = 0, bytesRecv = 0;
	int exitClient = FALSE;
	char response[STN_BUFFER];
	int task = 0;
	int (*tasks[TOTAL_TASKS])(const int), task_success = 0;

	// set up the hints structure
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // Ipv4 or Ipv6
	hints.ai_socktype = SOCK_STREAM;

	// find the server information
	if (getaddrinfo(SERVER_ADDRESS, PORT_STR, &hints, &results) != 0){
		perror("getaddrinfo(): ");
		exitClient = TRUE;
	}

	// search the returned linked list for server details
	for (ptr = results; ptr != NULL && foundAddress != TRUE; ptr = ptr->ai_next){
		sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (sock < 0){
			perror("socket(): ");
			printf("Trying next node.\n");
		}
	
		else{
			status = connect(sock, ptr->ai_addr, ptr->ai_addrlen);
			if (status == -1){
				perror("connect(): ");
				close(sock);
			}
			
			else{
				foundAddress = TRUE;
				exitPtr = ptr;
			}

		}

	}
	
	if (exitPtr == NULL){
		printf("Failed to find a suitable node to connect to.\n");
		exitClient = TRUE;
	}

	freeaddrinfo(results);

	// assemble the menu
	if (createTaskMenuClient(tasks)){
		printf("Error creating task menu.\n");
		exitClient = TRUE;
	}
	
	// client main loop
	while (exitClient != TRUE){
		memset(response, 0, STN_BUFFER);
		printf(">: ");
		char buffer[BUFFER_SIZE], *strPtr = NULL;
		memset(buffer, 0, BUFFER_SIZE);
		strPtr = fgets(buffer, BUFFER_SIZE, stdin);
		
		// send data to the server
		bytesSent = send(sock, buffer, strlen(buffer), 0);
		if (bytesSent < 0){
			perror("send() error: ");
			exitClient = TRUE;
		}
		
		// determine what the user wants to do
		task = clientAction(buffer, sizeof(buffer));
		#ifdef DEBUG
			printf("task = %d.\n", task);
		#endif
		if (task){
			// do what the client wants
			task_success = (*tasks[task])(sock);
			if (!task_success){
				printf("Task failed to complete correctly.\n");
			}

			if (task == CLOSE_SERVER && task_success){
				break;
			}
		}

		else{
			// receive data from the server
			bytesRecv = recv(sock, response, sizeof(response), 0);
			if (bytesRecv <= 0){
				perror("recv() error: ");
				exitClient = TRUE;
			}

			response[bytesRecv] = NULL_CHAR;
			printf("server>: %s\n", response);
		}
	}
	
	if (task != CLOSE_SERVER) { close(sock); } // server closes master socket first
	return EXIT_SUCCESS;
}
