/* 
	linkList test file 
	Note: Compile using the following command:
	gcc - Wall -Werror -std=c99 -o <program name> linkList.c linkListTest.c

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include "linkList.h"

#define TEST_VALUE_1 52
#define TEST_VALUE_2 53
#define TEST_VALUE_3 54
#define TEST_VALUE_4 55
#define TEST_VALUE_5 46

#define LIST_SIZE_3 3

#define BEFORE 0
#define AFTER 1

// this file uses the functions that interact with linked lists
void testFrontBackSplit(void);
void testFunctions(void);
void testMoveNode(void);
void testDeleteNode(void);
void testAlternatingSplit(void);
void testAlternatingSplit2(void);
void testShuffleMerge(void);
void testSortedMerge(void);
void testMergeSort(void);
void testReverse(void);


// to avoid repetition in testing the functions
void printListStatus(List [], int);
void printListStatusMerge(List [], int);

int main(void){

	// testSortedMerge();
	testReverse();
	
	return EXIT_SUCCESS;
}

void testReverse(void){
	List testList = createList();
	testList->head = NULL;
	
	// test en empty list
	printf("Testing an empty list.\n");
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	reverse(testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head == NULL);
	printf("Passed first test!\n");
	
	// test a list with one node
	printf("Testing with a list containing one element.\n");
	addNode(testList, 65);
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	reverse(testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head->value == 65 && testList->head->next == NULL);
	printf("Passed second test!\n");

	// test a list containing two nodes
	printf("Testing with a list containnig two nodes.\n");
	addNode(testList, 55);
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	reverse(testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head->value == 55 && testList->head->next->value == 65 && testList->head->next->next == NULL);
	printf("Passed third test!\n");

	// test a list containing 5 nodes
	printf("Testing a list containing five nodes.\n");
	addNode(testList, 31);
	addNode(testList, 78);
	addNode(testList, 95);
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	reverse(testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head->value == 95 && testList->head->next->value == 78 && testList->head->next->next->value == 31);
	assert(testList->head->next->next->next->value == 65 && testList->head->next->next->next->next->value == 55);
	assert(testList->head->next->next->next->next->next == NULL);
	printf("Passed the fourth test!\n");

	deleteList(testList);
	
	printf("Passed all tests! You sir, are legendary!\n"); 	
}

void testMergeSort(void){
	List testList = createList();
	

	// test an empty list
	printf("Testing an empty list.\n");
	testList->head = NULL;
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	mergeSort(&testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head == NULL);
	printf("Passed test 1/6.\n");

	// testing a list with only one element
	printf("\nTesting a list with one element.\n");
	addNode(testList, 56);
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	mergeSort(&testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head->value == 56 && testList->head->next == NULL);
	printf("Passed test 2/6.\n");

	// testing two unordered nodes
	printf("\nTesting a list with two unordered nodes.\n");
	addNode(testList, 45);
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	mergeSort(&testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head->value == 45 && testList->head->next->value == 56);
	assert(testList->head->next->next == NULL);
	printf("Passed test 3/6.\n");

	// testing 4 unordered nodes
	printf("\nTesting list with 4 unordered nodes.\n");
	addNode(testList, 26);
	addNode(testList, 32);
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	mergeSort(&testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);
	assert(testList->head->value == 26 && testList->head->next->value == 32 && testList->head->next->next->value == 45);
	assert(testList->head->next->next->next->value == 56);
	assert(testList->head->next->next->next->next == NULL);
	printf("Passed test 4/6.\n");

	// testing 5 unordered nodes
	printf("\nTesting list with 5 unordered nodes.\n");
	testList->head = NULL;
	addNode(testList, 65);
	addNode(testList, 15);
	addNode(testList, 11);
	addNode(testList, 9);
	addNode(testList, 3);
	
	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	
	mergeSort(&testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);

	assert(testList->head->value == 3 && testList->head->next->value == 9 && testList->head->next->next->value == 11);
	assert(testList->head->next->next->next->value == 15 && testList->head->next->next->next->next->value == 65);
	assert(testList->head->next->next->next->next->next == NULL);
	printf("Passed test 5/6.\n");

	// test list with 8 ordered nodes
	printf("\nTesting list with 8 ordered nodes.\n");
	addNode(testList, 68);
	addNode(testList, 70);
	addNode(testList, 75);

	printf("[BEFORE FUNCTION]:\n");
	printList(testList);
	mergeSort(&testList);
	printf("[AFTER FUNCTION]:\n");
	printList(testList);

	assert(testList->head->value == 3 && testList->head->next->value == 9 && testList->head->next->next->value == 11);
	assert(testList->head->next->next->next->value == 15 && testList->head->next->next->next->next->value == 65);
	assert(testList->head->next->next->next->next->next->value == 68 && testList->head->next->next->next->next->next->next->value == 70);
	assert(testList->head->next->next->next->next->next->next->next->value == 75);
	printf("Passed test 6/6.\n");

	deleteList(testList);
	printf("All tests passed. Great job, good sir!\n");

}

void testSortedMerge(void){
	List testList1 = createList();
	List testList2 = createList();
	List listArray[2] = {testList1, testList2};
	List sortedList;
	
	// test empty lists
	testList1->head = NULL;
	testList2->head = NULL;
	printf("Testing empty lists.\n");
	printListStatusMerge(listArray, BEFORE);
	
	sortedList = sortedMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Sorted list:\n");
	printList(sortedList);
	assert(testList1->head == NULL && testList2->head == NULL && sortedList->head == NULL);
	printf("Passed test 1/6.\n");

	// test for when one list contains one element and the other list contains no elements
	printf("Testing with one list containing an element and the other list empty.\n");
	addNode(testList1, 65);
	printListStatusMerge(listArray, BEFORE);
	
	sortedList = sortedMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Sorted list:\n");
	printList(sortedList);
	assert(sortedList->head->value == 65 && sortedList->head->next == NULL);
	assert(testList1->head->value == 65 && testList1->head->next == NULL);
	assert(testList2->head == NULL);
	printf("Passed test 2/6.\n");

	// test for when the value of the first node in list 1 is greater than the valeu of the first node in list 2
	printf("Testing function more rigorously.\n");
	testList1->head = NULL;
	testList2->head = NULL;
	addNode(testList1, 56);
	addNode(testList2, 45);
	printListStatusMerge(listArray, BEFORE);
	
	sortedList = sortedMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Sorted list:\n");
	printList(sortedList);
	assert(sortedList->head->value == 49 && sortedList->head->next->value == 65 && sortedList->head->next->next == NULL);
	assert(testList1->head->value == 65 && testList1->head->next == NULL);
	assert(testList2->head->value == 49 && testList2->head->next == NULL);
	printf("Passed rigorous test.\n");

	// test for when both lists have one element
	printf("Testing for when both lists have one element.\n");
	testList1->head = NULL;
	testList2->head = NULL;
	addNode(testList1, 65);
	addNode(testList2, 45);
	printListStatusMerge(listArray, BEFORE);
	
	sortedList = sortedMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Sorted list:\n");
	printList(sortedList);
	assert(sortedList->head->value == 45 && sortedList->head->next->value == 65 && sortedList->head->next->next == NULL);
	assert(testList1->head->value == 45 && testList1->head->next == NULL);
	assert(testList2->head->value == 65 && testList2->head->next == NULL);
	printf("Passed test 3/6.\n");
	
	// test for when both list are the same size and contain more than one element
	printf("Testing for when both lists are the same size.\n");
	testList1->head = NULL;
	testList2->head = NULL;
	sortedList->head = NULL;
	addNode(testList1, 46);
	addNode(testList1, 55);
	addNode(testList2, 52);
	addNode(testList2, 57);
	printListStatusMerge(listArray, BEFORE);
	
	sortedList = sortedMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Sorted list:\n");
	printList(sortedList);
	assert(sortedList->head->value == 46 && sortedList->head->next->value == 52);
	assert(sortedList->head->next->next->value == 55 && sortedList->head->next->next->next->value == 57);
	assert(testList1->head->value == 46 && testList1->head->next->value == 55);
	assert(testList2->head->value == 52 && testList2->head->next->value == 57);
	printf("Passed test 4/6.\n");

	// test for when one list exceeds the other list
	printf("Testing for when list one exceeds the second list.\n");
	sortedList->head = NULL;
	addNode(testList1, 65);
	printListStatusMerge(listArray, BEFORE);
	
	sortedList = sortedMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Sorted list:\n");
	printList(sortedList);
	assert(sortedList->head->value == 46 && sortedList->head->next->value == 52);
	assert(sortedList->head->next->next->value == 55 && sortedList->head->next->next->next->value == 57 && sortedList->head->next->next->next->next->value == 65);
	assert(testList1->head->value == 46 && testList1->head->next->value == 55 && testList1->head->next->next->value == 65);
	assert(testList2->head->value == 52 && testList2->head->next->value == 57);
	printf("Passed test 5/6.\n");

	// test for when the first list is smaller than the second list
	
	printf("Testing for when list one is smaller than the second list.\n");
	sortedList->head = NULL;
	addNode(testList2, 64);
	addNode(testList2, 66);
	printListStatusMerge(listArray, BEFORE);
	
	sortedList = sortedMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Sorted list:\n");
	printList(sortedList);
	assert(sortedList->head->value == 46 && sortedList->head->next->value == 52);
	assert(sortedList->head->next->next->value == 55 && sortedList->head->next->next->next->value == 57 && sortedList->head->next->next->next->next->value == 64);
	assert(sortedList->head->next->next->next->next->next->value == 65 && sortedList->head->next->next->next->next->next->next->value == 66);
	assert(testList1->head->value == 46 && testList1->head->next->value == 55 && testList1->head->next->next->value == 65);
	assert(testList2->head->value == 52 && testList2->head->next->value == 57 && testList2->head->next->next->value == 64 && testList2->head->next->next->next->value == 66);
	printf("Passed test 6/6.\n");

	
	
	deleteList(testList1);
	deleteList(testList2);
	deleteList(sortedList);

	printf("All the tests have been passed. Well done good sir!.\n");
	
}

void testShuffleMerge(void){
	List testList1 = createList();
	List testList2 = createList();
	List mergedList;
	List listArray[2] = {testList1, testList2};
	nodePtr testNode;
	int i = 0, testValue = 0;
	
	// test an empty list
	printf("Testing an empty list.\n");
	testList1->head = NULL;
	testList2->head = NULL;
	printListStatusMerge(listArray, BEFORE);

	mergedList = shuffleMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);	
	printf("Merged list:\n");
	printList(mergedList);
	assert(mergedList->head == NULL);
	assert(testList1->head == NULL && testList2->head == NULL);
	printf("Passed first test.\n");

	// test when one list contains one node and the other list is empty
	printf("Testing with one node in one list and no ndoes in the other.\n");
	addNode(testList1, TEST_VALUE_1);
	printListStatusMerge(listArray, BEFORE);
	
	mergedList = shuffleMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Merged list:\n");
	printList(mergedList);
	assert(mergedList->head->value == TEST_VALUE_1 && mergedList->head->next == NULL);
	assert(testList1->head->value == TEST_VALUE_1 && testList1->head->next == NULL);
	assert(testList2->head == NULL);
	printf("Passed second test.\n");


	// test when both list have one element
	printf("Testing when both list have exactly one element.\n");
	testList1->head = NULL;
	testList2->head = NULL;
	mergedList->head = NULL;
	addNode(testList1, TEST_VALUE_1);
	addNode(testList2, TEST_VALUE_2);
	printListStatusMerge(listArray, BEFORE);
	
	mergedList = shuffleMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Merged list:\n");
	printList(mergedList);
	assert(testList1->head->value == TEST_VALUE_1 && testList1->head->next == NULL);
	assert(testList2->head->value == TEST_VALUE_2 && testList2->head->next == NULL);
	assert(mergedList->head->value == TEST_VALUE_1 && mergedList->head->next->value == TEST_VALUE_2 && mergedList->head->next->next == NULL);
	printf("Passed third test.\n");

	// test for when one list contains an even number of nodes and one list contains an odd numebr of nodes
	printf("Testing when list1 contains an even number of nodes and list2 contains an odd number of nodes.\n");
	testList1->head = NULL;
	testList2->head = NULL;
	mergedList->head = NULL;
	testValue = TEST_VALUE_1;
	for (i = 0; i < 2; i++){
		addNode(testList1, testValue);
		testValue++;
	}

	for (i = 0; i < 3; i++){
		addNode(testList2, testValue);
		testValue++;
	}

	printListStatusMerge(listArray, BEFORE);
	
	mergedList = shuffleMerge(testList1, testList2);
	printListStatusMerge(listArray, AFTER);
	printf("Merged list:\n");
	printList(mergedList);
	
	testNode = mergedList->head;
	testValue = TEST_VALUE_1;
	for (i = 0; i < 2; i++){
		assert(testNode->value == testValue);
		testNode = testNode->next->next;
		testValue++;
	}

	testNode = mergedList->head->next;
	for (i = 0; i < 1; i++){
		assert(testNode->value == testValue);
		testNode = testNode->next->next;
		testValue++;
	}
	
	// make sure the original two lists were not altered
	testNode = testList1->head;
	testValue = TEST_VALUE_1;
	for (i = 0; i < 2; i++){
		assert(testNode->value == testValue);
		testNode = testNode->next;
		testValue++;
	}
	
	testNode = testList2->head;

	for (i = 0; i < 3; i++){
		assert(testNode->value == testValue);
		testNode = testNode->next;
		testValue++;
	}


	printf("Passed fourth test.\n");
	
	deleteList(testList1);
	deleteList(testList2);
	deleteList(mergedList);
	
	printf("Passed all tests, You are Awesome!\n");

}

void printListStatusMerge(List listArray[], int current){
	printf("[%s FUNCTION]:\n", (current == BEFORE) ? "BEFORE" : "AFTER");
	printf("List 1:\n");
	printList(listArray[0]);
	printf("List 2:\n");
	printList(listArray[1]);
}

void testAlternatingSplit2(void){
	nodePtr currentNode;
	int i = 0, testValue = 0;
	List testSourceList = createList();
	List testList1 = createList();
	List testList2 = createList();
	List testArray[LIST_SIZE_3] = {testSourceList, testList1, testList2};
	
	// test 5 elements in source List
	printf("Testing with five elements.\n");
	testSourceList->head = NULL;
	testList1->head = NULL;
	testList2->head = NULL;
 	i = 0;
	testValue = TEST_VALUE_1;
	while (i < 5){
		addNode(testSourceList, testValue);
		testValue++;
		i++;
	}
	
	printListStatus(testArray, BEFORE);
	alternatingSplit2(testSourceList, testList1, testList2);	
	printListStatus(testArray, AFTER);

	printf("Testing List1.\n");
	currentNode = testList1->head;
	testValue = 56;
	while (currentNode != NULL){
		assert(currentNode->value == testValue);
		testValue -= 2;
		currentNode = currentNode->next;
	}

	printf("Testing List2.\n");
	currentNode = testList2->head;
	testValue = 55;
	while (currentNode != NULL){
		assert(currentNode->value == testValue);
		testValue -= 2;
		currentNode = currentNode->next;
	}

	printf("Passed the fourth test.\n");

	deleteList(testSourceList);
	deleteList(testList1);
	deleteList(testList2);
	
	printf("All tests passed. You are awesome!\n");
}

void testAlternatingSplit(void){
	nodePtr currentNode;
	int i = 0, testValue = 0;
	List testSourceList = createList();
	List testList1 = createList();
	List testList2 = createList();
	List testArray[LIST_SIZE_3] = {testSourceList, testList1, testList2};
	
	testSourceList->head = NULL;
	testList1->head = NULL;
	testList2->head = NULL;
	
	// test an empty source list
	printf("Testing an empty list.\n");
	printListStatus(testArray, BEFORE);
	alternatingSplit(testSourceList, testList1, testList2);
	printListStatus(testArray, AFTER);

	assert(testList1->head == NULL && testList2->head == NULL && testSourceList->head == NULL);
	printf("Passed first test.\n");

	// test one element in sourceList
	printf("Testing with one element.\n");
	addNode(testSourceList, TEST_VALUE_1);
	printListStatus(testArray, BEFORE);
	alternatingSplit(testSourceList, testList1, testList2);
	printListStatus(testArray, AFTER);
	
	assert(testList1->head->value == TEST_VALUE_1 && testList1->head->next == NULL);
	// check that the sourceList wasnt modified
	assert(testSourceList->head->value == TEST_VALUE_1 && testSourceList->head->next == NULL);
	assert(testList2->head == NULL);
	printf("Passed second test.\n");

	// test two elements in sourceList
	printf("Testing with two elements.\n");
	testSourceList->head = NULL;
	testList1->head = NULL;
	testList2->head = NULL;
	addNode(testSourceList, TEST_VALUE_1);
	addNode(testSourceList, TEST_VALUE_2);
	printListStatus(testArray, BEFORE);
	alternatingSplit(testSourceList, testList1, testList2);
	printListStatus(testArray, AFTER);
	
	assert(testSourceList->head->value == TEST_VALUE_1 && testSourceList->head->next->value == TEST_VALUE_2 && testSourceList->head->next->next == NULL);
	assert(testList1->head->value == TEST_VALUE_1 && testList1->head->next == NULL);
	assert(testList2->head->value == TEST_VALUE_2 && testList2->head->next == NULL);
	printf("Passed third test.\n");

	// test 5 elements in source List
	printf("Testing with five elements.\n");
	testSourceList->head = NULL;
	testList1->head = NULL;
	testList2->head = NULL;
 	i = 0;
	testValue = TEST_VALUE_1;
	while (i < 5){
		addNode(testSourceList, testValue);
		testValue++;
		i++;
	}
	
	printListStatus(testArray, BEFORE);
	alternatingSplit(testSourceList, testList1, testList2);	
	printListStatus(testArray, AFTER);
	
	testValue = TEST_VALUE_1;
	currentNode = testSourceList->head;
	printf("Testing sourceList.\n");
	while (currentNode != NULL){
		assert(currentNode->value == testValue);
		testValue++;
		currentNode = currentNode->next;
	}

	printf("Testing List1.\n");
	currentNode = testList1->head;
	testValue = TEST_VALUE_1;
	while (currentNode != NULL){
		assert(currentNode->value == testValue);
		testValue += 2;
		currentNode = currentNode->next;
	}

	printf("Testing List2.\n");
	currentNode = testList2->head;
	testValue = TEST_VALUE_2;
	while (currentNode != NULL){
		assert(currentNode->value == testValue);
		testValue += 2;
		currentNode = currentNode->next;
	}

	printf("Passed the fourth test.\n");

	deleteList(testSourceList);
	deleteList(testList1);
	deleteList(testList2);
	
	printf("All tests passed. You are awesome!\n");
	

}

void printListStatus(List listArray[], int tested){
	printf("[%s FUNCTION]:\n", (tested == BEFORE) ? "BEFORE" : "AFTER");
	printf("SourceList:\n");
	printList(listArray[0]);
	printf("List 1:\n");
	printList(listArray[1]);
	printf("List 2:\n");
	printList(listArray[2]);
	
}

void testMoveNode(void){
	int i = 0;
	List testList1 = createList();
	List testList2 = createList();
	testList1->head = NULL;
	testList2->head = NULL;
	// test an empty list
	printf("Testing empty list.\n");
	moveNode(testList1, testList2);
	assert(testList1->head == NULL && testList2->head == NULL);
	printf("Passed first test.\n");

	// test with one node in the second list
	addNode(testList2, TEST_VALUE_1);
	printf("\nTesting with one node in second list.\n");
	printf("[BEFORE FUNCTION]: \n");
	printf("List 1:\n");
	printList(testList1);
	printf("List 2:\n");
	printList(testList2);

	moveNode(testList1, testList2);
	printf("[AFTER FUNCTION]: \n");
	printf("List 1:\n");
	printList(testList1);
	printf("List 2:\n");
	printList(testList2);
	assert(testList1->head->value == TEST_VALUE_1 && testList1->head->next == NULL);
	assert(testList2->head == NULL);
	printf("Passed second test.\n");

	// test with one node in each list
	testList1 = createList();
	testList2 = createList();
	addNode(testList1, TEST_VALUE_1);
	addNode(testList2, TEST_VALUE_2);
	
	printf("\nTesting with one node in each list.\n");
	printf("[BEFORE FUNCTION]: \n");
	printf("List 1:\n");
	printList(testList1);
	printf("List 2:\n");
	printList(testList2);

	moveNode(testList1, testList2);
	printf("[AFTER FUNCTION]: \n");
	printf("List 1:\n");
	printList(testList1);
	printf("List 2:\n");
	printList(testList2);

	assert(testList1->head->value == TEST_VALUE_2 && testList1->head->next->value == TEST_VALUE_1);
	assert(testList1->head->next->next == NULL && testList2->head == NULL);
	printf("Passed third test.\n");

	// test with 2 nodes in first list and 3 nodes in second list
	printf("\nTesting with list1 having 2 nodes and list2 having 3 nodes.\n");
	testList1 = createList();
	testList2 = createList();
	while (i < 2){
		addNode(testList1, TEST_VALUE_1);
		i++;
	}

	i = 0;
	addNode(testList2, 65);
	while (i < 2){
		addNode(testList2, TEST_VALUE_2);
		i++;
	}

	printf("[BEFORE FUNCTION]: \n");
	printf("List 1:\n");
	printList(testList1);
	printf("List 2:\n");
	printList(testList2);

	moveNode(testList1, testList2);
	printf("[AFTER FUNCTION]: \n");
	printf("List 1:\n");
	printList(testList1);
	printf("List 2:\n");
	printList(testList2);

	assert(testList1->head->value == 65 && testList1->head->next->value == TEST_VALUE_1 && testList1->head->next->next->value == TEST_VALUE_1);
	assert(testList1->head->next->next->next == NULL);
	assert(testList2->head->value == TEST_VALUE_2 && testList2->head->next->value == TEST_VALUE_2 && testList2->head->next->next == NULL);
	printf("Passed fourth test.\n");
	printf("Passed all tests. You are Awesome!\n");
	
	deleteList(testList1);
	deleteList(testList2);
}

void testDeleteNode(void){
	nodePtr tempNode;
	List list1 = createList();
	list1->head = NULL;
	addNode(list1, TEST_VALUE_1);
	addNode(list1, TEST_VALUE_2);
	addNode(list1, TEST_VALUE_3);
	addNode(list1, TEST_VALUE_4);
	tempNode = list1->head->next->next;

	// test if the delete function clears the list
	assert(list1->head->next->next->value == TEST_VALUE_3);
	printf("[BEFORE FUNCTION]\n");
	printf("Address tempNode points to %p.\n", tempNode);
	printList(list1);
	deleteList(list1);
	printf("[AFTER FUNCTION]\n");
	printList(list1);
	printf("Address tempNode points to %p.\n", tempNode);
	assert(list1->head == NULL);
	

	printf("Passed all tests. You are phenomenal!\n");

}


void testFunctions(void){
	int testValue = 5, i = 0;
	nodePtr newNode, nodeInList;

	srand(time(NULL));
	List lTest = malloc(sizeof(*lTest));
	lTest->head = NULL;
	addNode(lTest, testValue);
	printList(lTest);
	assert(lTest->head->value == testValue);
	printf("Passed first test for adding node to empty list.\n\n");
	
	nodeInList = lTest->head;
	// test the case where there are already nodes in the list
	while (i < 3){
		newNode = malloc(sizeof(node));
		testValue = 1 + rand() % 6;
		nodeInList->next = newNode;
		nodeInList = nodeInList->next;
		nodeInList->value = testValue;
		i++;
	}

	nodeInList->next = NULL;
	printList(lTest);
	assert(getLength(lTest) == 4);
	printf("Passed test length of list = %d\n", getLength(lTest));
	printf("Testing idea....\n");
	printf("Idea value = %d.\n", lTest->head->next->next->next->value);

	/*
		nodeInList is just a pointer to a node, so if nodeInList is assigned to another node
		then it just simply points to the newNode. This does not alter anything in the list if this process is 
		done similiar to the process below.

		NOTE: to change things in a list, must use the nodePtr->next = newNode;




	*/

	printf("Doing discovery.\n");
	newNode = malloc(sizeof(node));
	newNode->value = 9999;
	newNode->next = lTest->head->next->next->next;
	printf("Mem address of newNode: %p.\n", newNode);
	nodeInList = lTest->head->next->next;
	printf("Mem address of nodeInList (third node): %p.\n", nodeInList); 
	nodeInList = newNode;
	printf("Mem address of third node ( -> new node): %p.\n", nodeInList);
	printf("Mem address of third node access from list: %p.\n", lTest->head->next->next);
	printf("The second node is pointing to: %p.\n", lTest->head->next->next);
	printList(lTest);
	printf("To change pointers in a list: \n");
	lTest->head->next->next = newNode;
	printList(lTest);
	// test the delete function
	printf("Address of ltest = %p.\n", lTest);
	
	// this shows that we have to loop through the list to delete each node
	nodePtr tempNode;
	tempNode = lTest->head->next;
	free(lTest);
	printf("Address of lTest->head = %p.\n", lTest->head);
	printf("Address tempNode -> to = %p.\n", tempNode);
	printf("Address of tempNode = %p.\n", &tempNode);
	int testV = TEST_VALUE_1;
	printf("++x or x++: %d.\n", testV++);
	printf("testV = %d.\n", testV); 
	
	free(newNode);
	
}

void testFrontBackSplit(void){
	nodePtr newNode, nodeInList;
	int testValue = TEST_VALUE_1, i = 0;
	List testList = malloc(sizeof(*testList));
	List frontList = malloc(sizeof(*frontList));
	List backList = malloc(sizeof(*backList));
	
	// test an empty list
	printf("Testing empty list.\n");
	testList->head = NULL;
	frontList->head = NULL;
	backList->head = NULL;
	frontBackSplit(testList, frontList, backList);
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);
	assert(frontList->head == NULL && backList->head == NULL);
	printf("Passed test for empty list.\n\n");
	
	// test a list with one element
	// the one element should go into the frontList
	printf("Testing with one element.\n");
	newNode = malloc(sizeof(node));
	newNode->value = TEST_VALUE_1;
	newNode->next = NULL;
	testList->head = newNode;
	frontBackSplit(testList, frontList, backList);
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);
	assert(frontList->head->value == TEST_VALUE_1 && frontList->head->next == NULL);
	assert(backList->head == NULL);
	printf("Passed test for one element.\n\n");
	
	// test a list with 2 elements
	printf("Testing with two elements.\n");
	nodeInList = testList->head;
	nodeInList->value = TEST_VALUE_1;
	nodeInList->next = NULL;
	testValue++;
	while (i < 1){
		newNode = malloc(sizeof(node));
		newNode->value = testValue;
		newNode->next = NULL;
		nodeInList->next = newNode;	
		nodeInList = nodeInList->next;	
		i++;
	}

	frontList->head = NULL;
	backList->head = NULL;
	printf("[BEFORE FUNCTION].\n");
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);

	frontBackSplit(testList, frontList, backList);

	printf("[AFTER FUNCTION].\n");
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);

	assert(frontList->head->value == TEST_VALUE_1 && frontList->head->next == NULL);
	assert(backList->head->value == TEST_VALUE_2 && backList->head->next == NULL);
	printf("Passed test for 2 elements.\n\n");

	// test a list with 3 elements
	printf("Testing with 3 elements.\n");
	testValue = TEST_VALUE_1;
	testList->head->value = testValue;
	testList->head->next = NULL;
	nodeInList = testList->head;
	testValue++;
	i = 0;
	while (i < 2){
		newNode = malloc(sizeof(node));
		if (newNode != NULL){
			printf("Iterations.\n");
		}
		newNode->value = testValue;
		newNode->next = NULL;
		nodeInList->next = newNode;	
		nodeInList = nodeInList->next;	
		i++;
		testValue++;
		
	}
	
	frontList->head = NULL;
	backList->head = NULL;

	printf("[BEFORE FUNCTION].\n");
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);

	frontBackSplit(testList, frontList, backList);

	printf("[AFTER FUNCTION].\n");
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);
	
	assert(frontList->head->value == TEST_VALUE_1 && frontList->head->next->value == TEST_VALUE_2 && frontList->head->next->next == NULL);
	assert(backList->head->value == TEST_VALUE_3 && backList->head->next == NULL);
	printf("Passed test for 3 elements.\n\n");

	// test a list with 4 elements
	printf("Testing with 4 elements.\n");
	testValue = TEST_VALUE_1;
	testList->head->value = testValue;
	testList->head->next = NULL;
	nodeInList = testList->head;
	testValue++;
	i = 0;
	while (i < 3){
		newNode = malloc(sizeof(node));
		newNode->value = testValue;
		newNode->next = NULL;
		nodeInList->next = newNode;
		nodeInList = nodeInList->next;
		i++;
		testValue++;
	}

	frontList->head = NULL;
	backList->head = NULL;
	printf("[BEFORE FUNCTION].\n");
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);
	

	frontBackSplit(testList, frontList, backList);
	printf("[AFTER FUNCTION].\n");
	printf("Source list: \n");
	printList(testList);
	printf("Front list: \n");
	printList(frontList);
	printf("Back List: \n");
	printList(backList);
	
	assert(frontList->head->value == TEST_VALUE_1 && frontList->head->next->value == TEST_VALUE_2 && frontList->head->next->next == NULL);
	assert(backList->head->value == TEST_VALUE_3 && backList->head->next->value == TEST_VALUE_4 && backList->head->next->next == NULL);
	printf("Passed the test with 4 elements.\n\n");

	printf("All tests passed, you are awesome.\n");
	free(testList);
	free(frontList);
	free(backList);
	free(newNode);
	printf("Freed all lists and nodes.\n");


}
