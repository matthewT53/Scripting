/*
	Name: Matthew Ta
	Date: 14/11/2015
	Description: Constants used by both the server and client
*/

#define DONT_KNOW -1
#define INVALID_INPUT 0
#define MESSAGE 1

// server constants
#define SERVER_PORT 13540
#define PORT_STR "13540"
#define SERVER_ADDRESS "192.168.0.15"

// from client
#define FILE_TRANSFER_UPLOAD 2
#define FILE_TRANSFER_DOWN 3
#define PRINT_SERVER_DIRECTORY 4
#define CLOSE_SERVER 5

#define UPLOAD "./uld"
#define DOWNLOAD "./dld"
#define DIRECTORY "./dir"
#define PRINT_MESS "./msg"
#define SHUTDOWN "./x"

// delays in ms
#define TRANSFER_SIZE 35840 // approximately 35 kb
#define TRANSFER_DELAY 50000 // microseconds
#define BUFFER_SIZE 2048 // 2kb?
#define MAX_SIZE 5000 // sizes for directories and such

// string constants
#define LOG_PATH "/home/beaniestyle/server/logs/"
#define UPLOAD_PATH "/home/beaniestyle/server/uploads/"
#define MESSAGE_PATH "/home/beaniestyle/server/messages/"
#define DOWNLOAD_PATH "/home/beaniestyle/server/downloads/"
#define DIRECTORY_PATH "/home/beaniestyle/server"
#define END_DIR "end_dir"
#define PW_DIR "Password.txt"

// file name constants
#define MESSAGE_FILE "messages.txt"
#define LOG_FILE "logs.txt"

// character constants
#define NULL_CHAR 0
#define NEW_LINE '\n'

// protocols
#define READY_FLAG 0
#define CONFIRM_FLAG 1
#define ERROR_FLAG -1
#define ERROR -1

// other stuff
#define MESSAGE_LENGTH 500

// pthread stuff
#define NUMBER_TASKS 3
#define FREE 0
#define BUSY 1

// boolean constants
#define TRUE 1
#define FALSE 0

// hashing stuff
#define HASHES_NOT_EQUAL_MESSAGE "File has been corrupted or tamperred with.\n"


