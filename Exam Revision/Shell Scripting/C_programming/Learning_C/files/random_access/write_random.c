/*
    Name: Matthew Ta    
    Date:
    Description: write data to a random access file
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NAME_SIZE 30
#define SENTINEL_VALUE -1

typedef struct _clientData{
    int accnum;
    char name[NAME_SIZE];
    char lastname[NAME_SIZE];
    double balance;

} clientData;

int main(void)
{
    FILE *wfPtr = NULL;
    clientData customer = {0,"","",0}; // initialise the struct
    int accountNumber = 0, bytes_written = 0;
    
    if ( (wfPtr = fopen("client.dat", "rb+")) == NULL ){
        printf("Error: Unable to open file for reading and writing.\n");
        return 1;
    }

    printf("Enter an account number: ");
    scanf("%d", &accountNumber);

    while (accountNumber != SENTINEL_VALUE){
        // get details from stdin
        printf("Enter first name, last name and balance (with one space inbetween): ");
        customer.accnum = accountNumber;
        fscanf(stdin, "%s %s %lf", customer.name, customer.lastname, &customer.balance);

        // seek to the desired position
        fseek(wfPtr, accountNumber * sizeof(clientData), SEEK_SET);

        // write to the file
        bytes_written = fwrite(&customer, sizeof(customer), 1, wfPtr);
        assert(bytes_written > 0);

        printf(">: ");
        scanf("%d", &accountNumber);
    }

    fclose(wfPtr);

    return EXIT_SUCCESS;
}
