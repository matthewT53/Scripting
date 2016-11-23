/*
	Name: Matthew Ta
	Date: 14/7/2015
	Description: Contains the function definitions from server.h
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <errno.h>
#include <assert.h>
#include <fcntl.h>
#include <dirent.h>
#include <time.h>

#include "server.h"
#include "sha_256.h" // library for generating hashes

#define STRING_LENGTH 250

#define TRUE 1
#define FALSE 0

#define DEBUG

int action(char *recvData, const int length)
{
	int returnValue = DONT_KNOW;
		
	if(strstr(recvData, UPLOAD) != NULL){
		memset(recvData, 0, length);
		strcpy(recvData, "upload");
		returnValue = FILE_TRANSFER_UPLOAD;
	}

	else if (strstr(recvData, DOWNLOAD) != NULL){
		memset(recvData, 0, length);
		strcpy(recvData, "download");
		returnValue = FILE_TRANSFER_DOWN;
	}

	else if (strstr(recvData, DIRECTORY) != NULL){
		memset(recvData, 0, length);
		strcpy(recvData, "open directory");
		returnValue = PRINT_SERVER_DIRECTORY;
	}

	else if (strstr(recvData, PRINT_MESS) != NULL){
		memset(recvData, 0, length);
		strcpy(recvData, "send a message");
		returnValue = MESSAGE;
	}

	else if (strstr(recvData, SHUTDOWN) != NULL){
		memset(recvData, 0, length);
		strcpy(recvData, "close server");
		returnValue = CLOSE_SERVER;
	}
	
	// the client wants to close the connection
	else{
		memset(recvData, 0, length);
		strcpy(recvData, "invalid input");
		returnValue = INVALID_INPUT;
	}

	return returnValue;
}

void createTaskMenu(void * (*tasks[])(void *))
{
	tasks[0] = NULL;
	tasks[1] = writeMessage;
	tasks[2] = takeFile;
	tasks[3] = giveFile;
	tasks[4] = directory;
}


void *writeMessage(void *threadArguments)
{
	int clientSock = 0;
	int successful = FALSE, bytesWritten = 0;
	FILE *fp = NULL;
	char filePath[STRING_LENGTH], message[MESSAGE_LENGTH];
	char *retPtr = NULL, *nullChar = NULL;
	int protocol = READY_FLAG, bytesSent = 0, bytesRecv = 0;
	int messageReceived = FALSE, bytes_written = 0, printOnce = FALSE;
	threadArgs *currentArgs;	

	// file stuff
	struct tm *timeInfo;
	time_t currentTime;
	char *timeStr = NULL;

	struct sockaddr clientAddr;
	int addrlen = 0;
	char address[INET_ADDRSTRLEN];
	
	// deal with the arguments, set the status of the socket to busy so that no other threads will interfere with this one
	currentArgs = (threadArgs *) threadArguments;
	currentArgs->sockStatus = BUSY;
	clientSock = currentArgs->sock;

	// construct the path for the message file
	memset(filePath, 0, STRING_LENGTH);
	memset(message, 0, MESSAGE_LENGTH);
	retPtr = strcat(filePath, MESSAGE_PATH);
	retPtr = strcat(filePath, MESSAGE_FILE);
	printf("File descriptor: %d and filePath = %s\n", clientSock, retPtr);
	
	// make a sure filePath is null terminated
	nullChar = strchr(filePath, NULL_CHAR);	
	assert(nullChar != NULL);

	// now open the file to to write the message
	fp = fopen(filePath, "ab");
	if (fp == NULL){
		perror("Couldnt open the file.");
		successful = FALSE;
	}
	
	else{
		// send a "ready to acquire message" flag to client
		printf("Waiting for client...\n");
		protocol = htonl(protocol);
		bytesSent = send(clientSock, &protocol, sizeof(int), 0);
		if (bytesSent == -1){
			printf("Error sending ready flag to client.\n");
			successful = FALSE;
		}

		else{
			// loop until message is received
			while (messageReceived != TRUE){
				memset(message, 0, MESSAGE_LENGTH);
				bytesRecv = recv(clientSock, message, sizeof(message), 0);
				if (bytesRecv == -1){
					// detect serious errors
					if (errno != EAGAIN){
						perror("recv(): ");
						messageReceived = TRUE;
					}
					
					if (printOnce != TRUE){
						printf("Still waiting for the message.\n");
						printOnce = TRUE;
					}
				}

				else if (bytesRecv == 0){
					// random stupid error
					messageReceived = TRUE;
				}

				else{
					// get the address of the client
					memset(&clientAddr, 0, sizeof(clientAddr));
					addrlen = sizeof(clientAddr);
					if (getpeername(clientSock, &clientAddr, &addrlen) == -1){
						perror("getpeername(): ");
					}

					inet_ntop(AF_INET, &(((struct sockaddr_in *) &clientAddr)->sin_addr), address, INET_ADDRSTRLEN);
					time(&currentTime);
					timeInfo = localtime(&currentTime);
					timeStr = asctime(timeInfo);
					// write the message to the file we opened
					printf("Message received from client on socket: %d.\n", clientSock);
					// bytes_written = fwrite(message, sizeof(message[0]), strlen(message), fp);

					bytes_written = fprintf(fp, "Address: %s\nTime: %sMessage: %s\n", address, timeStr, message);
					printf("Bytes Written: %d.\n", bytes_written);
					if (bytes_written <= 0){
						printf("Error writing to file.\n");
						perror("fwrite(): ");
					}
					// add some error checking
					messageReceived = TRUE;
					
				}
			}
		}

		fclose(fp);
	}
	
	// free the socket as it is no longer busy
	currentArgs->sockStatus = FREE;
	pthread_exit(NULL);
}

/*
	Notes:
	* two consec sends() clogs the data line so having a send, recv, send, recv is much better.
	* careful when using fseek() and rewind()

*/
void *giveFile(void *threadArguments)
{
	FILE *directory = NULL;
	char buffer[TRANSFER_SIZE], fileDirectory[TRANSFER_SIZE], fileName[TRANSFER_SIZE];
	// pre-send data stuff
	int preTransfer = 0, bytesSent = 0, clientResponse = 0, bytesRecv = 0, fileSize = 0, fsSend = 0;
	// socket stuff
	int clientSock = 0, exitThread = FALSE;
	threadArgs *sockArgs;
	// file transfer stuff
	int totalTransferred = 0;
	int dataRead = 0, seekResult = 0;
	int exitTransfer = FALSE;
	int receivedPath = FALSE;
	int receivedFileName = FALSE;
	int status = 0;

	// hashing stuff
	sha256_context *sha256 = NULL;
	char hash[HASH_SIZE];
	
	sockArgs = (threadArgs *) threadArguments;
	sockArgs->sockStatus = BUSY;
	clientSock = sockArgs->sock;

	// receive a directory from the client
	memset(fileDirectory, 0, TRANSFER_SIZE);
	while (!receivedPath){ // sometimes receives the filename as well. need to fix this
		bytesRecv = recv(clientSock, fileDirectory, sizeof(fileDirectory), 0);
		if (bytesRecv == -1){
			if (errno != EAGAIN){
				perror("recv(): ");
				receivedPath = TRUE; // set to true so we can break out of the loop
			}
		}

		else if (bytesRecv == 0){ // some stupid shit happened
			receivedPath = TRUE; // no we didnt really get the path but at this point we can do anything else
		}

		else{ // we may have gotton the path
			receivedPath = TRUE;
		}
	}	

	#ifdef DEBUG
		printf("Client sent path: %s\n", fileDirectory);
	#endif

	// check if the directory is valid
	if (strstr(fileDirectory, DOWNLOAD_PATH) == NULL){
		printf("Path requested is not a valid path.\n");
		exitThread = TRUE;
	}

	status = htonl(exitThread);
	if (send(clientSock, &status, sizeof(int), 0) <= 0){
		perror("send() :");
		exitThread = TRUE;
	}

	while (!receivedFileName){ // receive the filename from the client
		bytesRecv = recv(clientSock, fileName, sizeof(fileName), 0);
		if (bytesRecv == -1){
			if (errno != EAGAIN){
				perror("recv(): ");
				receivedFileName = TRUE;
			}
		}

		else if (bytesRecv == 0){
			receivedFileName = TRUE;
		}

		else{
			receivedFileName = TRUE;
		}
	}

	#ifdef DEBUG
		printf("Filename: %s\n", fileName);
	#endif

	strcat(fileDirectory, fileName);

	// open the file
	if (exitThread != TRUE){
		directory = fopen(fileDirectory, "rb");
		if (directory == NULL){
			perror("fopen(): \n");
		}

		// determine the file size
		fileSize = determineFileSize(directory);
		fsSend = htonl(fileSize);
		if (send(clientSock, &fsSend, sizeof(int), 0) <= 0){
			printf("Error sending file size to client.\n");
			exitTransfer = TRUE;
		}
		
		else{
			// start reading and send the file in chunks to the client
			sha256 = malloc(sizeof(sha256_context));
			assert(sha256 != NULL);

			sha256_start(sha256);
			exitTransfer = FALSE;
			while (totalTransferred < fileSize && exitTransfer != TRUE){
				// clear the buffer
				memset(buffer, 0, TRANSFER_SIZE);
				dataRead = fread(buffer, sizeof(buffer[0]), TRANSFER_SIZE - 1, directory);
				
				// check for errors
				if (dataRead <= 0){
					perror("fread() ");
					exitTransfer = TRUE;
				}

				// update the hash
				sha256_update(sha256, buffer, dataRead);

				// send the data
				bytesSent = send(clientSock, buffer, dataRead, 0);
				if (bytesSent <= 0){
					//we have a problem or theres no more data
					printf("Error sending data\n");
					perror("send(): ");
					exitTransfer = TRUE;
				}
				totalTransferred += bytesSent;
				#ifdef DEBUG
					printf("tt = %d and bs = %d\n", totalTransferred, bytesSent);
				#endif
			}

			if (totalTransferred < fileSize || exitTransfer == TRUE){
				printf("Failed to read the file or send the data correctly.\n");
			}
		
			else{
				printf("Client downloading has finished successfully.\n");
			}

			fclose(directory);
			
			// finialise the hash
			sha256_finish(sha256, hash);
			sha256_tohex(sha256, hash);

			memset(hash, 0, HASH_SIZE);
			strcpy(hash, sha256->buffer);
			#ifdef DEBUG
				printf("Hash: %s\n", hash);
			#endif
			usleep(TRANSFER_DELAY);
			if (send(clientSock, hash, HASH_SIZE, 0) <= 0){ // send the hash to the client
				perror("send() hash: ");
			}
		}

	}
	
	// free the thread and clean stuff
	sockArgs->sockStatus = FREE;
	pthread_exit(NULL);
}

// gets a file from the client
void *takeFile(void *threadArguments)
{
	char buffer[TRANSFER_SIZE], uploadDirectory[MAX_SIZE];
	int clientSock = 0;
	int clientResponse = 0, preTransfer = 0, bytesSent = 0, bytesRecv = 0;
	int exitThread = FALSE;
	int fileSize = 0, bytesWritten = 0, totalBytes = 0, seekResult = 0;
	FILE *upDirectory = NULL;
	int exitTransfer = FALSE;
	threadArgs *args;
	int reFileSize = FALSE;
	int reUploadDir = FALSE;

	// hash stuff
	int receivedHash = FALSE;
	char ourHash[HASH_SIZE]; 
	char hash[HASH_SIZE];

	args = (threadArgs *) threadArguments;
	clientSock = args->sock;
	args->sockStatus = BUSY;

	// receive a file size from the client , dont forget to verify
	while (!reFileSize){
		bytesRecv = recv(clientSock, &fileSize, sizeof(int), 0);
		if (bytesRecv == -1){
			if (errno != EAGAIN){
				perror("recv(): ");
				reFileSize = TRUE;
			}
		}

		else if (bytesRecv == 0){
			reFileSize = TRUE;
		}

		else{
			reFileSize = TRUE;
		}
	}

	fileSize = ntohl(fileSize);
	#ifdef DEBUG
		printf("fileSize = %d\n", fileSize);
	#endif

	// send a confirmation flag to the client
	preTransfer = CONFIRM_FLAG;
	preTransfer = htonl(preTransfer);
	if ((bytesSent = send(clientSock, &preTransfer, sizeof(int), 0)) <= 0 && exitThread != TRUE){
		perror("Error sending confirmation flag send(): ");
		exitThread = TRUE;
	}

	// receive a destination directory for the file, dont forget to verify
	memset(uploadDirectory, 0, MAX_SIZE);
	while (!reUploadDir){
		bytesRecv = recv(clientSock, uploadDirectory, sizeof(uploadDirectory), 0);
		if (bytesRecv == -1){
			if (errno != EAGAIN){
				perror("recv(): ");
				reUploadDir = TRUE;
			}
		}

		else if (bytesRecv == 0){
			reUploadDir = TRUE;
		}

		else{
			reUploadDir = TRUE;
		}
	}

	#ifdef DEBUG
		printf("Path upload is: %s\n", uploadDirectory);
	#endif
	
	// validate the path
	if (strstr(uploadDirectory, UPLOAD_PATH) == NULL){
		printf("Requested path is invalid.\n");
		exitThread = TRUE;
	}
	
	if (exitThread != TRUE){
		uploadDirectory[bytesRecv] = NULL_CHAR;
		int reBuffer = FALSE;
		// create a file in the directory to write to
		upDirectory = fopen(uploadDirectory, "wb");
		if (upDirectory == NULL){
			perror("fopen(): ");
		}

		else{
			// start writing to the file 
			while (totalBytes < fileSize && exitTransfer != TRUE){
				reBuffer = FALSE;
				while (!reBuffer){ // receive the file buffer from client
					memset(buffer, 0, MAX_SIZE);
					bytesRecv = recv(clientSock, buffer, sizeof(buffer), 0);
					if (bytesRecv == -1){
						if (errno != EAGAIN){
							perror("recv(): ");
							reBuffer = TRUE;
						}
					}

					else if (bytesRecv == 0){
						reBuffer = TRUE;
					}

					else{
						reBuffer = TRUE;
					}
				}
				
				bytesWritten = fwrite(buffer, sizeof(buffer[0]), bytesRecv, upDirectory);
				if (bytesWritten <= 0){
					perror("Error fwrite(): ");
					exitTransfer = TRUE;
				}	

				totalBytes += bytesWritten;
				#ifdef DEBUG
					printf("tb = %d and bw = %d and fs = %d\n", totalBytes, bytesWritten, fileSize);
				#endif
			}

			if (totalBytes < fileSize || exitTransfer == TRUE){
				printf("Error copying file.\n");
			}
			
			else{
				printf("File was successfully copied to the server.\n");
			}
	
			fclose(upDirectory);
			
			while (!receivedHash){
				bytesRecv = recv(clientSock, hash, HASH_SIZE, 0);
				if (bytesRecv == -1){
					if (errno != EAGAIN){
						perror("recv(): ");
						receivedHash = TRUE;
					}
				}

				else{
					receivedHash = TRUE;
				}
			}

			hashFile(uploadDirectory, fileSize, ourHash);
			#ifdef DEBUG
				printf("Hash recv: %s\n", hash);
				printf("Our hash: %s\n", ourHash);
			#endif
			if (strcmp(hash, ourHash) != 0){
				printf("%s", HASHES_NOT_EQUAL_MESSAGE);
			}
		}

	}

	// free the resources and clean up
	args->sockStatus = FREE;
	pthread_exit(NULL);
}

void *directory(void *threadArguments)
{
	char directory[BUFFER_SIZE], *directoryPtr = NULL;
	int clientSock = 0;
	int bytesSent = 0, bytesRecv = 0, clientResponse = 0;
	int exitThread = FALSE;
	threadArgs *myArgs = NULL;
	struct dirent *currentDirectory = NULL;
	DIR *dir = NULL;
	int receivedDir = FALSE;
	
	// task setup
	myArgs = (threadArgs *) threadArguments;
	clientSock = myArgs->sock;
	myArgs->sockStatus = BUSY;

	// receive the directory from the client
	while (!receivedDir){
		bytesRecv = recv(clientSock, directory, BUFFER_SIZE, 0);
		if (bytesRecv == -1){
			if (errno != EAGAIN){
				perror("recv(): ");
				receivedDir = TRUE;
			}
		}

		else{
			receivedDir = TRUE;
		}
	}
	// validate the path to prevent client from searching private directories
	if (strstr(directory, DIRECTORY_PATH) == NULL){
		printf("Invalid directory.\n");
		exitThread = TRUE;
	}

	// loop through and send the directory to the client
	if (exitThread != TRUE){
		directory[bytesRecv] = NULL_CHAR;
		// open the directory
		dir = opendir(directory);
		#ifdef DEBUG
			printf("dir = %s\n", directory);
		#endif
		// search through the directory
		if (dir != NULL){
			while (currentDirectory = readdir(dir)){
				directoryPtr = currentDirectory->d_name;
				bytesSent = send(clientSock, directoryPtr, strlen(directoryPtr), 0);

				// sleep for TRANSFER_DELAY microseconds to prevent buffer clogging
				usleep(TRANSFER_DELAY);
				if (bytesSent <= -1){
					printf("Error sending directory to client.\n");
				}
			}

			// close the directory
			closedir(dir);
		}

		memset(directory, 0, BUFFER_SIZE);
		strcpy(directory, END_DIR);
		if (send(clientSock, directory, strlen(directory), 0) <= 0){
			perror("send() ");
		}
	}
	
	// free resources
	myArgs->sockStatus = FREE;
	pthread_exit(NULL);
}

int determineFileSize(FILE *f)
{
    int pos;
    int end;

    pos = ftell (f);
    fseek (f, 0, SEEK_END);
    end = ftell (f);
    fseek (f, pos, SEEK_SET);

    return end;
}


