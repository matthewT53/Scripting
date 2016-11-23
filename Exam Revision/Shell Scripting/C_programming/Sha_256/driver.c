/*
	Name: Matthew Ta
	Date: 20/11/2015
	Description: Driver for the sha 256 things
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "sha_256.h"

int main(void)
{
	sha256_context *sha256 = malloc(sizeof(sha256_context));
	unsigned char data[80] = "sdoggnosdgsdmgopsdopgsopg0240gj90jgogmkdasdasf5s9asdmgklsdklbxclbmklxc";
	unsigned char hash[65];

	assert(sha256 != NULL);
	
	memset(hash, 0, 65);
	
	sha256_start(sha256); // initialise the struct
	sha256_update(sha256, data, strlen(data));
	sha256_finish(sha256, data);
	sha256_tohex(sha256, data);

	strcpy(hash, sha256->buffer);
	
	printf("Hash: %s\n", sha256->buffer);

	free(sha256);
	return EXIT_SUCCESS;
}
