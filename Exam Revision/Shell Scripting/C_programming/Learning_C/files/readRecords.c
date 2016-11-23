/*
    Name: Matthew Ta
    Date: 7/9/2015
    Description: Reading records from a file
*/

#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

int main(void)
{
    FILE *rfptr = NULL;
    int account_num = 0; // account number
    char name[30]; // name of customer
    double balance = 0; // money owed by the client
    
    unsigned int objsRead = 0;

    if ((rfptr = fopen("clients.dat", "r")) == NULL){
        printf("Error: Unable to open file for reading.\n");
        return 1;
    }
    
    objsRead = fscanf(rfptr, "%d %s %lf", &account_num, name, &balance);    
    assert(objsRead > 0);
    while ( !feof(rfptr) ){
        printf("Account number: %d, name: %s and balance: %.2f\n", account_num, name, balance);  
        objsRead = fscanf(rfptr, "%d %s %lf", &account_num, name, &balance);
        assert(objsRead > 0);
    }
        
    return EXIT_SUCCESS;
}
