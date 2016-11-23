#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(void)
{
    int accountNum;
    char name[30];
    double balance;

    int itemsRead = 0;

    FILE *fptr = NULL;
    
    if ((fptr = fopen("clients.dat", "w")) == NULL){
        printf("Could not open the file.\n");
        return 1;
    }

    printf("Enter account number, name and balance (amount owed):\n");
    printf(">: ");
    itemsRead = scanf("%d %s %lf", &accountNum, name, &balance);
    assert(itemsRead != 0);
    while ( !feof(stdin) ){
        fprintf(fptr, "%d %s %.2f\n", accountNum, name, balance);
        printf(">: ");
        itemsRead = scanf("%d %s %lf", &accountNum, name, &balance);
        assert(itemsRead != 0);
    }

    fclose(fptr);

    return EXIT_SUCCESS;
}
