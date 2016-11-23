/*
    Name: Matthew Ta
    Date: 26/8/2015
    Description: Experimenting with hash tables
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linkList.h"

#define MAX_VALUE 10
#define SENTINEL_VALUE -999

#define TRUE 1
#define FALSE 0

void printHashTable(List *table);
int findElement(List *table, int element);

int main(void)
{
    List table[MAX_VALUE];
    int i = 0, input = 0, key = 0, bytesRead = 0;

    // create the hash table
    for (i = 0; i < MAX_VALUE; i++){
        table[i] = createList();
    }

    printf("Enter a value: ");
    bytesRead = scanf("%d", &input);
    while (input != SENTINEL_VALUE && bytesRead != EOF){
        key = input % MAX_VALUE;
        if (key >= 0 && key <= 9){
            addNode(table[key], input);
        }

        printf("Enter a value: ");
        bytesRead = scanf("%d", &input);
    }

    printHashTable(table);

    printf("Find an element: ");
    bytesRead = scanf("%d", &key);
    if (findElement(table, key)) {printf("Found element\n");}

    // free the hash table
    for (i = 0; i < MAX_VALUE; i++){
        deleteList(table[i]);
    }

    return EXIT_SUCCESS;
}

void printHashTable(List *table)
{   
    int i = 0;
    
    printf("Printing hash table.\n");
    for (i = 0; i < MAX_VALUE; i++){
        printf("{%d}: ", i);
        printList(table[i]);
    }
        
    printf("\n");
}

int findElement(List *table, int element)
{
    int i = 0, position = FALSE;
    nodePtr currentNode = NULL;
    
    for (i = 0; i < MAX_VALUE && !position; i++){
        currentNode = table[i]->head;
        while (currentNode != NULL){
            if (currentNode->value == element){
                position = TRUE;
                break;
            }
            
            currentNode = currentNode->next;
        }

    }

    return position;
}
