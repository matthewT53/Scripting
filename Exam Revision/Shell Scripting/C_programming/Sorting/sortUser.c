/*
    Sort user
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sort.h"

// order of elements
#define ASCENDING "A"
#define DESCENDING "D"
#define RANDOM "R"
#define RANDOM_DUP "d"

// sorting algorithms
#define SELECTION 0
#define INSERTION 1
#define BUBBLE 2
#define QUICKSORT 3
#define MERGESORT 4
#define SHELLSORT 5
#define NUMBER_SORTS 6

#define TRUE 1
#define FALSE 0

static void fillRandom(int *, const int); // has duplicates
static void fillRandomNoDups(int *, const int);
void printUsage(void);

void data(int *a, const int size, const char *order); // store data into the array
int type(const char *sort); // determine which sort the user wants

int main(int argc, char **argv)
{
    int *a = NULL;
    int numberElements = 0, sort = 0;
    void (*sortTypes[NUMBER_SORTS])(int *, const int, const int) = {selectionSort, insertionSort, bubbleSort, quicksort, mergesort, shellsort};
    srand(time(NULL));

    if (argc != 4){
        printUsage();
        return 1;
    }
    
    numberElements = atoi(argv[3]);
    sort = type(argv[1]);
    a = (int *) malloc(sizeof(int) * numberElements);   
    data(a, numberElements, argv[2]);
    printf("[BEFORE SORT]:\n");
    show(a, 0, numberElements - 1);

    sortTypes[sort](a, 0, numberElements - 1);
    printf("[AFTER SORT]:\n");
    show(a, 0, numberElements - 1);
    return EXIT_SUCCESS;
}

int type(const char *sort)
{
    char c = sort[0];
    int returnValue;
    
    switch (c){
        case 'S':
            returnValue = SELECTION;
            break;
        case 'I':
            returnValue = INSERTION;
            break;
        case 'B':
            returnValue = BUBBLE;
            break;

        case 'Q':
            returnValue = QUICKSORT;
            break;
        case 'M':        
            returnValue = MERGESORT;
            break;
        case 's':
            returnValue = SHELLSORT;
            break;
        default:
            printf("Error couldn't determine which type of sort.\n");
            returnValue = -1;
            break;
    }

    return returnValue;
}

void data(int *a, const int size, const char *order)
{
    if (strcmp(order, RANDOM) == 0){
        fillRandomNoDups(a, size);
    }

    else if (strcmp(order, RANDOM_DUP) == 0){
        fillRandom(a, size);
    }

    else{
        printf("Don't know yet\n");
    }  
}

void printUsage(void)
{
    printf("./sort <type> <order> < # elements>\n");
    printf("type = S|I|B|Q|M|s\norder = A|R|D|d\n");
}


static void fillRandom(int *a, const int size)
{
    int i = 0, randomNumber = 0;
    
    for (i = 0; i < size; i++){
        randomNumber = 1 + rand() % size;
        a[i] = randomNumber;
    }

}

static void fillRandomNoDups(int *a, const int size)
{
    int i = 0;
    int j = 0, k = 0;    

    for (i = 0; i < size; i++){
        a[i] = i;
    }

    // now do random swaps to put them in rnadom order
    for (i = 0; i < size; i++){
        j = rand() % (size - 1);
        k = rand() % (size - 1);
        int temp = a[j];
        a[j] = a[k];
        a[k] = temp;
    }
}
