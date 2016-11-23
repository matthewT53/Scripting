/*
	Name: Matthew Ta
	Date: 2/11/2015
	Description: Implementation of the ADT for red and black trees
*/

#include <stdio.h>
#include <stdlib.h>

#include "rb.h"

// boolean constants
#define TRUE 1
#define FALSE 0

// some macros
#define isRed(n) (n != NULL && n->clr == RED) // determines if a node's colour is red
#define cmp(a, b) (a - b) // calculates the differene between two numbers a,b
#define swapColour(n) \
						if (n != NULL)\
						{ \
							if (n->clr == RED){ \
								n->clr = BLACK; \
							} \
						    else { \
								n->clr = RED; \
							} \
						}  // swaps the colour of a node

// constants for the position of the double black
#define LEFT 0
#define RIGHT 1

#define DEBUG // debugging constant

typedef enum {RED = 0, BLACK} Colour;

typedef struct _rbRep{
	Node root; // contains the root node
} rbRep;

typedef struct _node{
	int value;
	Node left;
	Node right;
	Colour clr; // red or black
} node;

// tree functions
void deleteTree(Node n); // deletes a tree
Node insert_rb(Node n, int value); // inserts a value into the tree
Node search_rb(Node n, int value); // searches for a node containing a value
Node remove_rb(Node n, int value, int *db); // removes a value from the tree

// functions to deal with the cases of deletion
Node redSibling(Node *p, Node *u, int dbPos, int *db); // deals with the case when the sibling of a db is red
Node blackSibling(Node *p, Node *u, int dbPos, int *db); // deals with the case when the siblnig of a db is black

// rotations
Node rotateLeft(Node n); // rotates the tree left
Node rotateRight(Node n); // rotates the tree right

// tree output functions
void preOrder(Node n);
void postOrder(Node n);
void inOrder(Node n);

// find inorder successor (smallest value in right subtree)
int findSuccessor(Node n);

static Node newNode(int value, Colour clr); // creates a new node

// create a new tree
Tree newTree(void)
{
	Tree rb = malloc(sizeof(rbRep));
	rb->root = NULL;
	return rb;
}

// free the tree
void disposeTree(Tree rb)
{
	if (rb != NULL) { deleteTree(rb->root); }	
}

void deleteTree(Node n)
{
	if (n != NULL){
		deleteTree(n->left);
		deleteTree(n->right);
		free(n);
	}
}

// insert a value into the tree
void insertValue(Tree rb, int value)
{
	if (rb != NULL){
		rb->root = insert_rb(rb->root, value);
		if (isRed(rb->root)){ // make root node always black
			swapColour(rb->root)
		}
	}
}

/*
	Time complexity: O(log(n))
	Parent: n->left || n->right
	GP: n
*/
Node insert_rb(Node n, int value)
{
	if (n == NULL) { return newNode(value, RED); }
	int diff = cmp(value, n->value);

	// red and black tree is isometric to 2-3-4 trees so need to do the split thing (top down approach)
	if (n->clr == BLACK && isRed(n->left) && isRed(n->right)){ // split and promote
		n->clr = RED;
		n->left->clr = BLACK;
		n->right->clr = BLACK;
	}

	// the value is already in the tree
	if (diff == 0){
		n->value = value;
	}

	else if (diff < 0){
		n->left = insert_rb(n->left, value);
		// fix each layer after insertion method
		if (isRed(n->left) && isRed(n->right) && isRed(n->left->left)){ // case 3 on wikipedia
			swapColour(n) // swap the colours of the GP, P and uncle
			swapColour(n->right)
			swapColour(n->left)
		}

		else if (isRed(n->left) && isRed(n->left->right)){ // case 4
			n->left = rotateLeft(n->left); // rotate left about parent
		}

		else if (isRed(n->left) && isRed(n->left->left)){ // case 5
			swapColour(n);
			swapColour(n->left);
			n = rotateRight(n); // rotate right about GP
		}
	}

	else{ // diff > 0
		n->right = insert_rb(n->right, value);
		if (isRed(n->left) && isRed(n->right) && isRed(n->right->right)){ // case 3
			swapColour(n)
			swapColour(n->left)
			swapColour(n->right)
		}

		else if (isRed(n->right) && isRed(n->right->left)){ // case 4
			n->right = rotateRight(n->right); // rotate right about parent
		}

		else if (isRed(n->right) && isRed(n->right->right)){ // case 5
			swapColour(n);
			swapColour(n->right);
			n = rotateLeft(n); // rotate about left about GP
		}
	}
	
	return n;
}



// search for a value
int searchValue(Tree rb, int value)
{
	if (rb != NULL){
		Node retNode = search_rb(rb->root, value);
		if (retNode != NULL) { return TRUE; }
	}
	
	return FALSE;
}

Node search_rb(Node n, int value)
{
	Node retNode = NULL;
	if (n == NULL) { return NULL; } // reached the end of a branch

	if (value == n->value){ // found the value
		return n;
	}

	else if (value < n->value){ // check left branch
		retNode = search_rb(n->left, value);
	}

	else{ // check right branch
		retNode = search_rb(n->right, value);
	}

	return retNode;
}

// delete a value
void removeValue(Tree rb, int value)
{
	int doubleBlack = FALSE;
	if (rb != NULL){ 
		rb->root = remove_rb(rb->root, value, &doubleBlack);
		if (isRed(rb->root)){ swapColour(rb->root) }
	}
}

Node remove_rb(Node n, int value, int *db) // note: db = double black
{
	if (n == NULL) { return NULL; } // basically, the value was not found
	Node retNode = NULL;
	int diff = cmp(value, n->value);

	if (diff == 0){ // found the value to be deleted
		if (n->left == NULL && n->right == NULL){ // delete a leaf
			if (n->clr == BLACK) { *db = TRUE; } // NULL nodes count as black nodes by def of red and black tree
			free(n);
			return NULL;
		}
	
		else if (n->left != NULL && n->right == NULL){ // node has left child
			retNode = n->left;
			if (!isRed(n) && !isRed(n->left)){ *db = TRUE; } // two black nodes -> db node		
			else{ n->left->clr = BLACK; }
			free(n);
			return retNode;
		}

		else if (n->right != NULL && n->left == NULL){ // node has right child
			retNode = n->right;
			if (!isRed(n) && !isRed(n->right)){ *db = TRUE; }
			else { n->right->clr = BLACK; }
			free(n);
			return retNode;
		}

		else{ // node has two children
			int successor = findSuccessor(n->right);
			n->value = successor;
			n->right = remove_rb(n->right, successor, db); // remove the successor
		}
	}

	else if (diff < 0){ // search the left subtree
		n->left = remove_rb(n->left, value, db);
		// now fix up the tree's properties
		if (*db){ // deletion produced a double black node
			#ifdef DEBUG
				printf("Double black detected.\n");
			#endif
			if (isRed(n->right)){
				n = redSibling(&n, &(n->right), LEFT, db);
			}

			else{ // sibling is black
				n = blackSibling(&n, &(n->right), LEFT, db);
			}
		}
	}

	else{ // diff > 0, search the right subtree
		n->right = remove_rb(n->right, value, db);
		if (*db){
			#ifdef DEBUG
				printf("Double black detected.\n");
			#endif
			if (isRed(n->left)){	
				n = redSibling(&n, &(n->left), RIGHT, db);
			}

			else{
				n = blackSibling(&n, &(n->left), RIGHT, db);
			}
		}
	}
	return n;
}

// handles the case with a db and a red sibling
Node redSibling(Node *p, Node *u, int dbPos, int *db)
{
	#ifdef DEBUG
		printf("Red sib case.\n");
	#endif
	if (p != NULL && u != NULL){
		swapColour((*p)) // swap the colour of p and sib
		swapColour((*u))
		if (dbPos == LEFT){ // double black node is on the left
			(*p) = rotateLeft(*p); // u is now the new p
			(*p)->left = blackSibling(&(*p)->left, &(*p)->left->right, LEFT, db); // function overhead by makes code neater, detect if sibling of p->left has black children
		}

		else{
			(*p) = rotateRight(*p);
			(*p)->right = blackSibling(&(*p)->right, &(*p)->right->left, RIGHT, db);
		}
	}

	return *p;
}

// handles the case with a db and a black sibling (this has many sub cases)
Node blackSibling(Node *p, Node *u, int dbPos, int *db)
{
	#ifdef DEBUG
		printf("Black sib case.\n");
	#endif
	if (*p != NULL && *u != NULL){
		if (!isRed((*u)->left) && !isRed((*u)->right)){ // both sibling's children are black nodes
			(*u)->clr = RED; // remove black from sibling
			if ((*p)->clr == RED){ (*p)->clr = BLACK; *db = FALSE; }
			else { *db = TRUE; }
		}

		else if (isRed((*u)->left) && !isRed((*u)->right)){
			#ifdef DEBUG
				printf("One child is red.\n");
			#endif
			int tmpColour = (*u)->clr; // swap u's colour with u's left child
			if (dbPos == LEFT){ // db on left so right-left case
				(*u)->clr = (*u)->left->clr;
				(*u)->left->clr = tmpColour;
			}

			else{ // db on right so this is left-right case
				(*u)->clr = (*u)->right->clr;
				(*u)->right->clr = tmpColour;
			}
		}

		else{ 
			#ifdef DEBUG
				printf("RR or LL.\n");
			#endif
			int tempColour = (*u)->clr; // swap colour of u and p
			if (dbPos == LEFT){ // db is on left so right right case
				(*u)->right->clr = BLACK; // remove red from right child of w
				(*u)->clr = (*p)->clr;
				(*p)->clr = tempColour;
				*p = rotateLeft(*p); // rotate p left
			}

			else{ // db is on right so left left case
				(*u)->left->clr = BLACK;
				(*u)->clr = (*p)->clr;
				(*p)->clr = tempColour;
				*p = rotateRight(*p);
			}
			*db = FALSE; // remove black from the db node
		}
	}
	return *p;
}

int findSuccessor(Node n)
{
	if (n->left == NULL){
		return n->value;
	}

	int smallest = findSuccessor(n->left);
	return smallest;
}

// rotation functions
Node rotateLeft(Node n)
{
	if (n == NULL) { return NULL; }
	Node n2 = n->right;
	if (n2 == NULL) { return n; }
	n->right = n2->left;
	n2->left = n;
	return n2;
}

Node rotateRight(Node n)
{
	if (n == NULL){ return NULL; }
	Node n2 = n->left;
	if (n2 == NULL) { return n; }
	n->left = n2->right;
	n2->right = n;
	return n2;
}

// outputs the red and black tree
void printTree(Tree rb, int order)
{
	switch (order){
		case PREORDER: printf("[PREORDER]:\n"); preOrder(rb->root); break;
		case POSTORDER: printf("[POSTORDER]:\n"); postOrder(rb->root); break;
		case INORDER: printf("[INORDER]:\n"); inOrder(rb->root); break;
		default: printf("Order not recognised.\n"); break;
	}

	printf("\n");
}

void preOrder(Node n)
{
	if (n != NULL){
		printf("[%d, clr = %s] ", n->value, (!n->clr) ? "R" : "B");
		preOrder(n->left);
		preOrder(n->right);
	}
}

void postOrder(Node n)
{
	if (n != NULL){
		postOrder(n->left);
		postOrder(n->right);
		printf("[%d, clr = %s] ", n->value, (!n->clr) ? "R" : "B");
	}
}

void inOrder(Node n)
{
	if (n != NULL){
		inOrder(n->left);
		printf("[%d, clr = %s] ", n->value, (!n->clr) ? "R" : "B");
		inOrder(n->right);
	}
}

// creates a new node
static Node newNode(int value, Colour clr)
{
	Node n = malloc(sizeof(node));
	n->value = value;
	n->clr = clr;
	n->left = n->right = NULL;
	return n;
}




