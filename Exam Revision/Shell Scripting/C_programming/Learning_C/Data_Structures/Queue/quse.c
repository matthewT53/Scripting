/*
    Name: Matthew Ta
    Date: 13/9/2015
    Description: User of a queue ADT
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "queue.h"

#define ADD_ITEM 0
#define REMOVE_ITEM 1
#define SHOW_Q 2

#define SENTINEL_VALUE -999

int main(void)
{
    Queue q = newQueue();
    int choice = 0, v;

    printf("Queue: \n");
    printf(">: ");
    int charsRead = scanf("%d", &choice);
    assert(charsRead != 0);
    while (choice != SENTINEL_VALUE){
        switch(choice){
            case ADD_ITEM:
                printf("Enter a value: ");
                charsRead = scanf("%d", &v);
                assert(charsRead != 0);
                enQueue(q, v);
                break;
            case REMOVE_ITEM:
                v = deQueue(q);
                printf("v = %d\n", v);
                break;
            case SHOW_Q:
                showQueue(q);
                break;
            default:
                printf("Unknown action.\n");
                break;
        }

        printf(">: ");
        charsRead = scanf("%d", &choice);
        assert(charsRead != 0);
    }

    return EXIT_SUCCESS;
}
