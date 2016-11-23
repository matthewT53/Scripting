/*
	Name: Matthew Ta
	Date: 15/11/2015
	Description: Tests the stability of a sorting algorithm

	Compile: gcc -Wall -Werror -std=c99 -o stab stab.c
    Usage: ./stab <name of unsorted file> <name of sorted file>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// boolean stuff
#define TRUE 1
#define FALSE 0

#define MAX_SIZE 100000 // max values to read
#define B_SIZE 4 // size of the second field

typedef struct _item{
    int a; // key value
    char b[B_SIZE]; // field value to distinguish stable vs non-stable
} item;

void printUsage(void);
int isStable(item unsorted[], item sorted[], int lo, int high); // takes index of start and index of end

int main(int argc, char *argv[])
{
    FILE *ufp = NULL, *sfp = NULL;
    item ublock[MAX_SIZE], sblock[MAX_SIZE];
    int itemsRead = 1, i = 0, stable = FALSE;

    // check if the user has given the correct arguments
    if (argc != 3){
        printUsage();
        exit(1);
    }

    else{
        printf("Unsorted file: %s and sorted file: %s\n", argv[1], argv[2]); 
    }

    // clear the arrays
    memset(ublock, 0, sizeof(item) * MAX_SIZE);
    memset(sblock, 0, sizeof(item) * MAX_SIZE);
    
    // open the files
    ufp = fopen(argv[1], "r"); // unsorted file
    sfp = fopen(argv[2], "r"); // sorted file
    if (ufp == NULL || sfp == NULL){ // error checking
        printf("Failed to open one of the files.\n");
        exit(1);
    }

    // read from unsorted list
    itemsRead = fscanf(ufp, "%d %s", &ublock[i].a, ublock[i].b);
    while (itemsRead > 1 && i < MAX_SIZE){ // should be always reading 2 values each call to fscanf()
        i++;
        itemsRead = fscanf(ufp, "%d %s", &ublock[i].a, ublock[i].b);
    }

    // read from sorted list
    i = 0;
    itemsRead = fscanf(sfp, "%d %s", &sblock[i].a, sblock[i].b);
    while (itemsRead > 1 && i < MAX_SIZE){
        i++;
        itemsRead = fscanf(sfp, "%d %s", &sblock[i].a, sblock[i].b);
    }

    stable = isStable(ublock, sblock, 0, i - 1);
    printf("Stable: %s\n", (stable) ? "TRUE" : "FALSE");

    fclose(ufp);
    fclose(sfp);

    return EXIT_SUCCESS;
}

void printUsage(void)
{
    printf("Usage: ./stab <name of unsorted file> <name of sorted file>\n");
}

/*
    Best case: No dups O(n)
    Worst case: all dups O(n^2)
    Average case: contains some dups O((n/2)^2) ~ O(n^2) since the inner for loop will only execute sometimes
*/


int isStable(item unsorted[], item sorted[], int lo, int high)
{
    int i, j, prev = 0;
    item key; 
    assert(lo >= 0 && lo <= high);
    for (i = lo; i <= high; i++){ // step through the sorted list
        key = sorted[i]; 
        if ( (i >= 0 && (sorted[i].a == sorted[i + 1].a)) || (i != 0 && (sorted[i].a == sorted[i - 1].a)) ){ // finds dups in sorted array, will skip if none found
            j = 0;
            for (j = 0; j <= high; j++){ // loop through unsorted list
                if (key.a == unsorted[j].a && strcmp(key.b, unsorted[j].b) == 0){ // try to find the same key
	                if (j < prev){ // not in same order
	                    return FALSE; // sorting algo is not stable
	                }
	                prev = j;
	                break;
                }
            }
            
            if (sorted[i].a != sorted[i + 1].a){ // if the next key != key[i - 1] reset prev
                prev = 0;
            }            
        }
    }

    return TRUE; // is stable
}



