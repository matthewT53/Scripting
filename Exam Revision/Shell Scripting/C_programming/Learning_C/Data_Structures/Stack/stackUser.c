/*
    Name:
    Date:
    Description:
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

#define SENTINEL_VALUE -999

#define PUSH 1
#define POP 2
#define SHOW 3

int main(void)
{
    Stack s = newStack();
    int choice = 0, value = 0, bytesRead = 0;

    printf("Stack: \n");
    printf(">: ");
    bytesRead = scanf("%d", &choice);
    assert(bytesRead != 0);
    while (choice != SENTINEL_VALUE){
        switch (choice){
            case PUSH:
                printf("Enter a value to push: ");
                bytesRead = scanf("%d", &value);
                assert(bytesRead != 0);
                push(s, value);
                break;
            case POP:
                value = pop(s);
                printf("Popped the value: %d\n", value);
                break;
            case SHOW:
                showStack(s);
                break;
            default:
                printf("Unknown action.\n");
                break;
        }

        printf(">: ");
        bytesRead = scanf("%d", &choice);
        assert(bytesRead != 0);
    }

    deleteStack(s);

    return EXIT_SUCCESS;
}
