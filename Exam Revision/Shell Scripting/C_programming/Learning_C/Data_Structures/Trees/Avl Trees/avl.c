/*	
	Name: Matthew Ta
	Date: 24/10/2015
	Description: Implementation of ADT for AVL trees
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "avl.h"
#include "queue.h"

#define TRUE 1
#define FALSE 0

/*
	AVL Notes:
	* is a height balanced BST
	* insertion at leaves causes imbalance
	* repair the imbalance as soon as it occurs
	* unbalanced when abs(depth(left) - depth(right)) > 1
	* determining height of subtrees may be expensive, instead store the depth in the node, increases space complexity but not much
	* rotate right when left subtree too deep
	* rotate left when right subtree too deep
	* O(log(n)) average/worst case time complexity
	* searching in an AVL tree is the same as for an unbalanced BST
	* height balanced but not weight balanced (i.e # nodes in each subtree)

	Note: This algorithm is sub-optimal i.e it may not always repair the height imbalance
*/

// tree functions
void deleteTree(Link n);
Link insertAvl(Link n, int value); // insert a node into the tree using AVL method
int getDepth(Link n); // returns the depth of the tree from the node n
int determineDepth(Link n); // determines the new depth of a tree
Link rotateLeft(Link n); // rotate a tree left
Link rotateRight(Link n); // rotate a tree right
Link deleteAvl(Link n, int value); // deletes a value from AVL maintaining the tree in AVL
int searchAvl(Link n, int value); // searches the AVL tree for a value
void levelOrder(Link n); // prints the tree in level order

// helper functions
static Link newNode(int value); // creates and returns a new node
int findMax(Link n); // finds the max element node

typedef struct _treeRep{
	Link root;
} treeRep;

typedef struct _tnode{
	int value;
	int depth;
	Link left;
	Link right;
} tnode;

// creates a new tree
Tree newTree(void)
{
	Tree t = malloc(sizeof(treeRep));
	t->root = NULL;
	return t;
}

// frees a tree
void disposeTree(Tree t)
{
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

// insert a value into the tree
void insertValue(Tree t, int value)
{
	t->root = insertAvl(t->root, value);
	t->root->depth = determineDepth(t->root);
}

// inserts a value into the tree using avl method
Link insertAvl(Link n, int value)
{
	if (n == NULL){ return newNode(value); } // base case
	if (value == n->value){ // basically ignoring duplicates
		n->value = value; 
	}

	else if (value < n->value){ // go down left branch
		n->left = insertAvl(n->left, value);
	}

	else{ // value > n->value
		n->right = insertAvl(n->right, value);
	}
	
	// check if the subtree is not unbalanced
	int leftDepth = determineDepth(n->left);
	int rightDepth = determineDepth(n->right);
	if ((leftDepth - rightDepth) > 1){ // left sub tree is deeper then right
		n = rotateRight(n);
	}

	else if ((rightDepth - leftDepth) > 1){ // right sub tree is deeper then left
		n = rotateLeft(n);
	}
	
	return n;
}

// remove one value from the tree
void removeValue(Tree t, int value)
{
	t->root = deleteAvl(t->root, value);
	t->root->depth = determineDepth(t->root);
}

// remove a value from the tree maintaing the tree in AVL
Link deleteAvl(Link n, int value)
{
	if (n == NULL) { return NULL; }	
	
	if (value == n->value){
		// case 1: leaf
		if (n->left == NULL && n->right == NULL){	
			free(n);
			return NULL;
		}

		// case 2: 1 child
		else if (n->left == NULL && n->right != NULL){
			return n->right;
		}

		else if (n->right == NULL && n->left != NULL){
			return n->left;
		}

		// case 3: 2 children
		else{
			int maxValue = findMax(n->left);
			n->value = maxValue;
			// n->left->depth--;
			n->left = deleteAvl(n->left, maxValue);
		}
	}

	else if (value < n->value){
		// n->left->depth--;
		n->left = deleteAvl(n->left, value);
	}

	else{ // value > n->value
		// n->right->depth--;
		n->right = deleteAvl(n->right, value);
	}

	int leftDepth = determineDepth(n->left);
	int rightDepth = determineDepth(n->right);

	// check for height balance
	if ((leftDepth - rightDepth) > 1){ // left subtree is causing unbalance
		n = rotateRight(n);
	}

	else if ((rightDepth - leftDepth) > 1){ // right subtree is causing unbalance
		n = rotateLeft(n);
	}
	
	return n;
}

// finds the max value in a tree
int findMax(Link n)
{
	if (n->right == NULL) { return n->value; }
	int maxValue = findMax(n->right);
	return maxValue;
}

// searches for a value
int search(Tree t, int value)
{
	int found = FALSE;
	found = searchAvl(t->root, value);
	return found;
}

// searches the AVL tree for a value
int searchAvl(Link n, int value)
{
	int found = FALSE;
	if (n == NULL) { return FALSE; }
	
	if (value == n->value){
		found = TRUE;
	}

	else if (value < n->value){
		found = searchAvl(n->left, value);
	}

	else{
		found = searchAvl(n->right, value);
	}

	return found;
}

// get the depth of the tree
int getTreeDepth(Tree t)
{
	int d = getDepth(t->root);
	return d;
}

int getDepth(Link n)
{
	if (n != NULL) { return n->depth; }
	else { return 0; }
}

// calculate the depth of the tree
int determineDepth(Link n)
{
	if (n == NULL) { return 0; } // base case
	int leftDepth = determineDepth(n->left);
	int rightDepth = determineDepth(n->right);
	int depth = 1 + ((leftDepth > rightDepth) ? leftDepth : rightDepth);
	n->depth = depth;
	return depth;
}

// rotates the tree left
Link rotateLeft(Link n)
{
	Link n2 = NULL;
	if (n == NULL) { return NULL; }
	n2 = n->right;
	if (n2 == NULL) { return n; }
	n->right = n2->left;
	n2->left = n;
	return n2;
}

// rotates the tree right
Link rotateRight(Link n)
{
	Link n2 = NULL;
	if (n == NULL) { return NULL; }
	n2 = n->left;
	if (n2 == NULL) { return n; }
	n->left = n2->right;
	n2->right = n;
	return n2;
}

// creates a new node
static Link newNode(int value)
{
	Link n = malloc(sizeof(tnode));
	n->value = value;
	n->depth = 1;
	n->left = NULL;
	n->right = NULL;
	return n;
}

void printTree(Tree t)
{
	levelOrder(t->root);
}

void levelOrder(Link n)
{
	Queue q = newQueue();
	Link cur = NULL;
	enQueue(q, n);

	while ( !emptyQueue(q) ){
		cur = deQueue(q);
		if (cur->left != NULL) { enQueue(q, cur->left); }
		if (cur->right != NULL) { enQueue(q, cur->right); }
		printf("[v = %d, depth =  %d]\n", cur->value, cur->depth);
	}
	
	printf("\n");
	deleteQueue(q);
}





