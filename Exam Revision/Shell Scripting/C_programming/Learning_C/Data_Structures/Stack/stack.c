/*
    Name: Matthew Ta
    Date: 13/9/2015
    Description: Implementation for the interface functions of the stack
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "stack.h"

typedef struct _stackRep{
    Node top;
} stackRep;

typedef struct _node{
    int value;
    Node next;
} node;
    
Stack newStack(void)
{
    Stack s = malloc(sizeof(stackRep));
    assert(s != NULL);
    s->top = NULL;
    return s;
}

void deleteStack(Stack s)
{
    Node current, temp;
    
    current = s->top;
    while (current != NULL){
        temp = current;
        current = current->next;
        free(temp);
    }

    free(s);
}

void push(Stack s, int item)
{
    Node newNode(int v);
    
    Node n = newNode(item);
    if (n != NULL){
        Node curr;
        curr = s->top;
        n->next = curr;
        s->top = n;
    }
}

Node newNode(int v)
{
    Node n = malloc(sizeof(node));
    if (n != NULL){
        n->value = v;
        n->next = NULL;
    }
    return n;
}

int pop(Stack s)
{
    Node n = s->top;
    int retValue = 0;
    if (n != NULL){
        retValue = n->value;
        s->top = s->top->next;
        free(n);
    }

    return retValue;
}

void showStack(Stack s)
{
    Node curr;
    curr = s->top;
    while (curr != NULL){
        printf("[%d]->", curr->value);
        curr = curr->next;
    }

    printf("X\n");
}
