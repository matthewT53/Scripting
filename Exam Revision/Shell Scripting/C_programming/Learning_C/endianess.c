#include <stdio.h>
#include <stdlib.h>

int main(void){
	unsigned int x = 0x76543210;
	char *ptr = NULL;
	int i = 0;

	ptr = (char *) &x;
	printf("Address: 0x%x\n", x);
	printf("|");
	for (i = 0; i < 4; i++, ptr++){
		printf(" %x |", *ptr);
	}

	printf("\n");

	if (*ptr == 0x76){
		printf("Machine is big endian.\n");
	} else{
		printf("Machine is little endian.\n");
	}

	return EXIT_SUCCESS;

}
