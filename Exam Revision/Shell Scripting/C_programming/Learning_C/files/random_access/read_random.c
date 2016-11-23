/*
    Name: Matthew Ta
    Date:
    Description: Read data from a random access file
*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 30
#define SENTINEL_VALUE -1

typedef struct _clientData{
    int accnum;
    char firstname[SIZE];
    char lastname[SIZE];
    double balance;

} clientData;

int main(void)
{
    FILE *rfPtr = NULL;
    clientData user = {0, "", "", 0};
    int bytesRead = 0;
    
    if ( (rfPtr = fopen("client.dat", "rb")) == NULL ){
        printf("Error: Unable to open file for reading.\n");
        return 1;
    }
    
    printf("Credit accounts: \n");
    printf("%-20s%-20s%-20s%-20s\n", "Account number:", "First name:", "Last name:", "Balance:");
    while ( !feof( rfPtr ) ){
        // read the file
        bytesRead = fread(&user, sizeof(clientData), 1, rfPtr);
        if (bytesRead > 0){
            // print the data
            if (user.accnum != -1){
                printf("%-20d%-20s%-20s%-20.2lf\n", user.accnum, user.firstname, user.lastname, user.balance);
                printf("\n");
            }
        }
    }

    fclose(rfPtr);
    return EXIT_SUCCESS;
}
