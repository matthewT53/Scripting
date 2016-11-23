#include <stdio.h>
#include <stdlib.h>

#define BYTE_BITS 8
#define SIZE BYTE_BITS*sizeof(unsigned int)

typedef unsigned int BitNum;

// input is from any data type
void printInBinary(BitNum);
void expmt(void);
void shifting(void);

int main(void)
{
    BitNum someNum;
    int objectsRead = 0;

    printf("Enter a number to convert to binary:\n");
    objectsRead = scanf("%u", &someNum);
    if (!objectsRead){
        printf("No data was entered.\n");
    }

    else{
        printInBinary(someNum);
    }

    expmt();
    shifting();

    return EXIT_SUCCESS;
}

// starts from the left
void printInBinary(BitNum num)
{
    int i = 0, j = 0;
    BitNum mask = 1, result = 0;
    BitNum bitrep[SIZE];

    for (i = 0; i < SIZE; i++){
        result = num & mask;
        mask <<= 1;
        bitrep[i] = (result) ? 1 : 0;
    }
    
    printf("[%05u] = ", num);
    // print in correct readable format
    for (j = i - 1; j >= 0; j--){
        printf("%d", bitrep[j]);
        if (j % 8 == 0){
            printf(" ");
        }
    }

    printf("\n");

}

void expmt(void)
{
    BitNum x = 56, y = 100, z = 34783, mask = 1;

    printInBinary(x);
    x = x ^ y;
    printInBinary(x);
    printInBinary(y);
    y = ~y;
    printInBinary(y);
    printInBinary(z);
    printInBinary(z & (mask <<= 6));

    printf("Largest possible unsigned interger: %u\n", (BitNum) ~0);
    printInBinary(~0);
}

void shifting(void)
{
    BitNum x = 65, y = 89;
    
    printf("\n");
    printInBinary(x);
    printInBinary(x >> 3);
    printInBinary(x >> 10); // bit overflow
    printInBinary(y);
    printInBinary(y << 3);
    printInBinary(y << 10);

}
