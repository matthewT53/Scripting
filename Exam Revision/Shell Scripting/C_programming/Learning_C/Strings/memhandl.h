/* 
	Name: Matthew Ta
	Date: 14/7/2015
	Description: This header file contains the function prototypes for memory handling functions.
*/

// copies n blocks from memb2 into memb1
void *memblkcpy(void *memb1, const void *memb2, const unsigned int numbytes);

// copies n blocks from memb2 into a temp array and then the contents of the temp array is copied into memb1
void *memblkmove(void *memb1, const void *memb2, const unsigned int numbytes);

// compares n bytes of memb2 to memb1
int memblkcmp(const void *memb1, const void *memb2, const unsigned int numbytes);

// locates a specific byte in the first n chars in memb and returns a pointer if found
void *memblkchr(const void *memb, int byte, const unsigned int numbytes);

// copies a byte into n blocks in memb and returns a pointer to the result
void *memblkset(void *memb, int byte, const unsigned int numbytes);
