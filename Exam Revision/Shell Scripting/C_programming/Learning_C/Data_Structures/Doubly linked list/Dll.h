/*
    Name: Matthew Ta    
    Date:
    Description: Doubly linked lists function prototypes (ADT)
*/

typedef struct _DllRep *List;
typedef struct _node *Node;

// create a new list
List createList(void);

// free the list
void deleteList(List l);

// insert an item into the list after the current item
void insertNode(List l, int item);

// remove an the current node
void removeNode(List l, int item);

// show list
void showList(List l);
