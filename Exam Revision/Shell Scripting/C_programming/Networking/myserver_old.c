/*
	Name: Matthew Ta
	Date: 14/7/2015
	Description: This is a multithreaded messaging and file transfer server

	For reference: 

	Notes:
	* Tried poll, couldnt get two clients to interact with server simultaneously
	* Could only connect two clients and after the first client closes, only then will the server start interacting ith the second client
	* Exit the client using cntrl-c instead of cntrl-z to prevent hanging the server
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <errno.h>
#include <fcntl.h>

#include "server.h"

// server constants
#define PORT 3456
#define QUEUE_SIZE 32
#define TIME_OUT 3 * 60 * 1000 // in milliseconds
#define NUMBER_FDS 200
#define LOG_FILE "home/beaniestyle/Documents/logs.txt"
#define UPLOAD_PATH "home/beaniestyle/Documents/uploads/"

// boolean constants
#define TRUE 1
#define FALSE 0

// data transfer constants
#define BUFFER_SIZE 2048
#define NULL_CHAR 0

int main(int argc, char *argv[])
{
	int listenSocket = 0;
	int rsock = 0, on = 1;
	int timeout = 0, currentNumSockets = 0;
	struct sockaddr_in addr;
	int closeServer = FALSE;
	// declare the poll stuff
	struct pollfd fds[NUMBER_FDS];
  	int nfds = 1, i = 0;
	// accepting new conditions
	int newSocket = 0, closeConnection = FALSE;
	// data transfer
	char buffer[BUFFER_SIZE];
	int bytesRecv = 0;//, bytesSent = 0;
	int compressPoll = FALSE;
	// interaction with the client
	int clAction = DONT_KNOW;
	int actionSuccess = FALSE;

	// create a socket to listen for connections
	listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket < 0){
		perror("socket() failed");
		exit(-1);
	}

	// allow the socket to be reuseable
	/*
		Note: on needs to be declared with a value of 1
	*/
	rsock = setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));

	if (rsock < 0){
		perror("setsockopt() failed");
		close(listenSocket);
		exit(-1);
	}

	// set sockets to be nonblocking
	rsock = ioctl(listenSocket, FIONBIO, (char *)&on);
	if (rsock < 0){
		perror("ioctl() failed");
		close(listenSocket);
		exit(-1);
	}

	// bind the socket
	memset(&addr, 0, sizeof(addr));
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port        = htons(PORT);
	
	rsock = bind(listenSocket, (struct sockaddr *)&addr, sizeof(addr));
	if (rsock < 0){
		perror("bind() failed");
		close(listenSocket);
		exit(-1);
	}

	// set up the socket to listen for connections
	rsock = listen(listenSocket, QUEUE_SIZE);
	if (rsock < 0){
		perror("listen() failed");
		close(listenSocket);
		exit(-1);
	}

	// initialise the poll structures
	memset(fds, 0, sizeof(fds));
	fds[0].fd = listenSocket;
	fds[0].events = POLLIN;
	timeout = TIME_OUT;

	// loop through the polls
	while (closeServer != TRUE){
		printf("Poll() Searching for data and connections...\n");
		rsock = poll(fds, nfds, timeout);
		
		currentNumSockets = nfds;
		// detect errors with poll()
		if (rsock < 0){
			perror("Poll processing error.");
			closeServer = TRUE;
		}

		// detect a timeout 
		if (rsock == 0){
			perror("Poll timed out");
			closeServer = TRUE;
		}
		
		// one or more fds are listening or readable
		else{
			for (i = 0; i < currentNumSockets && closeServer != TRUE; i++){
				if(fds[i].revents == 0){
					continue;
				}
				// determine if listening or active connection
				// if return value is not pollin then log this and exit the server
				if (fds[i].revents != POLLIN){
					perror("Not POLLIN");
					// call a logging function
					closeServer = TRUE;
				}

				if (fds[i].fd == listenSocket){
					// listening descriptor is readable
					printf("Client has connected.\n");
					printf("Listening socket is readable.\n");
					newSocket = 0;
					// accept all incoming connections
					while (newSocket != -1){
						newSocket = accept(listenSocket, NULL, NULL);
						
						// there has been an error
						if (newSocket < 0){
							// if accept fails with a EWOULDBLOCK then we have accepted all the connections
							if (errno != EWOULDBLOCK){
								printf("Accept failed.\n");
								closeServer = TRUE;
							}
								
							break;
						}

						else{
							printf("New connection accepted...\n");
							fcntl(newSocket, F_SETFL, O_NONBLOCK);
							fds[nfds].fd = newSocket;
							fds[nfds].events = POLLIN;
							nfds++;
						}
					}

					// printf("Broke out.\n");

				}

				else{
					// a current connection is trying to send data
					closeConnection = FALSE;
					while (closeConnection != TRUE){
						// receive some data from a pipe
						clAction = DONT_KNOW;
						memset(buffer, 0 , BUFFER_SIZE);
						bytesRecv = recv(fds[i].fd, buffer, BUFFER_SIZE, 0);
						buffer[bytesRecv] = NULL_CHAR;
						if (bytesRecv < 0){
							if (errno != EWOULDBLOCK){
								perror("recv() failed");
								closeConnection = TRUE;
							}
						}

						// check if connection has been closed
						else if (bytesRecv == 0){
							printf("Connection has been closed.\n");
							closeConnection = TRUE;
		
						}
					
						// connection is fine
						else{
							// do w/e with the data
							printf("Received data of length: %d from client on socket fd: %d.\n", bytesRecv, fds[i].fd);
							printf("Trying to figure out what the client wants...\n");
							printf("Clients response: %s.\n", buffer);
							// determine what the client wants to do
							clAction = action(buffer, strlen(buffer));
							printf("The client wants to: %s.\n", buffer);
							char *message = "Thank you for responding.";
							send(fds[i].fd, message, strlen(message), 0);
							// try to perform the task
							actionSuccess = performTask(clAction);
							printf("Task %s.\n", (actionSuccess) ? "Successful" : "Failed");
					
						}


					}

					// if the connection was closed, mark this is the poll structure
					if (closeConnection){
						printf("Removing the disconnected client from poll.\n");
						close(fds[i].fd);
						fds[i].fd = -1;
						compressPoll = TRUE;
					}

			
				} // end of the else statement
	
		

			} // end of for loop
		

			// compress poll array removing discon clients
			if (compressPoll){
				compressArray(fds, &nfds);
				printf("Compressed polls.\n");
			}
		} // end of other else statement

	} // end of server

	// clean up the file descriptors we used
	cleanUp(fds, nfds);

	return EXIT_SUCCESS;
}
