/*
	Name: Matthew Ta
	Date: 25/7/2015
	Description: Implementations of the function prototypes in client.h.
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

#include "client.h"
#include "sha_256.h"

#define DEBUG

void removeNewLine(char *str); // removes a new line char from the str

int clientAction(char *recvData, const int length)
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
		strcpy(recvData, "closing server");
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

int createTaskMenuClient(int (*tasks[])(const int))
{
	tasks[0] = NULL;
	tasks[1] = message;
	tasks[2] = upload;
	tasks[3] = download;
	tasks[4] = printDirectory;
	tasks[5] = closeServer;

	return 0;
}

int closeServer(const int socket)
{
	sha256_context *sha256 = malloc(sizeof(sha256_context));
	char password[MAX_SIZE], hash[HASH_SIZE];
	int shutdown = FALSE;

	assert(sha256 != NULL);
	printf("Enter the password: ");
	fgets(password, MAX_SIZE, stdin);
	removeNewLine(password);

	// hash the password
	sha256_start(sha256);
	sha256_update(sha256, password, strlen(password));
	sha256_finish(sha256, hash);
	sha256_tohex(sha256, hash);

	memset(hash, 0, HASH_SIZE);
	strcpy(hash, sha256->buffer);
	#ifdef DEBUG
		printf("Hash: %s\n", hash);
	#endif
	if (send(socket, hash, HASH_SIZE, 0) <= 0){ // send the hashed password to the server
		perror("send() hash: ");
	}

	if (recv(socket, &shutdown, sizeof(int), 0) <= 0){ // receive the result of the shutdown command
		perror("recv(): ");
	}

	shutdown = ntohl(shutdown); // change the byte ordering
	#ifdef DEBUG
		printf("shutdown = %s\n", (shutdown) ? "SUCCESS" : "FAILED");
	#endif
	free(sha256);
	return shutdown;
}

int message(const int socket)
{
	int ready = 0;
	int exitProcess = FALSE, returnValue = 0;
	char buffer[MAX_SIZE], *strPtr = NULL;
	
	// receive the ready flag from server
	if (recv(socket, &ready, sizeof(int), 0) <= 0){
		perror("recv(): ");
		exitProcess = TRUE;
	}

	if (ready != READY_FLAG){
		exitProcess = TRUE;
	}

	// input the message
	printf("Enter a message: ");
	strPtr = fgets(buffer, MAX_SIZE, stdin);
	removeNewLine(buffer);
	
	// send the message to the server
	if (send(socket, buffer, strlen(buffer), 0) <= 0){
		perror("send(): ");
		exitProcess = TRUE;
	}
	
	// determine if the process succeeded
	if (exitProcess){
		returnValue = TRUE;
	}

	return returnValue;
}


int download(const int socket)
{
	FILE *fp = NULL;
	char directory[TRANSFER_SIZE], filename[TRANSFER_SIZE], localDir[TRANSFER_SIZE];
	char buffer[TRANSFER_SIZE], hash[HASH_SIZE], ourHash[HASH_SIZE]; 
	int proceed = TRUE;
	int totalBytes = 0, bytesWritten = 0, bytesRecv = 0;
	int fileSize = 0;
	int transferStatus = 0;

	memset(directory, 0, TRANSFER_SIZE);
	printf("Server directory: \n");
	fgets(directory, TRANSFER_SIZE, stdin); // get the input from stdin
	removeNewLine(directory);

	printf("Filename: \n"); // get the file from the server
	fgets(filename, TRANSFER_SIZE, stdin);
	removeNewLine(filename);

	printf("Local directory: \n"); // local dir to save file
	fgets(localDir, TRANSFER_SIZE, stdin);
	removeNewLine(localDir);
	strcat(localDir, filename);

	// send the directory to the server
	#ifdef DEBUG
		printf("Directory: %s\n", directory);
	#endif
	if (send(socket, directory, strlen(directory), 0) <= 0){
		perror("send(): ");
		proceed = FALSE;
	}

	if (recv(socket, &transferStatus, sizeof(int), 0) <= 0){
		perror("recv(): ");
		transferStatus = ntohl(transferStatus);
		proceed = transferStatus; 
	}

	// send the file name to the server
	if (send(socket, filename, strlen(filename), 0) <= 0){
		perror("send(): ");
		proceed = FALSE;
	}

	// receive the file size from the server
	if (recv(socket, &fileSize, sizeof(int), 0) <= 0){
		perror("recv(): ");
		proceed = FALSE;
	}
	fileSize = htonl(fileSize); // change the byte ordering from ntohl

	#ifdef DEBUG
		printf("fileSize = %d\n", fileSize);
	#endif
	
	// create the file locally
	if (proceed){
		#ifdef DEBUG
			printf("Local directory: %s\n", localDir);
		#endif
		fp = fopen(filename, "wb"); // create a file for writing
		if (fp == NULL) { perror("fopen(): "); } // permission denied
		memset(buffer, 0, BUFFER_SIZE);
		if (fp != NULL){
			while (totalBytes < fileSize){
				bytesRecv = recv(socket, buffer, sizeof(buffer), 0);
				if (bytesRecv <= 0){
					perror("Error receiving file: ");
					proceed = FALSE;
					break;
				}

				#ifdef DEBUG
					printf("b r/x = %d\n", bytesRecv);
				#endif
				bytesWritten = fwrite(buffer, sizeof(buffer[0]), bytesRecv, fp);
				if (bytesWritten <= 0){
					printf("Error writing to file.\n");
					proceed = FALSE;
					break;
				}
				totalBytes += bytesWritten;
				#ifdef DEBUG
					printf("Bytes written = %d and total = %d\n", bytesWritten, totalBytes);
				#endif
			}
			fclose(fp);
			
			memset(hash, 0, HASH_SIZE);
			
			// get the hash from the server
			if (recv(socket, hash, sizeof(hash), 0) <= 0){ // this is the valid hash
				perror("recv() for hash: ");
			}
			printf("Hash recv: %s\n", hash);
			
			hashFile(filename, fileSize, ourHash); // hash the file we just downloaded
			printf("Our hash: %s\n", ourHash);
	
			if (strcmp(hash, ourHash) != 0){ // both hashes are not equal
				printf("Hashes not equal!\nFile is either corrupted or has been tampered with.\n");
			}
		}
	}

	return proceed;
}

int upload(const int socket)
{
	FILE *fileUpload = NULL;
	int preTransfer = 0, fileSize = 0;
	int bytesRecv = 0, bytesSent = 0;
	int exitTransfer = FALSE;
	char directoryToUpload[MAX_SIZE], directoryServer[MAX_SIZE], *strPtr = NULL, *newLine = NULL;
	// file transfer stuff
	char buffer[TRANSFER_SIZE];
	int totalRead = 0, bytesRead = 0;
	int seekResult = 0;
	int returnValue = 0;
	
	// hash stuff
	sha256_context *sha256 = malloc(sizeof(sha256_context));
	unsigned char hash[HASH_SIZE]; 

	// initialise the sha-256 stuff
	memset(hash, 0, HASH_SIZE);
	assert(sha256 != NULL);
	sha256_start(sha256);

	// send the file size to the server
	printf("Enter the directory containing the file (including file name): ");
	strPtr = fgets(directoryToUpload, MAX_SIZE, stdin);
	removeNewLine(directoryToUpload);
	
	// now open the file and determine tis size
	fileUpload = fopen(directoryToUpload, "rb");
	if (fileUpload == NULL){ perror("fopen(): "); exit(1); }
	fileSize = determineFileSize(fileUpload);
	if (fileSize == ERROR){
		printf("Invalid file size.\n");
		exitTransfer = TRUE;
	}

	else{
		int fs = htonl(fileSize);
		printf("fs = %d\n", fileSize);
		bytesSent = send(socket, &fs, sizeof(int), 0);
		if (bytesSent <= 0){
			perror("send(): ");
		}

	}

	// receive a confirmation flag from the server
	if (!exitTransfer){
		bytesRecv = recv(socket, &preTransfer, sizeof(int), 0);
		preTransfer = ntohl(preTransfer);
		if (bytesRecv <= 0){
			perror("recv(): ");
			exitTransfer = TRUE;
		}

		else{
			if (preTransfer == CONFIRM_FLAG){
				printf("Received confirmation flag from server.\n");
			}
		}
	}

	// get the destination path for the file
	if (!exitTransfer){
		printf("Enter a path on the server to save the file to (including filename): ");
		strPtr = fgets(directoryServer, MAX_SIZE, stdin);
		removeNewLine(directoryServer);

		bytesSent = send(socket, directoryServer, strlen(directoryServer), 0);
		if (bytesSent <= 0){
			perror("send(): ");
			exitTransfer = TRUE;
		}
	}

	// start transferring the file
	while (totalRead < fileSize && exitTransfer != TRUE){
		memset(buffer, 0, TRANSFER_SIZE);
		bytesRead = fread(buffer, sizeof(buffer[0]), TRANSFER_SIZE - 1, fileUpload);
		if (bytesRead < 0){
			perror("fread(): ");
			exitTransfer = TRUE;
		}

		bytesSent = send(socket, buffer, strlen(buffer), 0);
		sha256_update(sha256, buffer, bytesRead);
		if (bytesSent < 0){
			perror("send(): ");
			exitTransfer = TRUE;
		}
		
		totalRead += bytesSent;
		#ifdef DEBUG
			printf("tr = %d and bs = %d and br = %d and fs = %d\n", totalRead, bytesSent, bytesRead, fileSize);
		#endif
	}

	if (exitTransfer){
		returnValue = FALSE;
	}
	
	else{
		sha256_finish(sha256, hash);
		sha256_tohex(sha256, hash);
		strcpy(hash, sha256->buffer);
		usleep(TRANSFER_DELAY);
		if (send(socket, hash, HASH_SIZE, 0) <= 0){
			perror("send() hash: ");
		}
		returnValue = TRUE;
	}

	fclose(fileUpload);
	
	return returnValue;
}

/*
	Notes:
	* can't get this to work with the server
	* after running this command, no other commands will work, the server reads nothing
	* fixed this, when sending avoid sending the whole buffer by using strlen() instead of sizeof()
*/

int printDirectory(const int socket)
{	
	char buffer[BUFFER_SIZE];
	int bytesRecv = 0;
	int ret = TRUE;

	printf("Server directory: ");
	fgets(buffer, BUFFER_SIZE, stdin);
	removeNewLine(buffer);
	if (send(socket, buffer, strlen(buffer), 0) <= 0){ // send the dir to the server
		perror("send(): ");
		ret = FALSE;
	}

	while (1){ // receive files and directories from server
		memset(buffer, 0, BUFFER_SIZE);
		bytesRecv = recv(socket, buffer, BUFFER_SIZE, 0);
		if (bytesRecv <= 0) { perror("recv(): "); ret = FALSE; break; } // something went wrong
		if (strcmp(buffer, END_DIR) == 0) { break; } // no more directories
		if (!(strcmp(buffer, ".") == 0 || strcmp(buffer, "..") == 0)){ // don't print meaningless directories
			printf("/%s\n", buffer);
		}
	}

	return ret;
}

int determineFileSize(FILE *f)
{
	int pos;
	int end;

	pos = ftell (f);
	fseek (f, 0, SEEK_END);
	end = ftell (f);
	fseek (f, pos, SEEK_SET);
	
	if (end <= 0){
		end = ERROR;
	}
	
	return end;
}

void removeNewLine(char *str)
{
	char *nl = strchr(str, NEW_LINE);
	if (nl != NULL){
		*nl = NULL_CHAR;
	}
}


