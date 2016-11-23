/* 
    Name: Matthew Ta
    Date:
    Description: Creates a random access file
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NAME_SIZE 30

typedef struct _clientData{
    int accnum; // account number
    char firstname[NAME_SIZE]; // first name
    char lastName[NAME_SIZE]; // last name
    double balance;

} clientData;

int main(void)
{
    FILE *wfPtr = NULL;
    clientData customer = {-1, "", "", 0};
    int i = 0, bytesWritten = 0;

    if ((wfPtr = fopen("client.dat", "wb")) == NULL){
        printf("Error: Couldn't open the file for writing.\n");
        return 1;
    }

    for (i = 0; i < 100; i++){
        bytesWritten = fwrite(&customer, sizeof(customer), 1, wfPtr);
        assert(bytesWritten > 0);
    }

    fclose(wfPtr);

    return EXIT_SUCCESS;
}
