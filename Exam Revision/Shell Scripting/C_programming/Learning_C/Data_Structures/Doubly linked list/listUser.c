/*
    Name: Matthew Ta
    Date:
    Description: User of a doubly linked list
*/

#include <stdio.h>
#include <stdlib.h>

#include "Dll.h"

int main(void)
{
    List l = createList();
	insertNode(l, 5);
	insertNode(l, 4);
	insertNode(l, -1);
	insertNode(l, 8);
	showList(l);
	removeNode(l, 8);
	showList(l);
    deleteList(l);
    return 0;
}
