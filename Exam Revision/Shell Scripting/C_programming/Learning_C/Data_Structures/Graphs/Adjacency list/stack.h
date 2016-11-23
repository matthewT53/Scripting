/*
    Name: Matthew Ta
    Date: 13/9/2015
    Description: Interface for a linked list stack (ADT)
*/

typedef struct _stackRep *Stack;

#define EMPTY -1

// create a new stack
Stack newStack(void); 

// delete a stack
void deleteStack(Stack s);

// push an item onto the stack
void push(Stack s, int item);

// remove an item from the top of the stack
int pop(Stack s);

// print the stack
void showStack(Stack s);

// checks if the stack is empty
int isEmptyStack(Stack s);

// gets the value at the top of the stack without popping
int getTop(Stack s);


