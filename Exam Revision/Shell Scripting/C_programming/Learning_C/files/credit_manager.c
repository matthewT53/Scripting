/*
    Name: Matthew Ta
    Date:
    Description: Credit manager program
    Credit Balance = money company owes customers
    Debit = money customers owe company
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NAME_SIZE 30

int main(void)
{
    int request;
    int accnum; // account number
    char name[NAME_SIZE];
    double balance;

    FILE *rfPtr = NULL;

    printf("%s\n%38s\n%41s\n%40s\n%18s\n", "Credit management program", "1: Show customers with zero balance", "2: Show customers with credit balances",
                                           "3: Show customers with debit balances", "4: Exit program");

    if ( (rfPtr = fopen("clients.dat", "r")) == NULL){
        printf("Error: Couldn't open file for reading.\n");
        return 1;
    }
    
    printf(">: ");
    scanf("%d", &request);    
    
    while ( request != 4 ){
        switch (request){
            case 1: // show accounts of zero balances
                printf("Accounts with zero balances: \n");
                fscanf(rfPtr, "%d %s %lf", &accnum, name, &balance);
                while ( !feof(rfPtr) ){
                    if (balance == 0){
                        printf("Account number: %d, Name: %s and balance: %.2lf\n", accnum, name, balance);
                    }

                    fscanf(rfPtr, "%d %s %lf", &accnum, name, &balance);
                }
                
                break;

            case 2: // show accounts with a credit balance
                printf("Accounts with a credit balance: \n");
                fscanf(rfPtr, "%d %s %lf", &accnum, name, &balance);
                while ( !feof(rfPtr) ){
                    if (balance < 0){
                        printf("Account number: %d, Name: %s and balance: %.2lf\n", accnum, name, balance);
                    }

                    fscanf(rfPtr, "%d %s %lf", &accnum, name, &balance);
                }
                
                break;
    
            case 3: // show accounts with a debit balance
                printf("Accounts with a debit balance: \n");
                fscanf(rfPtr, "%d %s %lf", &accnum, name, &balance);
                while ( !feof(rfPtr) ){
                    if (balance > 0){
                        printf("Account number: %d, Name: %s and balance: %.2lf\n", accnum, name, balance);
                    }

                    fscanf(rfPtr, "%d %s %lf", &accnum, name, &balance);
                }
                
                break;

            default: // user has entered garbage
                printf("Please enter a number in the range of 1-4 (inclusive).\n");
                break;
        }

        printf(">: ");
        scanf("%d", &request);
        rewind(rfPtr); // reset the file offset ptr to 0
    }

    fclose(rfPtr);

    return EXIT_SUCCESS;
}
