/*
	Name: Matthew Ta
	Date: 20/10/2015
	Description: Implementation of the splay ADT
*/

#include <stdio.h>
#include <stdlib.h>

#include "splay.h"
#include "queue.h" // use the queue ADT

// boolean constants
#define TRUE 1
#define FALSE 0

#define DEBUG

/* Notes:
	* Splay trees basically involve double rotations 
	4 cases to be considered:
	ZIG ZIG:
	* left child of left child -> rotate through grand parent i.e rotate n then n (right rotations)
	* right child of right child -> rotate through grand parent i.e rotate n then n (left rotations)
	
	ZIG ZAG
	* left child of right child -> rotate through parent then grandparent rotate n->right right then rotate n left
	* right child of left child -> rotate through parent then grandparent i.e rotate n->left left then rotate n right
	
	Also when the node is to be inserted/deleted/searched after the root node
*/

// helper functions
static Link newNode(int value); // creates a new node with a value and returns it

Link rotateLeft(Link t); // rotates a tree left
Link rotateRight(Link t); // rotates a tree right 

Link splayJoin(Link s, Link t); // join trees s and t
void levelOrder(Link n); // prints the tree in level order

typedef struct _treeRep{
	Link root;
} treeRep;

typedef struct _tnode{
	int value;
	Link left;
	Link right;	
} tnode;

Tree newTree(void)
{
	Tree t = malloc(sizeof(treeRep));
	t->root = NULL;
	return t;
}

/* ====== Delete a splay tree =========== */
void disposeTree(Tree t)
{
	void deleteTree(Link n); // deletes the tree using post order traversal
	deleteTree(t->root);
}

void deleteTree(Link n)
{
	if (n != NULL){
		deleteTree(n->left);
		deleteTree(n->right);
		free(n);
	}
}

/* ========= inserting into a splay tree ========= */
void insertValue(Tree t, int value)
{
	Link insertSplay(Link n, int value); // insert a value into t using splay method
	t->root = insertSplay(t->root, value);
	#ifdef DEBUG
	printf("Inserted value = %d into tree using splay method.\n", value);
	#endif
}

/*
	Notes:
	* tree insertion using splay method
	* produces different results to the visualiser

*/
Link insertSplay(Link n, int value)
{
	if (n == NULL) { return newNode(value); }

	if (value < n->value){ // right rotations
		if (n->left == NULL){ // left branch is NULL
			n->left = newNode(value);
		}

		else if (value < n->left->value){ // zig zig left
			n->left->left = insertSplay(n->left->left, value);
			// n->left = rotateRight(n->left);
			n = rotateRight(n);
		}

		else{ // zig zag left
			n->left->right = insertSplay(n->left->right, value);
			n->left = rotateLeft(n->left);
		}

		n = rotateRight(n);
	}

	if (value > n->value){ // left rotations
		if (n->right == NULL){
			n->right = newNode(value);
		}

		else if (value > n->right->value){ // zig zig right
			n->right->right = insertSplay(n->right->right, value);
			// n->right = rotateLeft(n->right);
			n = rotateLeft(n);
		}

		else{ // zig zag right
			n->right->left = insertSplay(n->right->left, value);
			n->right = rotateRight(n->right);
		}
		
		n = rotateLeft(n);
	}

	return n;
}

/* ============= splay searching ================= */
int search(Tree t, int value)
{
	int located = FALSE;
	Link splaySearch(Link n, int value, int *found); // splay searches a value
	t->root = splaySearch(t->root, value, &located);
	return located;
}

/* 
	Notes:
	* the element found is splayed to the top root
*/
Link splaySearch(Link n, int value, int *found)
{
	if (n == NULL) { return NULL; }
	
	if (value == n->value){
		*found = TRUE;
	}

	else if (value < n->value){ // rotate right
		if (n->left != NULL){
			if (value == n->left->value){ // found the value
				*found = TRUE;
			}
	
			else if (value < n->left->value){ // zig zig 
				n->left->left = splaySearch(n->left->left, value, found);
				// n->left = rotateRight(n->left);
				n = rotateRight(n);
			}

			else{ // zig zag
				n->left->right = splaySearch(n->left->right, value, found);
				n->left = rotateLeft(n->left);
			}
			n = rotateRight(n);
		}
	}

	else{ // value is > n->value, rotate left
		if (n->right != NULL){
			if (value == n->right->value){ // found the value
				*found = TRUE;
			}				
		
			else if (value > n->right->value){ // zig zig
				n->right->right = splaySearch(n->right->right, value, found);
				// n->right = rotateLeft(n->right);
				n = rotateLeft(n);
			}

			else{ // zig zag
				n->right->left = splaySearch(n->right->left, value, found);
				n->right = rotateRight(n->right);
			}
		}
		n = rotateLeft(n);
	}

	return n;
}

/* ======================= Splay deletion ====================== */
void removeValue(Tree t, int value)
{
	Link splayDelete(Link n, int value); // deletes a node from a splay tree
	t->root = splayDelete(t->root, value);
}

/*
	Notes:
	* splay the node to be deleted to the top of the tree
	* delete the node leaving two subtrees
	* use a join operation to join the two subtrees s and t
	* Note the nodes in the tree s have to be < the nodes in tree t
*/
Link splayDelete(Link n, int value)
{
	Link rightNode = NULL, leftNode = NULL, newTree = NULL;
	int found = 0;

	n = splaySearch(n, value, &found); // search for the value to be deleted, this value should be at the root
	leftNode = n->left;
	rightNode = n->right;
	free(n);
	
	newTree = splayJoin(leftNode, rightNode); // join the two subtrees
	return newTree;
}

// joins two trees
Link splayJoin(Link t, Link s)
{
	int largestValue = 0, found = 0;

	// helper functions
	int findLargestValue(Link n);
		
	// splay the largest element in t
	if (t == NULL) { return s; }
	largestValue = findLargestValue(t);
	t = splaySearch(t, largestValue, &found);

	// assign s to the right child of t
	t->right = s;
	return t;
}

// fund through the right subtree to find the largest value
int findLargestValue(Link t)
{
	int largestValue = 0;
	if (t->right == NULL) { return t->value; }

	largestValue = findLargestValue(t->right);
	return largestValue;
}

void printTree(Tree t)
{
	levelOrder(t->root);
}

// Note: Level order cannot be done recursively
void levelOrder(Link n)
{
	Queue q = newQueue();
	Link curNode = NULL;
	enQueue(q, n);
	while ( !emptyQueue(q) ){
		curNode = deQueue(q);
		if (curNode->left != NULL){
			enQueue(q, curNode->left);
		}

		if (curNode->right != NULL){
			enQueue(q, curNode->right);
		}
		printf("%d ", curNode->value);
	} 
	printf("\n");
	deleteQueue(q);
}

static Link newNode(int value)
{
	Link n = malloc(sizeof(tnode));
	n->value = value;
	n->left = NULL;
	n->right = NULL;
	return n;
}

// rotates the tree left
Link rotateLeft(Link t)
{
	Link t2 = NULL;
	if (t == NULL) { return NULL; }
	t2 = t->right;
	if (t2 == NULL) { return t; }
	t->right = t2->left;
	t2->left = t;
	return t2; // t2 is now root
}

// rotates the tree right
Link rotateRight(Link t)
{
	Link t2 = NULL;
	if (t == NULL) { return NULL; }
	t2 = t->left;
	if (t2 == NULL) { return t; }
	t->left = t2->right;
	t2->right = t; // t2 is now root
	return t2;
}






