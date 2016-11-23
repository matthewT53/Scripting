#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "linkList.h"

#define NOT_SET 0
#define SET 1
#define SIZE 2
#define SWITCH_LIST_1 0
#define SWITCH_LIST_2 1

List createList(void){
	List newList = malloc(sizeof(list));
	return newList;
}

void deleteList(List l){
	nodePtr currentNode, previousNode;
	
	currentNode = l->head;
	if (currentNode != NULL){
		while (currentNode != NULL){
			previousNode = currentNode;
			currentNode = currentNode->next;
			free(previousNode);
		}

		l->head = NULL;
	}
	
	// list is already empty
	else{
		l->head = NULL;
	}
}

void addNode(List l, int valueToAdd){
	nodePtr currentNode, lastNode;
	currentNode = l->head;
	
	// what if the list is empty?
	if (l->head == NULL){
		l->head = malloc(sizeof(node));
		lastNode = l->head;
		lastNode->value = valueToAdd;
		lastNode->next = NULL;
	}
	
	else{
		// get the pointer to the last node
		while (currentNode != NULL){
			lastNode = currentNode;
			currentNode = currentNode->next;
		}
	
	
		lastNode->next = malloc(sizeof(node));
		lastNode = lastNode->next;
		lastNode->value = valueToAdd;
		lastNode->next = NULL;
	}
}

int findNode(List l, int value)
{
	int occurences = 0;
	nodePtr currentNode;
		
	for ( currentNode = l->head; currentNode != NULL; currentNode = currentNode->next ){
		if (currentNode->value == value){
			occurences++;
		}
	}

	return occurences;
}

void deleteNode(List l, int value)
{
	nodePtr cur = NULL, prev = NULL;
	cur = l->head;
	if (cur != NULL){
		// might be first node
		if (cur->value == value){
			l->head = cur->next;
			free(cur);
		}

		else{
			while (cur != NULL){
				if (cur->value == value){
					prev->next = cur->next;
					free(cur);
					break;
				}

				prev = cur;
				cur = cur->next;
			}
		}

	}

}

void removeDups(List l)
{
	nodePtr cur = NULL, temp = NULL, searchn = NULL, prev = NULL;

	/*
		Cases:
		* 2 nodes in list same value
		* remove last node
		* remove middle of list
		* 2 consec dups
	*/
	
	if ( l != NULL ){
		cur = l->head;
		while ( cur != NULL ){
			searchn = cur->next;
			prev = cur;
			while ( searchn != NULL ){
				if ( cur->value == searchn->value ){ // delete the duplicate
					temp = searchn;
					prev->next = searchn->next;
					searchn = prev;
					free(temp);
				}			

				prev = searchn;	
				searchn = searchn->next;
			}
	
			cur = cur->next;
		}
	}

}

void copyListArray(int *array, List l, const int size)
{
	int i;
	nodePtr cur;
	
	for ( i = 0, cur = l->head; i < size && cur != NULL; i++, cur = cur->next){
		array[i] = cur->value;
	}
}

void printList(List l){
	nodePtr currentNode;
	currentNode = l->head;	
		
	// loop through the list and print out the nodes
	while (currentNode != NULL){
		printf("[%d]->", currentNode->value);
		currentNode = currentNode->next;
		
	}
	
	// print the null node
	printf("[X].\n");
}

int getLength(List l){
	int length = 0;
	nodePtr currentNode;
	
	currentNode = l->head;
	// loop through the list and count the number of nodes
	while (currentNode != NULL){
		length++;
		currentNode = currentNode->next;
	}

	return length;
}

void frontBackSplit(List source, List frontList, List backList){
	int lengthList = getLength(source), nodesPassed = 0;
	nodePtr currentNode = NULL, tempNode = NULL, frontNodes = NULL;
	
	currentNode = source->head;
	if (currentNode != NULL){
		if (lengthList == 1){
			frontList->head = currentNode;
			frontList->head->next = NULL;
			backList->head = NULL;
		}

		else{
			if (lengthList % 2 == 0){
				while (currentNode != NULL && nodesPassed < (lengthList / 2)){
					tempNode = malloc(sizeof(node));
					tempNode->value = currentNode->value;
					tempNode->next = currentNode->next;
					
					// copy the nodes into the front list
					if (frontList->head == NULL){
						frontList->head = tempNode;
						frontNodes = frontList->head;
					}

					else{
						frontNodes->next = tempNode;
						frontNodes = frontNodes->next;
					}

					nodesPassed++;
					currentNode = currentNode->next;
				}
				
				frontNodes->next = NULL;
				backList->head = currentNode;

			}

			else{
				while (currentNode != NULL && nodesPassed < (lengthList / 2) + 1){
					tempNode = malloc(sizeof(node));
					tempNode->value = currentNode->value;
					tempNode->next = currentNode->next;
					
					// copy the nodes into the front list
					if (frontList->head == NULL){
						frontList->head = tempNode;
						frontNodes = frontList->head;
					}

					else{
						frontNodes->next = tempNode;
						frontNodes = frontNodes->next;
					}

					nodesPassed++;
					currentNode = currentNode->next;
				}
				
				frontNodes->next = NULL;
				backList->head = currentNode;

			}

		}
	
	}

	else{
		frontList->head = NULL;
		backList->head = NULL;
	}
	
}

void moveNode(List list1, List list2){
	nodePtr firstNodeList2, tempNode, headOfList2, newSecondNodeList1;
	
	newSecondNodeList1 = NULL;
	firstNodeList2 = list2->head;
	if (firstNodeList2 != NULL){
		// create two new nodes for first list
		// first node is the first node of second list
		// second node is the first node of list 1
		if (list1->head != NULL){
			newSecondNodeList1 = malloc(sizeof(node));
			newSecondNodeList1->value = list1->head->value;
			newSecondNodeList1->next = list1->head->next;
		}

		tempNode = malloc(sizeof(node));
		tempNode->value = firstNodeList2->value;
		tempNode->next = newSecondNodeList1;
		list1->head = tempNode;
		
		// remove the first node of the second list
		headOfList2 = list2->head;
		free(headOfList2);
		list2->head = list2->head->next;

	} 

}

void alternatingSplit(List sourceList, List list1, List list2){
	int switchFlag = SWITCH_LIST_1;
	int headSet[SIZE] = {0, 0};
	nodePtr currentNode = NULL, newNode = NULL, nodeList1 = NULL, nodeList2 = NULL;
		
	currentNode = sourceList->head;
	
	if (currentNode != NULL){
		while (currentNode != NULL){
			if (switchFlag == SWITCH_LIST_1){
				newNode = malloc(sizeof(node));
				newNode->value = currentNode->value;
				newNode->next = NULL;
				// set the head of the first list
				if (headSet[0] == NOT_SET){
					list1->head = newNode;
					nodeList1 = list1->head;
					headSet[0] = SET;
				}
				
				else{
					nodeList1->next = newNode;
					nodeList1 = nodeList1->next;				
				}

				
			}

			if (switchFlag == SWITCH_LIST_2){
				newNode = malloc(sizeof(node));
				newNode->value = currentNode->value;
				newNode->next = NULL;
				// set the head of list2
				if (headSet[1] == NOT_SET){
					list2->head = newNode;
					nodeList2 = list2->head;
					headSet[1] = SET;
				}

				else{
					nodeList2->next = newNode;
					nodeList2 = nodeList2->next;
				}

			}

			// switch the flags to copy alternate nodes of the source list
			if (switchFlag == SWITCH_LIST_1){
				switchFlag = SWITCH_LIST_2;
			}

			else{
				switchFlag = SWITCH_LIST_1;
			}

			currentNode = currentNode->next;
	
		}
	}
}

void alternatingSplit2(List source, List list1, List list2){
	int switchFlag = SWITCH_LIST_1;
	nodePtr currentNode;
	
	currentNode = source->head;
	while (currentNode != NULL){
		if (switchFlag == SWITCH_LIST_1){
			moveNode(list1, source);
		}

		if (switchFlag == SWITCH_LIST_2){
			moveNode(list2, source);
		}

		// switch the flags to add the nodes into the sublists in alternating order
		if (switchFlag == SWITCH_LIST_1){
			switchFlag = SWITCH_LIST_2;
		}

		else{
			switchFlag = SWITCH_LIST_1;
		}

		currentNode = source->head;
	}

}

List shuffleMerge(List list1, List list2){
	List mergeList = createList();
	nodePtr newNode1, newNode2, walkList1, walkList2;
	nodePtr walkNewList = NULL;
	int assignedHead = 0;

	mergeList->head = NULL;
	walkList1 = list1->head;
	walkList2 = list2->head;
	walkNewList = mergeList->head;
	
	if (walkList1 != NULL && walkList2 != NULL){
		
		while (walkList1 != NULL && walkList2 != NULL){
			newNode1 = malloc(sizeof(node));
			newNode2 = malloc(sizeof(node));
			
			// connect the two corresponding nodes from each list
			newNode2->value = walkList2->value;
			newNode2->next = walkList2->next;
			newNode1->value = walkList1->value;
			newNode1->next = newNode2;
			
			// assign the node from list 1 to either the head or the tail
			if (assignedHead == 0){
				mergeList->head = newNode1;
				walkNewList = mergeList->head->next;
				assignedHead = 1;
			}

			else{
				walkNewList->next = newNode1;
				walkNewList = walkNewList->next->next;
			}
			
			
			walkList1 = walkList1->next;
			walkList2 = walkList2->next;

		}
		
	}
	
	// if one of the lists is empty, the other list becomes the new list
	else{
		if (walkList1 != NULL && walkList2 == NULL){
			mergeList->head = walkList1;

		}

		if (walkList2 != NULL && walkList1 == NULL){
			mergeList->head = walkList2;
		}
	}
		
	return mergeList;
	
}

List sortedMerge(List l1, List l2){
	List sortedList = createList();
	nodePtr walkList1, walkList2, walkSortedList;
	int switchValue = SWITCH_LIST_1, list1Value = 0, list2Value = 0, assignedHead = NOT_SET;
	
	walkList1 = l1->head;
	walkList2 = l2->head;
	
	if (walkList1 != NULL && walkList2 != NULL){
		// assign the head of the new list to the first node in list 1
		// need to determine which list has the greatest first node
		if (walkList1->value < walkList2->value){
			copyNodes(&sortedList->head, &walkList1, &assignedHead);
		}

		else{
			copyNodes(&sortedList->head, &walkList2, &assignedHead);
		}
		walkSortedList = sortedList->head;
		// printf("Seg fault.\n");
		
		while (walkList1 != NULL || walkList2 != NULL){
			if (switchValue == SWITCH_LIST_1 || walkList2 == NULL){
				if (walkList2 != NULL){
					list2Value = walkList2->value;
				}
				while (walkList1 != NULL && (walkList1->value < list2Value || walkList2 == NULL)){
					copyNodes(&walkSortedList, &walkList1, &assignedHead);
					
				}

				switchValue = SWITCH_LIST_2;

			}
			
			// printf("Seg fault.2\n");
			if (switchValue == SWITCH_LIST_2 || walkList1 == NULL){
				if (walkList1 != NULL){
					list1Value = walkList1->value;
				}

				while (walkList2 != NULL && (walkList2->value < list1Value || walkList1 == NULL)){
					copyNodes(&walkSortedList, &walkList2, &assignedHead);
				}

				switchValue = SWITCH_LIST_1;		
			}
			// printf("Seg fault.3\n");

		}

	}
	
	// if one of the lists is empty, copy the non-empty list into sortedList
	else{
		if (walkList1 != NULL && walkList2 == NULL){
			// assign the head its first node
			copyNodes(&sortedList->head, &walkList1, &assignedHead);
			walkSortedList = sortedList->head;
			while (walkList1 != NULL){
				copyNodes(&walkSortedList, &walkList1, &assignedHead);
			}
			
		}

		if (walkList2 != NULL && walkList1 == NULL){
			// assign the head its first node
			copyNodes(&sortedList->head, &walkList2, &assignedHead);
			walkSortedList = sortedList->head;
			while (walkList2 != NULL){
				copyNodes(&walkSortedList, &walkList2, &assignedHead);
			}
		}
	}

	return sortedList;
}

void copyNodes(nodePtr *node1, nodePtr *node2, int *setHead){
	nodePtr newNode = malloc(sizeof(node));
	newNode->value = (*node2)->value;
	newNode->next = NULL;
	if (*setHead == NOT_SET){
		(*node1) = newNode;
		*setHead = SET;
	}

	else{
		(*node1)->next = newNode;
		(*node1) = (*node1)->next;
	}

	(*node2) = (*node2)->next;
}

void mergeSort(List *l){
	List l1 = createList();
	List l2 = createList();

	// check if list is empty
	if ((*l)->head != NULL){
		frontBackSplit((*l), l1, l2);
		/*
		printf("Sublists after split:\n");
		printList(l1);
		printList(l2);
		printf("\n");
		*/

		// if each sublist contains one element
		if (l1->head != NULL && l2->head != NULL){
			if (l1->head->next != NULL || l2->head->next != NULL){
				if (l1->head->next != NULL){
					mergeSort(&l1);
				}

				if (l2->head->next != NULL){
					mergeSort(&l2);
				}
			}

		}
		
		(*l) = sortedMerge(l1, l2);
		// printList(*l);
	}

}

#ifdef IMP
/*
	Notes:
	* need to modify the function below to get it to work
	* need to add function prototypes
	* changed l -> q to make it works
*/
void swapNodes(List q, nodePtr n1, nodePtr n2)
{
	Node beforeN1 = NULL, afterN1 = NULL;
	Node beforeN2 = NULL, afterN2 = NULL;
	
	if (q->head != NULL && n1 != n2){ // account for empty list
		// find nodes before and after n1
		findPrevAndNext(q, n1, &beforeN1, &afterN1);
		findPrevAndNext(q, n2, &beforeN2, &afterN2);

		// swap the nodes
		if (beforeN1 == NULL){ // case where n1 is the first node (head)
			q->head = n2;
			if (n1->next == n2){ // detect if n1 and n2 are neighbours
				q->head->next = n1;
			}

			else{
				q->head->next = afterN1;
				beforeN2->next = n1;
			}
			n1->next = afterN2;
		}

		else if (beforeN2 == NULL){ // when n2 is the first node
			q->head = n1;
			if (n2->next == n1){ // n2 is first node and neightbours with n2
				q->head->next = n2;
			}

			else{
				q->head->next = afterN2;
				beforeN1->next = n2;
			}

			n2->next = afterN1;
		}

		else{ // swap n1 and n2
			beforeN1->next = n2;
			n2->next = afterN1;

			beforeN2->next = n1;
			n1->next = afterN2;
		}
	}
}

static void findPrevAndNext(List q, Node n, Node *prevN, Node *nextN)
{
	Node cur = q->head; 
	Node prev = NULL;

	while (cur != NULL){
		if (cur == n){
			*prevN = prev;
			*nextN = cur->next;
			break;
		}
		prev = cur;
		cur = cur->next;
	}
}
#endif 

// reverse a list
void reverse(List l)
{
	nodePtr cur = NULL, lastNode = NULL, prev = NULL;
	nodePtr rev = NULL, startNode = NULL;
		
	if (l != NULL){
		// find the last node
		if (l->head != NULL){ 
			cur = l->head;
			while (cur->next != NULL){
				cur = cur->next;
			}
			lastNode = cur; // set the last node
			rev = lastNode; // use rev as point to re-arrange the original list
			startNode = rev; // the new start of the list is the last node
			while (rev != l->head){ // while we haven't added the first node of the list into the reverse list
				prev = NULL;
				cur = l->head; // loop from the start of the list
				while (cur->next != lastNode){ // dont consider the last node since this node is the start of the reverse list
					prev = cur;
					cur = cur->next;
				}
		
				if (prev != NULL){ prev->next = lastNode; }
				cur->next = NULL;
				rev->next = cur;
				rev = rev->next; // eventually rev points to the first node in the original list
			}
			l->head = startNode; // set the start of the original list to point to the reverse list.
		}
	}
}


