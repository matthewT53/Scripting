/*
	Name: Matthew Ta
	Date: 17/7/2015
	Description: Multithreaded messaging and file transfer server using Epoll 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <assert.h>
#include <pthread.h>

#include "server.h"

// server constants
#define SERVER_PORT 13542
#define PORT_STR "13542"
#define QUEUE_SIZE 32

// boolean constants
#define TRUE 1
#define FALSE 0

// Epoll stuff
#define MAX_EVENTS 64

// file transfer
#define FILE_LENGTH 350

// pthread stuff
#define MAX_SOCKETS 500

int main(int argc, char *argv[])
{
	int masterSocket = 0, sock = 0, status = 0;
	int sockbinded = FALSE, closeServer = FALSE;
	int reuseSock = 1;
	int clientAction = 0;
	int resultAction = 0;
	struct addrinfo hints, *servInfo, *ptr;

	// epoll stuff
	int efd = 0, n = 0, i = 0;
	struct epoll_event event;
	struct epoll_event *events;

	// epoll listening stuff
	struct sockaddr in_addr;
	socklen_t in_len;
	int infd = 0;
	char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
	int incomingConnections = FALSE;

	// epoll reading data stuff
	int dataRead = 0;
	char buffer[BUFFER_SIZE];
	int readStatus = FALSE;

	// writing data
	int sentBytes = 0;
	int endOfConnection = FALSE;
	FILE *fp = NULL;
	char filePath[FILE_LENGTH], *retPtr = NULL;

	// pthread stuff
	void * (*tasks[NUMBER_TASKS])(void *) = {NULL};
	pthread_t child_thread;
	int currentThread = 0;
	threadArgs currentSock[MAX_SOCKETS];
	unsigned int numberSockets = 0;

	// find who is at the other end of the socket
	struct sockaddr clientAddr;
	int addrlen = 0;
	char address[INET_ADDRSTRLEN];

	// time stuff
	time_t currentTime;
	struct tm *timeInfo;
	char *timeStr = NULL;
	
	// clear the structs so we can fill it with information
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_UNSPEC; // ipv4 or ipv6
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; // bind to the ip of the host the program is running on
	
	// use the magical function that fills out information for us
	if ((status = getaddrinfo(NULL, PORT_STR, &hints, &servInfo)) != 0){
		printf("Error getting host details.\n");
		fprintf(stderr, "getaddrinfo(): %s", gai_strerror(status));
	}
	
	// use the first result which was returned to us from the results of the getaddrinfo()
	for (ptr = servInfo; ptr != NULL && sockbinded != TRUE; ptr = ptr->ai_next){
		masterSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		// make the socket reuseable
		if (setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, &reuseSock, sizeof(int)) == -1){
			perror("setsockopt: ");
		}

		if (masterSocket == -1){
			printf("Couldn't create socket for this node, looking for others....\n");
		}

		else{
			printf("Successfully created the socket.\n");
			sock = bind(masterSocket, ptr->ai_addr, ptr->ai_addrlen);
			if (sock == -1){
				printf("Couldn't bind to this socket.\n");
			}

			else{
				printf("Successfully binded to the socket.\n");
				sockbinded = TRUE;
			}
		}	

	}

	if (ptr == NULL){
		printf("Could not find any nodes to bind to.\n");
		closeServer = TRUE;
	}

	freeaddrinfo(servInfo);

	// make the socket non-blocking
	fcntl(masterSocket, F_SETFL, O_NONBLOCK);
	printf("Socket has been set to non-blocking mode.\n");
	
	// put the socket to listening mode
	sock = listen(masterSocket, QUEUE_SIZE);
	if (sock == -1){
		perror("Listen(): ");
		closeServer = TRUE;
	}

	// set up the epoll
	efd = epoll_create1(0);
	if (efd == -1){
		perror("Epoll_create(): ");
		closeServer = TRUE;
	}

	event.data.fd = masterSocket;
	event.events = EPOLLIN | EPOLLET;
	sock = epoll_ctl(efd, EPOLL_CTL_ADD, masterSocket, &event);
	if (sock == -1){
		perror("epoll_ctl(): ");
		closeServer = TRUE;
	}

	// create a buffer where events are returned
	events = calloc(MAX_EVENTS, sizeof(event));

	// set the pthreads stuff
	createTaskMenu(tasks);
	
	// main server loop
	while (closeServer != TRUE && numberSockets < MAX_SOCKETS){
		n = epoll_wait(efd, events, MAX_EVENTS, -1);
		for (i = 0; i < n; i++){
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN))){
			      fprintf (stderr, "epoll error\n");
			      close (events[i].data.fd);
			      continue;
			}

			else if (events[i].data.fd == masterSocket){
				// there are incoming connections
				incomingConnections = FALSE;
				while (incomingConnections != TRUE){
					in_len = sizeof(in_addr);
					infd = accept(masterSocket, &in_addr, &in_len);
					if (infd == -1){
						// all connections have been accepted
						if ((errno == EAGAIN) || (errno == EWOULDBLOCK)){
							incomingConnections = TRUE;
						}

						else{
							perror("Accept(): ");
							incomingConnections = TRUE;
						}
					}

					else{
						sock = getnameinfo (&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
						if (sock == 0){
							printf("Accepted connection on file descriptor: %d and client: %s from port: %s.\n", infd, hbuf, sbuf);
							// infd is the id of the socket
							currentSock[infd].sock = infd;
							currentSock[infd].sockStatus = FREE;
							numberSockets++;
						}

						// make socket non-blocking
						fcntl(infd, F_SETFL, O_NONBLOCK);

						event.data.fd = infd;
                  				event.events = EPOLLIN | EPOLLET;
                  				sock = epoll_ctl (efd, EPOLL_CTL_ADD, infd, &event);
						if (sock == -1){
						      perror ("epoll_ctl");
						      incomingConnections = TRUE; // might need to change this
						}
						
					}
					
				} // end of while loop to accept incoming connections
				
				// value of infd at this point is -1
				
			} // end of else if

			else{
				// there is data on some of the file descriptors waiting to be read
				printf("\nDetected activity on socket: %d.\n", events[i].data.fd);
				// printf("currentSock[events[i].data.fd].sock = %d.\n", currentSock[events[i].data.fd].sock);
				// printf("currentSock[events[i].data.fd].sockStatus = %d.\n", currentSock[events[i].data.fd].sockStatus);
				if (currentSock[events[i].data.fd].sockStatus == FREE){
					// this is done only if no threads are using the current socket
					readStatus = FALSE;
					endOfConnection = FALSE;
					while (readStatus != TRUE){
						memset(buffer, 0, BUFFER_SIZE);
						dataRead = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
						if (dataRead == -1){
							if (errno != EAGAIN){
								perror("recv(): ");
							}
							readStatus = TRUE;
						}

						else if (dataRead == 0){
							// the client has closed the connection
							readStatus = TRUE;
							endOfConnection = TRUE;

						}

						else{
							// echo the data back to the client
							printf("Received %d bytes from client on socket descriptor: %d.\n", (int) strlen(buffer), events[i].data.fd);
							buffer[strlen(buffer)] = NULL_CHAR;
							printf("Client sent this: %s\n", buffer);

							// set up the directory for file writing
							memset(filePath, 0, FILE_LENGTH);
							retPtr = strcat(filePath, LOG_PATH);
							retPtr = strcat(filePath, LOG_FILE);
							fp = fopen(filePath, "ab");

							// check for errors opening the file
							if (fp == NULL){
								perror("fopen(): ");
							}
	
							else{
								memset(&clientAddr, 0, sizeof(clientAddr));
								addrlen = sizeof(clientAddr);
								if (getpeername(events[i].data.fd, &clientAddr, &addrlen) == -1){
									perror("getpeername(): ");
								}

								inet_ntop(AF_INET, &(((struct sockaddr_in *) &clientAddr)->sin_addr), address, INET_ADDRSTRLEN);
								// log everything the user enters on the terminal
								// fwrite(buffer, sizeof(buffer[0]), strlen(buffer), fp);
								time(&currentTime);
								timeInfo = localtime(&currentTime);
								timeStr = asctime(timeInfo);
								fprintf(fp, "Address: %s\nTime: %sEntered: %s\n", address, timeStr, buffer);
								fclose(fp);
							}
	
							// decide what the client wants to do
							clientAction = action(buffer, strlen(buffer));
							printf("The client wants to: %s\n", buffer);
						
							if (clientAction != INVALID_INPUT){
								printf("Creating thread to serve request.\n");
								// printf("Some addresses:\ntasks[clientAction] = %p\n*tasks[clientAction] = %p.\n", tasks[clientAction], *tasks[clientAction]);
								// how is tasks[clientAction] the same as *tasks[clientAction] ?
								resultAction = pthread_create(&child_thread, NULL, tasks[clientAction], (void *) &currentSock[events[i].data.fd]);
								if (resultAction){
									perror("pthread_create(): \n");
								}
							
							}

							else{
								sentBytes = send(events[i].data.fd, buffer, strlen(buffer), 0);
							}

							if (sentBytes == -1){
								perror("send() failed: ");
								readStatus = TRUE;
							}

							printf("Sent %d bytes to the client.\n", sentBytes);
						}
					
					} // end of while
		
					if (endOfConnection){
						printf("Closed connection on file descriptor: %d.\n", events[i].data.fd);
						close(events[i].data.fd);
					}
				} // end of intermediate condition


			} // end of else
		
		} // end of for loop
	} // end of main server loop

	free(events);
	close(masterSocket);
	pthread_exit(NULL);

	printf("Server has closed.\n");
	
	return EXIT_SUCCESS;
}
